/*
 * Kevin Wang
 * kwang43@ucsc.edu
 * PA_2
 *
 * List.c
 */

/*
 * A bi-directional queue in the form of a doubly linked list. The user of this
 * interface has precise control over where in the list each element is
 * inserted. The user can access elements by their integer index (position in
 * the list), and search for elements in the list. A list has two ends referred
 * to as "front" and "back" respectively. It pair will be used by the client to
 * traverse the list in either direction. Each list element is associated with
 * an index ranging from 0 (front) to n-1 (back), where n is the length of the
 * list.
 * 
 * Note that it is a valid state for this ADT to have no distinguished element
 * (i.e. the cursor index may be undefined or "off the list") which is in fact
 * its default state. Thus the set of "mathematical structures" for this ADT
 * consists of all finite sequences of integers in which at most one element is
 * underscored.
 * 
 * Contains a private doubly linked list class which itself contains fields for an
 * integer (the data), and two Node references (the previous and next Nodes,
 * respectively) which may be null.
 *
 * @author Kevin Wang
 * @since 5.15.2018
 */

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

/****************************************************************************
 ******************************* STRUCTURES *********************************
 ****************************************************************************/

/* NodeObj Type */
typedef struct NodeObj {
	int data;
	struct NodeObj* prev;
	struct NodeObj* next;
} NodeObj;

typedef NodeObj* Node;

/* ListObj Type */
typedef struct ListObj {
	Node front;
	Node back;
	Node cursor;
	int index;
	int length;
} ListObj;

/****************************************************************************
 *********************** CONSTRUCTORS & DESTRUCTORS *************************
 ****************************************************************************/

/* Node Constructor */
Node newNode(int data) {
	Node N = malloc(sizeof(NodeObj));
	N->data = data;
	N->prev = NULL;
	N->next = NULL;
	return (N);
}

/* Node Destructor */
void freeNode(Node* pN) {
	if (pN != NULL && *pN != NULL) {
		free(*pN);
		*pN = NULL;
	}
}

/* List Constructor */
List newList(void) {
	List L;
	L = malloc(sizeof(ListObj));
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->index = -1;
	L->length = 0;
	return (L);
}

/* List Destructor */
void freeList(List *pL) {
	if (pL != NULL && *pL != NULL) {
		while (length(*pL) > 0) {
			deleteBack(*pL);
		}
		free(*pL);
		*pL = NULL;
	}
}

/****************************************************************************
 **************************** ACCESS FUNCTIONS ******************************
 ****************************************************************************/

/* Returns the number of elements in this List. */
int length(List L) {
	if (L == NULL) {
		printf("List error: Cannot call length() on NULL List \n");
		exit(1);
	}
	if (L->length < 0) {
		printf("List Error: length of List cannot be less than 0 \n");
		exit(1);
	}
	return L->length;
}

/* 
 * If cursor is defined, returns the index of the cursor element,
 * otherwise returns -1.
 */
int index(List L) {
	if (L == NULL) {
		printf("List error: Cannot call index() on NULL List \n");
		exit(1);
	}
	if (L->index < -1) {
		printf("List Error: length of List cannot be less than 0 \n");
		exit(1);
	}
	return L->index;
}

/* Returns front element. Pre: length()>0 */
int front(List L) {
	if (L == NULL) {
		printf("List error: Cannot call front() on NULL List \n");
		exit(1);
	}
	if (length(L) == 0) {
		printf("List Error: Cannot call front() on empty List \n");
		exit(1);
	} else {
		return L->front->data;
	}
}

/* Returns back element. Pre: length()>0 */
int back(List L) {
	if (L == NULL) {
		printf("List error: Cannot call back() on NULL List \n");
		exit(1);
	}
	if (length(L) == 0) {
		printf("List Error: Cannot call back() on empty List \n");
		exit(1);
	} else {
		return L->back->data;
	}
}

/* Returns cursor element. Pre: length()>0, index()>=0 */
int get(List L) {
	if (L == NULL) {
		printf("List error: Cannot call get() on NULL List \n");
		exit(1);
	}
	if (length(L) <= 0) {
		printf("List Error: Cannot call get() on empty List \n");
		exit(1);
	}
	if (index(L) < 0) {
		printf("List Error: Cannot call get() on undefined index \n");
		exit(1);
	} else {
		return L->cursor->data;
	}
}

