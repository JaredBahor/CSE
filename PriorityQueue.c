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
    if(nprios <= 0){
        return NULL;
    }else {
        struct PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
        pq -> head = NULL;
        pq -> nprios = nprios;
        struct PQNode** arr = (PQNode**)malloc(sizeof(PQNode*) * nprios);
        pq->tails = arr;
        for (int i = 0; i < nprios; i++){
            pq->tails[i] = NULL;
            //*(arr + i) = NULL; //same as line 19
        }
      return pq;
    }
}

/*
 * Free all structures associated with this priority queue, including their
 * queue structure itself.  Any access to pqueue after this function returns
 * should be considered invalid.
 *
 * pqueue: the queue to free
 */

//Step 1) Set tails array to NULL, then free tails array.
//Step 2) Iterate pqueue to free each individual node.
//Step 3) Free the pqueue structure itself.

void pqueue_free(PriorityQueue *pqueue) {
    for (int i = 0; i < pqueue->nprios; i++){//set each pointer to NULL
        pqueue->tails[i] = NULL;
    }
    free(pqueue->tails);
    //Step 1 ^^
    PQNode* node = pqueue->head;
    PQNode* freed = pqueue->head;
    while(node->next != NULL){
        freed = node;
        free(freed);
        node = node->next;
    }
    free(node);
    //Step 2 ^^
    free(pqueue);
    //Step 3 ^^
}

/*
 * Insert a new node into a queue by priority and value.
 *
 * pqueue: the queue into which the new node should be inserted
 * value: the opaque value being inserted into the queue
 * priority: the priority at which this value is to be inserted
 */
void pqueue_insert(PriorityQueue *pqueue, int value, int priority) {

    if (pqueue != NULL){
        if (priority <= pqueue->nprios - 1 && priority >= 0){
            PQNode* pq = pqueue->head;
            if (pq == NULL){// empty queue
                PQNode* newNode = (PQNode*)malloc(sizeof(PQNode));
                newNode->priority = priority;
                newNode->value = value;
                newNode->prev = NULL;
                newNode->next = NULL;
                pqueue->tails[priority] = newNode;//make newNode tail
                pqueue->head = newNode;//make newNode head
            }else{
                if (pqueue->tails[priority] != NULL){
                    PQNode* newNode = (PQNode*)malloc(sizeof(PQNode));
                    PQNode* prev = pqueue->tails[priority];
                    PQNode* next = pqueue->tails[priority]->next;//could be NULL
                    newNode->priority = priority;
                    newNode->value = value;
                    newNode->next = next;
                    newNode->prev = prev;
                    prev->next = newNode;
                    if (next != NULL){
                        next->prev = newNode;
                    }
                    //next->prev = newNode;
                    pqueue->tails[priority] = newNode;
                }else{//pqueue->tails[priority] == NULL
                    int i = 0;
                    for(i = priority; pqueue->tails[i] == NULL && i >= 0; i--);
                    if(i < 0){//the inserted node is the lowest prio (becomes the head)
                        PQNode* next = pqueue->head;
                        PQNode* prev = NULL;
                        PQNode* newNode = (PQNode*)malloc(sizeof(PQNode));
                        newNode->priority = priority;
                        newNode->value = value;
                        newNode->prev = prev;//NULL
                        newNode->next = next;//old head
                        next->prev = newNode;
                        pqueue->tails[priority] = newNode;
                        pqueue->head = newNode;
                    }else{//a tail comes before the inserted node
                        PQNode* prev = pqueue->tails[i];
                        PQNode* next = pqueue->tails[i]->next;//could be NULL
                        PQNode* newNode = (PQNode*)malloc(sizeof(PQNode));
                        newNode->priority = priority;
                        newNode->value = value;
                        newNode->prev = prev;
                        newNode->next = next;
                        prev->next = newNode;
                        if (next != NULL){
                            next->prev = newNode;
                        }
                        //next->prev = newNode;
                        pqueue->tails[priority] = newNode;
                    }
                }
            }
        }
    }

    return;

}


/*
 * Return the head queue node without removing it.
 */
PQNode *pqueue_peek(PriorityQueue *pqueue) {
    if (pqueue == NULL){
        return NULL;
    }else if (pqueue->head != NULL){
        return pqueue->head;
    }else{
        return NULL;
    }
}

/*
 * Remove and return the head queue node.
 */
PQNode *pqueue_get(PriorityQueue *pqueue) {

    if (pqueue->head != NULL && pqueue != NULL){
        PQNode* head = pqueue->head;
        PQNode* next = pqueue->head->next;
        PQNode* tmp = pqueue->head;
        int prio = pqueue->head->priority;
        if (next != NULL){//has more than just head
            if (pqueue->tails[prio] == head){//the head is the tail for the prio
                pqueue->head = head->next;
                next->prev = NULL;
                pqueue->tails[prio] = NULL;
                return tmp;
            }else{//the head is not the tail for the prio
                pqueue->head = head->next;
                next->prev = NULL;
                return tmp;
            }
        }else{//only 1 Node (head node)
            pqueue->head = NULL;//set head to NULL
            pqueue->tails[prio] = NULL;//set tail to NULL
            return tmp;//return original head
        }
    }else {
        return NULL;
    }
}
