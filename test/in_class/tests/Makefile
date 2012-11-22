main : main.o ../linked_list/list.o 
	gcc -o main main.o ../linked_list/list.o
main.o : main.c ../linked_list/list.h
	gcc -c main.c -I../linked_list
../linked_list/list.o : ../linked_list/list.c
	gcc -c ../linked_list/list.c -I../linked_list
clean :
	\rm -f *.o *~ *# main