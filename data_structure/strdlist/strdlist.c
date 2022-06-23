#include <stdlib.h> // malloc
#include <stdio.h>
#include <string.h> // strdup, strcmp
#include <ctype.h> // toupper

#define QUIT			1
#define FORWARD_PRINT	2
#define BACKWARD_PRINT	3
#define SEARCH			4
#define DELETE			5
#define COUNT			6

// User structure type definition
typedef struct 
{
	char	*token;
	int		freq;
} tTOKEN;

////////////////////////////////////////////////////////////////////////////////
// LIST type definition
typedef struct node
{
	tTOKEN		*dataPtr;
	struct node	*llink;
	struct node	*rlink;
} NODE;

typedef struct
{
	int		count;
	NODE	*pos; // unused
	NODE	*head;
	NODE	*rear;
} LIST;

////////////////////////////////////////////////////////////////////////////////
// Prototype declarations

/* Allocates dynamic memory for a list head node and returns its address to caller
	return	head node pointer
			NULL if overflow
*/
LIST *createList( void);

/* Deletes all data in list and recycles memory
*/
void destroyList( LIST *pList);

/* Inserts data into list
	return	0 if overflow
			1 if successful
			2 if duplicated key
*/
int addNode( LIST *pList, tTOKEN *dataInPtr);

/* Removes data from list
	return	0 not found
			1 deleted
*/
int removeNode( LIST *pList, char *keyPtr, tTOKEN **dataOut);

/* interface to search function
	Argu	key being sought
	dataOut	contains found data
	return	1 successful
			0 not found
*/
int searchList( LIST *pList, char *pArgu, tTOKEN **pDataOut);

/* returns number of nodes in list
*/
int countList( LIST *pList);

/* returns	1 empty
			0 list has data
*/
int emptyList( LIST *pList);

//int fullList( LIST *pList);

/* prints data from list (forward)
*/
void printList( LIST *pList);

/* prints data from list (backward)
*/
void printListR( LIST *pList);

/* internal insert function
	inserts data into a new node
	return	1 if successful
			0 if memory overflow
*/
static int _insert( LIST *pList, NODE *pPre, tTOKEN *dataInPtr);

/* internal delete function
	deletes data from a list and saves the (deleted) data to dataOut
*/
static void _delete( LIST *pList, NODE *pPre, NODE *pLoc, tTOKEN **dataOutPtr);

/* internal search function
	searches list and passes back address of node
	containing target and its logical predecessor
	return	1 found
			0 not found
*/
static int _search( LIST *pList, NODE **pPre, NODE **pLoc, char *pArgu);

/* Allocates dynamic memory for a token structure, initialize fields(token, freq) and returns its address to caller
	return	token structure pointer
			NULL if overflow
*/
tTOKEN *createToken( char *str);

/* Deletes all data in token structure and recycles memory
	return	NULL head pointer
*/
void destroyToken( tTOKEN *pToken);

////////////////////////////////////////////////////////////////////////////////
/* gets user's input
*/
int get_action()
{
	char ch;
	scanf( "%c", &ch);
	ch = toupper( ch);
	switch( ch)
	{
		case 'Q':
			return QUIT;
		case 'F':
			return FORWARD_PRINT;
		case 'B':
			return BACKWARD_PRINT;
		case 'S':
			return SEARCH;
		case 'D':
			return DELETE;
		case 'C':
			return COUNT;
	}
	return 0; // undefined action
}

