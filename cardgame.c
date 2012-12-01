#include <time.h>
#include "cardgame.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void swap(char** a, char** b, int szblob);
void KnuthShuffle(void** arr, int size, int szblob);


/* This function initializes the deck of cards to 52.*/
void deck_init(Deck *deck){
  int i,j;
  queue_init(deck, NULL);

  /* Add 52 cards to the queue */
  for(j = 0; j < 4; ++j){
    for(i = 0; i < 13; ++i){
      Card *c = malloc(sizeof(Card));
      c->rank = i;
      c->suit = j;
      queue_enqueue(deck,(const void*)c);
    }
  }
}

/* Initialize the four players */
void players_init(Player *player, char *name){
  int i,j;
  for(i = 0; i < 4; ++i){
    /* AI player, generate names for them */
    if(i != 0){
      char *s = malloc(50);
      sprintf(s, "Player %d",i);
      player[i].name = s;
      player[i].isAI = 1;
    }
    /* Human player */
    else{
      player[i].name = name;
      player[i].isAI = 0;
    }

    /* Initiazlize the space for store poker hand for each player */
    player[i].hand = malloc(sizeof(Hand));
    for(j = 0; j < 5; ++j){
      *((player[i].hand)->cards+j) = malloc(sizeof(Card));
    }
  }
}

/* 
   This method shuffles the deck of card using Knuth's shuffle algorithm
   It does not require the deck to be of any particular number, in case
   the user wants to shuffle a deck that is not consists of 52 cards
*/
void deck_shuffle(Deck *deck){
  int i,size;
  Card *tmp[52];
  size = deck->size;

  /* put all the card to an array in order to use KnuthShuffle */
  for(i = 0; i < size; ++i){
    queue_dequeue(deck, (void**)&tmp[i]);
    /*list_print(deck->q);
    printf("%d: %d %d\n",i,tmp[i]->suit,tmp[i]->rank);*/
  }
  
  /* apply KnuthShuffle on the array */
  KnuthShuffle((void**)&tmp, size, sizeof(Card));
  
  /* put the shuffled cards back to the deck */
  for(i = 0; i < size; ++i){
    queue_enqueue(deck, (const void*)tmp[i]);
  }
}

/* Shuffle algorithm by Knuth */
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
}

/*
   This function deals five cards to each player in the game.
*/

void deck_deal(Deck *deck, Player *player){
  int i,j;
  for(i = 0; i < 4; ++i){
    for(j = 0; j < 5; ++j){
      queue_dequeue(deck,  (void**)&((player+i)->hand->cards[j]));
    }
  }
}

/* 
   This function displays the current deck of cards in order.
   I implemented using a temp queue that stores the cards
   as they are removed from the origin queue and enqueue them
   again after displaying all the cards.
*/
void deck_display(Deck *deck){
  int padding = 0;
  Deck *tmp = malloc(sizeof(Deck));
  Card *c = malloc(sizeof(Card));
  queue_init(tmp,NULL);
  while(deck->size > 0){
    if(padding % 13 == 0){
      printf("\n");
    }
    padding++;
    queue_dequeue(deck, (void**)&c);
    card_print(c->suit, c->rank);
    queue_enqueue(tmp, (const void*)c);
  }
  printf("\n");
  /* Move the cards back from the temp queue */
  while(tmp->size > 0){
    queue_dequeue(tmp, (void**)&c);
    queue_enqueue(deck, (const void*)c);
  }
  free(tmp);
}

void player_display(Player *player){
  int i;
  for(i = 0; i < 5; ++i){
    card_print((player->hand->cards)[i]->suit, (player->hand->cards)[i]->rank);
  }
  printf("\n");
}

void card_print(int suit, int rank){
  char *suit_s = malloc(10*sizeof(char));
  char rank_c;
  /* Turn the suit into human-readable form */
  switch(suit){
  case 0:
    suit_s = "Spades";
    break;
  case 1:
    suit_s = "Hearts";
    break;
  case 2:
    suit_s = "Diamonds";
    break;
  case 3:
    suit_s = "Clubs";
    break;
  }

  /* Turn the rank into human-readable form */
  switch(rank){
  case 12:
    rank_c = 'A';
    break;
  case 11:
    rank_c = 'K';
    break;
  case 10:
    rank_c = 'Q';
    break;
  case 9:
    rank_c = 'J';
    break;
  default:
    rank_c = rank + 2 + '0';
  }

  /* deals wit the special case where rank is two character long (10) */
  if(rank == 8)
    printf("(%s 10) ", suit_s);
  else
    printf("(%s %c) ", suit_s, rank_c);
}


