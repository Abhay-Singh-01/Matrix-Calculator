//-----------------------------------------------------------------------------
// Abhay Singh, abrsingh
// 2022 Spring CSE101 PA#4
// Matrix.c
// Matrix ADT implementation
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "Matrix.h"

// Exported type --------------------------------------------------------------

typedef struct EntryObj* Entry;

typedef struct EntryObj {
    int col;
    double val;
} EntryObj;

typedef struct MatrixObj{
    List *array;
    int size;
    int NNZ;
} MatrixObj;

// Constructors-Destructors ---------------------------------------------------

//create a new EntryObj
Entry newEntry(int col, double val){
    Entry E;
    E = malloc(sizeof(EntryObj));
    E->col = col;
    E->val = val;
    return E;
}

//create a new Matrix of size nxn
Matrix newMatrix(int n) {
    Matrix M;
    M = malloc(sizeof(MatrixObj));
    M->array = calloc((n + 1), sizeof(List));
    M->array[0] = NULL;
    for (int i = 1; i <= n; i += 1) {
        M->array[i] = newList();
    }
    M->size = n;
    M->NNZ = 0;
    return M;   
}

// Frees heap memory associated with *pM, sets *pM to NULL.
void freeMatrix(Matrix* pM) {
    if (pM != NULL && *pM != NULL) {
        for (int i = 1; i <= (*pM)->size; i += 1){
            if (length((*pM)->array[i]) > 0) {
                for(moveFront((*pM)->array[i]); index((*pM)->array[i]) >= 0; moveNext((*pM)->array[i])) {
                    free(get((*pM)->array[i]));
                }
            }
            freeList(&(*pM)->array[i]);
        }
        free((*pM)->array);
        free(*pM);
        *pM = NULL;
    }
}   

// Access functions -----------------------------------------------------------

// Return the size of square Matrix M.
int size(Matrix M) {
    return M->size;
}

// Return the number of non-zero elements in M.
int NNZ(Matrix M) {
    return M->NNZ;
}

// Return true (1) if matrices A and B are equal, false (0) otherwise.
int equals (Matrix A, Matrix B) {
    if (A->size != B->size || A->NNZ != B->NNZ) {
        return false;
    } else {
        for (int i = 1; i <= A->size; i += 1) {
            if (length(A->array[i]) == length(B->array[i])) {
                moveFront(A->array[i]);
                moveFront(B->array[i]);
                while(index(A->array[i]) >= 0) {
                    Entry x = get(A->array[i]);
                    Entry y = get(B->array[i]);
                    if (x->col != y->col && x->val != y->val) {
                        return false;
                    } 
                    moveNext(A->array[i]);
                    moveNext(B->array[i]);
                }
            } else {
                return false;
            }

        }
        return true;
    }
}

// Manipulation procedures ----------------------------------------------------

// Re-sets M to the zero Matrix state.
void makeZero(Matrix M) {
    if (M == NULL) {
        printf("Matrix Error: calling makeZero on NULL Matrix reference\n");
        freeMatrix(&M);
        exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= M->size; i += 1) {
        if (length(M->array[i]) > 0) {
            for (moveFront(M->array[i]); index(M->array[i]) >= 0; moveNext(M->array[i])) {
                free(get(M->array[i]));
            }
            clear(M->array[i]);
        }
    }
    M->NNZ = 0;
}


// Changes the ith row, jth column of M to the value x.
// Pre: 1<=i<=size(M), 1<=j<=size(M)
void changeEntry(Matrix M, int i, int j, double x) {
    if (M == NULL) {
        printf("Matrix Error: calling changeEntry on NULL Matrix reference\n");
        freeMatrix(&M);
        exit(EXIT_FAILURE);
    }
    if (i >= 1 && i <= M->size && j >= 1 && j <= M->size) {
        Entry E = newEntry(j, x);
        if (length(M->array[i]) == 0 && x != 0) {
            append(M->array[i], E);
            M->NNZ += 1;
        } else if (x == 0) {
            if (length(M->array[i]) > 0) {
                for (moveFront(M->array[i]); index(M->array[i]) >= 0; moveNext(M->array[i])) {
                    Entry k = get(M->array[i]);
                    if (k->col == j) {
                        free(get(M->array[i]));
                        delete(M->array[i]);
                        M->NNZ = M->NNZ - 1;
                    }
                }
            }
            free(E);
        } else {
            bool exists = false;
            if (length(M->array[i]) > 0) {
                for (moveFront(M->array[i]); index(M->array[i]) >= 0; moveNext(M->array[i])) {
                    Entry check = get(M->array[i]);
                    if (check->col == j && check->val != x) {
                        check->val = x;
                        exists = true;
                    }
                    if (check->col == j && check->val == x) {
                        free(E);
                        exists = true;
                    }
                }
            }
            if (exists == false) {
                moveBack(M->array[i]);
                Entry k = get(M->array[i]);
                while(j < k->col) {
                    movePrev(M->array[i]);
                    if (index(M->array[i]) == -1) {
                        prepend(M->array[i], E);
                        break;
                    }
                    k = get(M->array[i]);
                }
                if (index(M->array[i]) >= 0) {
                    insertAfter(M->array[i], E);
                }
                M->NNZ += 1;
            }
        }
    }
}


