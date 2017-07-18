

typedef struct ThreadedBinaryTreeNode {
	struct ThreadedBinaryTreeNode *left;
	int lTag;
	int data;
	int rTag;
	struct ThreadedBinaryTreeNode *right; 
} TBTN;

TBTN *inorderSuccessor(TBTN *P)
{
	TBTN *position;
	if(P->rTag == 0)
		return P->right;
	else {
		/* 
		 * 右子节点存在
		 * position 先为其右子节点
		 *       A
		 *        \
		 *         B
		 *        /
		 *       C
		 *      /
		 *     D
		 *
		 * 中序遍历：D 是 A 的后继节点(先右再一直左)
		 * */
		position = P->right;
		while(position->lTag == 1)
			position = position->left;
		return position;
	}
}

void inorderTraversal(TBTN *root)
{
	TBTN *P = inorderSuccessor(root);
	while(P != root) {
		P = inorderSuccessor(P);
		printf("%d ", P->data);
	}
}

/* Finding preorder successor in inorder threaded binary tree */
TBTN *preorderSuccessor(TBTN *P)
{
	TBTN *position;
	if(P->lTag == 1)
		return P->left;
	else {
		position = P;
		while(position->rTag == 0)
			position = position->right;
		return position->right;
	}
}




