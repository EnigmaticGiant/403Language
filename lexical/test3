#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bst.h"
#include "tnode.h"
#include "string.h"
#include "real.h"
#include "integer.h"
#include "queue.h"
#include "cda.h"

void printGivenLevel(BST *tree, FILE *f, TNODE* node);
int getHeight(TNODE *node, char *ts);
void preorder(TNODE *, FILE *, BST *);
void inorder(TNODE *, FILE *,BST * );
void postorder(TNODE *, FILE *,BST *);

typedef struct bst{
    TNODE *root;
    int size;
    void (*display)(void *, FILE *);
    int (*compare)(void *,void *);
    void (*swap)(TNODE *, TNODE *);
    int debug;
    void (*free)(void *);
} BST;

BST *newBST(int (*b)(void *,void *)){
	BST *tree = malloc(sizeof(BST));
	if(tree == 0){
		fprintf(stderr, "out of memory");
		exit(-1);
	}
	tree->root = NULL;
	tree->compare = b;
	tree->size = 0;
	tree->debug = 0;
	tree->free = NULL;
	tree->swap = NULL;
	tree->display = NULL;
	return tree;
}

void setBSTdisplay(BST *t,void (*d)(void *,FILE *)){
	t->display = d;
	return;
}

void setBSTswapper(BST *t,void (*s)(TNODE *,TNODE *)){
	t->swap = s;
}

void setBSTfree(BST *t,void (*f)(void *)){
	t->free = f;
}

void setBSTroot(BST *tree, TNODE *replacement){
	tree->root = replacement;
}

TNODE *getBSTroot(BST *tree){
	return tree->root;
}

void setBSTsize(BST *t,int s){
	t->size = s;
}

TNODE *insertBST(BST *tree, void *value){
	TNODE *insertee = newTNODE(value, NULL, NULL, NULL);
	TNODE *current = tree->root;
	TNODE *currentP = NULL;
	tree->size++;
	if(tree->root == NULL){
		tree->root = insertee;
		setTNODEparent(tree->root, insertee);
	}
	else{
		int pos;
		while(current != NULL) {
			currentP = current;
			if(tree->compare(getTNODEvalue(current), value) < 0){
				current = getTNODEright(current);
				pos = 1;
			}
			else{
			 current = getTNODEleft(current);
			 pos = 0;
			}
		}
		if(pos == 0) setTNODEleft(currentP, insertee);
		else setTNODEright(currentP, insertee);
		setTNODEparent(insertee, currentP);
		setTNODEleft(insertee, NULL);
		setTNODEright(insertee, NULL);
	}
	return insertee;
}

void *findBST(BST *tree, void *target){
	if(tree->root == NULL) return NULL;
	int found = 0;
	TNODE *n = tree->root;
	while(n != NULL) {
		if(tree->compare(getTNODEvalue(n), /*getTNODEvalue(temp)*/target) == 0){
			found = 1;
			break;
		}
		else if(tree->compare(target,getTNODEvalue(n)) < 0) n = getTNODEleft(n);
		else n = getTNODEright(n);
	}
	if(found != 1){
		return NULL;
	}
	return getTNODEvalue(n);
}

TNODE *locateBST(BST *tree,void *target){
	//printf("starting comapre\n");
	if(tree->root == NULL) return NULL;
	int found = 0;
	TNODE *n = tree->root;
	while(n != NULL) {
		if(tree->compare(getTNODEvalue(n), target) == 0){
			//printf("MATCH!!\n");
			found = 1;
			break;
			//return n;
		}
		else if(tree->compare(target,getTNODEvalue(n)) < 0){
			//printf("moving to the left\n");
			n = getTNODEleft(n);
		}
		else{
			//printf("moving to the right\n");
			n = getTNODEright(n);
		}	
	}
	if(found != 1){
		//printf("count not found\n");
		return NULL;
	}
	else{
		return n;
	}
}

