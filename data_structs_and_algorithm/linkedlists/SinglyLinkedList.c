#include<stdio.h>
#include<stdlib.h>

struct listNode{
	int data;
	struct listNode *next;
};

int singlyListLength(struct listNode *head){
	int count = 0;
	struct listNode *current = head;

	while(current != NULL){
		count++;
		current = current->next;	
	}
	return count;
}

void insertInSinglyLinkedList(struct listNode **head, int data, int pos){
	int k=1;
	struct listNode *q,*p;
	struct listNode *newNode = (struct listNode*)malloc(sizeof(struct listNode));

	if(!newNode){
		printf("Memory Error\n");
		return;
	}
	newNode->data = data;
	p = *head;
	// Inserting at the beginning
	if(pos==1 || p==NULL){
		newNode->next = *head;
		*head = newNode;
	}
	else{
		// Traverse the list until position where we want to insert
		while(p!=NULL && (k<pos)){
			k++;
			q = p;
			p = p->next;
		}
		newNode->next = q->next; //more optimum way to do this
		q->next = newNode;
		/*
		 * q->next = newNode;
		 * newNode->next = p;
		 */
	}
}

void deleteNodeFromLinkedList(struct listNode **head, int pos){
	int k=1;
	struct listNode *p,*q;
	p = *head;

	if(*head == NULL){
		printf("List Empty\n");
		return;
	}

	/* from the beginning */
	if(pos == 1){
		*head = (*head)->next;
		free(p);
	}
	else{
		/* Traverse the list until arriving at the position */
		while(p!=NULL && k<pos){
			k++;
			q = p;
			p = p->next;
		}
		if(p == NULL){ /* At the end */
			printf("Position does not exist.\n");
		}
		else{ /* From the middle */
			q->next = p->next;
			free(p);
		}
	}
}

/*
void deleteLinkedList(struct ListNode **head)
{
	struct ListNode *auxilaryNode = NULL;
	struct ListNode *iterator = NULL;
	iterator = *head;

	while(iterator) {
		auxilaryNode = iterator->next;
		free(iterator);
		iterator = auxilaryNode;
	}
	*head = NULL;
}
*/

void printSLList(struct listNode *head){
	while(head != NULL){
		printf("%d ",head->data);
		head = head->next;
	}
	printf("\n");
}

int SinglyLinkedList_test(){
	struct listNode *head = NULL;
	insertInSinglyLinkedList(&head, 5, 5);
	insertInSinglyLinkedList(&head, 2, 5);
	printf("Elements in List:%d\n", singlyListLength(head));
	printSLList(head);
	deleteNodeFromLinkedList(&head, 1);
	printSLList(head);
	return 0;
}

int main()
{
	SinglyLinkedList_test();
}
