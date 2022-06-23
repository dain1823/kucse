#define SHOW_STEP 0
#define BALANCING 1

#include <stdlib.h> // malloc, rand
#include <stdio.h>
#include <time.h> // time
#include <string.h> //strcmp, strdup

#define max(x, y)	(((x) > (y)) ? (x) : (y))

////////////////////////////////////////////////////////////////////////////////
// AVL_TREE type definition
typedef struct node
{
	char		*data;
	struct node	*left;
	struct node	*right;
	int			height;
} NODE;

typedef struct
{
	NODE	*root;
	int		count;  // number of nodes
} AVL_TREE;

////////////////////////////////////////////////////////////////////////////////
// Prototype declarations

/* Allocates dynamic memory for a AVL_TREE head node and returns its address to caller
	return	head node pointer
			NULL if overflow
*/
AVL_TREE *AVL_Create( void);

/* Deletes all data in tree and recycles memory
*/
void AVL_Destroy( AVL_TREE *pTree);
static void _destroy( NODE *root);

/* Inserts new data into the tree
	return	1 success
			0 overflow
*/
int AVL_Insert( AVL_TREE *pTree, char *data);

/* internal function
	This function uses recursion to insert the new data into a leaf node
	return	pointer to new root
*/
static NODE *_insert( NODE *root, NODE *newPtr);

static NODE *_makeNode( char *data);

/* Retrieve tree for the node containing the requested key
	return	address of data of the node containing the key
			NULL not found
*/
char *AVL_Retrieve( AVL_TREE *pTree, char *key);

/* internal function
	Retrieve node containing the requested key
	return	address of the node containing the key
			NULL not found
*/
static NODE *_retrieve( NODE *root, char *key);

/* Prints tree using inorder traversal
*/
void AVL_Traverse( AVL_TREE *pTree);
static void _traverse( NODE *root);

/* Prints tree using inorder right-to-left traversal
*/
void printTree( AVL_TREE *pTree);
/* internal traversal function
*/
static void _infix_print( NODE *root, int level);

/* internal function
	return	height of the (sub)tree from the node (root)
*/
static int getHeight( NODE *root);

/* internal function
	Exchanges pointers to rotate the tree to the right
	updates heights of the nodes
	return	new root
*/
static NODE *rotateRight( NODE *root);

/* internal function
	Exchanges pointers to rotate the tree to the left
	updates heights of the nodes
	return	new root
*/
static NODE *rotateLeft( NODE *root);

////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv)
{
	AVL_TREE *tree;
	char str[1024];
	
	if (argc != 2)
	{
		fprintf( stderr, "Usage: %s FILE\n", argv[0]);
		return 0;
	}
	
	// creates a null tree
	tree = AVL_Create();
	
	if (!tree)
	{
		fprintf( stderr, "Cannot create tree!\n");
		return 100;
	} 

	FILE *fp = fopen( argv[1], "rt");
	if (fp == NULL)
	{
		fprintf( stderr, "Cannot open file! [%s]\n", argv[1]);
		return 200;
	}

	while(fscanf( fp, "%s", str) != EOF)
	{

#if SHOW_STEP
		fprintf( stdout, "Insert %s>\n", str);
#endif		
		// insert function call
		AVL_Insert( tree, str);

#if SHOW_STEP
		fprintf( stdout, "Tree representation:\n");
		printTree( tree);
#endif
	}
	
	fclose( fp);
	
#if SHOW_STEP
	fprintf( stdout, "\n");

	// inorder traversal
	fprintf( stdout, "Inorder traversal: ");
    AVL_Traverse( tree);
	fprintf( stdout, "\n");

	// print tree with right-to-left infix traversal
	fprintf( stdout, "Tree representation:\n");
	printTree(tree);
#endif
	fprintf( stdout, "Height of tree: %d\n", tree->root->height);
	fprintf( stdout, "# of nodes: %d\n", tree->count);
	
	// retrieval
	char *key;
	fprintf( stdout, "Query: ");
	while( fscanf( stdin, "%s", str) != EOF)
	{
		key = AVL_Retrieve( tree, str);
		
		if (key) fprintf( stdout, "%s found!\n", key);
		else fprintf( stdout, "%s NOT found!\n", str);
		
		fprintf( stdout, "Query: ");
	}
	
	// destroy tree
	AVL_Destroy( tree);

	return 0;
}

/* Allocates dynamic memory for a AVL_TREE head node and returns its address to caller
	return	head node pointer
			NULL if overflow
*/
AVL_TREE* AVL_Create(void) {
	AVL_TREE* tree;
	if (tree = (AVL_TREE*)malloc(sizeof(AVL_TREE))) {
		tree->root = NULL;
		tree->count = 0;
		return tree;
	}

	return NULL;
}

/* Deletes all data in tree and recycles memory
*/
void AVL_Destroy(AVL_TREE* pTree) {
	if (pTree) _destroy(pTree->root);

	free(pTree);
}

static void _destroy(NODE* root) {
	if (root != NULL) {
		if (root->left != NULL) _destroy(root->left);
		if (root->right != NULL) _destroy(root->right);
		free(root->data);
		free(root);
	}
}

