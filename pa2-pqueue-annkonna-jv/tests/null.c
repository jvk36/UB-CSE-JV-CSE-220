#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "../src/priority_queue.h"

#define NPRIOS 3

int main(int argc, char *argv[]) {
    PriorityQueue *pqueue = pqueue_init(NPRIOS);

    /* Check that queue was allocated */
    if (pqueue == NULL) {
        puts("failed");
        return 1;
    }

    /* Check that the list is empty and all priority pointers are NULL */
    if (pqueue->head != NULL) {
        puts("failed");
        return 1;
    }
    for (int i = 0; i < NPRIOS; i++) {
        if (pqueue->tails[i] != NULL) {
            puts("failed");
            return 1;
        }
    }
    puts("passed");
    return 0;
}
