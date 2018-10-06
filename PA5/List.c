/*
 * Kevin Wang
 * kwang43@ucsc.edu
 * PA_5
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
 * Contains a private doubly linked list class which itself contains fields for 
 * an integer (the data), and two Node references (the previous and next Nodes,
 * respectively) which may be null.
 *
 * @author Kevin Wang
 * @since 6.5.2018
 */

#include <stdio.h>
#include <stdlib.h>
#include "List.h"

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
    Node N = malloc(sizeof (NodeObj));
    N->data = data;
    N->prev = NULL;
    N->next = NULL;
    return (N);
}

/* Node Destructor */
void freeNode(Node* pN) {
    if ((pN != NULL) && (*pN != NULL)) {
        free(*pN);
        *pN = NULL;
    }
}

/* List Constructor */
List newList(void) {
    List L;
    L = malloc(sizeof (ListObj));
    L->front = NULL;
    L->back = NULL;
    L->cursor = NULL;
    L->index = -1;
    L->length = 0;
    return (L);
}

/* List Destructor */
void freeList(List* pL) {
    if ((pL != NULL) && (*pL != NULL)) {
        clear(*pL);
        free(*pL);
        *pL = NULL;
    }
}

/****************************************************************************
 **************************** ACCESS FUNCTIONS ******************************
 ****************************************************************************/

/* Returns the length (number of elements) of this List. */
int length(List L) {
    if (L == NULL) {
        printf("List Error: Cannot call length() on NULL List \n");
        exit(1);
    }
    if (L->length < 0) {
        printf("List Error: length of List cannot be less than 0 \n");
        exit(1);
    }
    return L->length;
}

/* 
 * Returns the index of List L's cursor element, or returns -1 if the cursor 
 * is undefined.
 */
int index(List L) {
    if (L == NULL) {
        printf("List Error: Cannot call index() on NULL List \n");
        exit(1);
    }
    if (L->index < -1) {
        printf("List Error: index of cursor cannot be less than -1 \n");
        exit(1);
    }
    return L->index;
}

/* Returns the front element of L. Pre: length(L) > 0 */
int front(List L) {
    if (L == NULL) {
        printf("List Error: Cannot call front() on NULL List \n");
        exit(1);
    }
    if (length(L) == 0) {
        printf("List Error: Cannot call front() on empty List \n");
        exit(1);
    } else {
        return L->front->data;
    }
}

/* Returns the back element of L. Pre: length(L) > 0 */
int back(List L) {
    if (L == NULL) {
        printf("List Error: Cannot call back() on NULL List \n");
        exit(1);
    }
    if (length(L) == 0) {
        printf("List Error: Cannot call back() on empty List \n");
        exit(1);
    } else {
        return L->back->data;
    }
}

/* 
 * Returns the cursor element of L. Cursor must be defined.
 * Pre: length(L) > 0, index(L) != -1 
 */
