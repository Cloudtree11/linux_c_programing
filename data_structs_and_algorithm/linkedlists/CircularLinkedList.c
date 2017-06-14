#include <stdio.h>
#include <stdlib.h>

struct CLLNode {
	int data;
	struct CLLNode *next;
};

int CLLLength(struct CLLNode *head)
{
	struct CLLNode *current = head;
	int count = 0;

	if(head == NULL)
		return 0;
	do {
		current = current->next;
		count++;
	} while(current != head);

	return count;
}

void printCLLData(struct CLLNode *head)
{
	struct CLLNode *current = head;
	printf("CLLData: \n");
	if(head == NULL)
		return;
	do {
		printf("%d ", current->data);
		current = current->next;
	}while(current != head);
	printf("\n");
}

void insertAtEndInCLL(struct CLLNode **head, int data)
{
	struct CLLNode *current = *head;
	struct CLLNode *newNode = NULL;
		
	newNode = (struct CLLNode *)malloc(sizeof(struct CLLNode));
	if(!newNode) {
		printf("Memory Error");
		return;
	}

	newNode->data = data;

	if(*head == NULL){
		*head = newNode;
		newNode->next = newNode;
	} else {
		while(current->next != *head)
			current = current->next;
		newNode->next = *head;
		current->next = newNode;
	}
}

void insertAtBeginInCLL(struct CLLNode **head, int data)
{
	struct CLLNode *current = *head;
	struct CLLNode *newNode = NULL;
		
	newNode = (struct CLLNode *)malloc(sizeof(struct CLLNode));
	if(!newNode) {
		printf("Memory Error");
		return;
	}

	newNode->data = data;

	if(*head == NULL) {
		*head = newNode;
		newNode->next = newNode;
	} else {
		while(current->next != *head)
			current = current->next;
		newNode->next = *head;
		current->next = newNode;
		*head = newNode;
	}
}

void deleteLastNodeFromCLL(struct CLLNode **head)
{
	struct CLLNode *temp = *head, *current = *head;

	if(*head == NULL) {
		printf("List Empty");
		return;
	}

	while(current->next != *head){
		temp = current;
		current = current->next;
	}
	temp->next = current->next;
	free(current);
	return;
}

void deleteFrontNodeFromCLL(struct CLLNode **head)
{
	struct CLLNode *temp = *head, *current = *head;

	if(*head == NULL) {
		printf("List Empty");
		return;
	}

	while(current->next != *head){
		current = current->next;
	}
	current->next = (*head)->next;
	*head = (*head)->next;
	free(temp);
	return;
}

void testCLL()
{
	struct CLLNode *head = NULL;

	printf("CLL length = %d\n", CLLLength(head));
	insertAtBeginInCLL(&head, 1);
	insertAtEndInCLL(&head, 2);
	insertAtEndInCLL(&head, 3);
	insertAtBeginInCLL(&head, 0);
	insertAtEndInCLL(&head, 4);
	printf("CLL length = %d\n", CLLLength(head));
	printCLLData(head);
	deleteLastNodeFromCLL(&head);
	deleteFrontNodeFromCLL(&head);
	printf("CLL length = %d\n", CLLLength(head));
	printCLLData(head);
}

int main()
{
	testCLL();
	return 0;
}
