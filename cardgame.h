#include "queue.h"

typedef Queue Deck;

typedef enum suit_ {
  SPADES, HEARTS, DIAMONDS, CLUBS
} Suit;

typedef struct card_ {
  int rank;
  Suit suit;
} Card;

typedef struct hand_ {
  Card *cards[5];
} Hand;

typedef struct player_ {
  char *name;
  int isAI;
  Hand *hand;
} Player;

void welcome();

void deck_init(Deck *deck);
void deck_shuffle(Deck *deck);
void deck_deal(Deck *deck, Player *player);
void deck_display(Deck *deck);

void hand_value(Hand *hand);

void card_print(int suit, int rank);

void players_init(Player *player,char *name);
void player_display(Player *player);

void exchange_card(Card **card, Deck *deck);
void prompt_for_exchange(Player *players,Deck *d);
void check_winner(Player *players);
void suggest(Hand *hand);
