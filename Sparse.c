//-----------------------------------------------------------------------------
// Abhay Singh, abrsingh
// 2022 Spring CSE101 PA#4
// Sparce.c
// Implementation of the Matrix Arithemtic Program
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "Matrix.h"

int main(int argc, char* argv[]) {
    FILE *in, *out;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

    in = fopen(argv[1], "r");
    if (in == NULL) {
        fprintf(stderr, "Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }

    out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    char buffer[16384];

    int n = 0;
    int m1size = 0;
    int m2size = 0;

    fgets(buffer, 16384, in);
    sscanf(buffer, "%d %d %d", &n, &m1size, &m2size);

    Matrix A = newMatrix(n);
    Matrix B = newMatrix(n);

    fgets(buffer, 16384, in);

    int param1 = 0;
    int param2 = 0;
    double param3 = 0;

    for (int i = 1; i <= m1size; i += 1) {
        fgets(buffer, 16384, in);
        sscanf(buffer, "%d %d %lf", &param1, &param2, &param3);
        changeEntry(A, param1, param2, param3);
    }

    fgets(buffer, 16384, in);

    for (int i = 1; i <= m2size; i += 1) {
        fgets(buffer, 16384, in);
        sscanf(buffer, "%d %d %lf", &param1, &param2, &param3);
        changeEntry(B, param1, param2, param3);
    }

    fprintf(out, "A has %d non-zero entries: \n", NNZ(A));
    printMatrix(out, A);
    fprintf(out, "\n");

    fprintf(out, "B has %d non-zero entries: \n", NNZ(B));
    printMatrix(out, B);
    fprintf(out, "\n");

    Matrix C = scalarMult(1.5, A);
    fprintf(out, "(1.5)*A = \n");
    printMatrix(out, C);
    fprintf(out, "\n");

    Matrix D = sum(A, B);
    fprintf(out, "A+B = \n");
    printMatrix(out, D);
    fprintf(out, "\n");

    Matrix E = sum(A, A);
    fprintf(out, "A+A = \n");
    printMatrix(out, E);
    fprintf(out, "\n");

    Matrix F = diff(B, A);
    fprintf(out, "B-A = \n");
    printMatrix(out, F);
    fprintf(out, "\n");

    Matrix G = diff(A, A);
    fprintf(out, "A-A = \n");
    printMatrix(out, G);
    fprintf(out, "\n");

    Matrix H = transpose(A);
    fprintf(out, "Transpose(A) = \n");
    printMatrix(out, H);
    fprintf(out, "\n");

    Matrix I = product(A, B);
    fprintf(out, "A*B = \n");
    printMatrix(out, I);
    fprintf(out, "\n");

    Matrix J = product(B, B);
    fprintf(out, "B*B = \n");
    printMatrix(out, J);
    fprintf(out, "\n");

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);
   freeMatrix(&I);
   freeMatrix(&J);

   fclose(in);
   fclose(out);
}
