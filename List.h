//-----------------------------------------------------------------------------
// Abhay Singh, abrsingh
// 2022 Spring CSE101 PA#4
// List.h
// Header file for List ADT
//-----------------------------------------------------------------------------
#ifndef LIST_H_INCLUDE_
#define LIST_H_INCLUDE_

#include <stdbool.h>
// Exported type --------------------------------------------------------------
typedef struct ListObj* List;

// Constructors-Destructors ---------------------------------------------------
List newList(void);

void freeList(List* pL);

// Access functions -----------------------------------------------------------
int length(List L);

int index(List L);

void* front(List L);

void* back(List L);

void* get(List L);

// Manipulation procedures ----------------------------------------------------
void clear(List L);

void set(List L, void* x);

void moveFront(List L);

void moveBack(List L);

void movePrev(List L);

void moveNext(List L);

void prepend(List L, void* x);

void append(List L, void* x);

void insertBefore(List L, void* x);

void insertAfter(List L, void* x);

void deleteFront(List L);

void deleteBack(List L);

void delete(List L);

// Other Functions ------------------------------------------------------------
void printList(FILE* out, List L);

#endif


