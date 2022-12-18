#include <pthread.h>
#include <stdlib.h>

#include <unistd.h>

#include "csesem.h"
#include "pcq.h"

/* This structure must contain everything you need for an instance of a
 * PCQueue.  The given definition is ABSOLUTELY NOT COMPLETE.  You will
 * have to add several items to this structure. */
struct PCQueue {
    int slots;
    void **queue;
    int front;                          
    int back;  
    int destroy;                         
    CSE_Semaphore mutex;                // protects access to queue
    CSE_Semaphore sem_add_count;        // counts available slots 
    CSE_Semaphore sem_remove_count;     // counts available items
};

/* The given implementation performs no error checking and simply
 * allocates the queue itself.  You will have to create and initialize
 * (appropriately) semaphores, mutexes, condition variables, flags,
 * etc. in this function. */
PCQueue pcq_create(int slots) {
    PCQueue pcq;

    pcq = calloc(1, sizeof(*pcq));
    pcq->queue = calloc(slots, sizeof(void *));
    pcq->slots = slots;

    pcq->front = 0;
    pcq->back = 0;

    pcq->mutex = csesem_create(1); 
    pcq->sem_add_count = csesem_create(slots);
    pcq->sem_remove_count = csesem_create(0);

    return pcq;
}

/* This implementation does nothing, as there is not enough information
 * in the given struct PCQueue to even usefully insert a pointer into
 * the data structure. */
void pcq_insert(PCQueue pcq, void *data) {
    csesem_wait(pcq->sem_add_count); // wait for a free slot to become available.
    csesem_wait(pcq->mutex);         // lock to protect the queue.
    pcq->back++;                     
    pcq->queue[(pcq->back)%(pcq->slots)] = data;  // insert data to the back of the queue
    csesem_post(pcq->mutex);               // unlock the queue 
    csesem_post(pcq->sem_remove_count);    // notify that a free slot is available.
}

/* This implementation does nothing, for the same reason as
 * pcq_insert(). */
void *pcq_retrieve(PCQueue pcq) {
    void *data = NULL;

    csesem_wait(pcq->sem_remove_count); // wait for data to become available.
    csesem_wait(pcq->mutex);            // lock to protect the queue.
    pcq->front++;
    data = pcq->queue[(pcq->front)%(pcq->slots)]; // retrieve data from the front of the queue.
    csesem_post(pcq->mutex);                // unlock the queue
    csesem_post(pcq->sem_add_count);        // notify that a free slot has become available.

    return data;
}

/* The given implementation blindly frees the queue.  A minimal
 * implementation of this will need to work harder, and ensure that any
 * synchronization primitives allocated here are destroyed; a complete
 * and correct implementation will have to synchronize with any threads
 * blocked in pcq_create() or pcq_destroy().
 *
 * You should implement the complete and correct clean teardown LAST.
 * Make sure your other operations work, first, as they will be tightly
 * intertwined with teardown and you don't want to be debugging it all
 * at once!
 */
void pcq_destroy(PCQueue pcq) {
    csesem_destroy(pcq->mutex);
    csesem_destroy(pcq->sem_add_count);
    csesem_destroy(pcq->sem_remove_count);
    free(pcq->queue);
    free(pcq);
}
