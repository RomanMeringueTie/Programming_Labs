all: app

app: main.c lib.c strings.c
	gcc -Wall -g -O0 -o app main.c lib.c strings.c

.PHONY: run

run: app
	./app

.PHONY: clean

clean: app
	rm app