////////////////////////////////////////////////////////////////////////////////
int main( int argc, char **argv)
{
	LIST *list;
	char str[1024];
	tTOKEN *pToken;
	int ret;
	FILE *fp;
	
	if (argc != 2){
		fprintf( stderr, "usage: %s FILE\n", argv[0]);
		return 1;
	}
	
	fp = fopen( argv[1], "rt");
	if (!fp)
	{
		fprintf( stderr, "Error: cannot open file [%s]\n", argv[1]);
		return 2;
	}
	
	// creates an empty list
	list = createList();
	if (!list)
	{
		printf( "Cannot create list\n");
		return 100;
	}
	
	while(fscanf( fp, "%s", str) == 1)
	{
		pToken = createToken( str);
		
		// insert function call
		ret = addNode( list, pToken);
		
		if (ret == 2) // duplicated 
			destroyToken( pToken);
	}
	
	fclose( fp);
	
	fprintf( stderr, "Select Q)uit, F)orward print, B)ackward print, S)earch, D)elete, C)ount: ");
	
	while (1)
	{
		int action = get_action();
		
		switch( action)
		{
			case QUIT:
				destroyList( list);
				return 0;
			
			case FORWARD_PRINT:
				printList( list);
				break;
			
			case BACKWARD_PRINT:
				printListR( list);
				break;
			
			case SEARCH:
				fprintf( stderr, "Input a string to find: ");
				fscanf( stdin, "%s", str);
				
				if (searchList( list, str, &pToken))
				{
					fprintf( stdout, "(%s, %d)\n", pToken->token, pToken->freq);
				}
				else fprintf( stdout, "%s not found\n", str);
				break;
				
			case DELETE:
				fprintf( stderr, "Input a string to delete: ");
				fscanf( stdin, "%s", str);
				
				if (removeNode( list, str, &pToken))
				{
					fprintf( stdout, "%s deleted\n", pToken->token);
					destroyToken( pToken);
				}
				else fprintf( stdout, "%s not found\n", str);
				break;
			
			case COUNT:
				fprintf( stdout, "%d\n", countList( list));
				break;
			}
		
		if (action) fprintf( stderr, "Select Q)uit, F)orward print, B)ackward print, S)earch, D)elete, C)ount: ");
	}
	return 0;
}


/* Allocates dynamic memory for a list head node and returns its address to caller
	return	head node pointer
			NULL if overflow
*/
LIST* createList(void) {
	LIST* list;
	if (list = (LIST*)malloc(sizeof(LIST))) {
		list->count = 0;
		list->head = NULL;
		list->pos = NULL;
		list->rear = NULL;

		return list;
	}

	return NULL;
}

/* Deletes all data in list and recycles memory
*/
void destroyList(LIST* pList) {
	NODE* temp;

	while (!emptyList(pList)) {
		temp = pList->head;
		pList->head = pList->head->rlink;
		destroyToken(temp->dataPtr);
		free(temp);

		--(pList->count);
	}

	free(pList);
}

/* Inserts data into list
	return	0 if overflow
			1 if successful
			2 if duplicated key
*/
int addNode(LIST* pList, tTOKEN* dataInPtr) {
	int insert;
	int found;
	int add = 0;
	
	NODE* pPre;
	NODE* pLoc;

	found = _search(pList, &pPre, &pLoc, dataInPtr->token);
	if (found) {
		++pLoc->dataPtr->freq;
		add = 2;
	}
	else {
		insert = _insert(pList, pPre, dataInPtr);

		if (insert) add = 1;
		else add = 0;
	}

	return add;
}

/* Removes data from list
	return	0 not found
			1 deleted
*/
int removeNode(LIST* pList, char* keyPtr, tTOKEN** dataOut) {
	NODE* pPre;
	NODE* pLoc;
	
	int found = _search(pList, &pPre, &pLoc, keyPtr);

	if (found) {
		_delete(pList, pPre, pLoc, dataOut);
		return 1;
	}

	return 0;
}

/* interface to search function
	Argu	key being sought
	dataOut	contains found data
	return	1 successful
			0 not found
*/
int searchList(LIST* pList, char* pArgu, tTOKEN** pDataOut) {
	int found;

	NODE* pPre;
	NODE* pLoc;

	found = _search(pList, &pPre, &pLoc, pArgu);

	if (found) {
		*pDataOut = pLoc->dataPtr;
		return 1;
	}

	return 0;
}

