//-----------------------------------------------------------------------------
// Abhay Singh, abrsingh
// 2022 Spring CSE101 PA#4
// List.c
// Implementation file for List ADT
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "List.h"

// structs --------------------------------------------------------------------

typedef struct NodeObj* Node;

typedef struct NodeObj{
    void* data;
    Node previous;
    Node next;
} NodeObj;

typedef struct ListObj{
    Node front;
    Node back;
    Node cursor;
    int length;
    int index;
} ListObj;

// Constructors-Destructors ---------------------------------------------------

// allocates memory and creates a node object
Node newNode(void* data){
    Node N = malloc(sizeof(NodeObj));
    N->data = data;
    N->previous = NULL;
    N->next = NULL;
    return(N);
}

//frees the node object
void freeNode(Node* pN){
    if (pN!=NULL && *pN!= NULL) {
        free(*pN);
        *pN = NULL;
    }
}

// Creates and returns a new empty List.
List newList(void) {
    List L;
    L = malloc(sizeof(ListObj));
    L->front = L->back = L->cursor = NULL;
    L->length = 0;
    L->index = -1;
    return(L);
}

// Frees all heap memory associated with *pL, and sets
// *pL to NULL.
void freeList(List* pL){
    if ((*pL)->length != 0) {
        clear(*pL);
    }
    if (pL!=NULL && *pL!=NULL){
        free(*pL);
        *pL = NULL;
    }
}

// Access functions -----------------------------------------------------------

// Returns the number of elements in L.
int length(List L){
    return(L->length);
}

// Returns index of cursor element if defined, -1 otherwise.
int index(List L){
    if (L == NULL) {
        printf("List Error: calling index() on NULL List reference\n");
        freeList(&L);
        exit(EXIT_FAILURE);
    }
    if (L->cursor != NULL){
        return(L->index);
    } else {
        return(-1);
    }
}

// Returns front element of L. Pre: length()>0
void* front(List L){
    if (L == NULL) {
        printf("List Error: calling front() on NULL List reference\n");
        freeList(&L);
        exit(EXIT_FAILURE);
    }
    if (L->length < 0) {
        printf("List Error: calling front() on List of invalid length\n");
        freeList(&L);
        exit(EXIT_FAILURE);
    } else {
        return(L->front->data);
    }
}

// Returns back element of L. Pre: length()>0
void* back(List L) {
    if (L == NULL) {
        printf("List Error: calling back() on NULL List reference\n");
        freeList(&L);
        exit(EXIT_FAILURE);
    }
    if (L->length < 0) {
        printf("List Error: calling back() on List of invalid length\n");
        freeList(&L);
        exit(EXIT_FAILURE);
    } else {
        return(L->back->data);
    }
}

// Returns cursor element of L. Pre: length()>0, index()>=0
void* get(List L) {
    if (L == NULL) {
        printf("List Error: calling get() on NULL List reference\n");
        freeList(&L);
        exit(EXIT_FAILURE);
    }
    if (L->length > 0 && L->index >= 0) {
        return(L->cursor->data);
    } else {
        printf("List error: Invalid length or index parameter\n");
        freeList(&L);
        exit(EXIT_FAILURE);
    }
}


// Manipulation procedures ----------------------------------------------------

// Resets L to its original empty state.
void clear(List L) {
    moveBack(L);
    int place = L->length;
   for(int i = 0; i < place; i += 1) {
       deleteFront(L);
    }
}

// Overwrites the cursor element’s data with x.
// Pre: length()>0, index()>=0
void set(List L, void* x) {
    if (L == NULL) {
        printf("List Error: calling set() on NULL List reference\n");
        freeList(&L);
        exit(EXIT_FAILURE);
    }
    if (L->length > 0 && L->index >= 0) {
        L->cursor->data = x;
    } else {
        printf("List Error: calling set() on NULL List reference\n");
        freeList(&L);
        exit(EXIT_FAILURE);        
    }
}

// If L is non-empty, sets cursor under the front element,
// otherwise does nothing.
void moveFront(List L) {
    if (L->length > 0) {
        L->cursor = L->front;
        L->index = 0;
    }
}


// If L is non-empty, sets cursor under the back element,
// otherwise does nothing.
void moveBack(List L) {
    if (L->length > 0) {
        L->cursor = L->back;
        L->index = L->length - 1;
    }
}


// If cursor is defined and not at front, move cursor one
// step toward the front of L; if cursor is defined and at
// front, cursor becomes undefined; if cursor is undefined
// do nothing
void movePrev(List L) {
    if (L->cursor != NULL && L->index != -1) {
        if (L->cursor != L->front) {
            L->cursor = L->cursor->previous;
            L->index = L->index - 1;
        } else if (L->cursor == L->front) {
            L->cursor = NULL;
            L->index = -1;
        }
    } else {
        ;
    }
}

