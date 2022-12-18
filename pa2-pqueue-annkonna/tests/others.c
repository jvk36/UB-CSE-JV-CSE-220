#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#include "../src/priority_queue.h"

#define NPRIOS 8

void printPQueue(PriorityQueue *pqueue){

    if(pqueue != NULL){
        printf("\npqueue: nprios - %d.\n", pqueue->nprios);
    }
    
    printf("\n Tails array status\n");
    for(int i = 0; i < pqueue->nprios; i++){
        if(pqueue->tails[i] == NULL){
            printf("Index %d is NULL\n", i);
            continue;
        }
        printf("Index %d is node with priority %d and value %d\n",
               i, pqueue->tails[i]->priority, pqueue->tails[i]->value);
    }

    printf("\nNodes in the queue: \n");
    PQNode *temp = pqueue->head;
    while(temp){
        printf("Node with priority %d value %d\n", temp->priority, temp->value);
        temp = temp->next;
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

    pqueue_insert(pqueue, 0, 2);
    pqueue_insert(pqueue, 3, 0);
    pqueue_insert(pqueue, 2, 2); /* value 0, priority 2 */
    pqueue_peek(pqueue);  
    pqueue_insert(pqueue, 1, 5);
    pqueue_get(pqueue);    
    pqueue_insert(pqueue, 2, 1); 
    pqueue_insert(pqueue, 2, 2); 

    printPQueue(pqueue);
    
    if (!pqueue_validate(pqueue)) {
        printf("\nValidate failed.\n");
    }

    /* Verify nprios */
    if (pqueue->nprios != NPRIOS) {
        puts("failed nprios");
        return 1;
    }

    /* Verify that head points to a list node */
    if (pqueue->head == NULL) {
        puts("failed head is not NULL check.");
        return 1;
    }

    /* Verify the well-formedness of the list */
    if (pqueue->head->prev != NULL) {
        puts("failed well-formedness");
        return 1;
    }

    pqueue_free(pqueue);
    
    puts("passed");
    return 0;
}
