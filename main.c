#include "cardgame.h"
#include <stdio.h>

int main(int argc, char **argv){
  int winner,godmode,firstgame = 1,chip,bet_sum,iteration, round = 1;
  char c = ' ';
  char *name = malloc(50);
  Deck *d = malloc(sizeof(Deck));
  Player p[4];
  welcome(firstgame,p,&round);
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

      printf("Please enter the number of iteration for the Monte-Carlo advisor(100000 recommended): ");
      scanf("%d",&iteration);

      printf("Please enter the initial chips for each player(1000 recommended): ");
      scanf("%d",&chip);

      /* Initialize four players */
      printf("Creating players...\n");
      players_init(p,name, chip);
      firstgame = 0;   
    }
      printf("\n");
      printf("********************************************************************************\n");

      /* Initialize the deck of 52 cards in order */
      printf("Creating deck..\n");
      deck_init(d);

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

      /*For testing, the below block will give the live player a royal flush */
      /*
      p->hand->cards[0]->rank = 12;
      p->hand->cards[0]->suit = 1;
      p->hand->cards[1]->rank = 11;
      p->hand->cards[1]->suit = 1;
      p->hand->cards[2]->rank = 10;
      p->hand->cards[2]->suit = 1;
      p->hand->cards[3]->rank = 9;
      p->hand->cards[3]->suit = 1;
      p->hand->cards[4]->rank = 8;
      p->hand->cards[4]->suit = 1;
      */

      bet_sum = 0;
      bet_sum = prompt_for_exchange(p, d, godmode,iteration);
      printf("********************************************************************************\n");
      winner = check_winner(p);
      if(winner == 0){
	printf("You won!\n");
	p->chip += bet_sum;
      }
      else{
	if(!p->fold)
	  printf("You lost. ");
	printf("winner was player %d.", winner);
	printf("\n");
	(p+winner)->chip += bet_sum;
      }
      printf("********************************************************************************\n");
      getchar();

      welcome(firstgame,p,&round);
  }
  printf("Bye!\n");
  return 0;
}
