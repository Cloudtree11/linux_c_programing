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
#include "DAS.h"

struct DynArrayStack *createStack(){
    struct DynArrayStack *S = malloc(sizeof(struct DynArrayStack));  
    if(!S)
        return NULL;
    S->capacity = 1;
    S->top = -1;
    S->array = malloc(S->capacity * sizeof(int));	// allocate an array of size 1 initially

    if(!S->array) 
        return NULL;
    return S;
}

int isFullStack(struct DynArrayStack *S){
    return (S->top == S->capacity-1);
}

void doubleStack(struct DynArrayStack *S){
    S->capacity *= 2;
    S->array = realloc(S->array, S->capacity * sizeof(int));
}

void push(struct DynArrayStack *S, int x){
    // No overflow in this implementation
    if(isFullStack(S))   
     doubleStack(S); 

    S->array[++S->top] = x;
}

int isEmptyStack(struct DynArrayStack *S){
    return S->top == -1;
}

int top(struct DynArrayStack *S){
    if(isEmptyStack(S))     
     return INT_MIN;

    return S->array[S->top];
}

int pop(struct DynArrayStack *S){
    if(isEmptyStack(S))    
     return INT_MIN;

    return S->array[S->top--];
}

void deleteDynStack(struct DynArrayStack *S){
    if(S) {
        if(S->array) 
            free(S->array);
        free(S);
    }
}

void printStackData(struct DynArrayStack *S)
{
	int i = 0;
	if(isEmptyStack(S))
		printf("Stack is empty\n");
	else {
		for(i = S->top; i > -1; i--)
			printf("travel [%d] = %d\n", i, S->array[i]);
	}
}

void testDynamicStack(){
    struct DynArrayStack *s = createStack();
    push(s, 10);
    push(s, 1);
    push(s, 11);
    push(s, 2);
    push(s, 10);
    push(s, 50);
    printStackData(s);
    while(!isEmptyStack(s)){
        printf("%d \n", pop(s));
    }
    deleteDynStack(s);
}
