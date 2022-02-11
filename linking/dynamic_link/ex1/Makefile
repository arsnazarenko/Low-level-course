# before run executable you must do: export LD_LIBRARY_PATH=.

all: main


# -shared -> .so
#-fpic -> position independent code
lib.so: lib.c
	gcc -g -shared lib.c -o lib.so -fpic


#   -c param means that gcc run without linker
main.o: main.c
	gcc -g -c main.c -o main.o

main: lib.so main.o
	gcc -g  main.o lib.so -o main

clean:
	rm lib.so main main.o
