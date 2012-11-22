#include "cardgame.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void swap(char* a, char* b, int szblob);
void KnuthShuffle(void* arr, int size, int szblob);

void deck_init(Deck *deck){
  deck->q = malloc(sizeof(Queue));
  queue_init(deck->q, NULL);
  deck->size = 52;
  Card *c = malloc(sizeof(Card));
  //*c = {1, HEARTS};
  c->rank = 2;
  c->suit = SPADES;
  queue_enqueue(deck->q,(const void*)c);
}

/* This method shuffles the deck of card using Knuth's shuffle algorithm
   It does not require the deck to be of any particular number */
void deck_shuffle(Deck *deck){
  int i;
  Card tmp[52];
  for(i = 0; i < deck->size; ++i){
    //tmp[i] = (Card*)queue_dequeue(deck)
    queue_dequeue((void*)deck, (void**)&tmp[i]);
  }
  KnuthShuffle((void*)deck, deck->size, sizeof(Card));
}

void deck_display(Deck *deck){
  Card *c = malloc(sizeof(Card));
  printf("Before: %d, %d\n",c->rank,c->suit);
  queue_dequeue((void*)deck->q, (void**)&c);
  printf("%d, %d\n",c->rank,c->suit);
}

void KnuthShuffle(void* arr, int size, int szblob){
  int r,i;
  for(i = size-1; i >= 0; --i){
    srand(time(NULL));
    r = rand() % (i+1);
    printf("r = %d\n", r);
    swap( ((char*)arr) + i * szblob, ((char*)arr) + r * szblob, szblob);
  }
}

void swap(char* a, char* b, int szblob){
  /*char *tmp = a;
  a = b;
  b = tmp;*/
  char* tmp = malloc(szblob);
  memcpy(tmp, a, szblob);
  memcpy(a, b, szblob);
  memcpy(b, tmp, szblob);
  free(tmp);
}
/*
int main(){
  int a[] = {1, 2, 3, 4, 5};

  KnuthShuffle((void*)a, 5, sizeof(int));

  printf("%d %d %d %d %d",a[0],a[1],a[2],a[3],a[4]);
}
*/
