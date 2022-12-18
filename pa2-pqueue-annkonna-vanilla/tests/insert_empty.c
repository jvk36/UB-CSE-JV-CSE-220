#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../src/priority_queue.h"

#define NPRIOS 1
#define PRIO   0
#define VALUE  1

int main(int argc, char *argv[])
{
    PriorityQueue *pqueue = pqueue_init(NPRIOS);

    /* Check that init did something */
    if (pqueue == NULL) {
        puts("failed");
        return 1;
    }

    pqueue_insert(pqueue, VALUE, PRIO); /* value 1, priority 0 */

    /* At this point, the priority queue should look like this:
     *
     * +-----------+
     * |   head    | -> { prev: NULL, next: NULL, priority: 0, value: 1 }
     * +-----------+    +------+
     * |   tails   | -> | head |
     * +-----------+    +------+
     * | nprios : 1|
     * +-----------+
     */

    /* Verify nprios */
    if (pqueue->nprios != NPRIOS) {
        puts("failed");
        return 1;
    }

    /* Verify that head and tails[0] are equal */
    if (pqueue->head != pqueue->tails[0]) {
        puts("failed");
        return 1;
    }

    /* Verify that head points to a list node */
    if (pqueue->head == NULL) {
        puts("failed");
        return 1;
    }

    /* Verify the well-formedness of the list */
    if (pqueue->head->prev != NULL || pqueue->head->next != NULL) {
        puts("failed");
        return 1;
    }

    /* Check the value and priority stored on the head node */
    if (pqueue->head->priority != PRIO || pqueue->head->value != VALUE) {
        puts("failed");
        return 1;
    }

    puts("passed");
    return 0;
}
