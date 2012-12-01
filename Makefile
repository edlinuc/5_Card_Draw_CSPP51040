main: queue.o list.o main.o cardgame.o
	gcc -Wall -ansi -pedantic -o main main.o queue.o cardgame.o list.o 

queue.o: queue.c queue.h list.o
	gcc -Wall -ansi -pedantic -c queue.c -I. -I./linked_list

main.o: main.c cardgame.h
	gcc -Wall -ansi -pedantic -c main.c -I. -I./linked_list

list.o: ./linked_list/list.c ./linked_list/list.h
	gcc -Wall -ansi -pedantic -c ./linked_list/list.c -I./linked_list

cardgame.o: cardgame.c cardgame.h
	gcc -Wall -ansi -pedantic -c cardgame.c -I.

clean:
	\rm -f *.o main *~
