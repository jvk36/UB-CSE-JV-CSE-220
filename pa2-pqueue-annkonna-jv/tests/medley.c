#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../src/priority_queue.h"

#define NPRIOS 3

void output_state(PriorityQueue *pqueue, char *message) {
    printf("\n%s\n", message);
    // output the state of the queue
    printf("tails array length = %d\n", pqueue->nprios);
    PQNode *pNode = pqueue->head;
    while (pNode!=NULL) {
        printf("Node Priority: %d, Value: %d\n", pNode->priority, pNode->value);
        pNode = pNode->next;
    }        
}

int main(int argc, char *argv[])
{
    PriorityQueue *pqueue = pqueue_init(NPRIOS);

    /* Check that init did something */
    if (pqueue == NULL) {
        puts("failed init");
        return 1;
    }

    if (!pqueue_validate(pqueue)) {
        puts("pqueue validation after queue initialization failed.");
        return 1;
    }

    
    pqueue_insert(pqueue, 0, 2); /* value 0, priority 2 */
    pqueue_insert(pqueue, 3, 0); /* value 3, priority 0 */
    pqueue_insert(pqueue, 1, 0); /* value 1, priority 0 */
    pqueue_insert(pqueue, 2, 2); /* value 2, priority 2 */

//    output_state(pqueue, "Queue state after 4 inserts:");

    if (!pqueue_validate(pqueue)) {
        puts("pqueue validation after inserts failed.");
        return 1;
    }

    if (pqueue_peek(pqueue) == NULL) {
        puts("failed peek.");
        return 1;
    }

    PQNode *pNode = pqueue_get(pqueue);
    if (pNode==NULL) {
        puts("failed get.");
        return 1;
    }
    free(pNode);
    
//    output_state(pqueue, "Queue state after get:");

    if (!pqueue_validate(pqueue)) {
        puts("pqueue validation after get failed.");
        return 1;
    } 

    pqueue_free(pqueue);
    pqueue = NULL;

    puts("passed");
    
    return 0;
}