int get(List L) {
    if (L == NULL) {
        printf("List Error: Cannot call get() on NULL List \n");
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
 * Returns 1 (TRUE) iff List A and List B are the same integer sequence.
 * Otherwise, returns 0 (FALSE). The cursor is ignored in both lists.
 */
int equals(List A, List B) {
    if (A == NULL || B == NULL) {
        printf("List Error: Cannot call equals() on NULL List \n");
        exit(1);
    }
    int equivalent = 1;

    if (length(A) != length(B)) { // check lengths
        equivalent = 0;
    } else {
        Node a = A->front;
        Node b = B->front;

        while ((equivalent == 1) && (a != NULL)) {
            if (a->data != b->data) { //check Nodes
                equivalent = 0;
            }
            a = a->next;
            b = b->next;
        }
    }
    return equivalent;
}

/****************************************************************************
 ************************* MANIPULATION PROCEDURES **************************
 ****************************************************************************/

/* Deletes all Nodes of L, restoring it to its original empty state. */
void clear(List L) {
    if (L == NULL) {
        printf("List Error: Cannot call clear() on NULL List \n");
        exit(1);
    }
    while (length(L) > 0) { // delete each Node
        deleteBack(L);
    }
}

/* 
 * If List is non-empty, places the cursor under the front element,
 * otherwise does nothing.
 */
void moveFront(List L) {
    if (L == NULL) {
        printf("List Error: Cannot call moveFront() on NULL List \n");
        exit(1);
    }
    if (length(L) > 0) { // if List is non-empty
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
        printf("List Error: Cannot call moveBack() on NULL List \n");
        exit(1);
    }
    if (length(L) > 0) { // if List is non-empty
        L->cursor = L->back;
        L->index = length(L) - 1;
    }
}

/* 
 * If cursor is defined and not at front, moves cursor one step toward
 * front of this List. If cursor is defined and at front, cursor becomes
 * undefined. If cursor is undefined does nothing.
 */
void movePrev(List L) {
    if (L == NULL) {
        printf("List Error: Cannot call movePrev() on NULL List \n");
        exit(1);
    }
    if (index(L) > 0) { // if cursor is not at front
        L->cursor = L->cursor->prev;
        L->index--;
    } else if (index(L) == 0) { // if cursor is at front
        L->cursor = NULL;
        L->index = -1;
    }
}

/*
 * If cursor is defined and not at back, moves cursor one step toward
 * back of this List. If cursor is defined and at back, cursor becomes
 * undefined. If cursor is undefined does nothing.
 */
void moveNext(List L) {
    if (L == NULL) {
        printf("List Error: Cannot call moveNext() on NULL List \n");
        exit(1);
    }
    if (index(L) < length(L) - 1) { // if cursor is not at back
        L->cursor = L->cursor->next;
        L->index++;
    } else if (index(L) == length(L) - 1) { // if cursor is at back
        L->cursor = NULL;
        L->index = -1;
    }
}

/*
 * Inserts a new element into L. If List is non-empty, insertion takes place 
 * before the front element.
 */
void prepend(List L, int data) {
    if (L == NULL) {
        printf("List Error: Cannot call prepend() on NULL List \n");
        exit(1);
    }

    Node N = newNode(data); // initialize Node to be prepended

    if (length(L) == 0) { // if List is empty
        L->front = N;
        L->back = L->front;
    } else { // if List is non-empty
        N->next = L->front;
        L->front->prev = N;
        L->front = N;

        L->index++;
    }
    L->length++;
}

/*
 * Inserts a new element into L. If List is non-empty, insertion takes place 
 * after the back element.
 */
void append(List L, int data) {
    if (L == NULL) {
        printf("List Error: Cannot call append() on NULL List \n");
        exit(1);
    }

    Node N = newNode(data); // initialize Node to be appended

    if (length(L) == 0) { // if List is empty
        L->back = N;
        L->front = L->back;
    } else { // if List is non-empty
        N->prev = L->back;
        L->back->next = N;
        L->back = N;
    }
    L->length++;
}

/* 
 * Inserts a new element before the cursor.
 * Pre: length(L) > 0, index(L) != -1
 */
void insertBefore(List L, int data) {
    if (L == NULL) {
        printf("List Error: Cannot call insertBefore() on NULL List \n");
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

    Node N = newNode(data); // initialize Node to be inserted

    if (index(L) == 0) { // cursor is at front
        N->next = L->cursor;
        L->cursor->prev = N;
        L->front = N;
    } else { // cursor not at front
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
 * Inserts a new element after the cursor.
 * Pre: length(L) > 0, index(L) != -1
 */
void insertAfter(List L, int data) {
    if (L == NULL) {
        printf("List Error: Cannot call insertAfter() on NULL List \n");
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

    Node N = newNode(data); // initialize Node to be inserted

    if (index(L) == length(L) - 1) { // if cursor is at back
        N->prev = L->cursor;
        L->cursor->next = N;
        L->back = N;
    } else { // if cursor is not at back
        Node suffix = L->cursor->next;

        N->next = suffix;
        N->prev = L->cursor;
        suffix->prev = N;
        L->cursor->next = N;
    }
    L->length++;
}

/* Deletes the front element of L. Pre: length(L) > 0 */
void deleteFront(List L) {
    if (L == NULL) {
        printf("List Error: Cannot call deleteFront() on NULL List \n");
        exit(1);
    }
    if (length(L) == 0) {
        printf("List Error: Cannot call deleteFront() on empty List\n");
        exit(1);
    }

    Node N = L->front; // get memory pointer of Node to be deleted

    if (length(L) == 1) { // if only one Node in List
        L->cursor = NULL;
        L->front = NULL;
        L->back = NULL;
        L->index = -1;
        L->length = 0;
    } else { // if multiple Nodes
        L->front = L->front->next;
        L->front->prev = NULL;

        if (index(L) == 0) { // if cursor is at front
            L->cursor = NULL;
            L->index = -1;
        } else if (index(L) > 0) { // if cursor is not at front
            L->index--;
        }
        L->length--;
    }
    freeNode(&N); // free deleted Node memory
}

/* Deletes the back element of L. Pre: length(L) > 0 */
void deleteBack(List L) {
    if (L == NULL) {
        printf("List Error: Cannot call deleteBack() on NULL List \n");
        exit(1);
    }
    if (length(L) == 0) {
        printf("List Error: Cannot call deleteBack() on empty List\n");
        exit(1);
    }

    Node N = L->back; // get memory pointer of Node to be deleted
    
    if (length(L) == 1) { // if only one Node in List
        L->cursor = NULL;
        L->front = NULL;
        L->back = NULL;
        L->index = -1;
        L->length = 0;
    } else { // if multiple Nodes
        L->back = L->back->prev;
        L->back->next = NULL;

        if (index(L) == length(L) - 1) { // if cursor is at back
            L->cursor = NULL;
            L->index = -1;
        }
        L->length--;
    }
    freeNode(&N); // free deleted Node memory
}

/* 
 * Deletes the cursor element of L, making the cursor undefined.
 * Pre: length(L) > 0, index(L) != 0
 * Post: L->cursor == NULL, index(L) == -1
 */
void delete(List L) {
    if (L == NULL) {
        printf("List Error: Cannot call delete() on NULL List \n");
        exit(1);
    }
    if (length(L) == 0) {
        printf("List Error: Cannot call delete() on empty List \n");
        exit(1);
    }
    if (index(L) == -1) {
        printf("List Error: Cannot call delete() on undefined cursor \n");
        exit(1);
    }
    if (index(L) == 0) { // if cursor is at front
        deleteFront(L);
    } else if (index(L) == length(L) - 1) { // if cursor is at back
        deleteBack(L);
    } else {
        Node N = L->cursor; // else get memory pointer of Node to be deleted
        
        Node prefix = L->cursor->prev;
        Node suffix = L->cursor->next;

        prefix->next = suffix;
        suffix->prev = prefix;
        
        L->cursor = NULL;
        L->index = -1;
        L->length--;
    
        freeNode(&N); // free deleted Node memory
    }
}

/****************************************************************************
 ***************************** OTHER PROCEDURES *****************************
 ****************************************************************************/

/* 
 * Returns a new List representing the same integer sequence as List L. The
 * cursor in the new list is undefined, regardless of the state of the cursor in
 * this List. This List is unchanged.
 */
List copyList(List L) {
    if (L == NULL) {
        printf("List Error: Cannot call copyList() on NULL List \n");
        exit(1);
    }
    // Initialize new List (Copy)
    List C = newList();
    
    Node N = L->back;
    
    while (N != NULL) {
        prepend(C, N->data); 
        N = N->prev;
    }
    return C;
}

/* 
 * Prints List L to the file pointed to by 'out', formatted as a 
 * space-separated string.
 */
void printList(FILE* out, List L) {
    if (L == NULL) {
        printf("List Error: Cannot call printList() on NULL List \n");
        exit(1);
    }
    for (Node N = L->front; N != NULL; N = N->next) {
        fprintf(out, "%d ", N->data);
    }
}