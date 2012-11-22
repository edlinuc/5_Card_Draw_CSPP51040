#include "cardgame.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void swap(char** a, char** b, int szblob);
void KnuthShuffle(void** arr, int size, int szblob);
/* This function initializes the deck of cards to 52.*/
void deck_init(Deck *deck){
  int i,j;
  deck->q = malloc(sizeof(Queue));
  queue_init(deck->q, NULL);

  /* Add 52 cards to the queue */
  for(j = 0; j < 4; ++j){
    for(i = 1; i < 14; ++i){
      Card *c = malloc(sizeof(Card));
      c->rank = i;
      c->suit = j;
      queue_enqueue(deck->q,(const void*)c);
    }
  }
}

/* This method shuffles the deck of card using Knuth's shuffle algorithm
   It does not require the deck to be of any particular number, in case
   the user wants to shuffle a deck that is not consists of 52 cards
*/
void deck_shuffle(Deck *deck){
  int i,size;
  Card *tmp[52];
  size = deck->q->size;
  for(i = 0; i < size; ++i){
    queue_dequeue(deck->q, (void**)&tmp[i]);
    printf("%d: %d %d\n",i,tmp[i]->suit,tmp[i]->rank);
  }
  KnuthShuffle((void**)&tmp, size, sizeof(Card));
  for(i = 0; i < size; ++i){
    queue_enqueue(deck->q, (const void*)tmp[i]);
  }
}

void KnuthShuffle(void** arr, int size, int szblob){
  int r,i;
  srand(time(NULL));
  for(i = size-1; i >= 0; --i){
    r = rand() % (i+1);
    swap( (char**)arr + i, (char**)arr + r, szblob);
    }
}

void swap(char** a, char** b, int szblob){ 
  char *tmp = *a;
  *a = *b;
  *b = tmp;
  /*char* tmp = malloc(szblob);
  memcpy(tmp, a, szblob);
  memcpy(a, b, szblob);
  memcpy(b, tmp, szblob);
  free(tmp);*/
}

/* This function displays the current deck of cards in order.
   I implemented using a temp queue that stores the cards
   as they are removed from the origin queue and enqueue them
   again after displaying all the cards.
*/
void deck_display(Deck *deck){
  int i;
  Queue *tmp = malloc(sizeof(Queue));
  Card *c = malloc(sizeof(Card));
  queue_init(tmp,NULL);
  for(i = 0; i < deck->q->size;){
    queue_dequeue(deck->q, (void**)&c);
    printf("(%d %d) ", c->suit, c->rank);
    queue_enqueue(tmp, (const void*)c);
  }

  /* Move the cards back from the temp queue */
  for(i = 0; i < tmp->size;){
    queue_dequeue(tmp, (void**)&c);
    queue_enqueue(deck->q, (const void*)c);
  }
  free(c);
}
/*
int main(){
  int a[] = {1, 2, 3, 4, 5};

  KnuthShuffle((void*)a, 5, sizeof(int));

  printf("%d %d %d %d %d",a[0],a[1],a[2],a[3],a[4]);
}
*/
