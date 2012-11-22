#include<stdlib.h>
#include<stdio.h>

#include "queue.h"
void *destroy(void *data);
int main(){
  int *x;
  Queue *queue;
  queue = (Queue *) malloc(sizeof(Queue));
  queue_init(queue,NULL);
  x = malloc(1);
  *x = 100;
  queue_enqueue(queue, (const void *) x);
  x = malloc(1);
  *x = 200;
  queue_enqueue(queue, (const void *) x);
  x = malloc(1);
  *x = 300;
  queue_enqueue(queue, (const void *) x);
  queue_dequeue(queue, (void **) &x);
  printf("head: %d\n", *x);
  queue_dequeue(queue, (void **) &x);
  printf("head: %d\n", *x);
  printf("size before destroy: %d\n", queue_size(queue));
  queue_destroy(queue);
  printf("size after destroy: %d\n", queue_size(queue));
}

void *destroy(void *data){
  free(data);
}

