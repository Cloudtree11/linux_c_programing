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

struct DynArrayStack {
    int top;
    int capacity;
    int *array;
};

struct DynArrayStack *createStack();
int isFullStack(struct DynArrayStack *S);
void doubleStack(struct DynArrayStack *S);
void push(struct DynArrayStack *S, int x);
int isEmptyStack(struct DynArrayStack *S);
int top(struct DynArrayStack *S);
int pop(struct DynArrayStack *S);
void deleteDynStack(struct DynArrayStack *S);
void printStackData(struct DynArrayStack *S);

