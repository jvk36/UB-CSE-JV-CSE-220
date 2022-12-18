#include <string.h>
#include <stdio.h>

#include <unistd.h>

/* When requesting memory from the OS using sbrk(), request it in
 * increments of CHUNK_SIZE. */
#define CHUNK_SIZE (1<<12)

#define BULK_ALLOC_THRESHOLD 24

//#define DEBUG



typedef struct Block{
    size_t header;
    struct Block *next;
}Block;

static Block **freeListTable = NULL;

void free(void *ptr);

/*
o * This function, defined in bulk.c, allocates a contiguous memory
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


/*
 * Invariant 1: Head pointers in the freeListTable must be NULL or must point to a 
 *              location that contains a value equal to the  block size 
 *              (2^n where 5<=n<=12)
 * Invariant 2: Each node in the free list should have its lowest order bit 
 *              in the header field set to zero
 * Invariant 3: Each node in the free list should have a next pointer that is either 
 *              NULL or must point to a location that contains the value of block size
 *              (2^n where 5<=n<=12)
 */

void validate_pool(char *callee){

#ifdef DEBUG
    
    for (int i = 5; i < 13; i++){
        if (!freeListTable[i]) continue;

        size_t blockSize = 0x1 << i;
        // invariant 1
        if (freeListTable[i]->header != blockSize) {
            fprintf(stderr,"\nInvariant 1 failed in %s.\n", callee);
            return;
        }
        
        //invariant 2 and 3
        Block *temp = freeListTable[i];
        while (temp->next != NULL) {
            if ((*(size_t *)temp & 0x1) != 0) {
                fprintf(stderr,"\nInvariant 2 failed in %s.\n", callee);
                return;
            }

            if (temp->header != blockSize) {
                fprintf(stderr,"\nInvariant 3 failed in %s.\n", callee);
                return;
            }
        
            temp = temp->next;
        }
    }

//    fprintf(stderr, "\nvalidated pool in %s", callee);
    
#endif
    
}

Block *setup_free_list(size_t blockIndex) {
    
    if (blockIndex < 5 || blockIndex > 12) {
        return NULL;
    }

    int blockSize = 0x1 << blockIndex;
    void *p = sbrk(CHUNK_SIZE);

    if (p == (void *)-1) return NULL;
    
    freeListTable[blockIndex] = p;
    int blocks = CHUNK_SIZE/blockSize;

    Block *temp = (Block *)p;
    for(int i = 1; i <= blocks; i++){
        temp->header = blockSize;
        if(i == blocks){
            temp->next = NULL;
            return p;
        }
        temp->next = (void *)temp + blockSize;
        temp = (void *)temp + blockSize;
    }
    return p;
}

/*
 * You must implement malloc().  Your implementation of malloc() must be
 * the multi-pool allocator described in the project handout.
 */
void *malloc(size_t size) {

#ifdef DEBUG    
    fprintf(stderr,"\ninside malloc size = %ld\n", size);
#endif
    
    if (size <= 0) {
        return NULL;
    }

    if (size > BULK_ALLOC_THRESHOLD) {
        size = size + 8;
        void *ptr = bulk_alloc(size);
        if (!ptr) return NULL;
        size = size | 0x1;
        *(size_t *)ptr = size;
        return (ptr + 8);
    }

    int blockIndex = block_index(size);

    if(freeListTable == NULL){
        void *temp = sbrk(13 * sizeof(Block *));
        freeListTable = (Block **)temp;
        for(int i = 0; i < 13; i++){
            freeListTable[i] = NULL;
        }
    }

    if (blockIndex < 5 || blockIndex > 12) {
        return NULL;
    }
    
    if (freeListTable[blockIndex] == NULL) {
        freeListTable[blockIndex] = setup_free_list(blockIndex);
        if (!freeListTable[blockIndex]) return NULL;
    }

    void *temp = freeListTable[blockIndex];
    freeListTable[blockIndex] = freeListTable[blockIndex]->next;

    validate_pool("malloc");

    return temp + 8;
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

    size_t curSize = *(size_t *)(ptr-8);
    curSize = curSize - 8;
    if (curSize >= size) return ptr;

//    fprintf(stderr, "\nrealloc old size = %ld, new size = %ld\n", curSize, size);
    
    void *pNew = malloc(size);
    if (!pNew) return NULL;
    strncpy(pNew, ptr, curSize);
    free(ptr);

//    fprintf(stderr, "\nreturning from realloc\n");

    return pNew;
}

/*
 * You should implement a free() that can successfully free a region of
 * memory allocated by any of the above allocation routines, whether it
 * is a pool- or bulk-allocated region.
 *
 * The given implementation does nothing.
 */
void free(void *ptr) {

#ifdef DEBUG
//    fprintf(stderr,"\ninside free\n");
#endif
    
    if(ptr == NULL){
        return;
    }

    ptr = ptr - 8;
    *(size_t *)ptr =*(size_t *)ptr & ~0x1;
    size_t size = *(size_t *)ptr;

#ifdef DEBUG    
    fprintf(stderr,"\ninside free size = %ld\n", size);
#endif
    
    if (size > BULK_ALLOC_THRESHOLD + 8) {
        bulk_free(ptr, size);
        return;
    }

    int blockIndex = block_index(size - 8);
    if (blockIndex < 5 || blockIndex > 12) {
        return;
    }

    if(freeListTable[blockIndex] == NULL){
        freeListTable[blockIndex] = ptr;
        freeListTable[blockIndex]->next = NULL;
        return;
    }

    void *temp = freeListTable[blockIndex];
    freeListTable[blockIndex] = ptr;
    freeListTable[blockIndex]->next = temp;

    validate_pool("free");
    
    return;
}