/* 
 * Returns 1 if this List and L are the same integer
 * sequence. The cursor is ignored in both lists.
 */
int equals(List A, List B) {
	if (A == NULL || B == NULL) {
		printf("List error: Cannot call equals() on NULL List \n");
		exit(1);
	}
	int equivalent = 1;

	if (length(A) != length(B)) {
		equivalent = 0;
	} else {
		Node a = A->front;
		Node b = B->front;

		while ((equivalent == 1) && (a != NULL)) {
			if (a->data != b->data) { //check Nodes
				equivalent = 0;
			}
		}
		a = a->next;
		b = b->next;
	}
	return equivalent;
}

/****************************************************************************
 ************************* MANIPULATION PROCEDURES **************************
 ****************************************************************************/

/* Resets this List to its original empty state. */
void clear(List L) {
	if (L == NULL) {
		printf("List error: Cannot call clear() on NULL List \n");
		exit(1);
	}
	L->front = NULL;
	L->back = NULL;
	L->cursor = NULL;
	L->index = -1;
	L->length = 0;
}
/* 
 * If List is non-empty, places the cursor under the front element,
 * otherwise does nothing.
 */
void moveFront(List L) {
	if (L == NULL) {
		printf("List error: Cannot call moveFront() on NULL List \n");
		exit(1);
	}
	if (length(L) > 0) { // if List is non-empty...
		L->cursor = L->front;
		L->index = 0;
	}
}

/* 
 * If List is non-empty, places the cursor under the back element,
 * otherwise does nothing.
 */
void moveBack(List L) {
	if (L == NULL) {
		printf("List error: Cannot call moveBack() on NULL List \n");
		exit(1);
	}
	if (L->length > 0) {
		L->cursor = L->back;
		L->index = length(L) - 1;
	}
}

/* 
 * If cursor is defined and not at front, moves cursor one step toward
 * front of this List, if cursor is defined and at front, cursor becomes
 * undefined, if cursor is undefined does nothing
 */
void movePrev(List L) {
	if (L == NULL) {
		printf("List error: Cannot call movePrev() on NULL List \n");
		exit(1);
	}
	if ((L->cursor != NULL) && (index(L) > 0)) {
		L->cursor = L->cursor->prev;
		L->index--;
	} else if ((L->cursor != NULL) && (index(L)) == 0) {
		L->cursor = NULL;
		L->index = -1;
	}
}

/*
 * If cursor is defined and not at back, moves cursor one step toward
 * back of this List, if cursor is defined and at back, cursor becomes
 * undefined, if cursor is undefined does nothing.
 */
void moveNext(List L) {
	if (L == NULL) {
		printf("List error: Cannot call moveNext() on NULL List \n");
		exit(1);
	}
	if ((L->cursor != NULL) && (index(L) < length(L) - 1)) {
		L->cursor = L->cursor->next;
		L->index++;
	} else if ((L->cursor != NULL) && (index(L) == length(L) - 1)) {
		L->cursor = NULL;
		L->index = -1;
	}
}

/*
 * Insert new element into this List. If List is non-empty,
 * insertion takes place before front element.
 */
void prepend(List L, int data) {
	if (L == NULL) {
		printf("List error: Cannot call prepend() on NULL List \n");
		exit(1);
	}
	if (length(L) == 0) { // empty List
		L->front = newNode(data);
		L->back = L->front;
	} else { // non-Empty List
		Node N = newNode(data);

		N->next = L->front;
		L->front->prev = N;
		L->front = N;

		L->index++;
	}
	L->length++;
}

/* 
 * Insert new element into this List. If List is non-empty,
 * insertion takes place after back element.
 */
void append(List L, int data) {
	if (L == NULL) {
		printf("List error: Cannot call append() on NULL List \n");
		exit(1);
	}
	if (L->length == 0) { // empty List
		L->back = newNode(data);
		L->front = L->back;
	} else { // non-empty List
		Node N = newNode(data);

		N->prev = L->back;
		L->back->next = N;
		L->back = N;
	}
	L->length++;
}

/* 
 * Insert new element before cursor.
 * Pre: length()>0, index()>=0
 */
