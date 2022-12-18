#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define COUNT 100000
#define THREADS 9
#define OFFSET 0x1134A

pthread_mutex_t lock;
pthread_cond_t barrier;
int nwaiting;
int nthreads;

int value;

void barrier_wait() {
}


/* This thread will simply add COUNT to the global value, one at a
 * time. */
void *counter(void *arg) {
    barrier_wait();
    for (int i = 0; i < COUNT; i++) {
        pthread_mutex_lock(&lock);
        value++;
        pthread_mutex_unlock(&lock);
    }

    return NULL;
}

int main(int argc, char *argv[])
{
    value = 0;
    
    pthread_mutex_init(&lock, NULL);
    pthread_cond_init(&barrier, NULL);

    pthread_t t[THREADS];
    int result;

    nthreads = THREADS;
    nwaiting = 0;
    for (int i = 0; i < THREADS; i++) {
        if ((result = pthread_create(&t[i], NULL, counter, NULL)) != 0) {
            fprintf(stderr, "pthread_create: %s\n", strerror(result));
            return 1;
        }
    }

    /* Set the global value to OFFSET, as a place for the counting to
     * start.  If the threads above have already been released, this
     * will force a failure. */
    value = OFFSET;

    for (int i = 0; i < THREADS; i++) {
        pthread_join(t[i], NULL);
    }

    if (value == COUNT * THREADS + OFFSET) {
        printf("passed: value = %d, OFFSET = %d\n", value, OFFSET);
    } else {
        printf("failed: value = %d, OFFSET = %d\n", value, OFFSET);
        return 1;
    }

    return 0;
}
