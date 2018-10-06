/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   List.h
 * Author: Kevin
 *
 * Created on May 15, 2018, 5:35 AM
 */

#ifndef LIST_H
#define LIST_H

//-----------------------------------------------------------------------------
//  Kevin Wang
//  kwang43@ucsc.edu
//  PA_2
//
//  List.h
//  List ADT Header
//-----------------------------------------------------------------------------


typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------
List newList(void); // Creates a new empty List
void freeList(List* pL); // Frees associated heap memory & sets pointer to NULL

// Access functions -----------------------------------------------------------
int length(List L); // Returns the number of elements in the List
int index(List L); // Returns index of cursor element or -1 if undefined
int front(List L); // Returns front element
int back(List L); // Returns back element
int get(List L); // Returns cursor element
int equals(List A, List B); // Returns TRUE iff List A & List B 
                            // are the same integer sequence

// Manipulation procedures ----------------------------------------------------
void clear(List L); // Resets List L to its original empty state
void moveFront(List L); // Place cursor under the front element of List L
void moveBack(List L); // Place cursor under the back element of List L
void movePrev(List L); // Moves cursor one step toward the front of List L
void moveNext(List L); // Moves cursor one step toward the back of List L
void prepend(List L, int data); // Insert new element at front of List L
void append(List L, int data); // Insert new element at back of List L
void insertBefore(List L, int data); // Insert new element before cursor
void insertAfter(List L, int data); // Insert new element after cursor
void deleteFront(List L); // Deletes the front element
void deleteBack(List L); // Deletes the back element
void delete(List L); // Deletes cursor element, cursor becomes undefined (-1)

// Other operations -----------------------------------------------------------
void printList(FILE* out, List L); // Prints  a String representation of the 
                                   // List consisting of a space separated 
                                   // sequence of integers, with front on left, 
                                   // to FILE

List copyList(List L); // Returns a new List representing the same integer
                       // sequence as List L.




#endif /* LIST_H */

