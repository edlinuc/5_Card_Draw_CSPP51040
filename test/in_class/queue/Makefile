main: queue.o list.o main.o
	gcc -o main main.o queue.o ../linked_list/list.o 

queue.o: queue.c queue.h
	gcc -c queue.c -I. -I../linked_list

main.o: main.c queue.h
	gcc -c main.c -I. -I../linked_list

list.o: ../linked_list/list.c ../linked_list/list.h
	gcc -c ../linked_list/list.c -I.

clean:
	\rm -f *.o main *~