// helper functions -------------------------------------------------------------

//computes the vector dot product of two lists
double vectorDot(List P, List Q) {
    double sum = 0;
    if (length(P) == 0 || length(Q) == 0) {
        return sum;
    }
    moveFront(P);
    moveFront(Q);
    while (index(P) >= 0 && index(Q) >= 0) {
        Entry one = get(P);
        Entry two = get(Q);
        if (one->col == two->col) {
            sum += one->val * two->val;
            moveNext(P);
            moveNext(Q);
        }
        if (one->col < two->col) {
            moveNext(P);
        }
        if (one->col > two->col) {
            moveNext(Q);
        }
    }
    return sum;
}

//computes the sum of two lists and returns a new list
List listsum(List A, List B) {
    List new = newList();
    if (length(A) == 0 && length(B) > 0) {
        for (moveFront(B); index(B) >= 0; moveNext(B)) {
            Entry k = get(B);
            Entry l = newEntry(k->col, k->val);
            append(new, l);
        }
        return new;
    }
    if (length(A) > 0 && length(B) == 0) {
        for (moveFront(A); index(A) >= 0; moveNext(A)) {
            Entry k = get(A);
            Entry l = newEntry(k->col, k->val);
            append(new, l); 
        }
        return new;
    }
    if (length(A) == 0 && length(B) == 0) {
        return new;
    }
    moveFront(A);
    moveFront(B);
    bool Abool = false;
    bool Bbool = false;
    while (true) {
        Entry k = NULL;
        Entry l = NULL;
        Entry E = NULL;
        if (index(A) >= 0) {
            k = get(A);
            Abool = true;
        } else {
            Abool = false;
        }
        if (index(B) >= 0) {
            l = get(B);
            Bbool = true;
        } else {
            Bbool = false;
        }

        if (Abool == true && Bbool == true) {
            if (k->col == l->col) {
                double newval = k->val + l->val;
                E  = newEntry(k->col, newval);
                append(new, E);
                moveNext(A);
                moveNext(B);
            }
            if (k->col < l->col) {
                E = newEntry(k->col, k->val);
                append(new, E);
                moveNext(A);
            }
            if (k->col > l->col) {
                E = newEntry(l->col, l->val);
                append(new, E);
                moveNext(B);
            }
        }
        if (Abool == false && Bbool == true) {
            E = newEntry(l->col, l->val);
            append(new, E);
            moveNext(B);
        }
        if (Abool == true && Bbool == false) {
            E = newEntry(k->col, k->val);
            append(new, E);
            moveNext(A);
        }
        if (Abool == false && Bbool == false) {
            break;
        }
    }
    return new;
}

//computes the difference of two lists and returns a new list
List listdiff(List A, List B) {
    List new = newList();
    if (length(A) == 0 && length(B) > 0) {
        for (moveFront(B); index(B) >= 0; moveNext(B)) {
            Entry k = get(B);
            Entry l = newEntry(k->col, 0 - k->val);
            append(new, l);
        }
        return new;
    }
    if (length(A) > 0 && length(B) == 0) {
        for (moveFront(A); index(A) >= 0; moveNext(A)) {
            Entry k = get(A);
            Entry l = newEntry(k->col, k->val);
            append(new, l); 
        }
        return new;
    }
    if (length(A) == 0 && length(B) == 0) {
        return new;
    }
    moveFront(A);
    moveFront(B);
    bool Abool = false;
    bool Bbool = false;
    while (true) {
        Entry k = NULL;
        Entry l = NULL;
        Entry E = NULL;
        if (index(A) >= 0) {
            k = get(A);
            Abool = true;
        } else {
            Abool = false;
        }
        if (index(B) >= 0) {
            l = get(B);
            Bbool = true;
        } else {
            Bbool = false;
        }

        if (Abool == true && Bbool == true) {
            if (k->col == l->col) {
                double newval = k->val - l->val;
                E  = newEntry(k->col, newval);
                append(new, E);
                moveNext(A);
                moveNext(B);
            }
            if (k->col < l->col) {
                E = newEntry(k->col, k->val);
                append(new, E);
                moveNext(A);
            }
            if (k->col > l->col) {
                E = newEntry(l->col, 0 - l->val);
                append(new, E);
                moveNext(B);
            }
        }
        if (Abool == false && Bbool == true) {
            double newval = 0 - l->val;
            E = newEntry(l->col, newval);
            append(new, E);
            moveNext(B);
        }
        if (Abool == true && Bbool == false) {
            E = newEntry(k->col, k->val);
            append(new, E);
            moveNext(A);
        }
        if (Abool == false && Bbool == false) {
            break;
        }
    }
    return new;
}


// Matrix Arithemtic Operations -------------------------------------------------

