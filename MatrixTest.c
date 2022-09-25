//-----------------------------------------------------------------------------
// Abhay Singh, abrsingh
// 2022 Spring CSE101 PA#4
// MatrixTest.c 
// A test client for the Matrix ADT
//-----------------------------------------------------------------------------
#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"Matrix.h"
     
int main(){
   int n=10;
   Matrix A = newMatrix(n);
   Matrix B = newMatrix(n);
   Matrix C, D, E, F, G, H;

   changeEntry(A, 1,1,100); 
   changeEntry(B, 1,1,900);
   changeEntry(A, 1,2,198); 
   changeEntry(B, 1,2,0);
   changeEntry(A, 1,3,450); 
   changeEntry(B, 1,3,1);
   changeEntry(A, 2,1,420); 
   changeEntry(B, 2,1,10);
   changeEntry(A, 2,2,795); 
   changeEntry(A, 2,3,640); 
   changeEntry(B, 2,3,90);
   changeEntry(A, 3,1,75); 
   changeEntry(B, 3,1,150);
   changeEntry(A, 3,2,80); 
   changeEntry(A, 3,3,93); 
   changeEntry(B, 3,3,197);


   printf("%d\n", NNZ(A));
   printf("%d\n", size(A));
   printMatrix(stdout, A);
   printf("\n");

   printf("%d\n", NNZ(B));
   printf("%d\n", size(A));
   printMatrix(stdout, B);
   printf("\n");

   C = scalarMult(1.5, A);
   printf("%d\n", size(A));
   printf("%d\n", NNZ(C));
   printMatrix(stdout, C);
   printf("\n");

   D = sum(A, B);
   printf("%d\n", NNZ(D));
   printf("%d\n", size(A));
   printMatrix(stdout, D);
   printf("\n");

   E = diff(A, A);
   printf("%d\n", NNZ(E));
   printf("%d\n", size(A));
   printMatrix(stdout, E);
   printf("\n");

   F = transpose(B);
   printf("%d\n", NNZ(F));
   printf("%d\n", size(A));
   printMatrix(stdout, F);
   printf("\n");

   G = product(B, B);
   printf("%d\n", NNZ(G));
   printf("%d\n", size(A));
   printMatrix(stdout, G);
   printf("\n");

   H = copy(A);
   printf("%d\n", NNZ(H));
   printf("%d\n", size(A));
   printMatrix(stdout, H);
   printf("\n");

   printf("%s\n", equals(A, G)?"true":"false" );
   printf("%s\n", equals(F, H)?"true":"false" );
   printf("%s\n", equals(A, A)?"true":"false" );
   printf("%s\n", equals(E, B)?"true":"false" );

   makeZero(A);
   printf("%d\n", NNZ(A));
   printf("%d\n", size(A));
   printMatrix(stdout, A);

   makeZero(B);
   printf("%d\n", NNZ(B));
   printf("%d\n", size(B));
   printMatrix(stdout, B);

   freeMatrix(&A);
   freeMatrix(&B);
   freeMatrix(&C);
   freeMatrix(&D);
   freeMatrix(&E);
   freeMatrix(&F);
   freeMatrix(&G);
   freeMatrix(&H);

   return EXIT_SUCCESS;
}

/*
Output of this program:
9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0)
3: (1, 1.0) (2, 1.0) (3, 1.0)

9
1: (1, 1.5) (2, 3.0) (3, 4.5)
2: (1, 6.0) (2, 7.5) (3, 9.0)
3: (1, 10.5) (2, 12.0) (3, 13.5)

9
1: (1, 2.0) (2, 2.0) (3, 4.0)
2: (1, 4.0) (2, 6.0) (3, 6.0)
3: (1, 8.0) (2, 9.0) (3, 10.0)

0

6
1: (1, 1.0) (3, 1.0)
2: (2, 1.0) (3, 1.0)
3: (1, 1.0) (3, 1.0)

7
1: (1, 2.0) (2, 1.0) (3, 2.0)
2: (2, 1.0)
3: (1, 2.0) (2, 2.0) (3, 2.0)

9
1: (1, 1.0) (2, 2.0) (3, 3.0)
2: (1, 4.0) (2, 5.0) (3, 6.0)
3: (1, 7.0) (2, 8.0) (3, 9.0)

true
false
true
0
*/
