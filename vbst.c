/**
 * @author: Alexander Mark Thompson
 * @title: CS 201 -- Assignment 2 -- Red Black Trees
 */

#include "vbst.h"

typedef struct vbstValue
{
	void *value;
	int freq;
	void (*display)(FILE *, void *);
	int (* compare)(void *, void *);
} vbstValue;

static vbstValue *newVBST_value(void (*disp)(FILE *,void *),int (*comp)(void *,void *))
{
	vbstValue *new_node = malloc(sizeof(vbstValue));
	new_node->value = NULL;
	new_node->freq = 1;
	new_node->display = disp;
	new_node->compare = comp;

	return new_node;
}

static void displayVBST_value(FILE *fp, void *value)
{
	vbstValue *x = value;
	x->display(fp, x->value);
	if(x->freq > 1) 
	{
		fprintf(fp, "-%d", x->freq);
	}
	
}

static int compareVBST_value(void *x, void *y)
{
	vbstValue *ex = x;
	vbstValue *wy = y;
	int result = ex->compare(ex->value, wy->value);
	return result;
}

vbst *newVBST(void (*disp)(FILE *,void *),int (*comp)(void *,void *))
{
	vbst *items = malloc(sizeof(vbst));
	items->tree = newBST(displayVBST_value, compareVBST_value);
	items->display = disp;
	items->compare = comp;
	items->size = 0;
	items->words = 0;
	return items;
}

void insertVBST(vbst *tree,void *value)
{
	vbstValue *new_node = newVBST_value(tree->display, tree->compare);
	new_node->value = value;

	bstNode *search = findBSTNode(tree->tree, new_node);

	if (search == 0)
	{
		insertBST(tree->tree, new_node);
		tree->size++;
		tree->words++;
	}
	else 
	{
		tree->words++;
		((vbstValue *)(search->value))->freq++;
	}
}

int findVBST(vbst *tree,void *value)
{

	
	vbstValue *new_node = newVBST_value(tree->display, tree->compare);
	new_node->value = value;

	bstNode *search =  findBSTNode(tree->tree, new_node);
	if(search == NULL)
	{
		return 0;
	}
	else
	{
		return ((vbstValue *)(search->value))->freq;
	}
}

void deleteVBST(vbst *tree,void *value)
{
	vbstValue *new_node = newVBST_value(tree->display, tree->compare);
	new_node->value = value;

	bstNode *search =  findBSTNode(tree->tree, new_node);

	if(search == NULL)
	{
		fprintf(stderr, "Value");
		new_node->display(stderr, new_node->value);
		fprintf(stderr, "not found.\n");
		return;
	}

	if (((vbstValue *)(search->value))->freq > 1)
	{
		((vbstValue *)(search->value))->freq -= 1;
		tree->words -= 1;
	}
	else
	{
		search = swapToLeafBSTNode(search);
		pruneBSTNode(tree->tree, search);
		tree->size -= 1;
		tree->words -= 1;
	}
}

int sizeVBST(vbst *tree)
{
	return tree->size;
}

int wordsVBST(vbst *tree)
{
	return tree->words;
}

void statisticsVBST(vbst *tree,FILE *fp)
{
	fprintf(fp, "Words/Phrases: %d\n", tree->words);
	return statisticsBST(tree->tree, fp);
}

void displayVBST(FILE *fp,vbst *tree)
{
	displayBST(fp, tree->tree);
}