void welcome(){
  printf("\n");
  printf("                    ___                                  ___      \n");
  printf("                   /  /\\      ___           ___         /  /\\     \n");
  printf("                  /  /:/_    /  /\\         /__/\\       /  /:/_    \n");
  printf("                 /  /:/ /\\  /  /:/         \\  \\:\\     /  /:/ /\\   \n");
  printf("                /  /:/ /:/ /__/::\\          \\  \\:\\   /  /:/ /:/_  \n");
  printf("               /__/:/ /:/  \\__\\/\\:\\__   ___  \\__\\:\\ /__/:/ /:/ /\\ \n");
  printf("               \\  \\:\\/:/      \\  \\:\\/\\ /__/\\ |  |:| \\  \\:\\/:/ /:/ \n");
  printf("                \\  \\::/        \\__\\::/ \\  \\:\\|  |:|  \\  \\::/ /:/  \n");
  printf("                 \\  \\:\\        /__/:/   \\  \\:\\__|:|   \\  \\:\\/:/   \n");
  printf("                  \\  \\:\\       \\__\\/     \\__\\::::/     \\  \\::/    \n");
  printf("                   \\__\\/                     ~~~~       \\__\\/     \n");
  printf("                  ___           ___           ___          _____     \n");
  printf("                 /  /\\         /  /\\         /  /\\        /  /::\\    \n");
  printf("                /  /:/        /  /::\\       /  /::\\      /  /:/\\:\\   \n");
  printf("               /  /:/        /  /:/\\:\\     /  /:/\\:\\    /  /:/  \\:\\  \n");
  printf("              /  /:/  ___   /  /:/~/::\\   /  /:/~/:/   /__/:/ \\__\\:| \n");
  printf("             /__/:/  /  /\\ /__/:/ /:/\\:\\ /__/:/ /:/___ \\  \\:\\ /  /:/ \n");
  printf("             \\  \\:\\ /  /:/ \\  \\:\\/:/__\\/ \\  \\:\\/:::::/  \\  \\:\\  /:/  \n");
  printf("              \\  \\:\\  /:/   \\  \\::/       \\  \\::/~~~~    \\  \\:\\/:/   \n");
  printf("               \\  \\:\\/:/     \\  \\:\\        \\  \\:\\         \\  \\::/    \n");
  printf("                \\  \\::/       \\  \\:\\        \\  \\:\\         \\__\\/     \n");
  printf("                 \\__\\/         \\__\\/         \\__\\/                   \n");
  printf("                 _____          ___           ___           ___      \n");
  printf("                /  /::\\        /  /\\         /  /\\         /__/\\     \n");
  printf("               /  /:/\\:\\      /  /::\\       /  /::\\       _\\_ \\:\\    \n");
  printf("              /  /:/  \\:\\    /  /:/\\:\\     /  /:/\\:\\     /__/\\ \\:\\   \n");
  printf("             /__/:/ \\__\\:|  /  /:/~/:/    /  /:/~/::\\   _\\_ \\:\\ \\:\\  \n");
  printf("             \\  \\:\\ /  /:/ /__/:/ /:/___ /__/:/ /:/\\:\\ /__/\\ \\:\\ \\:\\ \n");
  printf("              \\  \\:\\  /:/  \\  \\:\\/:::::/ \\  \\:\\/:/__\\/ \\  \\:\\ \\:\\/:/ \n");
  printf("               \\  \\:\\/:/    \\  \\::/~~~~   \\  \\::/       \\  \\:\\ \\::/  \n");
  printf("                \\  \\::/      \\  \\:\\        \\  \\:\\        \\  \\:\\/:/   \n");
  printf("                 \\__\\/        \\  \\:\\        \\  \\:\\        \\  \\::/    \n");
  printf("                               \\__\\/         \\__\\/         \\__\\/     \n");
  printf("                              Made by Shuoyuan Lin for CSPP51040. Nov, 2012\n");
  printf("Welcome to FIVE-CARD-DRAW\n");
  printf("1: Start new game\n");
  printf("2: Start new game(god mode) -- Deck and other players' card visible\n");
  printf("q: Quit\n");
}


/* Discard the card and replace it with another card from the deck */
void exchange_card(Card **card, Deck *deck){
  queue_dequeue(deck, (void**)card);
}


/* This function prompts the players including AI players for exchanging the cards */
void prompt_for_exchange(Player *players, Deck *d){
  int i,j;
  char *choice;

  /* choice is represented with a string of maximal length 5 */
  choice = malloc(6*sizeof(char));

  /* first deals with AI players */
  for(i = 0; i < 4; ++i){
    if((players+i)->isAI == 1){
      printf("%s is thinking...\n",(players+i)->name);
      player_display(players+i);
      exchange_card(&((players+i)->hand->cards[i]),d);
      player_display(players+i);
      printf("\n");
    }
  }

  /* prompt for exchange for the live player */
  printf("********************************************************************************\n");
  printf("   Your current hand:\n   ");
  player_display(players);
  printf("********************************************************************************\n");
  printf("%s, please enter the card you want to exchange\n(e.g. To exchange the first card, enter 1; To exchange the second and the fifth card, enter 25;\nIf you do not want to exchange any card, enter 0):",(players)->name);
  scanf("%s",choice);
  if(strcmp(choice,"0") != 0){
    for(j = 0; j < strlen(choice); ++j){
      exchange_card(&((players)->hand->cards[choice[j]-'0'-1]),d);
    }
    printf("Your hand after exchanging:\n");
    player_display(players);
    printf("\n");
  }
  else{
    printf("No card exchanged for %s.\n",players->name);
  }
}

