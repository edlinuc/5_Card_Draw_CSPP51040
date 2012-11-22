#include "cardgame.h"

int main(int argc, char **argv){
  Deck *d = malloc(sizeof(Deck));
  deck_init(d);
  deck_display(d);
}
