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
#include "DAS.h"
#include "DCAQ.h"

struct BinaryTreeNode{
    int data;
    struct BinaryTreeNode *left;
    struct BinaryTreeNode *right;
};

struct BinaryTreeNode* createNewNode(int data){
    struct BinaryTreeNode* node = (struct BinaryTreeNode*)malloc(sizeof(struct BinaryTreeNode));
    node->data = data;
    node->left = NULL;
    node->right = NULL;
    return node;
}

void preOrder(struct BinaryTreeNode* root){
     if (root == NULL) // or if (!root)
          return;
     printf("%d ", root->data);  
     preOrder(root->left);  
     preOrder(root->right);
} 

void preOrderNonRecursive(struct BinaryTreeNode *root){
      struct DynArrayStack *S = createStack();
      while(1)  {
            while(root) {
                //Process current node
                printf("%d ", root->data);
                push(S, root);
                //If left subtree exists, add to stack
                root = root->left;
            }
            if(isEmptyStack(S)) 
                break;
            root = pop(S); 
            //Indicates completion of left subtree and current node, now go to right subtree
            root = root->right; 
      }
      deleteDynStack(S);
}

void inOrder(struct BinaryTreeNode* root){
     if (root == NULL) // or if (!root)
          return;
     
     inOrder(root->left);  
     printf("%d ", root->data);  
     inOrder(root->right);
}

void inOrderNonRecursive(struct BinaryTreeNode *root){
      struct DynArrayStack *S = createStack();
      while(1)  {
            while(root) {
                  push(S, root);
                  //Got left subtree and keep on adding to stack
                  root = root->left;
            }
            if(isEmptyStack(S)) 
                break;
            root = pop(S); 

            printf("%d  ", root->data);   //After popping, process the current node
            //Indicates completion of left subtree and current node, now go to right subtree
            root = root->right; 
      }
      deleteDynStack(S);
}

void postOrder(struct BinaryTreeNode* root){
     if (root == NULL) // or if (!root)
          return;

     postOrder(root->left);  
     postOrder(root->right);
     printf("%d ", root->data);
}

/* ???  */
void postOrderIterative(struct BinaryTreeNode* root){
    struct DynArrayStack *S = createStack();
    struct BinaryTreeNode *previous = NULL;
    do{
        while (root != NULL){ 
            push(S, root);
            root = root->left;
        }
        while(root == NULL && !isEmptyStack(S)){
            root = top(S);
            if(root->right == NULL || root->right == previous){
                printf("%d ", root->data);
                pop(S);
                previous = root;
                root = NULL;
            }
            else
                root = root->right;
        }
    } while(!isEmptyStack(S));
}

void levelOrder(struct BinaryTreeNode *root)
{
	struct BinaryTreeNode *temp;
	DCAQ *Q = createQueue();

	if(!root)
		return;
	enQueue(Q, root);
	while(!isEmptyQueue(Q)) {
		temp = deQueue(Q);
		printf("%d ", temp->data);
		if(temp->left)
			enQueue(Q, temp->left);
		if(temp->right)
			enQueue(Q, temp->right);
	}
	deleteQueue(Q);
}

void testTraversalBinaryTree(){
    /* Sample binary tree is
            9
          /   \
        19      1
         \    /  \
          3  6   19
    */
    struct BinaryTreeNode* root = createNewNode(9);
    root->left        = createNewNode(19);
    root->right       = createNewNode(1);
    struct BinaryTreeNode* temp = root->left;
    temp->right  = createNewNode(3);
    temp = root->right;
    temp->left = createNewNode(6);
    temp->right = createNewNode(19);

	printf("preOrder: ");
	preOrder(root);
	printf("\n");
	printf("preOrderNonRecursive: ");
    preOrderNonRecursive(root);
	printf("\n");
	printf("inOrder: ");
	inOrder(root);
	printf("\n");
	printf("inOrderNonRecursive: ");
	inOrderNonRecursive(root);
	printf("\n");
	printf("postOrder: ");
	postOrder(root);
	printf("\n");
	printf("postOrderIterative: ");
	postOrderIterative(root);
	printf("\n");
	printf("levelOrder: ");
	levelOrder(root);
	printf("\n");
}

int main()
{
	testTraversalBinaryTree();
	return 0;
}
