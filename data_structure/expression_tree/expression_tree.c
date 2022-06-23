#include <stdlib.h> // malloc, atoi
#include <stdio.h>
#include <ctype.h> // isdigit
#include <assert.h> // assert
#include <string.h>

#define MAX_STACK_SIZE	50

////////////////////////////////////////////////////////////////////////////////
// LIST type definition
typedef struct node
{
	char		data;
	struct node	*left;
	struct node	*right;
} NODE;

typedef struct
{
	NODE	*root;
} TREE;

////////////////////////////////////////////////////////////////////////////////
// Prototype declarations

/* Allocates dynamic memory for a tree head node and returns its address to caller
	return	head node pointer
			NULL if overflow
*/
TREE* createTree(void);

/* Deletes all data in tree and recycles memory
*/
void destroyTree(TREE* pTree);

static void _destroy(NODE* root);

/*  Allocates dynamic memory for a node and returns its address to caller
	return	node pointer
			NULL if overflow
*/
static NODE* _makeNode(char ch);

/* converts postfix expression to binary tree
	return	1 success
			0 invalid postfix expression
*/
int postfix2tree(char* expr, TREE* pTree);

/* Print node in tree using inorder traversal
*/
void traverseTree(TREE* pTree);

/* internal traversal function
	an implementation of ALGORITHM 6-6
*/
static void _traverse(NODE* root);

/* Print tree using inorder right-to-left traversal
*/
void printTree(TREE* pTree);

/* internal traversal function
*/
static void _infix_print(NODE* root, int level);

float _evaluate(NODE* root);

/* evaluate postfix expression
	return	value of expression
*/
float evalPostfix(char* expr);

////////////////////////////////////////////////////////////////////////////////
void destroyTree( TREE *pTree)
{
	if (pTree)
	{
		_destroy( pTree->root);
	}
		
	free( pTree);
}

////////////////////////////////////////////////////////////////////////////////
void printTree( TREE *pTree)
{
	_infix_print(pTree->root, 0);
	
	return;
}

////////////////////////////////////////////////////////////////////////////////
void traverseTree( TREE *pTree)
{
	_traverse(pTree->root);
	
	return;
}

////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv)
{
	TREE *tree;
	char expr[1024];
	
	fprintf( stdout, "\nInput an expression (postfix): ");
	
	while (fscanf( stdin, "%s", expr) == 1)
	{
		// creates a null tree
		tree = createTree();
		
		if (!tree)
		{
			printf( "Cannot create tree\n");
			return 100;
		}
		
		// postfix expression -> expression tree
		int ret = postfix2tree( expr, tree);
		if (!ret)
		{
			fprintf( stdout, "invalid expression!\n");
			destroyTree( tree);
			continue;
		}
		
		// expression tree -> infix expression
		fprintf( stdout, "\nInfix expression : ");
		traverseTree( tree);
		
		// print tree with right-to-left infix traversal
		fprintf( stdout, "\n\nTree representation:\n");
		printTree(tree);
		
		// evaluate postfix expression
		float val = evalPostfix( expr);
		fprintf( stdout, "\nValue = %f\n", val);
		
		// destroy tree
		destroyTree( tree);
		
		fprintf( stdout, "\nInput an expression (postfix): ");
	}
	return 0;
}

TREE* createTree(void) {
	TREE* tree;
	if (tree = (TREE*)malloc(sizeof(TREE))) {
		return tree;
	}

	return NULL;
}

static void _destroy(NODE* root) {
	if (root != NULL) {
		if (root->left != NULL) _destroy(root->left);
		if (root->right != NULL) _destroy(root->right);
		free(root);
	}
}

/*  Allocates dynamic memory for a node and returns its address to caller
	return	node pointer
			NULL if overflow
*/
static NODE* _makeNode(char ch) {
	NODE* node;
	if (node = (NODE*)malloc(sizeof(NODE))) {
		node->data = ch;
		node->left = NULL;
		node->right = NULL;
		return node;
	}

	return NULL;
}

/* converts postfix expression to binary tree
	return	1 success
			0 invalid postfix expression
*/
int postfix2tree(char* expr, TREE * pTree) {
	NODE* stack[MAX_STACK_SIZE];
	int count = 0;
	for (int i = 0; i < MAX_STACK_SIZE; ++i) stack[i] = NULL;

	int success;
	NODE * temp = NULL;

	for (int i = 0; i < strlen(expr); ++i) {
		if (isdigit(expr[i])) {
			stack[count] = _makeNode(expr[i]);
			++count;
		}
		else {
			if (!count) return 0;
			temp = _makeNode(expr[i]);
			temp->right = stack[--count];
			stack[count] = NULL;

			if (!count) {
				_destroy(temp);
				return 0;
			}
			temp->left = stack[--count];
			stack[count] = NULL;

			stack[count] = temp;
			++count;
		}
	}

	if (count == 1) {
		pTree->root = stack[0];
		return 1;
	}
	else {
		for (int i = count; i > 0; --i) {
			_destroy(stack[count - 1]);
		}
	}

	return 0;
}

/* internal traversal function
	an implementation of ALGORITHM 6-6
*/
static void _traverse(NODE * root) {
	if ((root->left == NULL) && (root->right == NULL)) {
		fprintf(stdout, "%c", root->data);
	}
	else {
		fprintf(stdout, "(");
		_traverse(root->left);
		fprintf(stdout, "%c", root->data);
		_traverse(root->right);
		fprintf(stdout, ")");
	}
}

/* internal traversal function
*/
static void _infix_print(NODE * root, int level) {
	if (root->right != NULL) _infix_print(root->right, level + 1);
	for (int i = 0; i < level; ++i) fprintf(stdout, "\t");
	fprintf(stdout, "%c\n", root->data);
	if (root->left != NULL) _infix_print(root->left, level + 1);
}

float _evaluate(NODE * root) {
	float op1, op2;

	if ((root->left == NULL) && (root->right == NULL)) return (int)(root->data - '0');

	op1 = _evaluate(root->left);
	op2 = _evaluate(root->right);

	switch (root->data)
	{
	case '+':
		return op1 + op2;
	case '-':
		return op1 - op2;
	case '*':
		return op1 * op2;
	case '/':
		return op1 / op2;
	}

	return 0;
}

/* evaluate postfix expression
	return	value of expression
*/
float evalPostfix(char* expr) {
	TREE* tree;
	tree = createTree();
	int ret = postfix2tree(expr, tree);

	float value = _evaluate(tree->root);
	destroyTree(tree);

	return value;
}