/* returns number of nodes in list
*/
int countList(LIST* pList) {
	return pList->count;
}

/* returns	1 empty
			0 list has data
*/
int emptyList(LIST* pList) {
	if (pList->count == 0) return 1;
	else return 0;
}

//int fullList( LIST *pList);

/* prints data from list (forward)
*/
void printList(LIST* pList) {
	NODE* temp = pList->head;

	if (!emptyList(pList)) {
		while (temp->rlink != NULL) {
			fprintf(stdout, "%s, %d\n", temp->dataPtr->token, temp->dataPtr->freq);
			temp = temp->rlink;
		}
		fprintf(stdout, "%s, %d\n", temp->dataPtr->token, temp->dataPtr->freq);
	}
}

/* prints data from list (backward)
*/
void printListR(LIST* pList) {
	NODE* temp = pList->rear;

	if (!emptyList(pList)) {
		while (temp->llink != NULL) {
			fprintf(stdout, "%s, %d\n", temp->dataPtr->token, temp->dataPtr->freq);
			temp = temp->llink;
		}
		fprintf(stdout, "%s, %d\n", temp->dataPtr->token, temp->dataPtr->freq);
	}
}

/* internal insert function
	inserts data into a new node
	return	1 if successful
			0 if memory overflow
*/
static int _insert(LIST* pList, NODE* pPre, tTOKEN* dataInPtr) {
	NODE* node;
	NODE* pLoc;

	if (node = (NODE*)malloc(sizeof(NODE))) {
		node->dataPtr = dataInPtr;

		if (pPre == NULL) pLoc = pList->head;
		else pLoc = pPre->rlink;

		node->llink = pPre;
		node->rlink = pLoc;

		if (pPre == NULL) pList->head = node;
		else pPre->rlink = node;

		if (pLoc == NULL) pList->rear = node;
		else pLoc->llink = node;

		++pList->count;
		++node->dataPtr->freq;
		return 1;
	}
	
	return 0;
}

/* internal delete function
	deletes data from a list and saves the (deleted) data to dataOut
*/
static void _delete(LIST* pList, NODE* pPre, NODE* pLoc, tTOKEN** dataOutPtr) {
	*dataOutPtr = pLoc->dataPtr;

	if (pLoc->llink == NULL) {
		pList->head = pLoc->rlink;
		if (pLoc->rlink != NULL) pLoc->rlink->llink = pLoc->llink;
		else pList->rear = NULL;
	}
	else {
		pPre->rlink = pLoc->rlink;
		if (pLoc->rlink != NULL) pLoc->rlink->llink = pPre;
		else pList->rear = pPre;
	}

	free(pLoc);
	--pList->count;
}

/* internal search function
	searches list and passes back address of node
	containing target and its logical predecessor
	return	1 found
			0 not found
*/
static int _search(LIST* pList, NODE** pPre, NODE** pLoc, char* pArgu) {
	int found = 0;
	*pPre = NULL;
	*pLoc = pList->head;

	while ((*pLoc != NULL) && (strcmp(pArgu, (**pLoc).dataPtr->token) > 0)) {
		*pPre = *pLoc;
		*pLoc = (**pLoc).rlink;
	}

	if (*pLoc == NULL) found = 0;
	else {
		if (!(strcmp(pArgu, (**pLoc).dataPtr->token))) found = 1;
		else {
			found = 0;
		}
	}

	return found;
}

/* Allocates dynamic memory for a token structure, initialize fields(token, freq) and returns its address to caller
	return	token structure pointer
			NULL if overflow
*/
tTOKEN* createToken(char* str) {
	tTOKEN* t;
	if (t = (tTOKEN*)malloc(sizeof(tTOKEN))) {
		t->token = strdup(str);
		t->freq = 0;

		return t;
	}
	
	return NULL;
}

/* Deletes all data in token structure and recycles memory
	return	NULL head pointer
*/
void destroyToken(tTOKEN* pToken) {
	free(pToken->token);
	free(pToken);
}