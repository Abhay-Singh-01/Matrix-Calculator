//-----------------------------------------------------------------------------
// Abhay Singh, abrsingh
// 2022 Spring CSE101 PA#4
// ListClient.c
// Test client for List ADT
//-----------------------------------------------------------------------------
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"List.h"

int main(int argc, char* argv[]){

   // My Tests ----------------------------------------------------------------------------------------

   List A = newList();
   List B = newList();
   int K[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
   int i;

   for(i=1; i<=7; i++){
      append(A, &K[i]);
      prepend(B, &K[i]);
   }

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

   moveBack(A);
   movePrev(A);
   movePrev(A);
   delete(A);
   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");

   moveFront(B);
   moveNext(B);
   moveNext(B);
   delete(B);
   for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveBack(B); index(B)>=0; movePrev(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

   deleteFront(A);
   deleteBack(B);

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");


   int a = 99;
   int b = 100;
   int c = 101;

   moveFront(A);
   set(A, &b);

   moveBack(B);
   set(B, &b);

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

   moveFront(A);
   insertBefore(A, &a);
   insertAfter(A, &c);

   moveBack(B);
   insertBefore(B, &a);
   insertAfter(B, &c);

   for(moveFront(A); index(A)>=0; moveNext(A)){
      printf("%d ", *(int*)get(A));
   }
   printf("\n");
   for(moveFront(B); index(B)>=0; moveNext(B)){
      printf("%d ", *(int*)get(B));
   }
   printf("\n");

   moveFront(A);
   printf("Length A: %d\n", length(A));
   printf("Index A: %d\n", index(A));
   printf("Front A: %d\n", *(int*)front(A));
   printf("Back A: %d\n", *(int*)back(A));
   clear(A);
   printf("Length A: %d\n", length(A));

   moveBack(B);
   printf("Length B: %d\n", length(B));
   printf("Index B: %d\n", index(B));
   printf("Front B: %d\n", *(int*)front(B));
   printf("Back B: %d\n", *(int*)back(B));
   clear(B);
   printf("Length B: %d\n", length(B));

   freeList(&A);
   freeList(&B);

   return(0);
}

/*
Output of this program:
1 2 3 4 5 6 7 
7 6 5 4 3 2 1 
1 2 3 4 6 7 
7 6 4 3 2 1 
1 2 3 4 6 7 
1 2 3 4 6 7 
2 3 4 6 7 
7 6 4 3 2 
100 3 4 6 7 
7 6 4 3 100 
99 100 101 3 4 6 7 
7 6 4 3 99 100 101 
Length A: 7
Index A: 0
Front A: 99
Back A: 7
Length A: 0
Length B: 7
Index B: 6
Front B: 7
Back B: 101
Length B: 0
*/