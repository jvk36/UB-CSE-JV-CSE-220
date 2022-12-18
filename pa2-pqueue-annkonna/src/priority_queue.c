#include <stdlib.h>
#include <stdbool.h>
#include "priority_queue.h"

/*
 * Create a new PriorityQueue structure and return it.
 *
 * The newly-created structure should have a NULL head, and every tail
 * pointer in its tails table should be NULL.
 *
 * nprios: The maximum number of priorities to support
 */
PriorityQueue *pqueue_init(int nprios) {
    if(nprios<=0){
        return NULL;
    }
    PriorityQueue *emque = (PriorityQueue *)malloc(sizeof(PriorityQueue));
    emque->nprios = nprios;
    emque->head = NULL;
    emque->tails = (PQNode **) malloc(sizeof(PQNode*)*nprios);
    for(int i = 0; i < nprios; i++){
        emque->tails[i] = NULL;
    }
    return emque;
}

/*
 * Free all structures associated with this priority queue, including their
 * queue structure itself.  Any access to pqueue after this function returns
 * should be considered invalid.
 *
 * pqueue: the queue to free
 */
void pqueue_free(PriorityQueue *pqueue) {
    PQNode *temp = pqueue->head;
    while(temp){
        temp = temp->next;
        if(temp->next != NULL){
            free(temp);
            temp = NULL;
        }
    }
    free(pqueue->tails);
    pqueue->tails = NULL;
    free(pqueue);
    pqueue = NULL;
}

/*
 * Insert a new node into a queue by priority and value.
 *
 * pqueue: the queue into which the new node should be inserted
 * value: the opaque value being inserted into the queue
 * priority: the priority at which this value is to be inserted
 */
void pqueue_insert(PriorityQueue *pqueue, int value, int priority) {
    PQNode *newNode = (PQNode *) malloc(sizeof(PQNode));
    newNode->value = value;
    newNode->priority = priority;
    newNode->prev = NULL;
    newNode->next = NULL;
    if(pqueue->tails[priority] == NULL){
        for(int i = priority; i >= 0; i--){
            if(pqueue->tails[i]!=NULL){
                newNode->prev = pqueue->tails[i];
                newNode->next = pqueue->tails[i]->next;
                if(pqueue->tails[i]->next != NULL){
                    pqueue->tails[i]->next->prev = newNode;
                }
                pqueue->tails[i]->next = newNode;
                pqueue->tails[priority] = newNode;
                return;
            }
        }        
        pqueue->tails[priority] = newNode;
        if (pqueue->head != NULL) {
            newNode->next = pqueue->head;
            pqueue->head->prev = newNode;
        }
        pqueue->head = newNode;
    }
    else{
        newNode->prev = pqueue->tails[newNode->priority];
        newNode->next = pqueue->tails[newNode->priority]->next;
        if(pqueue->tails[newNode->priority]->next != NULL){
            pqueue->tails[newNode->priority]->next->prev = newNode;            
        }
        pqueue->tails[newNode->priority]->next = newNode;
        pqueue->tails[priority] = newNode;
    }
}

/*
 * Return the head queue node without removing it.
 */
PQNode *pqueue_peek(PriorityQueue *pqueue) {
    if(pqueue == NULL){
        return NULL;
    }
    return pqueue->head;
}

/*
 * Remove and return the head queue node.
 */
PQNode *pqueue_get(PriorityQueue *pqueue) {
    if(pqueue == NULL){
        return NULL;
    }
    
    if( pqueue->head== NULL){
        return NULL;
    }

    if ( pqueue->head->next == NULL ) {
        pqueue->tails[pqueue->head->priority] = NULL;
        PQNode *oldHead = pqueue->head;
        pqueue->head = NULL;
        return oldHead;
    }

    
    PQNode *oldHead = pqueue->head;
    pqueue->head = pqueue->head->next;
    oldHead->next->prev = NULL;
    oldHead->next = NULL;

    
    if(oldHead->priority != pqueue->head->priority){
        pqueue->tails[oldHead->priority] = NULL;
    }
    
    return oldHead;
}