/* Inserts new data into the tree
	return	1 success
			0 overflow
*/
int AVL_Insert(AVL_TREE* pTree, char* data) {
	NODE* node;
	node = _makeNode(data);

	if (pTree->root = _insert(pTree->root, node)) {
		pTree->count += 1;

		return 1;
	}

	return 0;
}

/* internal function
	This function uses recursion to insert the new data into a leaf node
	return	pointer to new root
*/
static NODE* _insert(NODE* root, NODE* newPtr) {
	int l;
	int r;
	int ll;
	int rr;

	if (root == NULL) {
		root = newPtr;
		return root;
	}

	if (strcmp(newPtr->data, root->data) < 0) {
		root->left = _insert(root->left, newPtr);
		root->height = getHeight(root);
#if BALANCING
		l = root->left->height;
		if (root->right != NULL) r = root->right->height;
		else r = 0;
		
		if (l - r > 1) {
			ll = getHeight(root->left->left);
			rr = getHeight(root->left->right);

			if (ll > rr) {
				root = rotateRight(root);
			}
			else {
			root->left = rotateLeft(root->left);
			root = rotateRight(root);
			}
		}
#endif
	}
	else {
		root->right = _insert(root->right, newPtr);
		root->height = getHeight(root);
#if BALANCING
		if (root->left != NULL) l = root->left->height;
		else l = 0;
		r = root->right->height;

		if (r - l > 1) {
			ll = getHeight(root->right->left);
			rr = getHeight(root->right->right);

			if (ll < rr) {
				root = rotateLeft(root);
			}
			else {
				root->right = rotateRight(root->right);
				root = rotateLeft(root);
			}
		}
#endif
	}

	return root;
}

static NODE* _makeNode(char* data) {
	NODE* node;
	if (node = (NODE*)malloc(sizeof(NODE))) {
		node->data = strdup(data);
		node->left = NULL;
		node->right = NULL;
		node->height = 1;

		return node;
	}

	return NULL;
}

/* Retrieve tree for the node containing the requested key
	return	address of data of the node containing the key
			NULL not found
*/
char* AVL_Retrieve(AVL_TREE* pTree, char* key) {
	if (pTree->root == NULL) return NULL;

	NODE* tempNode = _retrieve(pTree->root, key);
	if (tempNode == NULL) return NULL;
	else return tempNode->data;
}

/* internal function
	Retrieve node containing the requested key
	return	address of the node containing the key
			NULL not found
*/
static NODE* _retrieve(NODE* root, char* key) {
	if (strcmp(key, root->data) < 0) {
		if (root->left == NULL) return NULL;
		else return _retrieve(root->left, key);
	}
	else if (strcmp(key, root->data) > 0) {
		if (root->right == NULL) return NULL;
		else return _retrieve(root->right, key);
	}
	else if (strcmp(key, root->data) == 0){
		return root;
	}

	return NULL;
}

/* Prints tree using inorder traversal
*/
void AVL_Traverse(AVL_TREE* pTree) {
	_traverse(pTree->root);
}

static void _traverse(NODE* root) {
	if (root != NULL) {
		_traverse(root->left);
		fprintf(stdout, "%s ", root->data);
		_traverse(root->right);
	}
}

/* Prints tree using inorder right-to-left traversal
*/
void printTree(AVL_TREE* pTree) {
	_infix_print(pTree->root, 0);
}

/* internal traversal function
*/
static void _infix_print(NODE* root, int level) {
	if (root->right != NULL) _infix_print(root->right, level + 1);
	for (int i = 0; i < level; ++i) fprintf(stdout, "\t");
	fprintf(stdout, "%s\n", root->data);
	if (root->left != NULL) _infix_print(root->left, level + 1);
}

/* internal function
	return	height of the (sub)tree from the node (root)
*/
static int getHeight(NODE* root) {
	if (root == NULL) return 0;

	if ((root->left == NULL) && (root->right == NULL)) return 1;
	else if ((root->left != NULL) && (root->right == NULL)) return root->left->height + 1;
	else if ((root->left == NULL) && (root->right != NULL)) return root->right->height + 1;
	else {
		if (root->left->height > root->right->height) return root->left->height + 1;
		else return root->right->height + 1;
	}
}

/* internal function
	Exchanges pointers to rotate the tree to the right
	updates heights of the nodes
	return	new root
*/
static NODE* rotateRight(NODE* root) {
	NODE* tempNode;
	tempNode = root->left;

	root->left = tempNode->right;
	tempNode->right = root;

	root->height = getHeight(root);
	tempNode->height = getHeight(tempNode);

	return tempNode;
}

/* internal function
	Exchanges pointers to rotate the tree to the left
	updates heights of the nodes
	return	new root
*/
static NODE* rotateLeft(NODE* root) {
	NODE* tempNode;
	tempNode = root->right;

	root->right = tempNode->left;
	tempNode->left = root;

	root->height = getHeight(root);
	tempNode->height = getHeight(tempNode);

	return tempNode;
}