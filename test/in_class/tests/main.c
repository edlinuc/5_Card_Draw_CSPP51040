#include<stdio.h>
#include<stdlib.h>

#include "list.h"

int main(int argc, char **argv){
  ListElmt *node;
  int *xx = (int *) malloc(sizeof(int));
  int *x = (int *) malloc(sizeof(int));
  int *y = (int *) malloc(sizeof(int));
  int *z = (int *) malloc(sizeof(int));
  /* create a list */
  List *list = (List *) malloc(sizeof(List));
  /* too lazy for now to pass destroy */
  list_init(list,NULL);
  *x = 10;
  node = NULL;
  list_ins_next(list,node,x);
  *y = 100;
  node = list_head(list);
  list_ins_next(list,node, y);
  *z = 1000;
  node = node->next;
  list_ins_next(list,node, z);
  list_rem_next(list,list_head(list),(const void **) &xx);
  printf("the value returned from remove: %d\n", *xx);
}
