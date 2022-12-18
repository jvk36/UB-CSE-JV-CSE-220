#include <string.h>
#include <stdio.h>

#include <stdint.h> // for uint64_t
#include <unistd.h> // for sbrk

/* When requesting memory from the OS using sbrk(), request it in
 * increments of CHUNK_SIZE. */
#define CHUNK_SIZE (1<<12)

#define BULK_ALLOC_THRESHOLD 4088


#define DEBUG

typedef struct Block {
    uint64_t header;
    struct Block *next;
} Block;

static Block **freeListTable = NULL;

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

static int get_block_index(size_t x) {
    int y = 32;
    if (x<=0) return 0;
    if (x<=32) return 5;
    for (int i=6; i<=12; i++) {
        y = y*2;
        if (x<=y) return i;
    }
    return 0;
}

/* check the invariants of the pool. 
 * 
 * Invariant 1 - the head pointers in the freeListTable array should be either 
 *               NULL or point to a location that contains a value equal to
 *               the block size (2^n where 5 <= n <= 12).
 * Invariant 2 - each node in each of the free lists should have a next pointer  
 *               that is either NULL or point to a location that contains a 
 *               value equal to the block sze (2^n where 5 <= n <= 12).
 */
static void validate_pool(char *callee) {

#ifdef DEBUG    
    Block *temp = NULL;
    for (int i=5; i<=12; i++) {
        temp = freeListTable[i];
        if (!temp) continue;        
        int blockSize = 0x1 << i;
        // invariant 1        
        if ( temp->header != blockSize) {
            fprintf(stderr,
                    "\nInvariant 1 failed in %s: header: %ld, blockSize: %d, i: %d.\n",
                    callee, temp->header, blockSize, i);
            return;
        }
        // invariant 2        
        int count = 0;
        while (temp) {
            count = count+1;
            if (temp->header != blockSize) {
                fprintf(stderr,
                        "\nInvariant 2 failed in %s: header: %ld, blockSize: %d, count: %d.\n",
                        callee, temp->header, blockSize, count);
                return;
            }
            temp = temp->next;
        }
    }
#endif
    
    return;
}



static Block *setup_free_list(size_t blockSize) {
    void *p = sbrk(CHUNK_SIZE);
    
    if (p == (void *)-1) return NULL;

    fprintf(stderr, "\nsetup_free_list: block size = %ld\n", blockSize);
        
    // build the free list of blocks.
    int nBlocks = CHUNK_SIZE/blockSize;    
    Block *temp = (Block *)p;
    for (int i=1; i<=nBlocks; i++) {
        temp->header = (uint64_t)blockSize;
        if (i==nBlocks)
            temp->next = NULL;
        else
            temp->next = (void *)temp+blockSize;
        temp = (void *)temp+blockSize;
    }

    // set the value of freeListTable at blockIndex to be the
    // address returned by sbrk
    int blockIndex = get_block_index(blockSize);
    if (blockIndex<5 || blockIndex>12) return NULL;    

#ifdef DEBUG    
    fprintf(stderr, "\nBlocks: %d, block size: %ld, blockIndex: %d.\n",
            nBlocks, blockSize, blockIndex);
#endif
    
    return p;
}

/*
 * You must implement malloc().  Your implementation of malloc() must be
 * the multi-pool allocator described in the project handout.
 */
void *malloc(size_t size) {

    fprintf(stderr, "\nsize to malloc: %ld\n", size);
    
    if (size > BULK_ALLOC_THRESHOLD) {
        size = size+8;
        void *temp = bulk_alloc(size);
        if (!temp) return NULL;
        *(uint64_t *)temp = size;
        return temp+8;
    }

    // multi-pool allocator.
    if (!freeListTable) {
        size_t blockIndex = get_block_index(13*sizeof(Block *));
        size_t blockSize = 0x1 << blockIndex;
        Block *temp = setup_free_list(blockSize);
        if (!temp) {
            fprintf(stderr, "\nsetup_free_list returned NULL when building table.\n");
            return NULL;
        }
        freeListTable = (Block **)temp;
        temp = temp->next;
        if (blockIndex<5 || blockIndex>12)  {
            fprintf(stderr, "\nblockIndex out-of-range  when building table: %ld.\n", blockIndex);
            return NULL;
        }
        for (int i=0; i<=12; i++) {
            freeListTable[i] = NULL;
        }        
        freeListTable[blockIndex] = temp;
    }

    size_t blockIndex = get_block_index(size);
    size_t blockSize = 0x1 << blockIndex;
    fprintf(stderr, "\nBlock size: %ld, Block index: %ld\n", blockSize, blockIndex);
    if (blockIndex<5 || blockIndex>12) return NULL;

    // get the head of the free list table.
    Block *temp = freeListTable[blockIndex];
    if (!temp) {
        // build the free list for the block index
        Block *plst = setup_free_list(blockSize);
        if (!plst) {
            fprintf(stderr, "setup free list failed for blocksize %ld", blockSize);
            return NULL;
        }

        temp = plst;
    }

    // set the head of the free list table to the next node and
    // return the head offset by 8.
    if (!temp) return NULL;
    freeListTable[blockIndex] = temp->next;

    validate_pool("malloc");
    
    return (void *)temp+8;
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
    uint64_t curSize = *(uint64_t *)ptr;
    if ( curSize >= size) return ptr+8;

    if (size > 0) {
        void *temp =  malloc(size);
        if (!temp) return NULL;
        *(uint64_t *)temp = size;
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
    uint64_t size = *(uint64_t *)ptr;

#ifdef DEBUG    
    fprintf(stderr, "\nSize to free: %ld\n", size);
#endif    
    
    if (size>(BULK_ALLOC_THRESHOLD+8)) {
        bulk_free(ptr, size);
        return;
    }

//#ifdef JV    
    int blockIndex = get_block_index(size);
//    fprintf(stderr, "\nsize: %ld, Block index: %d\n", size, blockIndex);
    if (blockIndex<5 || blockIndex>12) return;
    
    // return to free list at blockIndex
    if (!freeListTable[blockIndex]) {
        freeListTable[blockIndex] = ptr;
        ((Block *)ptr)->next = NULL;
    } else {
        void *temp = freeListTable[blockIndex];
        freeListTable[blockIndex] = ptr;
        ((Block *)ptr)->next = temp;
    }
//#endif

    validate_pool("free");
    
    return;
}