int deleteBST(BST *t,void *value){
	//printf("mark\n");
	if(locateBST(t,value) == NULL){
	//printf("value not found\n");
	return -1;
	}
	TNODE *x = locateBST(t, value);
	//printf("starting deletion of ");
	//t->display(getTNODEvalue(x), stdout);
	//printf("\n");
	//printf("locate done \n");
	x = swapToLeafBST(t, x);
	//printf("swap done \n");
	pruneLeafBST(t, x);
	free(x);
	//printf("prune done \n");
	//setTNODEfree(x, t->free);
	//freeTNODE(x);
	t->size--;
	return 0;
}

TNODE *swapToLeafBST(BST *tree, TNODE *leaf){
	void *temp;
	TNODE *np = NULL;
	//printf("mark\n");
	if(getTNODEleft(leaf) == NULL && getTNODEright(leaf) == NULL){
		//printf("this is the end \n");
		return leaf;
	}
	else if(getTNODEleft(leaf) != NULL){
		np = getTNODEleft(leaf);
		while(getTNODEright(np) != NULL){
			np = getTNODEright(np);
		}
		if(tree->swap == NULL){
			temp = getTNODEvalue(leaf);
			setTNODEvalue(leaf, getTNODEvalue(np));
			setTNODEvalue(np, temp);
		}
		else{
			tree->swap(leaf, np);
		}
		return swapToLeafBST(tree, np);
	}
	else{
		np = getTNODEright(leaf);
		while(getTNODEleft(np) !=NULL){
			np = getTNODEleft(np);
		}
		if(tree->swap == NULL){
			temp = getTNODEvalue(leaf);
			setTNODEvalue(leaf, getTNODEvalue(np));
			setTNODEvalue(np, temp);
		}
		else{
			tree->swap(leaf,np);
		}
		return swapToLeafBST(tree, np);
	}
	return leaf;
}

void pruneLeafBST(BST *tree, TNODE *leaf){
	//tree->size--;
	/*printf("The item getting pruned is ");
	tree->display(getTNODEvalue(leaf), stdout);
	printf("\n");*/
	if(leaf == tree->root) {
		//printf("only node in the tree\n");
		tree->root = NULL;
		leaf = NULL;
	}
	else if(getTNODEleft(getTNODEparent(leaf)) == leaf){
		setTNODEleft(getTNODEparent(leaf), NULL);
		setTNODEparent(leaf, NULL);
		leaf = NULL;
	}
	else{
		setTNODEright(getTNODEparent(leaf), NULL);
		setTNODEparent(leaf, NULL);
		leaf = NULL;
	}
}
int sizeBST(BST *tree){
	return tree->size;
}

void statisticsBST(BST *tree, FILE *f){
	int longest = getHeight(tree->root, "longest");
	int shortest = getHeight(tree->root, "shortest");
	int size = tree->size;
	fprintf(f, "Nodes: %d\nMinimum depth: %d\nMaximum depth: %d\n", size, shortest-1, longest-1);
}

void displayBST(BST *tree, FILE *f){
	if(tree->debug == 1){
		//inorder traversal
		if(tree->size == 0){ 
			fprintf(f, "[]");
			return;
		}
		inorder(tree->root, f, tree);
	}
	else if(tree->debug == 2){
		//preorder traversal
		if(tree->size == 0){ 
			fprintf(f, "[]");
			return;
		}
		preorder(tree->root, f, tree);
	}
	else if(tree->debug == 3){
		//postorder traversal
		if(tree->size == 0){ 
			fprintf(f, "[]");
			return;
		}
		postorder(tree->root, f, tree);
	}
	else{
		if(tree->size == 0){ 
			fprintf(f, "0:\n");
			return;
		}
		printGivenLevel(tree, f, tree->root);
	}
}

void inorder(TNODE *node, FILE *fp, BST *tree){
/*1. traverse left
	2. process
	3. traverse right*/
	if(node != NULL){
		fprintf(fp, "[");
		inorder(getTNODEleft(node), fp, tree);
		if(getTNODEleft(node) != NULL) fprintf(fp, " ");
		tree->display(getTNODEvalue(node), fp);
		if(getTNODEright(node) != NULL) fprintf(fp, " ");
		inorder(getTNODEright(node), fp, tree);
		fprintf(fp, "]");
	}
}

