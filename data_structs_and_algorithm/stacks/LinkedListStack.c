
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct LLStack {
	int data;
	struct LLStack *next;
} S;

S *createStack()
{
	return NULL;
}

void push(S **top, int data)
{
	S *temp;
	temp = malloc(sizeof(S));
	if(!temp)
		printf("Memory alloc error\n");
	else {
		temp->data = data;
		temp->next = *top;
		*top = temp;
	}
}

int isEmptyStack(S *top)
{
	return top == NULL;
}

int pop(S **top)
{
	int data;
	S *temp;

	if(isEmptyStack(*top))
		return INT_MIN;
	temp = *top;
	*top = (*top)->next;
	data = temp->data;
	free(temp);
	return data;
}

int top(S *top)
{
	if(isEmptyStack(top))
		return INT_MIN;
	return top->next->data;
}

void deleteLLStack(S **top)
{
	S *temp, *p;
	p = *top;

	if(*top) 
	{
		while(p->next) {
			temp = p->next;
			p->next = temp->next;
			free(temp);
		}
		free(p);
	} else {
		printf("Stack is already empty\n");
	}
}

void printStackData(S *top)
{
	S *s = top;
	int i = 1;
	if(top == NULL)
		printf("Stack is empty\n");
	else {
		while(s != NULL) {
			printf("print [%d] = %d\n", i, s->data);
			i++;
			s = s->next;
		}
	}
}

void testLLStack()
{
	S *s;

	s = createStack();
	push(&s, 1);
	push(&s, 2);
	push(&s, 3);
	push(&s, 4);
	push(&s, 5);
	printf("", top(s));
	printStackData(s);
	while(s != NULL) {
		printf("Pop: %d\n", pop(&s));
		printStackData(s);
	}
	deleteLLStack(&s);
}

int main()
{
	testLLStack();
	return 0;
}
