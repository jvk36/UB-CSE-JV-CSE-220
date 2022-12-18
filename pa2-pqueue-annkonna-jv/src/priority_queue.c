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
    PriorityQueue *pQueue = (PriorityQueue *)calloc(1, sizeof(PriorityQueue));
    pQueue->head = NULL;

    pQueue->tails = calloc(nprios,sizeof(PQNode *));   
    for (int i=0; i<nprios; i++) {
        pQueue->tails[i] = NULL;
    }

    pQueue->nprios = nprios;
    
    return pQueue;
}

/*
 * Free all structures associated with this priority queue, including their
 * queue structure itself.  Any access to pqueue after this function returns
 * should be considered invalid.
 *
 * pqueue: the queue to free
 */
void pqueue_free(PriorityQueue *pqueue) {
    PQNode *pNode = pqueue->head;

    /* free the queue nodes */
    while (pNode != NULL) {
        PQNode *temp = pNode;
        pNode = pNode->next;
        free(temp);
    }
    pqueue->head = NULL;

    /* free the tails array */
    if (pqueue->tails != NULL) {
        free(pqueue->tails);
        pqueue->tails = NULL;
    }

    /* free the queue */
    free(pqueue);
    pqueue = NULL;
}

void add_node_old(PQNode *pTail, PQNode *pNode) {
    /* add node to the tail */
    pNode->prev = pTail;
    PQNode *pNext = pTail->next;
    if (pNext != NULL) {
        pNode->next = pNext;
        pNext->prev = pNode;
    }
    pTail->next = pNode;    
}

void add_node(PriorityQueue *pqueue, PQNode *pNode) {
    /* add node to the tail */
    PQNode *pTail = pqueue->tails[pNode->priority];
    if (pTail == NULL) {
        /* find tail - higher priority node with non-null tails pointer */
        for (int i=pNode->priority; i>=0; i--) {
            if (pqueue->tails[i] != NULL){
                pTail = pqueue->tails[i];
                break;
            }
        }
    }
    
    if (pTail != NULL) {
        /* set the new node's previous to the current tail and
           setup links to/from the new node from/to the next node */
        pNode->prev = pTail;
        PQNode *pNext = pTail->next;
        if (pNext != NULL) {
            pNode->next = pNext;
            pNext->prev = pNode;
        }
        pTail->next = pNode;    
    } else {
        /* No nodes with higher priority. So, the new node is the head. 
           Set new node's next to current head and current head's prev to new node.
           Then set head to the new node */
        pNode->next = pqueue->head;
        if (pqueue->head!=NULL) pqueue->head->prev = pNode;
        pqueue->head = pNode;        
    }

    
    /* set tails pointer for this priority to the new node */
    pqueue->tails[pNode->priority] = pNode;
}

/*
 * Insert a new node into a queue by priority and value.
 *
 * pqueue: the queue into which the new node should be inserted
 * value: the opaque value being inserted into the queue
 * priority: the priority at which this value is to be inserted
 */
void pqueue_insert(PriorityQueue *pqueue, int value, int priority) {
    if (priority < 0 || priority >= pqueue->nprios) return;

    PQNode *pNode = (PQNode *)calloc(1, sizeof(PQNode));
    pNode->priority = priority;
    pNode->value = value;
    pNode->next = NULL;
    pNode->prev = NULL;
    add_node(pqueue, pNode);
}

/*
 * Return the head queue node without removing it.
 */
PQNode *pqueue_peek(PriorityQueue *pqueue) {
    if (pqueue==NULL) {
        return NULL;
    }
    
    return pqueue->head;
}

/*
 * Remove and return the head queue node.
 */
PQNode *pqueue_get(PriorityQueue *pqueue) {
    if (pqueue==NULL) {
        return NULL;
    }

    if (pqueue->head == NULL) {
        return NULL;
    }

    // set tails pointer for the head node's priority, if needed.
    PQNode *pNext = pqueue->head->next;
    if (pNext == NULL || pNext->priority != pqueue->head->priority)
        pqueue->tails[pqueue->head->priority] = NULL;

    // store the head pointer to return and make head point to the next node.
    PQNode *pRet = pqueue->head;
    pqueue->head = pqueue->head->next;

    // remove links to and from the removed node.
    pRet->next = NULL;
    pqueue->head->prev = NULL;
    
    return pRet;
}
