#include<stdio.h>
#include<stdlib.h>

struct DLLNode{
	int data;
	struct DLLNode *prev;
	struct DLLNode *next;
};

int DLLLength(struct DLLNode *head)
{
	int count = 0;
	while(head != NULL){
		count++;
		head = head->next;
	}
	return count;
}

void DLLInsert(struct DLLNode **head, int data, int pos)
{
	int k=1;
	struct DLLNode *temp, *newNode;
	newNode = (struct DLLNode *)malloc(sizeof(struct DLLNode));

	if(!newNode){ /* Always check for memory errors */
		printf("Memory Error");
		return;
	}

	newNode->data = data;
	if(pos==1 || *head==NULL){
		newNode->next = *head;
		newNode->prev = NULL;
		if(*head){
			(*head)->prev = newNode;
		}
		*head = newNode;
		return;
	}
	
	temp = *head;
	while((k < pos-1) && temp->next != NULL) {
		temp = temp->next;
		k++;
	}
	if(k != pos-1)
		printf("Desired position doesn't exist\n");
	newNode->next = temp->next;
	newNode->prev = temp;
	if(temp->next)
		temp->next->prev = newNode;
	temp->next = newNode;
	return;
}

void DLLDelete(struct DLLNode **head, int pos)
{
	struct DLLNode *temp, *temp2;
	int k = 1;
	
	temp = *head;
	if(*head == NULL){
		printf("List is empty");
		return;
	}
	if(pos == 1){
		*head = (*head)->next;
		if(*head != NULL)
			(*head)->prev = NULL;
		free(temp);
		return;
	}

	while(k<pos && temp->next!=NULL){
		temp = temp->next;
		k++;
	}
	
	if(k != pos)
		printf("Desired position doesn't exist\n");
	temp2 = temp->prev;
	temp2->next = temp->next;

	if(temp->next)
		temp->next->prev = temp2;

	free(temp);
	return;
}

void printDLL(struct DLLNode *head)
{
	int k = 1;
	while(head != NULL){
		printf("%d-%d ", k, head->data);
		head = head->next;
		k++;
	}
	printf("\n");
}

int DLLtest(){
	struct DLLNode *head = NULL;
	printf("Elements in list are :%d\n", DLLLength(head));
	printDLL(head);
	DLLInsert(&head, 2, 3);
	DLLInsert(&head, 5, 3);
	DLLInsert(&head, 9, 1);
	DLLInsert(&head, 10, 3);
	printf("Elements in list are :%d\n", DLLLength(head));
	printDLL(head);
	DLLDelete(&head,3);
	printDLL(head);
	return 0;
}

int main()
{
	DLLtest();
	return 0;
}
