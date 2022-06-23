#include <stdlib.h> // malloc, atoi, rand
#include <stdio.h>
#include <assert.h> // assert
#include <time.h> // time

////////////////////////////////////////////////////////////////////////////////
// TREE type definition
typedef struct node
{
	int			data;
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
TREE *BST_Create( void);

/* Deletes all data in tree and recycles memory
*/
void BST_Destroy( TREE *pTree);

/* internal function (not mandatory)
*/
static void _destroy( NODE *root);

/* Inserts new data into the tree
	return	1 success
			0 overflow
*/
int BST_Insert( TREE *pTree, int data);

/* internal function (not mandatory)
*/
static void _insert( NODE *root, NODE *newPtr);

NODE *_makeNode( int data);

/* Deletes a node with dltKey from the tree
	return	1 success
			0 not found
*/
int BST_Delete( TREE *pTree, int dltKey);

/* internal function
	success is 1 if deleted; 0 if not
	return	pointer to root
*/
static NODE *_delete( NODE *root, int dltKey, int *success);

static NODE* findSmallestBST(NODE* root);

/* Retrieve tree for the node containing the requested key
	return	address of data of the node containing the key
			NULL not found
*/
int *BST_Retrieve( TREE *pTree, int key);

/* internal function
	Retrieve node containing the requested key
	return	address of the node containing the key
			NULL not found
*/
static NODE *_retrieve( NODE *root, int key);

/* prints tree using inorder traversal
*/
void BST_Traverse( TREE *pTree);
static void _traverse( NODE *root);

/* Print tree using inorder right-to-left traversal
*/
void printTree( TREE *pTree);
/* internal traversal function
*/
static void _infix_print( NODE *root, int level);

/* 
	return 1 if the tree is empty; 0 if not
*/
int BST_Empty( TREE *pTree);

////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv)
{
	TREE *tree;
	int data;
	
	// creates a null tree
	tree = BST_Create();
	
	if (!tree)
	{
		printf( "Cannot create a tree!\n");
		return 100;
	}

	fprintf( stdout, "How many numbers will you insert into a BST: ");

	int numbers;
	scanf( "%d", &numbers);

	fprintf( stdout, "Inserting: ");
	
	srand( time(NULL));
	for (int i = 0; i < numbers; i++)
	{
		data = rand() % (numbers*3) + 1; // random number (1 ~ numbers * 3)
		
		fprintf( stdout, "%d ", data);
		
		// insert funtion call
		int ret = BST_Insert( tree, data);
		if (!ret) break;
 	}
	fprintf( stdout, "\n");
			
	// inorder traversal
	fprintf( stdout, "Inorder traversal: ");
	BST_Traverse( tree);
	fprintf( stdout, "\n");
	
	// print tree with right-to-left infix traversal
	fprintf( stdout, "Tree representation:\n");
	printTree(tree);
	
	while (1)
	{
		fprintf( stdout, "Input a number to delete: "); 
		int num;
		int ret = scanf( "%d", &num);
		if (ret != 1) break;
		
		ret = BST_Delete( tree, num);
		if (!ret)
		{
			fprintf( stdout, "%d not found\n", num);
			continue;
		}
		
		// print tree with right-to-left infix traversal
		fprintf( stdout, "Tree representation:\n");
		printTree(tree);
		
		if (BST_Empty( tree))
		{
			fprintf( stdout, "Empty tree!\n");
			break;
		}
	}
	
	BST_Destroy( tree);

	return 0;
}

/* Allocates dynamic memory for a tree head node and returns its address to caller
	return	head node pointer
			NULL if overflow
*/
TREE* BST_Create(void) {
	TREE* tree;
	if (tree = (TREE*)malloc(sizeof(TREE))) {
		tree->root = NULL;
		return tree;
	}

	return NULL;
}

/* Deletes all data in tree and recycles memory
*/
void BST_Destroy(TREE* pTree) {
	if (pTree)
	{
		_destroy(pTree->root);
	}

	free(pTree);
}

/* internal function (not mandatory)
*/
static void _destroy(NODE* root) {
	if (root != NULL) {
		if (root->left != NULL) _destroy(root->left);
		if (root->right != NULL) _destroy(root->right);
		free(root);
	}
}

/* Inserts new data into the tree
	return	1 success
			0 overflow
*/
int BST_Insert(TREE* pTree, int data) {
	NODE* node;
	node = _makeNode(data);

	if (BST_Empty(pTree)) {
		pTree->root = node;
		return 1;
	}
	else {
		_insert(pTree->root, node);
		return 1;
	}

	return 0;
}

/* internal function (not mandatory)
*/
static void _insert(NODE* root, NODE* newPtr) {
	if (newPtr->data < root->data) {
		if (root->left == NULL) root->left = newPtr;
		else _insert(root->left, newPtr);
	}
	else {
		if (root->right == NULL) root->right = newPtr;
		else _insert(root->right, newPtr);
	}
}

NODE* _makeNode(int data) {
	NODE* node;
	if (node = (NODE*)malloc(sizeof(NODE))) {
		node->data = data;
		node->left = NULL;
		node->right = NULL;
		return node;
	}

	return NULL;
}

/* Deletes a node with dltKey from the tree
	return	1 success
			0 not found
*/
int BST_Delete(TREE* pTree, int dltKey) {
	int success = 0;
	NODE* node = _delete(pTree->root, dltKey, &success);

	return success;
}

/* internal function
	success is 1 if deleted; 0 if not
	return	pointer to root
*/
static NODE* _delete(NODE* root, int dltKey, int* success) {
	NODE* deleteNode;
	NODE* smallest;
	NODE* tNode;

	if (dltKey < root->data) {
		root->left = _delete(root->left, dltKey, success);
	}
	else if (dltKey > root->data) {
		root->right = _delete(root->right, dltKey, success);
	}
	else {
		if (root->left == NULL) {
			tNode = root->right;
			free(root);
			*success = 1;
			return tNode;
		}
		else if (root->right == NULL) {
			tNode = root->left;
			free(root);
			*success = 1;
			return tNode;
		}
		else {
			deleteNode = root;
			smallest = findSmallestBST(root->right);
			deleteNode->data = smallest->data;
			root->right = _delete(root->right, smallest->data, success);
		}
	}

	return root;
}

static NODE* findSmallestBST(NODE* root) {
	if (root->left == NULL) return root;

	return findSmallestBST(root->left);
}

/* Retrieve tree for the node containing the requested key
	return	address of data of the node containing the key
			NULL not found
*/
int* BST_Retrieve(TREE* pTree, int key);

/* internal function
	Retrieve node containing the requested key
	return	address of the node containing the key
			NULL not found
*/
static NODE* _retrieve(NODE* root, int key);

/* prints tree using inorder traversal
*/
void BST_Traverse(TREE* pTree) {
	_traverse(pTree->root);
}

static void _traverse(NODE* root) {
	if ((root->left == NULL) && (root->right == NULL)) {
		fprintf(stdout, "%d ", root->data);
	}
	else {
		_traverse(root->left);
		fprintf(stdout, "%d", root->data);
		_traverse(root->right);
	}
}

/* Print tree using inorder right-to-left traversal
*/
void printTree(TREE* pTree) {
	_infix_print(pTree->root, 0);
}
/* internal traversal function
*/
static void _infix_print(NODE* root, int level) {
	if (root->right != NULL) _infix_print(root->right, level + 1);
	for (int i = 0; i < level; ++i) fprintf(stdout, "\t");
	fprintf(stdout, "%d\n", root->data);
	if (root->left != NULL) _infix_print(root->left, level + 1);
}

/*
	return 1 if the tree is empty; 0 if not
*/
int BST_Empty(TREE* pTree) {
	if (pTree->root == NULL) return 1;

	return 0;
}
