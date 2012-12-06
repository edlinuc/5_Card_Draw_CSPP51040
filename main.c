#include "cardgame.h"
#include <stdio.h>

int main(int argc, char **argv){
  int winner,godmode,firstgame = 1;
  char c = ' ';
  char *name = malloc(50);
  Deck *d = malloc(sizeof(Deck));
  Player p[4];
  welcome(firstgame);
  while((c = getchar()) != 'q'){
    switch(c){
    case '1':
      godmode = 0;
      break;
    case '2':
      godmode = 1;
      break;
    }
    if(firstgame){
      printf("Please enter your name: ");
      scanf("%s",name);
      firstgame = 0;      
    }
      printf("\n");
      printf("********************************************************************************\n");

      /* Initialize the deck of 52 cards in order */
      printf("Creating deck..\n");
      deck_init(d);
      /* Initialize four players */
      printf("Creating players...\n");
      players_init(p,name);

      if(godmode == 1){      
	puts("Deck before shuffling:");
	deck_display(d);
      }
      printf("\n");

      /* Shuffle the deck */
      printf("Shuffling deck...\n");
      deck_shuffle(d);
      
      if(godmode == 1){
	puts("Deck after shuffling:");
	deck_display(d);
      }
      printf("\n");


      printf("Dealing cards to players...\n\n");
      deck_deal(d, p);

      /*
      p->hand->cards[0]->rank = 12;
      p->hand->cards[0]->suit = 2;
      p->hand->cards[1]->rank = 11;
      p->hand->cards[1]->suit = 1;
      p->hand->cards[2]->rank = 10;
      p->hand->cards[2]->suit = 1;
      p->hand->cards[3]->rank = 9;
      p->hand->cards[3]->suit = 1;
      p->hand->cards[4]->rank = 8;
      p->hand->cards[4]->suit = 1;
      */      

      prompt_for_exchange(p, d, godmode);
      printf("********************************************************************************\n");
      winner = check_winner(p);
      if(winner == 0){
	printf("You won!\n");
      }
      else{
	printf("You lost, winner is player %d.", winner);
	printf("\n");
      }
      printf("********************************************************************************\n");
      getchar();
      /*printf("1. Enter next round in regular game mode.\n2. Enter next round in god mode.\nq. quit the game.\n");*/
      welcome(firstgame);
  }
  return 0;
}
