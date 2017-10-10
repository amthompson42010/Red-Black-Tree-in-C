/**
 * @author: Alexander Mark Thompson
 * @title: CS 201 -- Assignment 2 -- Red Black Trees
 */

#include "bst.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>

#define min(a,b) (a<b?a:b)
#define max(a,b) (a>b?a:b)

bst *newBST(void (*d)(FILE *,void *),int (*comparator)(void *,void *))
{ 
	bst *items = malloc(sizeof(bst));
	items->root = 0;
	items->display = d;
	items->compare = comparator;
	return items;
}

bstNode *insertBST(bst *tree,void *value)
{ 
	++tree->size;
	bstNode *new_node = malloc(sizeof(bstNode));
	new_node->value = value;
	new_node->left = new_node->right = new_node->parent = 0;

	bstNode *helper_1 = tree->root; 
	bstNode *helper_2 = NULL;

	while(helper_1 != NULL)
	{
		helper_2 = helper_1;
		if(tree->compare(new_node->value, helper_1->value) < 0)
		{
			helper_1 = helper_1->left;
		}
		else
		{
			helper_1 = helper_1->right;
		}
	}

	new_node->parent = helper_2;
	if (helper_2 == NULL)
	{
		tree->root = new_node; 
		new_node->parent = new_node; 
	}
	else if(tree->compare(new_node->value, helper_2->value) < 0)
	{
		helper_2->left = new_node;
	}
	else
	{
		helper_2->right = new_node;
	}
	return new_node;
	
}

int findBST(bst *tree,void *value)
{ 
	bstNode *x = tree->root;

	if (x == NULL)
	{
		return 0;
	}

	while (x != NULL)
	{
		if(tree->compare(x->value, value) == 0)
		{
			return 1;
		}
		else if(tree->compare(x->value, value) < 0)
		{
			x = x->right;
		}
		else
		{
			x = x->left;
		}
	}
	return 0;
}

bstNode *findBSTNode(bst *tree,void *value)
{ 

	bstNode *x = tree->root;

	if (x == NULL)
	{
		return 0;
	}

	while (x != NULL)
	{
		if(tree->compare(x->value, value) == 0)
		{
			return x;
		}
		else if(tree->compare(x->value, value) < 0)
		{
			x = x->right;
		}
		else
		{
			x = x->left;
		}
	}
	return 0;
}

bstNode *swapToLeafBSTNode(bstNode *n)
{ 
	bstNode *hold;
	void *tmp;

	if (n->left == NULL && n->right == NULL)
	{
		return n;
	}
	else if(n->left != NULL)
	{
		hold = n->left;	
		while (hold->right != NULL)
		{						
			hold = hold->right;
		}
		tmp = n->value;
		n->value = hold->value;
		hold->value = tmp;
		return swapToLeafBSTNode(hold);
	}
	else
	{
		hold = n->right;
		while(hold->left != NULL)
		{
			hold = hold->left;
		}
		tmp = n->value;
		n->value = hold->value;
		hold->value = tmp;
		return swapToLeafBSTNode(hold);
	}
}

void pruneBSTNode(bst *tree, bstNode *n)
{ 
	if (n == tree->root && tree->root->left == NULL && tree->root->right == NULL)
	{
		tree->root = NULL;
	}

	if(n->left == NULL && n->right == NULL)
	{
		if(n->parent->left == n)
		{
			n->parent->left = NULL;
		}
		else
		{
			n->parent->right = NULL;
		}
	}
	else
	{
		printf("Value not found\n");
	}
	tree->size--;
}

int sizeBST(bst *tree)
{
	return (tree->size);
}

static int maxDepth(bstNode *x)
{
	if (x == NULL)
	{
		return 0;
	}

	int maxLeft = maxDepth(x->left);
	int maxRight = maxDepth(x->right);
	return 1 + max(maxLeft, maxRight);
}

static int minDepth(bstNode *x)
{
	if(x == NULL)
	{
		return 0;
	}
	else
	{
    	return 1 + min(minDepth(x->left),minDepth(x->right));
	}
}

void statisticsBST(bst *tree,FILE *fp)
{ 
	bstNode *x = tree->root;

	int min = minDepth(x);
	int max = maxDepth(x);
	fprintf(fp, "Nodes: %d\n", sizeBST(tree));
	fprintf(fp, "Minimum depth: %d\n", min);
	fprintf(fp, "Maximum depth: %d\n", max);
}
 
void displayBST(FILE *fp, bst *tree)
{ 
		
	if(tree->root == NULL)
	{
		fprintf(fp, "0:\n");
        return;
	}
	
	queue *newQ = newQueue(tree->display);
	enqueue(newQ, tree->root);
	enqueue(newQ, NULL);

	bstNode *x;

	int breadthLevel = 0;
	fprintf(fp, "%d: ", breadthLevel);

	while (sizeQueue(newQ)) 
	{
		x = dequeue(newQ); 
		if(sizeQueue(newQ) == 0)
		{
			fprintf(fp, "\n");
			break;
		}

		else if(x == NULL)	
		{
			fprintf(fp,"\n");
			enqueue(newQ, NULL);	
			breadthLevel++;
			if(sizeQueue(newQ) > 0)
			{
				fprintf(fp, "%d: ", breadthLevel);
			}
		}
		else
		{
			if(x->left == NULL && x->right == NULL)
			{
				fprintf(fp, "=");
			}
			
			tree->display(fp, x->value);

			if(x == tree->root)
			{
				fprintf(fp, "("); 
				tree->display(fp, x->parent->value);
				fprintf(fp, ")-");
			}
			else if(x->parent != NULL)
			{
				if(tree->compare(x->value, x->parent->value)<0)
				{
					fprintf(fp, "("); 
					tree->display(fp, x->parent->value);
					fprintf(fp, ")-l"); 
				}
				else
				{
					fprintf(fp, "("); 
					tree->display(fp, x->parent->value);
					fprintf(fp, ")-r"); 
				}

			}
			
			if(peekQueue(newQ) != NULL) 
			{
				fprintf(fp, " ");
			}

			if(x->left != NULL)
			{
				enqueue(newQ, x->left);
			}
			if(x->right != NULL)
			{
				enqueue(newQ, x->right);
			}
		}
	}
}
