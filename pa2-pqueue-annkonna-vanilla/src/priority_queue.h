#ifndef PRIORITY_QUEUE_H_
#define PRIORITY_QUEUE_H_

#include <stdbool.h>

/*
 * A single linked list node in the priority queue.
 */
typedef struct PQNode {
    int priority;
    int value;
    struct PQNode *next;
    struct PQNode *prev;
} PQNode;

/*
 * A Priority Queue.
 */
typedef struct PriorityQueue {
    PQNode *head;       /* Head of the list of all nodes on this queue */
    PQNode **tails;     /* Array of pointers to the tails of each priority */
    int nprios;         /* The number of valid priorities (and entries in tails) */
} PriorityQueue;

PriorityQueue *pqueue_init(int nprios);
PQNode *pqueue_peek(PriorityQueue *pqueue);
PQNode *pqueue_get(PriorityQueue *pqueue);
void pqueue_insert(PriorityQueue *pqueue, int value, int priority);
void pqueue_free(PriorityQueue *pqueue);
bool pqueue_validate(PriorityQueue *pqueue);

#endif /* PRIORITY_QUEUE_H */
