# before run executable you must do: export LD_LIBRARY_PATH=.

all: main

SOME_FLAGS = -g -Wall -Wextra -std=c11 

lib2.so: lib2.c
	gcc $(SOME_FLAGS) -shared lib2.c -o lib2.so -fpic

main.o: main.c
	gcc $(SOME_FLAGS) -c main.c -o main.o

main: main.o lib2.so
	gcc $(SOME_FLAGS) main.o lib2.so -o main
clean:
	rm -rf main main.o lib2.so
