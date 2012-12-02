#include "cardgame.h"
#include <stdio.h>

int main(int argc, char **argv){
  int i,max = -1,value, winner;
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
      printf("\n");
      printf("********************************************************************************\n");

      /* Initialize the deck of 52 cards in order */
      printf("Creating deck..\n");
      deck_init(d);
      /* Initialize four players */
      printf("Creating players...\n");
      players_init(p,name);
      
      puts("Deck before shuffling:");
      deck_display(d);
      printf("\n");

      /* Shuffle the deck */
      printf("Shuffling deck...\n");
      deck_shuffle(d);
      
      puts("Deck after shuffling:");
      deck_display(d);
      printf("\n");

      printf("Dealing cards to players...\n\n");
      deck_deal(d, p);

      prompt_for_exchange(p, d);

      /*      
      This block is for testing hand value
      p->hand->cards[0]->rank = 11;
      p->hand->cards[0]->suit = 1;
      p->hand->cards[1]->rank = 13;
      p->hand->cards[1]->suit = 0;
      p->hand->cards[2]->rank = 3;
      p->hand->cards[2]->suit = 2;
      p->hand->cards[3]->rank = 7;
      p->hand->cards[3]->suit = 1;
      p->hand->cards[4]->rank = 10;
      p->hand->cards[4]->suit = 0;
      */
      winner = check_winner(p);
      if(winner == 0){
	printf("You won!\n");
      }
      else{
	printf("You lost, winner is player %d, his/her hand was:", winner);
	  player_display(&p[winner]);
      }
    }
  }
  return 0;
}