int check_winner(Player *p){
  int i,value,max = -1,winner = -1;
  printf("Checking for winner...\n");
  for(i = 0; i < 4; ++i){
    value = hand_value((p+i)->hand);
    if(value > max){
      max = value;
      winner = i;	  
    }
    if(i == 0){
      printf("Your hand:");
      player_display(p);
    }
    else{
      printf("Player %d's hand: ",i);
      player_display(p+i);
    }
  }
  return winner;
}

int hand_value(Hand *hand){
  int value, rank, class = -1, i, j, contiguous = 0;
  int num_suits[4] = {0};
  int num_ranks[13] = {0};

  /* sort the hand by rank */
  qsort(hand->cards, 5, sizeof(Card),card_rank_cmp);

  for(i = 0; i < 5; ++i){
    if(hand->cards[i]->suit == SPADES){
      num_suits[SPADES]++;
    }
    if(hand->cards[i]->suit == HEARTS){
      num_suits[HEARTS]++;
    }
    if(hand->cards[i]->suit == DIAMONDS){
      num_suits[DIAMONDS]++;
    }
    if(hand->cards[i]->suit == CLUBS){
      num_suits[CLUBS]++;
    }
    /* CREATE A ARRAY OF 13 INT AND STORE THE OCCURANCE OF EACH RANK IN THE ARRAY */
    num_ranks[hand->cards[i]->rank]++;
  }

  /* Set rank to be the biggest card in the hand */
  rank = hand->cards[0]->rank;

  /* Check if the hand is contiguous */
  contiguous = 1;
  for(j = 0; j < 4; ++j){
    if(hand->cards[j]->rank != hand->cards[j+1]->rank + 1)
      contiguous = 0;
  }

  /* loop through the num_suits array to see whether all the cards are of the same suit */
  for(i = 0; i < 4; ++i){
    if(num_suits[i] == 5 && contiguous == 1){
      if(rank == 12)
	class = 10; /* 10 for royal flush */
      else
	class = 9; /* 9 for straight flush */
    }
  }

  /* check for four of a kind */
  if( class == -1 ){
    for(i = 0; i < 13; ++i){
      if( num_ranks[i] == 4){
	class = 8;
	rank = i;
      }
    }
  }

  /* check for full house */
  if( class == -1 ){
    int j ;
    for(i = 0; i < 13; ++i){
      if( num_ranks[i] == 3){
	for(j = i+1; j < 13; ++j){
	  if(num_ranks[j] == 2){
	    class = 7;
	    rank = i;
	  }
	}
      }
    }
  }

  /* check for flush */
  if( class == -1 ){
    for(i = 0; i < 4; ++i){
      if(num_suits[i] == 5){
	class = 6;
      }
    }
  }

  /* check for straight */
  if( class == -1 ){
    if(contiguous == 1)
      class = 5;
  }

  /* check for three of a kind */
  if( class == -1 ){
    for(i = 0; i < 13; ++i){
      if( num_ranks[i] == 3){
	class = 4;
	rank = i;
      }
    }
  }


  /* check for two pairs or one pair*/
  if( class == -1 ){
    int j;
    for(i = 0; i < 13; ++i){
      if( num_ranks[i] == 2){
	for(j = i+1; j < 13; ++j){
	  if(num_ranks[j] == 2){
	    class = 3;
	    rank = j;
	    break;
	  }
	}
	if(class == -1){
	  class = 2;
	  rank = i;	  
	}
      }
    }
  }

  if( class == -1 ){
    class = 1;
  }

  value = 13 * class + rank;
  /*printf("Class = %d, Rank = %d, value = %d\n",class, rank, value);*/
  hand->value = value;
  return value;
}

void suggest(Hand *hand);


/* compare function used by qsort based on the suit of the card */
int card_suit_cmp(const void *c1, const void *c2){
  Card *a = *(Card**)c1;
  Card *b = *(Card**)c2;
  if(a->suit > b->suit)
    return 1;
  else if(a->suit < b->suit)
    return -1;
  else
    return 0;
}

/* compare function used by qsort based on the rank of the card */
int card_rank_cmp(const void *c1, const void *c2){
  Card *a = *(Card**)c1;
  Card *b = *(Card**)c2;
  if(a->rank > b->rank)
    return -1;
  else if(a->rank < b->rank)
    return 1;
  else
    return 0;
}
