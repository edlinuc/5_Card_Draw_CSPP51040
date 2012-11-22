#include "queue.h"

typedef enum suit_ {
  SPADES, HEARTS, DIAMONDS, CLUBS
} Suit;

typedef struct card_ {
  int rank;
  Suit suit;
} Card;

typedef struct hand_ {
  Card hand[5];
} Hand;

typedef struct deck_ {
  Queue *q;
} Deck;

typedef struct player_ {
  char *name;
  int isAI;
  Hand *hand;
} Player;

void deck_init(Deck *deck);
void deck_shuffle(Deck *deck);
void deck_deal(Deck *deck, Player *player);
void deck_display(Deck *deck);