void preorder(TNODE *node, FILE *fp, BST *tree){
/*	1.process
	2.traverse left
	3.traverse right*/
	if(node != NULL){
		fprintf(fp, "[");
		//if(getTNODEleft(node) != NULL) fprintf(fp, " ");
		tree->display(getTNODEvalue(node), fp);
		if(getTNODEleft(node) != NULL) fprintf(fp, " ");
		preorder(getTNODEleft(node), fp, tree);
		if(getTNODEright(node) != NULL) fprintf(fp, " ");

		preorder(getTNODEright(node), fp, tree);
		fprintf(fp, "]");
	}
}

void postorder(TNODE *node, FILE *fp, BST *tree){
/*	traverse left
	traverse right
	process*/
	if(node != NULL){
		fprintf(fp, "[");
		postorder(getTNODEleft(node), fp, tree);
		if(getTNODEleft(node) != NULL) fprintf(fp, " ");
		postorder(getTNODEright(node), fp, tree);
		if(getTNODEright(node) != NULL) fprintf(fp, " ");
		tree->display(getTNODEvalue(node), fp);
		fprintf(fp, "]");
	}
}

void freePostOrder(TNODE *node, BST *t){
	if(node != NULL){
		if(t->free) t->free(getTNODEvalue(node));
		//setTNODEfree(node, t->free);
		freePostOrder(getTNODEleft(node), t);
		freePostOrder(getTNODEright(node), t);
		freeTNODE(node);
	}
}

int debugBST(BST *t,int level){
	int old = t->debug;
	t->debug = level;
	return old;
}

void freeBST(BST *t){
	freePostOrder(t->root, t);
	free(t);
	return;
}

void printGivenLevel(BST *tree, FILE *f, TNODE* node)
{
	QUEUE *lvl = newQUEUE();
	enqueue(lvl, node);
	enqueue(lvl, NULL);
	int level = 0;
	fprintf(f, "%d:", level);
	while(sizeQUEUE(lvl) != 0){
		node = dequeue(lvl);
		if(node == NULL){
			fprintf(f, "\n");
			if(sizeQUEUE(lvl) != 0){
				//fprintf(f, "\n");
				level++;
				enqueue(lvl, NULL);
				fprintf(f, "%d:",level);
			}
		}
		else{
				fprintf(f, " " );
				if(getTNODEleft(node) ==NULL && getTNODEright(node) ==NULL){
					fprintf(f, "=");
				}
				tree->display(getTNODEvalue(node), f);
				fprintf(f, "(");
				if(tree->root == node){
					tree->display(getTNODEvalue(node), f);
					fprintf(f, ")X");
				}
				else{
					tree->display(getTNODEvalue(getTNODEparent(node)), f);
					fprintf(f, ")");
					if(getTNODEleft(getTNODEparent(node)) == node){
						fprintf(f, "L");
					}
					else{
						fprintf(f, "R");
					}
				}
				if(getTNODEleft(node) != NULL){
					enqueue(lvl, getTNODEleft(node));
				}
				if(getTNODEright(node) != NULL){
					enqueue(lvl, getTNODEright(node));
				}
		}
	}
	setQUEUEfree(lvl, tree->free);
	freeQUEUE(lvl);
}

int getHeight(TNODE *node, char *ts){
	if (node==NULL)
        return 0;
    else
    {
        /* compute the height of each subtree */
        int lheight = getHeight(getTNODEleft(node), ts);
        int rheight = getHeight(getTNODEright(node), ts);
 
        /* use the larger one */
    	if(strcmp(ts, "longest") == 0){
			if (lheight > rheight)
      	      return(lheight+1);
      	    else return(rheight+1);
  		}
  	 	else if(strcmp(ts, "shortest") == 0){
  	  		if(lheight < rheight)
    			return(lheight+1);
    		else return(rheight+1);
    	}
    }
    return 0;
}



