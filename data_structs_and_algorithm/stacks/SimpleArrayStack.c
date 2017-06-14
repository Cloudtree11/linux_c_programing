/*Copyright (c) 2016 CareerMonk Publications and others.
#E-Mail            : info@careermonk.com 
#Creation Date     : 2008-01-10 06:15:46 
#Created by        : Narasimha Karumanchi 
#Book Title        : Data Structures And Algorithms Made Easy
#Warranty          : This software is provided "as is" without any 
#                    warranty; without even the implied warranty of 
#                    merchantability or fitness for a particular purpose.*/
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAXSIZE 5

struct SimpleArrayStack {
    int top;
    int capacity;
    int *array;
};

struct SimpleArrayStack *createStack()
{
    struct SimpleArrayStack *S = malloc(sizeof(struct SimpleArrayStack));  
    if(!S) 
        return NULL;
    S->capacity = MAXSIZE;
    S->top = -1;
    S->array = calloc(S->capacity, sizeof(int));	// allocate an array of size 1 initially

    if(!S->array) 
        return NULL;
    return S;
}

int isEmptyStack(struct SimpleArrayStack *S){
    return S->top == -1;
}

int isFullStack(struct SimpleArrayStack *S){
    return (S->top == S->capacity-1);
}

int top(struct SimpleArrayStack *S){
    if(isEmptyStack(S))
        return INT_MIN;

    return S->array[S->top];
}

int pop(struct SimpleArrayStack *S){
    if(isEmptyStack(S)){  
        printf("Underflow: Stack empty\n");
        return INT_MIN;
    }
    return S->array[S->top--];
}

void push(struct SimpleArrayStack *S, int x){
    // No overflow in this implementation
    if(isFullStack(S)){
        printf("Overflow: Stack full\n");
        return;
    }
    S->array[++S->top] = x;
}

void deleteStack(struct SimpleArrayStack *S){
    if(S) {
        if(S->array) 
            free(S->array);
        free(S);
    }
}

void printStackData(struct SimpleArrayStack *S)
{
	int i = 0;
	if(isEmptyStack(S))
		printf("Stack is empty\n");
	else {
		for(i = S->top; i > -1; i--)
			printf("travel [%d] = %d\n", i, S->array[i]);
	}
}

void testSimpleArrayStack()
{
    struct SimpleArrayStack *s = createStack();
    push(s, 10);
    push(s, 1);
    push(s, 11);
    push(s, 2);
    push(s, 10);
    push(s, 50);

	printStackData(s);

    while(!isEmptyStack(s)){
        printf("pop: %d\n", pop(s));
    }

    deleteStack(s);
}

int main()
{
	testSimpleArrayStack();
	return 0;
}
