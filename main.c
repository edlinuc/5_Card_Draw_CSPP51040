#include "cardgame.h"
#include <stdio.h>

int main(int argc, char **argv){
  int i;
  char c = ' ';
  char *name = malloc(50);
  Deck *d = malloc(sizeof(Deck));
  Player p[4];
  welcome();
  while((c = getchar()) != 'q'){
    switch(c){
    case '2':
      printf("Please enter your name: ");
      scanf("%s",name);

      /* Initialize the deck of 52 cards in order */
      deck_init(d);
      /* Initialize four players */
      players_init(p,name);
      
      puts("Deck before shuffling:");
      deck_display(d);
      printf("\n");

      /* Shuffle the deck */
      deck_shuffle(d);
      
      puts("Deck after shuffling:");
      deck_display(d);
      printf("\n");

      printf("Dealing cards to players...\n\n");
      deck_deal(d, p);
      /*
      player_display(&p[0]);
      exchange_card(&(p->hand->cards[0]),d);
      player_display(&p[0]);*/

      prompt_for_exchange(p, d);


      break;
    }
  }
}
