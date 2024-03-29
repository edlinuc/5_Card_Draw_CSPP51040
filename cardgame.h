#include "queue.h"

/* Typedef Deck as Queue */
typedef Queue Deck;

typedef enum suit_ {
  SPADES, HEARTS, DIAMONDS, CLUBS
} Suit;

typedef struct card_ {
  int rank;
  Suit suit;
} Card;

/* A hand has a array of pointer to its five cards
   and its value. */
typedef struct hand_ {
  Card *cards[5];
  int value;
  /* the defining rank of the hand */
  int rank;
  /* the class of the hand */
  int class;
} Hand;

typedef struct player_ {
  char *name;
  int isAI;
  Hand *hand;
  int chip;
  int alive;
  int fold;
} Player;

/* Display the welcome message */
void welcome(int firstgame,Player *p,int *round);

/* Initialize the deck in order. After this function,
   the deck will have all 52 cards in order. */
void deck_init(Deck *deck);
/* Shuffle the deck using Knuth Shuffle */
void deck_shuffle(Deck *deck);
/* Deal one card from the deck to the player */
void deck_deal(Deck *deck, Player *player);
/* Display the remaining deck of cards. */
void deck_display(Deck *deck);

/* Compute the hand value */
int hand_value(Hand *hand);
void hand_display(Hand *hand);
/* print a card */
void card_print(int suit, int rank);
/* compare functions used by qsort */
int card_suit_cmp(const void *c1, const void *c2);
int card_rank_cmp(const void *c1, const void *c2);

/* Initialize the players */
void players_init(Player *player,char *name, int chip);
/* Display a player's information */
void player_display(Player *player);

/* Exchange the card with a new card from the deck */
void exchange_card(Card **card, Deck *deck);

void parse_exchange(char *choice, Hand *hand, Deck *deck);
/* prompt for the player to exchange card(s) */
int prompt_for_exchange(Player *players,Deck *d,int godmode, int iteration);
/* Finds the winner based on their hand value */
int check_winner(Player *players);
int check_duplication(Hand *hand);
/* make suggestion on which card(s) to exchange*/
char* MC(Hand *hand,int godmode,int iteration);
