#include "cardgame.h"

int main(int argc, char **argv){
  Deck *d = malloc(sizeof(Deck));
  deck_init(d);
  puts("Before shuffling:");
  deck_display(d);
  puts("");
  deck_shuffle(d);
  puts("After shuffling:");
  deck_display(d);
}