void insertBefore(List L, int data) {
	if (L == NULL) {
		printf("List error: Cannot call insertBefore() on NULL List \n");
		exit(1);
	}
	if (length(L) == 0) {
		printf("List Error: Cannot call insertBefore() on empty List \n");
		exit(1);
	}
	if (index(L) == -1) {
		printf("List Error: Cannot call insertBefore() on undefined cursor \n");
		exit(1);
	}
	if (index(L) == 0) { // cursor is at front...
		Node N = newNode(data);

		N->next = L->cursor;
		L->cursor->prev = N;
		L->front = N;
	} else { // cursor not at front
		Node N = newNode(data);
		Node prefix = L->cursor->prev;

		N->prev = prefix;
		N->next = L->cursor;
		prefix->next = N;
		L->cursor->prev = N;
	}
	L->index++;
	L->length++;
}

/* 
 * Inserts new element after cursor.
 * Pre: length()>0, index()>=0
 */
void insertAfter(List L, int data) {
	if (L == NULL) {
		printf("List error: Cannot call insertAfter() on NULL List \n");
		exit(1);
	}
	if (length(L) == 0) {
		printf("List Error: Cannot call insertAfter() on empty List \n");
		exit(1);
	}
	if (index(L) == -1) {
		printf("List Error: Cannot call insertAfter() on undefined cursor \n");
		exit(1);
	}
	if (L->index == L->length - 1) { // cursor is at back
		Node N = newNode(data);

		N->prev = L->cursor;
		L->cursor->next = N;
		L->back = N;
	} else { // cursor is not at back
		Node N = newNode(data);
		Node suffix = L->cursor->next;

		N->next = suffix;
		N->prev = L->cursor;
		suffix->prev = N;
		L->cursor->next = N;
	}
	L->length++;
}

/* Deletes the front element. Pre: length()>0 */
void deleteFront(List L) {
	if (L == NULL) {
		printf("List error: Cannot call deleteFront() on NULL List \n");
		exit(1);
	}
	if (length(L) == 0) {
		printf("List Error: Cannot call deleteFront() on empty List\n");
		exit(1);
	}
	if (length(L) == 1) {
		clear(L);
	} else {
		L->front = L->front->next;
		L->front->prev = NULL;

		if (index(L) == 0) { // if index is defined and at front...
			L->cursor = NULL;
			L->index = -1;
		} else if (index(L) > 0) { // if index is defined and not at front...
			L->index--;
		} // if index is undefined, no change
		L->length--;
	}
}

/* Deletes the back element. Pre: length()>0 */
void deleteBack(List L) {
	if (L == NULL) {
		printf("List error: Cannot call deleteBack() on NULL List \n");
		exit(1);
	}
	if (length(L) == 0) {
		printf("List Error: Cannot call deleteBack() on empty List\n");
		exit(1);
	}
	if (length(L) == 1) {
		clear(L);
	} else {
		L->front = L->front->next;
		L->front->prev = NULL;

		if (index(L) == 0) { // if index is defined and at front...
			L->cursor = NULL;
			L->index = -1;
		} else if (index(L) > 0) { // if index is defined and not at front...
			L->index--;
		} // if index is undefined, no change
		L->length--;
	}
}

// Deletes cursor element, making cursor undefined.
// Pre: length()>0, index()>=0

void delete(List L) {
	if (L == NULL) {
		printf("List error: Cannot call delete() on NULL List \n");
		exit(1);
	}
	if (L->length <= 0) {
		printf("List Error: Cannot call delete() on empty List \n");
		exit(1);
	}
	if (L->index == -1) {
		printf("List Error: Cannot call delete() on undefined cursor \n");
		exit(1);
	}
	if (L->index == 0) {
		deleteFront(L);
	} else if (L->index == L->length - 1) {
		deleteBack(L);
	} else {
		Node prefix = L->cursor->prev;
		Node suffix = L->cursor->next;
		Node delete = L->cursor;

		prefix->next = suffix;
		suffix->prev = prefix;

		L->cursor = NULL;
		freeNode(&delete);

		L->index = -1;
		L->length--;
	}
}

// OTHER METHODS

void printList(FILE* out, List L) {
	Node N = NULL;
	for (N = L->front; N != NULL; N = N->next) {
		fprintf(out, "%d ", N->data);
	}
}

List copyList(List L) {
	Node N = L->front;
	List M = newList();
	while (N != NULL) {
		append(M, N->data);
		N = N->next;
		M->length += 1;
	}
	return M;
}
