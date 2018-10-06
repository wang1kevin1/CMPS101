/*
 * Kevin Wang
 * kwang43@ucsc.edu
 * PA_5
 *
 * List.h
 */

/*
 * Header file for List.c
 *
 * @author Kevin Wang
 * @since 6.2.2018
 */

#ifndef LIST_H
#define LIST_H

typedef struct ListObj* List;

/************************* Constructors-Destructors *************************/

// Returns a List pointing to a newly created ListObj representing an empty 
// List with undefined cursor elements.
List newList(void);

// Frees all dynamic memory associated with the List *pL, 
// then sets pointer to NULL.
void freeList(List* pL);

/***************************** Access Functions *****************************/

// Returns the length (number of elements) of this List.
int length(List L);

// Returns the index of List L's cursor element, or returns -1 if the cursor 
// is undefined.
int index(List L);

// Returns the front element of L. Pre: length(L) > 0
int front(List L);

// Returns the back element of L. Pre: length(L) > 0
int back(List L);

// Returns the cursor element of L. Cursor must be defined.
// Pre: length(L) > 0, index(L) != -1 
int get(List L);

// Returns 1 (TRUE) iff List A and List B are the same integer sequence.
// Otherwise, returns 0 (FALSE). The cursor is ignored in both lists.
int equals(List A, List B);

/************************** Manipulation Procedures **************************/

// Deletes all Nodes of L, restoring it to its original empty state.
void clear(List L);

// If List is non-empty, places the cursor under the front element,
// otherwise does nothing.
void moveFront(List L);

// If List is non-empty, places the cursor under the back element,
// otherwise does nothing.
void moveBack(List L);

// If cursor is defined and not at front, moves cursor one step toward
// front of this List. If cursor is defined and at front, cursor becomes
// undefined. If cursor is undefined does nothing.
void movePrev(List L);

// If cursor is defined and not at back, moves cursor one step toward
// back of this List. If cursor is defined and at back, cursor becomes
// undefined. If cursor is undefined does nothing.
void moveNext(List L);

// Inserts a new element into L. If List is non-empty, insertion takes place 
// before the front element.
void prepend(List L, int data);

// Inserts a new element into L. If List is non-empty, insertion takes place 
// after the back element.
void append(List L, int data);

// Inserts a new element before the cursor.
// Pre: length(L) > 0, index(L) != -1
void insertBefore(List L, int data);

// Inserts a new element after the cursor.
// Pre: length(L) > 0, index(L) != -1
void insertAfter(List L, int data);

// Deletes the front element of L. Pre: length(L) > 0
void deleteFront(List L);

// Deletes the back element of L. Pre: length(L) > 0
void deleteBack(List L);

// Deletes the cursor element of L, making the cursor undefined.
// Pre: length(L) > 0, index(L) != 0
// Post: L->cursor == NULL, index(L) == -1
void delete(List L);

/***************************** Other Procedures ******************************/

// Returns a new List representing the same integer sequence as List L. The
// cursor in the new list is undefined, regardless of the state of the cursor in
// this List. This List is unchanged.
List copyList(List L);

// Prints List L to the file pointed to by 'out', formatted as a 
// space-separated string.
void printList(FILE* out, List L); 

#endif /* LIST_H */

