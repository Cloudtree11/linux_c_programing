#include <stdio.h>
#include <stdlib.h>

typedef struct DynCirArrayQueue {
	int front, rear;
	int capacity;
	int *array;
} DCAQ;

DCAQ *createQueue();
int isEmptyQueue(DCAQ *Q);
int isFullQueue(DCAQ *Q);
int QueueSize(DCAQ *Q);
void resizeQueue(DCAQ *Q);
void enQueue(DCAQ *Q, int data);
int deQueue(DCAQ *Q);
void deleteQueue(DCAQ *Q);
void printQueueData(DCAQ *Q);
