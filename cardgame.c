#include <time.h>
#include "cardgame.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
void swap(char** a, char** b, int szblob);
void KnuthShuffle(void** arr, int size, int szblob);
int intcmp(const void *v1, const void *v2);

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
void players_init(Player *player, char *name,int chip){
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

    /* give every player initial chips */
    player[i].chip = chip;
    player[i].alive = 1;
    player[i].fold = 0;
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

/* Display the hand of a player */
void player_display(Player *player){
  int i;
  for(i = 0; i < 5; ++i){
    card_print((player->hand->cards)[i]->suit, (player->hand->cards)[i]->rank);
  }
  printf("\n");
}

/*Display a hand */
void hand_display(Hand *hand){
  int i;
  char *class_s = malloc(20*sizeof(char));

  switch(hand->class){
  case 1:
    class_s = "High card";
    break;
  case 2:
    class_s = "One pair";
    break;
  case 3:
    class_s = "Two pair";
    break;
  case 4:
    class_s = "Three of a kind";
    break;
  case 5:
    class_s = "Straight";
    break;
  case 6:
    class_s = "Flush";
    break;
  case 7:
    class_s = "Full house";
    break;
  case 8:
    class_s = "Four of a kind";
    break;
  case 9:
    class_s = "Straight flush";
    break;
  case 10:
    class_s = "Royal flush";
    break;
  }

  for(i = 0; i < 5; ++i){
    card_print((hand->cards)[i]->suit, (hand->cards)[i]->rank);
  }
  printf("[%s]",class_s);
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


void welcome(int firstgame,Player *p){
  int i;
  if(firstgame){
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
  }else{
    for(i = 0; i < 4; ++i){
      if((p+i)->alive){
	printf("%s's remaining chip: %d.\n",(p+i)->name, (p+i)->chip);
      }
      (p+i)->fold = 0;
      if((p+i)->chip == 0){
	(p+i)->alive = 0;
	if(i == 0){
	  printf("You have used all your chips, come back later, BYE!\n");
	  exit(0);
	}
      }
    }
  }
  printf("\n1: Start new round\n");
  printf("2: Start new round(god mode) -- Deck and other players' card visible\n");
  printf("q: Quit\n");
}


/* Discard the card and replace it with another card from the deck */
void exchange_card(Card **card, Deck *deck){
  queue_dequeue(deck, (void**)card);
}


/* This function prompts the players including AI players for exchanging the cards */
int prompt_for_exchange(Player *players, Deck *d, int godmode, int iteration){
  int i, bet, bet_sum, cur_bet = 0;
  char *choice;

  /* choice is represented with a string of maximal length 5 */
  choice = malloc(6*sizeof(char));
  bet_sum = 0;
  /* first deals with AI players */
  for(i = 0; i < 4; ++i){
    if((players+i)->isAI == 1){
      printf("%s is thinking...\n",(players+i)->name);

      if(godmode == 1){
	printf("%s's cards before exchanging:",(players+i)->name);
	player_display(players+i);	
      }


      choice = MC((players+i)->hand,godmode,iteration);
      printf("\n%s decides to exchange card %s \n",(players+i)->name,choice);
      parse_exchange(choice, (players+i)->hand, d);

      if(godmode == 1){
	printf("%s's cards after exchanging:",(players+i)->name);
	player_display(players+i);
      }
      printf("\n");


      bet = hand_value((players+i)->hand) + rand() % 10 + i * 10;

      /* small chance of doubling */
      if(rand() % 13 == 0)
	bet *= 2;

      /* if the bet is greater than the remaining chips for the player */
      if(bet <= (players+i)->chip && bet >= cur_bet){
	cur_bet = bet;
	(players+i)->chip -= bet;
	printf("[%s is betting %d on his/her hand.]\n\n", (players+i)->name, bet);
      }
      else if(bet > (players+i)->chip && (players+i)->chip >= cur_bet){
	bet = (players+i)->chip;
	cur_bet = bet;
	printf("[%s is betting %d on his/her hand.]\n\n", (players+i)->name, bet);
      }
      else{
	printf("[%s folds.]\n\n",(players+i)->name);
	(players+i)->fold = 1;
	bet = 0;
      }

      bet_sum += bet;

    }
  }

  /* prompt for exchange for the live player */
  printf("********************************************************************************\n");
  printf("   Your current hand:\n   ");
  player_display(players);
  printf("********************************************************************************\n");
  choice = MC(players->hand,godmode,iteration);
  printf("\nMC simulator suggest exchanging card %s\n\n",choice);

  printf("%s, please enter the card you want to exchange\n(e.g. To exchange the first card, enter 1; To exchange the second and the fifth card, enter 25;\nIf you do not want to exchange any card, enter 0):",(players)->name);
  scanf("%s",choice);
  if(strcmp(choice,"0") != 0){
    parse_exchange(choice, players->hand, d);
    printf("Your hand after exchanging:\n");
    player_display(players);
    printf("\n");
  }
  else{
    printf("No card exchanged for %s.\n",players->name);
  }
  hand_value((players)->hand);
  printf("Current highest bet: %d.\nPlease enter the amount you want to bet. (Enter 0 to fold)\n",cur_bet);
  scanf("%d",&bet);
  while( (bet > (players)->chip || bet < cur_bet) && bet != 0 ){
    if(bet > (players)->chip)
      printf("You current chip is %d, you do not have enough chip, try again with a smaller amount.\n",players->chip);
    else
      printf("Please enter a number bigger than the current bet(%d).\n",cur_bet);
    scanf("%d",&bet);
  }
  if(bet == 0)
    players->fold = 1;
  players->chip -= bet;
  bet_sum += bet;
  cur_bet = bet;
  return bet_sum;
}

void parse_exchange(char *choice, Hand *hand, Deck *deck){
  int j;
  for(j = 0; j < strlen(choice); ++j){
    exchange_card(&(hand->cards[choice[j]-'0'-1]),deck);
  }
}

int check_winner(Player *p){
  int i,max = -1,winner = -1;
  float value;
  printf("Checking for winner...\n");
  for(i = 0; i < 4; ++i){
    /*    value = hand_value((p+i)->hand);*/
    if(!((p+i)->fold)){
      value = (p+i)->hand->value;
      if(value > max){
	max = value;
	winner = i;	  
      }
      if(i == 0){
	printf("Your hand:");
	hand_display(p->hand);
      }
      else{
	printf("Player %d's hand: ",i);
	hand_display((p+i)->hand);
      }
    }
  }
  return winner;
}

int hand_value(Hand *hand){
  int value, rank, class = -1, i, j, contiguous = 0,max = 0;
  int num_suits[4] = {0};
  int num_ranks[13] = {0};
  int rank_arr[5];
  /* sort the hand by rank */
  for(i = 0; i < 5; ++i){
    rank_arr[i] = hand->cards[i]->rank;
  }
  qsort(rank_arr, 5, sizeof(int),intcmp);

  /* find the number of each suit */
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
    if(hand->cards[i]->rank>max)
      max = hand->cards[i]->rank;
  }

  /* Set rank to be the biggest card in the hand */
  rank = max;

  /* Check if the hand is contiguous */
  contiguous = 1;
  for(j = 0; j < 4; ++j){
    if(rank_arr[j] != rank_arr[j+1] + 1)
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

  hand->value = value;
  hand->class = class;
  hand->rank = rank;
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

int intcmp(const void *v1, const void *v2)
{
  return (*(int *)v2 - *(int *)v1);
}

char* MC(Hand *hand, int godmode, int iteration){
  int suit_tmp, rank_tmp, i,j,k,l,m,sum,maxi,redraw, suit_tmp2, rank_tmp2, suit_tmp3, rank_tmp3, suit_tmp4, rank_tmp4, suit_tmp5, rank_tmp5;
  float result[10000] = {0.0}, max, exp_all;
  char *choice = malloc(10*sizeof(char));

  /* Handle the case of swapping 1 cards */  
  for(i = 0; i < 5; ++i){
    sum = 0;
    suit_tmp = hand->cards[i]->suit;
    rank_tmp = hand->cards[i]->rank;

    for(j = 0; j < iteration; ++j){

      if(j%100 == 0 || j == iteration - 1 ){
	printf("MC running %d times for exchanging card %d. %7.2f%% Completed", iteration, i+1, (float)j/(iteration-1)*100);
	printf("\r");
      }
      /* for each card we randomly generated, check whether it is the same as one of the card that
	 is already in the hand, if yes, discard the card and redraw another card until we have 
	 something different than the other cards */

      do{      
	hand->cards[i]->suit = rand() % 4;
	hand->cards[i]->rank = rand() % 13;
	
	redraw = 0;


	if((rank_tmp == hand->cards[i]->rank && suit_tmp == hand->cards[i]->suit) || 
	   check_duplication(hand) == 1){
	  redraw = 1;
	}
      }while(redraw != 0);

      sum += hand_value(hand);


    }
    hand->cards[i]->suit = suit_tmp;
    hand->cards[i]->rank = rank_tmp;

    if(godmode)
    printf("Expected hand value for exchanging card %d: %5.2f                          \n",i+1,(float)sum/iteration);
    result[i+1] = (float)sum/iteration;
  }


  /* Handle the case of swapping 2 cards */  
  for(i = 0; i < 5; ++i){
    suit_tmp = hand->cards[i]->suit;
    rank_tmp = hand->cards[i]->rank;

    for(j = i+1; j < 5; ++j){
      sum = 0;
      
      suit_tmp2 = hand->cards[j]->suit;
      rank_tmp2 = hand->cards[j]->rank;
      
      for(k = 0; k < iteration; ++k){

	if(k%100 == 0 || k == iteration - 1 ){
	  printf("MC running %d times for exchanging card %d, %d. %7.2f%% Completed", iteration, i+1, j+1, (float)k/(iteration-1)*100);
	  printf("\r");
	}
	
	do{
	  redraw = 0;
	  hand->cards[i]->suit = rand() % 4;
	  hand->cards[i]->rank = rand() % 13;
	  
	  if((rank_tmp == hand->cards[i]->rank && suit_tmp == hand->cards[i]->suit) || 
	     check_duplication(hand) == 1){
	    
	    redraw = 1;
	  }
	}while(redraw != 0);
	
	
	do{
	  redraw = 0;
	  hand->cards[j]->suit = rand() % 4;
	  hand->cards[j]->rank = rand() % 13;
	  
	  if((rank_tmp2 == hand->cards[j]->rank && suit_tmp2 == hand->cards[j]->suit) || 
	     check_duplication(hand) == 1){

	    redraw = 1;
	  }
	}while(redraw != 0);
	
	sum += hand_value(hand);
	
      }

      hand->cards[i]->suit = suit_tmp;
      hand->cards[i]->rank = rank_tmp;
      hand->cards[j]->suit = suit_tmp2;
      hand->cards[j]->rank = rank_tmp2;

      if(godmode)
      printf("Expected hand value for exchanging card %d,%d: %5.2f                          \n",i+1,j+1,(float)sum/iteration);
      result[(i+1)*10+(j+1)] = (float)sum/iteration;
    }
  }
  

  /* Handle the case of swapping 3 cards */  
  for(i = 0; i < 5; ++i){
    suit_tmp = hand->cards[i]->suit;
    rank_tmp = hand->cards[i]->rank;

    for(j = i+1; j < 5; ++j){
      
      
      suit_tmp2 = hand->cards[j]->suit;
      rank_tmp2 = hand->cards[j]->rank;
		  	      

      
      for(l = j+1; l < 5; ++l){

	suit_tmp3 = hand->cards[l]->suit;
	rank_tmp3 = hand->cards[l]->rank;

	sum = 0;
	for(k = 0; k < iteration; ++k){

	  if(k%100 == 0 || k == iteration - 1 ){
	    printf("MC running %d times for exchanging card %d, %d, %d. %7.2f%% Completed", iteration, i+1, j+1, l+1, (float)k/(iteration-1)*100);
	    printf("\r");
	  }

	  do{
	    redraw = 0;
	    hand->cards[i]->suit = rand() % 4;
	    hand->cards[i]->rank = rand() % 13;
	    
	    if((rank_tmp == hand->cards[i]->rank && suit_tmp == hand->cards[i]->suit) || 
	       check_duplication(hand) == 1){
	      
	      redraw = 1;
	    }
	  }while(redraw != 0);
	  
	  
	  do{
	    redraw = 0;
	    hand->cards[j]->suit = rand() % 4;
	    hand->cards[j]->rank = rand() % 13;
	    
	    if((rank_tmp2 == hand->cards[j]->rank && suit_tmp2 == hand->cards[j]->suit) || 
	       check_duplication(hand) == 1){
	      
	      redraw = 1;
	    }
	  }while(redraw != 0);


	  do{
	    redraw = 0;
	    hand->cards[l]->suit = rand() % 4;
	    hand->cards[l]->rank = rand() % 13;
	    
	    if((rank_tmp3 == hand->cards[l]->rank && suit_tmp3 == hand->cards[l]->suit) || 
	       check_duplication(hand) == 1){
	      redraw = 1;
	    }
	  }while(redraw != 0);
	  
	  sum += hand_value(hand);
	  
	}
	hand->cards[i]->suit = suit_tmp;
	hand->cards[i]->rank = rank_tmp;
	
	hand->cards[j]->suit = suit_tmp2;
	hand->cards[j]->rank = rank_tmp2;
	
	hand->cards[l]->suit = suit_tmp3;
	hand->cards[l]->rank = rank_tmp3;
	if(godmode)
	printf("Expected hand value for exchanging card %d,%d,%d: %5.2f                          \n",i+1,j+1,l+1,(float)sum/iteration);
	result[(i+1)*100+(j+1)*10+(l+1)] = (float)sum/iteration;

      }
    }
  }

  /* Handle the case of swapping 4 cards */  
  for(i = 0; i < 5; ++i){
    suit_tmp = hand->cards[i]->suit;
    rank_tmp = hand->cards[i]->rank;

    for(j = i+1; j < 5; ++j){
      
      suit_tmp2 = hand->cards[j]->suit;
      rank_tmp2 = hand->cards[j]->rank;
		  	      
      for(l = j+1; l < 5; ++l){

	suit_tmp3 = hand->cards[l]->suit;
	rank_tmp3 = hand->cards[l]->rank;

	for(m = l+1; m < 5; ++m){

	  suit_tmp4 = hand->cards[m]->suit;
	  rank_tmp4 = hand->cards[m]->rank;

	  sum = 0;
	  for(k = 0; k < iteration; ++k){
	    if(k%100 == 0 || k == iteration - 1 ){
	      printf("MC running %d times for exchanging card %d, %d, %d, %d. %7.2f%% Completed", iteration, i+1, j+1, l+1, m+1, (float)k/(iteration-1)*100);
	      printf("\r");
	    }

	    do{
	      redraw = 0;
	      hand->cards[i]->suit = rand() % 4;
	      hand->cards[i]->rank = rand() % 13;
	      
	      if((rank_tmp == hand->cards[i]->rank && suit_tmp == hand->cards[i]->suit) || 
		 check_duplication(hand) == 1){
		
		redraw = 1;
	      }
	    }while(redraw != 0);
	    
	    
	    do{
	      redraw = 0;
	      hand->cards[j]->suit = rand() % 4;
	      hand->cards[j]->rank = rand() % 13;
	      
	      if((rank_tmp2 == hand->cards[j]->rank && suit_tmp2 == hand->cards[j]->suit) || 
		 check_duplication(hand) == 1){
		
		redraw = 1;
	      }
	    }while(redraw != 0);
	    
	    
	    do{
	      redraw = 0;
	      hand->cards[l]->suit = rand() % 4;
	      hand->cards[l]->rank = rand() % 13;
	      
	      if((rank_tmp3 == hand->cards[l]->rank && suit_tmp3 == hand->cards[l]->suit) || 
		 check_duplication(hand) == 1){
		redraw = 1;
	      }
	    }while(redraw != 0);

	    do{
	      redraw = 0;
	      hand->cards[m]->suit = rand() % 4;
	      hand->cards[m]->rank = rand() % 13;
	      
	      if((rank_tmp4 == hand->cards[m]->rank && suit_tmp4 == hand->cards[m]->suit) || 
		 check_duplication(hand) == 1){
		redraw = 1;
	      }
	    }while(redraw != 0);
	    
	    sum += hand_value(hand);
	    
	  }
	  
	  hand->cards[i]->suit = suit_tmp;
	  hand->cards[i]->rank = rank_tmp;
	  
	  hand->cards[j]->suit = suit_tmp2;
	  hand->cards[j]->rank = rank_tmp2;
	  
	  hand->cards[l]->suit = suit_tmp3;
	  hand->cards[l]->rank = rank_tmp3;

	  hand->cards[m]->suit = suit_tmp4;
	  hand->cards[m]->rank = rank_tmp4;
	  if(godmode)
	    printf("Expected hand value for exchanging card %d,%d,%d,%d: %5.2f                          \n",i+1,j+1,l+1,m+1,(float)sum/iteration);
	  result[(i+1)*1000+(j+1)*100+(l+1)*10+(m+1)] = (float)sum/iteration;
	}
      }
    }
  }
  
/* Handle the case of swapping 5 cards */  


    suit_tmp = hand->cards[0]->suit;
    rank_tmp = hand->cards[0]->rank;

    suit_tmp2 = hand->cards[1]->suit;
    rank_tmp2 = hand->cards[1]->rank;
    
    suit_tmp3 = hand->cards[2]->suit;
    rank_tmp3 = hand->cards[2]->rank;
    
    suit_tmp4 = hand->cards[3]->suit;
    rank_tmp4 = hand->cards[3]->rank;

    suit_tmp5 = hand->cards[4]->suit;
    rank_tmp5 = hand->cards[4]->rank;
    
    sum = 0;
    for(k = 0; k < iteration; ++k){
      if(k%100 == 0 || k == iteration - 1 ){
	printf("MC running %d times for exchanging all 5 cards(1,2,3,4,5). %7.2f%% Completed", iteration, (float)k/(iteration-1)*100);
	printf("\r");
      }


      do{
	redraw = 0;
	hand->cards[0]->suit = rand() % 4;
	hand->cards[0]->rank = rand() % 13;
	
	if((rank_tmp == hand->cards[0]->rank && suit_tmp == hand->cards[0]->suit) || 
	   check_duplication(hand) == 1){
	  
	  redraw = 1;
	}
      }while(redraw != 0);
      
      
      do{
	redraw = 0;
	hand->cards[1]->suit = rand() % 4;
	hand->cards[1]->rank = rand() % 13;
	
	if((rank_tmp2 == hand->cards[1]->rank && suit_tmp2 == hand->cards[1]->suit) || 
	   check_duplication(hand) == 1){
	  
	  redraw = 1;
	}
      }while(redraw != 0);
      
      
      do{
	redraw = 0;
	hand->cards[2]->suit = rand() % 4;
	hand->cards[2]->rank = rand() % 13;
	
	if((rank_tmp3 == hand->cards[2]->rank && suit_tmp3 == hand->cards[2]->suit) || 
	   check_duplication(hand) == 1){
	  redraw = 1;
	}
      }while(redraw != 0);
      
      do{
	redraw = 0;
	hand->cards[3]->suit = rand() % 4;
	hand->cards[3]->rank = rand() % 13;
	
	if((rank_tmp4 == hand->cards[3]->rank && suit_tmp4 == hand->cards[3]->suit) || 
	   check_duplication(hand) == 1){
	  redraw = 1;
	}
      }while(redraw != 0);
    
      do{
	redraw = 0;
	hand->cards[4]->suit = rand() % 4;
	hand->cards[4]->rank = rand() % 13;
	
	if((rank_tmp4 == hand->cards[4]->rank && suit_tmp4 == hand->cards[4]->suit) || 
	   check_duplication(hand) == 1){
	  redraw = 1;
	}
      }while(redraw != 0);
      
      sum += hand_value(hand);
      
    }
    
    hand->cards[0]->suit = suit_tmp;
    hand->cards[0]->rank = rank_tmp;
	  
    hand->cards[1]->suit = suit_tmp2;
    hand->cards[1]->rank = rank_tmp2;
    
    hand->cards[2]->suit = suit_tmp3;
    hand->cards[2]->rank = rank_tmp3;
    
    hand->cards[3]->suit = suit_tmp4;
    hand->cards[3]->rank = rank_tmp4;

    hand->cards[4]->suit = suit_tmp5;
    hand->cards[4]->rank = rank_tmp5;
    if(godmode)   
      printf("Expected hand value for exchanging ALL cards: %5.2f                                  \n",(float)sum/iteration);
    exp_all = (float)sum/iteration;


  

    for(i = 0, max = 0; i < 10000; ++i){
      if(result[i] > max){
	max = result[i];
	maxi = i;
      }
    }
    if(max < exp_all){
      max = exp_all;
      maxi = 12345;
    }
    
    sprintf(choice, "%d", maxi);
    return choice;
}


int check_duplication(Hand *hand){

  int i,j;
  for(i = 0; i < 5; ++i){
    for(j = i+1; j < 5; ++j){
      if(hand->cards[i]->rank == hand->cards[j]->rank && 
	 hand->cards[i]->suit == hand->cards[j]->suit){
	return 1;
      }
    }
  }
  return 0;
}
