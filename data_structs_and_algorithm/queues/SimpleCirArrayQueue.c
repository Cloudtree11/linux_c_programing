#include <stdio.h>
#include <stdlib.h>

typedef struct SimCirArrayQueue {
	int front, rear;
	int capacity;
	int *array;
} SCAQ;

SCAQ *createQueue(int size)
{
	SCAQ *Q = NULL;

	Q = malloc(sizeof(SCAQ));
	if(!Q)
		return NULL;

	Q->capacity = size;
	Q->front = -1;
	Q->rear = -1;
	Q->array = malloc(Q->capacity * sizeof(int));
	if(!Q->array)
		return NULL;

	return Q;
}

int isEmptyQueue(SCAQ *Q)
{
	return (Q->front == -1);
}

int isFullQueue(SCAQ *Q)
{
	return ((Q->rear+1) % Q->capacity == Q->front);
}

int QueueSize(SCAQ *Q)
{
	return (Q->capacity - Q->front + Q->rear +1) % Q->capacity;
}

void enQueue(SCAQ *Q, int data)
{
	if(isFullQueue(Q))
		printf("Queue Overflow\n");
	else {
		Q->rear = (Q->rear+1) % Q->capacity;
		Q->array[Q->rear] = data;
		/* if queue is empty */
		if(Q->front == -1)
			Q->front = Q->rear;
	}
}

int deQueue(SCAQ *Q)
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

void deleteQueue(SCAQ *Q)
{
	if(Q) {
		if(Q->array)
			free(Q->array);
		free(Q);
	}
}

void printQueueData(SCAQ *Q)
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

void testSCAQueue()
{
	SCAQ *q = NULL;

	q = createQueue(5);
	printQueueData(q);
	enQueue(q, 1);
	enQueue(q, 2);
	enQueue(q, 3);
	enQueue(q, 4);
	enQueue(q, 5);
	enQueue(q, 6);
	printQueueData(q);
	while(q->front != -1) {
		deQueue(q);
		printQueueData(q);
	}
	deleteQueue(q);
}

int main()
{
	testSCAQueue();
	return 0;
}
