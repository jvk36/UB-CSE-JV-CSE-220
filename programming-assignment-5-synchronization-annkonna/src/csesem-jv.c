#include <pthread.h>
#include <stdlib.h>

#include <stdio.h>
#include <string.h>

#include "csesem.h"

/* This definition of struct CSE_Semaphore is only available _inside_
 * your semaphore implementation.  This prevents calling code from
 * inadvertently invalidating the internal representation of your
 * semaphore.  See csesem.h for more information.
 *
 * You may place any data you require in this structure. */
struct CSE_Semaphore {
    pthread_mutex_t m;
    pthread_cond_t cv;
    int count;
};

/* This function must both allocate space for the semaphore and perform
 * any initialization that is required for safe operation on the
 * semaphore.  Te user should be able to immediately call csesem_post()
 * or csesem_wait() after this routine returns. */
CSE_Semaphore csesem_create(int count) {
    CSE_Semaphore sem = calloc(1, sizeof(struct CSE_Semaphore));
    int result;

    /* Create the lock and condition variables */
    if ((result = pthread_mutex_init(&sem->m, NULL)) != 0) {
        fprintf(stderr, "pthread_mutex_init: %s\n", strerror(result));
        return sem;
    }

    if ((result = pthread_cond_init(&sem->cv, NULL)) != 0) {
        fprintf(stderr, "pthread_cond_init: %s\n", strerror(result));
        return sem;
    }

    sem->count = count;

    return sem;
}

void csesem_post(CSE_Semaphore sem) {
    pthread_mutex_lock(&sem->m);
    sem->count = sem->count + 1;
    pthread_cond_signal(&sem->cv);
    pthread_mutex_unlock(&sem->m);
}

void csesem_wait(CSE_Semaphore sem) {
    pthread_mutex_lock(&sem->m);
    while (sem->count<=0) {
        pthread_cond_wait(&sem->cv, &sem->m);
    }
    sem->count = sem->count - 1;
    pthread_mutex_unlock(&sem->m);
}

/* This function should destroy any resources allocated for this
 * semaphore; this includes mutexes or condition variables. */
void csesem_destroy(CSE_Semaphore sem) {
    pthread_mutex_destroy(&sem->m);
    pthread_cond_destroy(&sem->cv);
    free(sem);
}