// If cursor is defined and not at back, move cursor one
// step toward the back of L; if cursor is defined and at
// back, cursor becomes undefined; if cursor is undefined
// do nothing
void moveNext(List L) {
    if (L->cursor != NULL && L->index != -1) {
        if (L->cursor != L->back) {
            L->cursor = L->cursor->next;
            L->index = L->index + 1;
        } else if (L->cursor == L->back) {
            L->cursor = NULL;
            L->index = -1;
        } 
    } else {
        ;
    }
}

// Insert new element into L. If L is non-empty,
// insertion takes place before front element.
void prepend(List L, void* x) {
    Node N = newNode(x);

    if (L == NULL) {
        printf("List Error: calling append on NULL List reference\n");
        freeNode(&N);
        freeList(&L);
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        L->front = L->back = N;

    } else {
        L->front->previous =  N;
        N->next = L->front;
        L->front = N;
    }
    L->length += 1;
    L->index += 1;
}

// Insert new element into L. If L is non-empty,
// insertion takes place after back element.
void append(List L, void* x) {
    Node N = newNode(x);

    if (L == NULL) {
        printf("List Error: calling append on NULL List reference\n");
        freeNode(&N);
        freeList(&L);
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        L->front = L->back = N;
        //freeNode(&N);
    } else {
        L->back->next =  N;
        N->previous = L->back;
        L->back = N;

    }
    L->length += 1;
}

// Insert new element before cursor.
// Pre: length()>0, index()>=0
void insertBefore(List L, void* x) {
    if (L == NULL) {
        printf("List Error: calling append on NULL List reference\n");
        freeList(&L);
        exit(EXIT_FAILURE);
    }
    if (L->length > 0 && L->index >= 0) {
        if (L->index == 0) {
            prepend(L, x);
        } else {
            Node insert = newNode(x);
            insert->next = L->cursor;
            insert->previous = L->cursor->previous;
            L->cursor->previous->next = insert;
            L->cursor->previous = insert;
            L->index += 1;
            L->length += 1;
        }
    } else {
        printf("List Error: calling insertBefore() on list of invalid parameters\n");
        freeList(&L);
        exit(EXIT_FAILURE);
    }
}


// Insert new element after cursor.
// Pre: length()>0, index()>=0
void insertAfter(List L, void* x) {
    if (L == NULL) {
        printf("List Error: calling append on NULL List reference\n");
        freeList(&L);
        exit(EXIT_FAILURE);
    }
    if (L->length > 0 && L->index >= 0) {
        if (L->index == L->length - 1) {
            append(L, x);
        } else {
            Node insert = newNode(x);
            insert->previous = L->cursor;
            insert->next = L->cursor->next;
            L->cursor->next->previous = insert;
            L->cursor->next = insert;
            L->length += 1;
        }
    } else {
        printf("List Error: calling insertAfter() on list of invalid parameters\n");
        freeList(&L);
        exit(EXIT_FAILURE);
    }
}

// Delete the front element. Pre: length()>0
void deleteFront(List L) {
    Node N = NULL;

    if (L == NULL) {
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        printf("List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    N = L->front;
    if (L->length > 1) {
        L->front = L->front->next;
    } else {
        L->front = L->back = NULL;
    }
    L->length--;
    if (L->index == 0) {
        L->index = -1;
        freeNode(&N);
        return;
    } else {
        L->index = L->index - 1;
    }
    freeNode(&N);
}

// Delete the back element. Pre: length()>0
void deleteBack(List L) {
    Node N = NULL;

    if (L == NULL) {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length == 0) {
        printf("List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    N = L->back;
    if (L->length > 1) {
        L->back = L->back->previous;
    } else {
        L->front = L->back = NULL;
    }

    if (L->index == L->length - 1) {
        L->index = -1;
    } 
    L->length--;
    freeNode(&N);
}

// Delete cursor element, making cursor undefined.
// Pre: length()>0, index()>=0
void delete(List L) {
    if (L->length > 0 && L->index >= 0) {
        if (L->index == L->length - 1) {
            deleteBack(L);
            L->index  = -1;
            return;
        }
        if (L->index == 0){
            deleteFront(L);
            L->index = -1;
            return;
        } 
        if (L->cursor->next != NULL) {
            L->cursor->next->previous = L->cursor->previous;
        }
        if (L->cursor->previous != NULL) {
            L->cursor->previous->next = L->cursor->next;
        }
        free(L->cursor);
        L->length = L->length - 1;
        L->index = -1;
    } else {
        return;
    }
}


