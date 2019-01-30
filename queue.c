//
//  queue.c
//  C_Primer_Plus
//
//  Created by 杨智帆 on 2019/1/28.
//  Copyright © 2019 杨智帆. All rights reserved.
//

/* queue.c -- 实现队列l抽象数据类型的接口 */
#include <stdlib.h>
#include <string.h>
#include "queue.h"

static void CopyToNode(Item item, Node * p);
static void CopyToItem(Item * pitem, Node * p);

void InitializeQueue(Queue * pq)
{
    pq->front = pq->rear = NULL;
    pq->items = 0;
}


bool QueueIsEmpty(const Queue * pq)
{
    return pq->items == 0;
}


bool QueueIsFull(const Queue * pq)
{
    return pq->items == MAXQUEUE;
}

int QueueItemCount(const Queue * pq)
{
    return pq->items;
}

bool EnQueue(Item item, Queue * pq)
{
    Node * pnew;
    
    if (QueueIsFull(pq))
        return false;
    
    pnew = (Node *) malloc(sizeof(Node));
    if (pnew == NULL)
    {
        fprintf(stderr, "Unable to allocate memory.\n");
        exit(1);
    }
    
    CopyToNode(item, pnew);
    pnew->next = NULL;
    
    if (QueueIsEmpty(pq))
        pq->front = pnew;
    else
        pq->rear->next = pnew;
    pq->rear = pnew;
    pq->items++;
    
    return true;
}


bool DeQueue(Item * pitem, Queue * pq)
{
    Node * pt;
    
    if (QueueIsEmpty(pq))
        return false;
    CopyToItem(pitem, pq->front);
    pt = pq->front;
    pq->front = pq->front->next;
    free(pt);
    pq->items--;
    if (pq->items == 0)
        pq->rear = NULL;
    
    return true;
}

void EmptyTheQueue(Queue * pq)
{
    Item dummy;
    while (!QueueIsEmpty(pq))
        DeQueue(&dummy, pq);
}

static void CopyToNode(Item item, Node * p)
{
    p->item = item;
}

static void CopyToItem(Item * pitem, Node * p)
{
    *pitem = p->item;
}
