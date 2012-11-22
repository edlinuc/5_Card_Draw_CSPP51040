#include<stdio.h>
#include<stdlib.h>

#include "stack.h"

main(){
  int i;
  int *x;
  int *top;

  int n = 10;
  x = (int *) malloc(n*sizeof(int));

  for (i=0;i<n;++i)
    x[i] = i;

  top = (int *) malloc(sizeof(int));

  Stack *stack = (Stack *) malloc(sizeof(Stack));
  stack_init(stack,NULL);
  stack_push(stack, &x[0]);
  stack_push(stack, &x[1]);
  stack_push(stack, &x[2]);
  top =  (int *)stack_peek(stack);
  printf("top of stack: %d\n", *top);
  stack_pop(stack,(void **) &top);
  printf("top of stack: %d\n", *top);
  stack_pop(stack,(void **) &top);
  printf("top of stack: %d\n", *top);
  stack_push(stack, &x[n-1]);
}