// Returns a reference to a new Matrix object having the same entries as A.
Matrix copy(Matrix A) {
    Matrix copy = newMatrix(A->size);
    for (int i = 1; i <= A->size; i += 1) {
        if (length(A->array[i]) > 0) {
            moveFront(A->array[i]);
            while (index(A->array[i]) >= 0) {
                Entry x = get(A->array[i]);
                changeEntry(copy, i, x->col, x->val);
                moveNext(A->array[i]);
            }
        }
    }
    return copy;
}


// Returns a reference to a new Matrix object representing the transpose
// of A.
Matrix transpose(Matrix A) {
    Matrix tran = newMatrix(A->size);
    for (int i = 1; i <= A->size; i += 1) {
        if (length(A->array[i]) > 0) {
            moveFront(A->array[i]);
            while (index(A->array[i]) >= 0){
                Entry x = get(A->array[i]);
                changeEntry(tran, x->col, i, x->val);
                moveNext(A->array[i]);
            }
        }
    }
    return tran;
}

// Returns a reference to a new Matrix object representing xA.
Matrix scalarMult(double x, Matrix A) {
    Matrix new = newMatrix(A->size);
    for (int i = 1; i <= A->size; i += 1) {
        if (length(A->array[i]) > 0) {
            moveFront(A->array[i]);
            while (index(A->array[i]) >= 0) {
                Entry y = get(A->array[i]);
                double newval = x * y->val;
                changeEntry(new, i, y->col, newval);
                moveNext(A->array[i]);
            }
        }
    }
    return new;
}

// Returns a reference to a new Matrix object representing A+B.
// pre: size(A)==size(B)
Matrix sum(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        printf("Matrix Error: Matrix are not of the same same\n");
        freeMatrix(&A);
        freeMatrix(&B);
        exit(EXIT_FAILURE);
    } else {
        Matrix check = copy(B);
        Matrix new = newMatrix(A->size);
        List sum = NULL;
        for (int i = 1; i <= A->size; i += 1) {
            sum = listsum(A->array[i], check->array[i]);
            if (length(sum) > 0) {
                moveFront(sum);
                while(index(sum) >= 0) {
                    Entry x = get(sum);
                    changeEntry(new, i, x->col, x->val);
                    free(get(sum));
                    moveNext(sum);
                }
            }
            freeList(&sum);
        }
        freeMatrix(&check);
        return new;
    }
}


// Returns a reference to a new Matrix object representing A-B.
// pre: size(A)==size(B)
Matrix diff(Matrix A, Matrix B) {
    if (size(A) != size(B)) {
        printf("Matrix Error: Matrix are not of the same same\n");
        freeMatrix(&A);
        freeMatrix(&B);
        exit(EXIT_FAILURE);
    } else {
        Matrix new = newMatrix(A->size);
        Matrix check = copy(B);
        List diff = NULL;
        for (int i = 1; i <= A->size; i += 1) {
            diff = listdiff(A->array[i], check->array[i]);
            if (length(diff) != 0) {
                moveFront(diff);
                while(index(diff) >= 0) {
                    Entry x = get(diff);
                    changeEntry(new, i, x->col, x->val);
                    free(get(diff));
                    moveNext(diff);
                }
            }
            freeList(&diff);
        }
        freeMatrix(&check);
        return new;
    }
}


// Returns a reference to a new Matrix object representing AB
// pre: size(A)==size(B)
Matrix product(Matrix A, Matrix B) {
    if (A->size == B->size) {
        Matrix new = newMatrix(B->size);
        Matrix transpo = transpose(B);
        for (int i = 1; i <= B->size; i += 1) {
            for (int y = 1; y <= B->size; y +=1) {
                double product = vectorDot(A->array[i], transpo->array[y]);
                changeEntry(new, i, y, product);
            }
        }
        freeMatrix(&transpo);
        return new;
    } else {
        printf("Matrix Error: Matrix fails preconditions\n");
        freeMatrix(&A);
        freeMatrix(&B);
        exit(EXIT_FAILURE);
    }
}

// Prints a string representation of Matrix M to filestream out. Zero rows
// are not printed. Each non-zero row is represented as one line consisting
// of the row number, followed by a colon, a space, then a space separated
// list of pairs "(col, val)" giving the column numbers and non-zero values
// in that row. The double val will be rounded to 1 decimal point.
void printMatrix(FILE* out, Matrix M) {
    if (M == NULL) {
        printf("Matrix Error: calling makeZero on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (NNZ(M) == 0) {
        return;
    }
    for (int i = 1; i <= M->size; i += 1) {
        Entry x;
        if (length(M->array[i]) > 0) {
            fprintf(out, "%d: ", i);
            for (moveFront(M->array[i]); index(M->array[i]) >= 0; moveNext(M->array[i])) {
                x = get(M->array[i]); 
                if (x->val != 0) {
                    fprintf(out, "(%d, %1.1f) ", x->col, x->val);
                }
            }
            fprintf(out, "\n");
        }
    }
}