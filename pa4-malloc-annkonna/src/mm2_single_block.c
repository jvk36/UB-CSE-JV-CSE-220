#include <string.h>
#include <stdio.h>

#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>

/* When requesting memory from the OS using sbrk(), request it in
 * increments of CHUNK_SIZE. */
#define CHUNK_SIZE (1<<12)

#define BULK_ALLOC_THRESHOLD 120


#define DEBUG

typedef struct Block {
    size_t header;
    struct Block *next;
} Block;

static Block *freeListHead = NULL;

void free(void *);

/*
 * This function, defined in bulk.c, allocates a contiguous memory
 * region of at least size bytes.  It MAY NOT BE USED as the allocator
 * for pool-allocated regions.  Memory allocated using bulk_alloc()
 * must be freed by bulk_free().
 *
 * This function will return NULL on failure.
 */
extern void *bulk_alloc(size_t size);

/*
 * This function is also defined in bulk.c, and it frees an allocation
 * created with bulk_alloc().  Note that the pointer passed to this
 * function MUST have been returned by bulk_alloc(), and the size MUST
 * be the same as the size passed to bulk_alloc() when that memory was
 * allocated.  Any other usage is likely to fail, and may crash your
 * program.
 */
extern void bulk_free(void *ptr, size_t size);

/*
 * This function computes the log base 2 of the allocation block size
 * for a given allocation.  To find the allocation block size from the
 * result of this function, use 1 << block_size(x).
 *
 * Note that its results are NOT meaningful for any
 * size > 4088!
 *
 * You do NOT need to understand how this function works.  If you are
 * curious, see the gcc info page and search for __builtin_clz; it
 * basically counts the number of leading binary zeroes in the value
 * passed as its argument.
 */
static inline __attribute__((unused)) int block_index(size_t x) {
    if (x <= 8) {
        return 5;
    } else {
        return 32 - __builtin_clz((unsigned int)x + 7);
    }
}

/* check the invariants of the pool. 
 *
 * Invariant 1 - the head pointer freeListHead should be either NULL or point to 
 *               a location that contains the value of the block size.
 * Invariant 2 - each node in the free list should have its lowest order bit in 
 *               the header field set to 0. 
 * Invariant 3 - each node in the free list should have a next pointer that is 
 *               either NULL or point to a location that contains the value 
 *               of the block size.
 */
static void validate_pool(char *callee) {

#ifdef DEBUG
    int blockSize = BULK_ALLOC_THRESHOLD+8;
    
    // invariant 1;
    if (!freeListHead)
        return;
    if (freeListHead->next!=NULL && freeListHead->header != blockSize) {
        fprintf(stderr,
                    "\nInvariant 1 failed in %s: header: %ld, blockSize: %d.\n",
                    callee, freeListHead->header, blockSize);
        return;
    }

    // invariant 2 & 3
    Block *temp = freeListHead;
    int count = 0;
    while (temp) {
        count = count+1;
        if ((temp->header & 0x1) != 0) {
            fprintf(stderr,
                    "\nInvariant 2 failed in %s: header: %ld, blockSize: %d, count: %d.\n",
                    callee, temp->header, blockSize, count);
            return;
        }

        if (temp->header != blockSize) {
            fprintf(stderr,
                    "\nInvariant 3 failed in %s: header: %ld, blockSize: %d, count: %d.\n",
                    callee, temp->header, blockSize, count);
            return;
        }
        temp = temp->next;
    }
#endif

    return;
}



void setup_free_list() {
    size_t blockSize = BULK_ALLOC_THRESHOLD+8;
    void *p = sbrk(CHUNK_SIZE);
    
    if (p == (void *)-1) return;

    freeListHead = p;

    int nBlocks = CHUNK_SIZE/blockSize;
    
    Block *temp = (Block *)p;
    for (int i=1; i<=nBlocks; i++) {
        temp->header = (size_t)blockSize;
        if (i==nBlocks) {
            temp->next = NULL;
        } else {
            temp->next = (void *)temp+blockSize;
            temp = (void *)temp+blockSize;
        }
    }

#ifdef DEBUG    
    fprintf(stderr, "\nBlocks: %d, block size: %ld.\n", nBlocks, blockSize);
#endif
    
    return;
}

/*
 * You must implement malloc().  Your implementation of malloc() must be
 * the multi-pool allocator described in the project handout.
 */
void *malloc(size_t size) {    
    if (size > BULK_ALLOC_THRESHOLD) {
        size = size+8;
        void *temp = bulk_alloc(size);
        if (!temp) return NULL;
        *(size_t *)temp = size;
        *(size_t *)temp = *(size_t *)temp | 0x1;
       return temp+8;
    }

    // pool allocator.
    if (!freeListHead) {
        setup_free_list();
        if (!freeListHead) return NULL;
    }
    
    void *temp = freeListHead;
    freeListHead = freeListHead->next;

    validate_pool("malloc");
    
    *(size_t *)temp = *(size_t *)temp | 0x1;
    return temp+8;
}

/*
 * You must also implement calloc().  It should create allocations
 * compatible with those created by malloc().  In particular, any
 * allocations of a total size <= 4088 bytes must be pool allocated,
 * while larger allocations must use the bulk allocator.
 *
 * calloc() (see man 3 calloc) returns a cleared allocation large enough
 * to hold nmemb elements of size size.  It is cleared by setting every
 * byte of the allocation to 0.  You should use the function memset()
 * for this (see man 3 memset).
 */
void *calloc(size_t nmemb, size_t size) {
    void *ptr = malloc(nmemb * size);
    memset(ptr, 0, nmemb * size);
    return ptr;
}

/*
 * You must also implement realloc().  It should create allocations
 * compatible with those created by malloc(), honoring the pool
 * alocation and bulk allocation rules.  It must move data from the
 * previously-allocated block to the newly-allocated block if it cannot
 * resize the given block directly.  See man 3 realloc for more
 * information on what this means.
 *
 * It is not possible to implement realloc() using bulk_alloc() without
 * additional metadata, so the given code is NOT a working
 * implementation!
 */
void *realloc(void *ptr, size_t size) {
    if (!ptr) return malloc(size);

    size = size + 8;
    ptr = ptr - 8;
    size_t curSize = *(size_t *)ptr;
    if ( curSize >= size) return ptr+8;

    if (size > 0) {
        void *temp =  malloc(size);
        if (!temp) return NULL;
        *(size_t *)temp = size;
        strncpy(temp+8, ptr+8, curSize);
        free(ptr+8);
        return temp+8;
    }
    
    return NULL;
}

/*
 * You should implement a free() that can successfully free a region of
 * memory allocated by any of the above allocation routines, whether it
 * is a pool- or bulk-allocated region.
 *
 * The given implementation does nothing.
 */
void free(void *ptr) {

    if (!ptr) return;
    
    ptr = ptr - 8;
    *(size_t *)ptr = *(size_t *)ptr & ~0x1;
    size_t size = *(size_t *)ptr;

    if (size>(BULK_ALLOC_THRESHOLD+8)) {
        bulk_free(ptr, size);
        return;
    }

    // return to free list
    if (!freeListHead) {
        freeListHead = ptr;
        freeListHead->next = NULL;
    } else {
        void *temp = freeListHead;
        freeListHead = ptr;
        freeListHead->next = temp;
    }

    validate_pool("free");
    
    return;
}
