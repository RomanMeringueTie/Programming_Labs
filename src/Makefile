all: app

app: main.o IntVector.o
	gcc -Wall -o app IntVector.o main.o
main.o: main.c
	gcc -Wall -c -o main.o main.c
IntVector.o: IntVector.c
	gcc -Wall -c -o IntVector.o IntVector.c