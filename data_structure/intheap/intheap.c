#include <stdio.h>
#include <stdlib.h> // malloc, rand
#include <time.h> // time

#define MAX_ELEM	20

typedef struct
{
	int *heapArr;
	int	last;
	int	capacity;
} HEAP;

/* Allocates memory for heap and returns address of heap head structure
if memory overflow, NULL returned
*/
HEAP *heapCreate( int capacity);

/* Free memory for heap
*/
void heapDestroy( HEAP *heap);

/* Inserts data into heap
return 1 if successful; 0 if heap full
*/
int heapInsert( HEAP *heap, int data);

/* Reestablishes heap by moving data in child up to correct location heap array
*/
static void _reheapUp( HEAP *heap, int index);

/* Deletes root of heap and passes data back to caller
return 1 if successful; 0 if heap empty
*/
int heapDelete( HEAP *heap, int* data);

/* Reestablishes heap by moving data in root down to its correct location in the heap
*/
static void _reheapDown( HEAP *heap, int index);

/* Print heap array */
void heapPrint( HEAP *heap);

int main(void)
{
	HEAP *heap;
	int data;
	int i;
	
	heap = heapCreate(MAX_ELEM);
	
	srand( time(NULL));
	
	for (i = 0; i < MAX_ELEM; i++)
	{
		data = rand() % MAX_ELEM * 3 + 1; // 1 ~ MAX_ELEM*3 random number
				
		fprintf( stdout, "Inserting %d: ", data);
		
		// insert function call
		heapInsert( heap, data);
		
		heapPrint( heap);
 	}

	while (heap->last >= 0)
	{
		// delete function call
		heapDelete( heap, &data);

		printf( "Deleting %d: ", data);

		heapPrint( heap);
 	}
	
	heapDestroy( heap);
	
	return 0;
}

/* Allocates memory for heap and returns address of heap head structure
if memory overflow, NULL returned
*/
HEAP* heapCreate(int capacity) {
	HEAP* heap;
	if (heap = (HEAP*)malloc(sizeof(HEAP))) {
		if (heap->heapArr = (int*)malloc(sizeof(int) * capacity)) {
			heap->last = -1;
			heap->capacity = capacity;

			return heap;
		}
	}

	return NULL;
}

/* Free memory for heap
*/
void heapDestroy(HEAP* heap) {
	free(heap->heapArr);
	free(heap);
}

/* Inserts data into heap
return 1 if successful; 0 if heap full
*/
int heapInsert(HEAP* heap, int data) {
	if (heap->last == (MAX_ELEM - 1)) return 0;

	++(heap->last);
	heap->heapArr[heap->last] = data;
	_reheapUp(heap, heap->last);

	return 1;
}

/* Reestablishes heap by moving data in child up to correct location heap array
*/
static void _reheapUp(HEAP* heap, int index) {
	int parent;
	int temp;

	if (index) {
		parent = (int)((index - 1) / 2);
		if (heap->heapArr[index] > heap->heapArr[parent]) {
			temp = heap->heapArr[index];
			heap->heapArr[index] = heap->heapArr[parent];
			heap->heapArr[parent] = temp;
			_reheapUp(heap, parent);
		}
	}
}

/* Deletes root of heap and passes data back to caller
return 1 if successful; 0 if heap empty
*/
int heapDelete(HEAP* heap, int* data) {
	int temp;

	if (heap->last == -1) return 0;

	*data = heap->heapArr[0];
	
	temp = heap->heapArr[heap->last];
	heap->heapArr[heap->last] = heap->heapArr[0];
	heap->heapArr[0] = temp;

	--(heap->last);

	_reheapDown(heap, 0);

	return 1;
}

/* Reestablishes heap by moving data in root down to its correct location in the heap
*/
static void _reheapDown(HEAP* heap, int index) {
	int left = -1;
	int right = -1;
	int large;
	int temp;

	if (heap->last >= (index * 2 + 1)) {
		left = index * 2 + 1;
		
		if (heap->last >= (index * 2 + 2)) {
			right = index * 2 + 2;
		}

		if (heap->heapArr[left] > heap->heapArr[right]) large = left;
		else large = right;

		if (heap->heapArr[index] < heap->heapArr[large]) {
			temp = heap->heapArr[index];
			heap->heapArr[index] = heap->heapArr[large];
			heap->heapArr[large] = temp;
			_reheapDown(heap, large);
		}
	}
}

/* Print heap array */
void heapPrint(HEAP* heap) {
	for (int i = 0; i <= heap->last; ++i) {
		printf("%6d", heap->heapArr[i]);
	}
	printf("\n");
}