#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include "priority_queue.h"


/*
 * Validate the given PriorityQueue for structural correctness.
 *
 * In order for this function to return true, the queue passed in must
 * meet the specification in the project handout precisely.  Every node
 * in the linked list and every pointer in the tails table must be
 * correct.
 *
 * pqueue: queue to validate
 *
 * Returns true if the queue is valid, false otherwise.
 */
bool pqueue_validate(PriorityQueue *pqueue) {

    
    if(pqueue->head == NULL){
        // invariant 1: every entry in tails is NULL, if head is NULL.
        for(int i = 0; i<pqueue->nprios; i++){
            if(pqueue->tails[i]!=NULL){
//                printf("\nFailed invariant 1.\n");
                return false;
            }
        }        
    } else {
        // invariant 4: head of the list has head->prev as NULL.
        if(pqueue->head->prev!=NULL){
//          printf("\nFailed invariant 4.\n");
            return false;
        }        
    }

//    printf("\nPassed invariant 1 & 4.\n");
    
    // invariant 6: tail of the list has node->next as NULL.
    for(int i = pqueue->nprios-1; i>=0; i--){
        if(pqueue->tails[i]!=NULL){
            if(pqueue->tails[i]->next!=NULL){
//              printf("\nFailed invariant 6.\n");
                return false;
            }
            else{
                break;
            }
        }
    }

//    printf("\nPassed invariant 6.\n");
    
    PQNode *temp = pqueue->head;
    while(temp){
        if(temp->next!=NULL){
            // invariant 2: the priorities of nodes in the list are sorted in non-increasing order.
            if(temp->next->priority < temp->priority){
//                printf("\nFailed invariant 2.\n");
                return false;
            }
            // invariant 3: every node in the list has priority between 0 and nprios-1
            if(temp->priority < 0 || temp->priority > pqueue->nprios-1){
//                printf("\nFailed invariant 3.\n");
                return false;
            }
            // invariant 7: every node with a non-null next pointer has node->next->prev == node.
            if(temp->next->prev != temp){
//                printf("\nFailed invariant 7.\n");
                return false;
            }
        }

        // invariant 5: every node with a non-null prev pointer has node->prev->next == node.
        if(temp->prev != NULL){
            if(temp->prev->next != temp){
//                printf("\nFailed invariant 5.\n");
                return false;
            }
        }
        temp = temp->next;
    }

//    printf("\nPassed invariant 2, 3, 5, and 7.\n");

    // invariant 8: every entry in tails is either NULL or points to the last list item with priority
    // equal to the index of tails that points to it.
    for(int i = 0; i < pqueue->nprios; i++){
        if(pqueue->tails[i] != NULL && pqueue->tails[i]->next != NULL){
            if(pqueue->tails[i]->next->priority <= pqueue->tails[i]->priority){
                printf("\nFailed invariant 8.\n");
                return false;
            }
        }
    }

//    printf("\nPassed invariant 8.\n");

    
    return true;
}
