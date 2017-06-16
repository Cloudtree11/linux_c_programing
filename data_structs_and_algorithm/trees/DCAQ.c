#include <stdio.h>
#include <stdlib.h>
#include "DCAQ.h"


DCAQ *createQueue()
{
	DCAQ *Q = NULL;

	Q = malloc(sizeof(DCAQ));
	if(!Q)
		return NULL;

	Q->capacity = 1;
	Q->front = -1;
	Q->rear = -1;
	Q->array = malloc(Q->capacity * sizeof(int));
	if(!Q->array)
		return NULL;

	return Q;
}

int isEmptyQueue(DCAQ *Q)
{
	return (Q->front == -1);
}

int isFullQueue(DCAQ *Q)
{
	return ((Q->rear+1) % Q->capacity == Q->front);
}

int QueueSize(DCAQ *Q)
{
	if(isEmptyQueue(Q))
		return 0;
	else
		return (Q->capacity - Q->front + Q->rear +1) % Q->capacity;
}

void resizeQueue(DCAQ *Q)
{
	int size = Q->capacity;
	int i;

	//printf("resize %d -> %d\n", Q->capacity, Q->capacity * 2);
	Q->capacity *= 2;
	Q->array = realloc(Q->array, Q->capacity);
	if(!Q->array) {
		printf("Memory error\n");
		return;
	}
	/* 下面的情况什么时候可能会发生？ */
	if(Q->front > Q->rear) {
		printf("test point!\n");
		for(i=0; i < Q->front; i++)
			Q->array[i+size] = Q->array[i];
		Q->rear = Q->rear + size;
	}
}

void enQueue(DCAQ *Q, int data)
{
	if(isFullQueue(Q))
		resizeQueue(Q);

	Q->rear = (Q->rear+1) % Q->capacity;
	Q->array[Q->rear] = data;

	/* if queue is empty */
	if(Q->front == -1)
		Q->front = Q->rear;
}

int deQueue(DCAQ *Q)
{
	int data = 0;
	if(isEmptyQueue(Q)) {
		printf("Queue is empty\n");
	} else {
		data = Q->array[Q->front];
		/* if only 1 element in queue */
		if(Q->front == Q->rear)
			Q->front = Q->rear = -1;
		else
			Q->front = (Q->front+1) % Q->capacity;
	}
	return data;
}

void deleteQueue(DCAQ *Q)
{
	if(Q) {
		if(Q->array)
			free(Q->array);
		free(Q);
	}
}

void printQueueData(DCAQ *Q)
{
	int i;
	if(!Q)
		printf("Queue doesn't exit\n");
	else {
		if(isEmptyQueue(Q))
			printf("Queue is empty\n");
		else {
			printf("front -> rear\n");
			for(i = Q->front; i <= Q->rear; i++)
				printf("[%d] = %d \n", i, Q->array[i]);
		}
	}
}

void testDCAQueue()
{
	DCAQ *q = NULL;

	q = createQueue(5);
	printQueueData(q);
	enQueue(q, 1);
	enQueue(q, 2);
	enQueue(q, 3);
	enQueue(q, 4);
	enQueue(q, 5);
	enQueue(q, 6);
	printf("Queue size is %d\n", QueueSize(q));
	printQueueData(q);
	while(q->front != -1) {
		deQueue(q);
		printQueueData(q);
		printf("Queue size is %d\n", QueueSize(q));
	}
	deleteQueue(q);
}
