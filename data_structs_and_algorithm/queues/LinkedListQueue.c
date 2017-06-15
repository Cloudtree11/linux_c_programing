#include <stdio.h>
#include <stdlib.h>

typedef struct LinkedListNode{
	int data;
	struct LinkedListNode *next;
} LLN;

typedef struct LinkedListQueue{
	LLN *front;
	LLN *rear;
} LLQ;

LLQ *createQueue()
{
	LLQ *Q;
	LLN *temp;

	Q = malloc(sizeof(LLQ));
	if(!Q)
		return NULL;
	temp = malloc(sizeof(LLN));
	Q->front = Q->rear = NULL;
	return Q;
}

int isEmptyQueue(LLQ *Q)
{
	return (Q->front == NULL);
}

void enQueue(LLQ *Q, int data)
{
	LLN *newNode;

	newNode = malloc(sizeof(LLN));
	if(!newNode){
		printf("Memory error\n");
		return;
	}
	
	newNode->data = data;
	newNode->next = NULL;
	if(Q->rear)
		Q->rear->next = newNode;
	Q->rear = newNode;

	if(isEmptyQueue(Q))
		Q->front = Q->rear;
}

int deQueue(LLQ *Q)
{
	int data = 0;
	LLN *temp;
	
	if(isEmptyQueue(Q))
		printf("Queue is empty\n");
	else {
		temp = Q->front;
		data = Q->front->data;
		Q->front = Q->front->next;
		free(temp);
	}
	return data;
}

void deleteQueue(LLQ *Q)
{
	LLN *temp;
	while(Q->front) {
		temp = Q->front;
		Q->front = Q->front->next;
		free(temp);
	}
	free(Q);
}

void printQueueData(LLQ *Q)
{
	LLN *temp;
	int i;
	if(isEmptyQueue(Q))
		printf("Queue is empty\n");
	else {
		temp = Q->front;
		while(temp) {
			i++;
			printf("[%d] = %d\n", i, temp->data);
			temp = temp->next;
		}
	}
}

void testLLQ()
{
	LLQ *q = NULL;
	q = createQueue();

	if(!q) {
		printf("Memory error\n");
		return;
	}
	
	enQueue(q, 1);
	enQueue(q, 2);
	enQueue(q, 3);
	enQueue(q, 4);
	enQueue(q, 5);

	printQueueData(q);
	while(q->front) {
		printf("Delete value: %d\n", deQueue(q));
		printQueueData(q);
	}

	deleteQueue(q);
}

int main()
{
	testLLQ();
	return 0;
}
