#include "cardgame.h"

int main(int argc, char **argv){
  Deck *d = malloc(sizeof(Deck));

  /* Initialize the deck of 52 cards in order */
  deck_init(d);
  puts("Before shuffling:");
  deck_display(d);

  /* Shuffle the deck */
  deck_shuffle(d);

  puts("After shuffling:");
  deck_display(d);
}
