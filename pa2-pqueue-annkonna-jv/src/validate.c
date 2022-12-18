#include <stdlib.h>
#include <stdbool.h>
#include "priority_queue.h"

#include <stdio.h>

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

    /* invariant 1: an empty queue has head==NULL and every entry in 
       tails is NULL. There are exactly as many entries in tails as the
       nprios entry */
    if (pqueue->head == NULL) {
        for (int i=0; i<pqueue->nprios; i++) {
            if (pqueue->tails[i] != NULL ) return false;
        }
    }

//   puts("passed invariant 1\n");
    
    /* invariant 2: the priorities of nodes in the list are sorted in non-decreasing order */
    /* invariant 3: every node in the list has priority between 0 and nprios-1 */
    /* invariant 5: every node with a non-NULL prev pointer has node->prev->next == node */
    /* invariant 7: every node with a non-NULL next pointer has node->next->prev == node */
    PQNode *pNode = pqueue->head;
    while (pNode != NULL) {
        if (pNode->next!=NULL && pNode->priority>pNode->next->priority) return false;
        if (pNode->priority<0 || pNode->priority>=pqueue->nprios) return false;
        if (pNode->prev!=NULL && pNode->prev->next!=pNode) return false;
        if (pNode->next!=NULL && pNode->next->prev!=pNode) return false;
        pNode = pNode->next;
    }


//   puts("passed invariant 2,3,5,7\n");
    
    /* invariant 4: head of the list has head->prev == NULL */
    if (pqueue->head != NULL) {
        if (pqueue->head->prev != NULL) return false;
    }   

//    puts("passed invariant 4\n");
    
    /* invariant 6: tail of the list has node->next == NULL */
    for (int i=pqueue->nprios-1; i>=0; i--) {
        if (pqueue->tails[i]!=NULL) {
            if (pqueue->tails[i]->next!=NULL) return false;
            else break;
        }
    }

//    puts("passed invariant 6\n");
    
    /* invariant 8: every entry in tails is either NULL or points to the last list item 
       with priority equal to the index of tails that point to it */
    for (int i=0; i<pqueue->nprios; i++) {
        PQNode *pTail = pqueue->tails[i];
        if (pTail!=NULL) {
            PQNode *pNext = pTail->next;
            if (pNext != NULL && pNext->priority<=pTail->priority) 
                return false;
        }
    }
    
//    puts("passed invariant 8\n");

    return true;
}
