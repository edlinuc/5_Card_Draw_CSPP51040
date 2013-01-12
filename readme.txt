Homework 4 - Shuoyuan(Edward) Lin

Notes for grader:
-- AI players make their choices based on the MC advisor.
-- The game implements the linear scale of hand value.
-- The game lets players to bet on each round, the AI players will place bet based on the hand value they have. Some randomness included here.
-- God mode will show information of each players as well as the expected value for every possible way to exchange the hand as the game goes on.
-- I used a string to represent the choice players make to exchange cards.(i.e. 135 means to exchange cards #1, #3 and #5, 0 for exchange nothing).
-- I used a queue to represent the deck of card. To exchange a card, I simple pass the pointer to the card to the dequeue function. The card that is dequeued will replace the old card automatically.
-- I used Knuth shuffle to shuffle the deck.

TO Andrew, Kyle and John,
THANK YOU FOR ALL YOUR HARD WORK THIS THE QUARTER!!
Shuoyuan Lin
