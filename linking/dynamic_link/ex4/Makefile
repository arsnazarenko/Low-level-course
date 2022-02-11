# before run executable you must do: export LD_LIBRARY_PATH=.

all: main

lib.o: lib.asm
	nasm -f elf64 -o lib.o lib.asm
main.o: main.asm
	nasm -f elf64 -o main.o main.asm
lib.so: lib.o
	ld -shared lib.o -o lib.so
main: lib.so main.o
	ld --dynamic-linker=/lib64/ld-linux-x86-64.so.2 main.o lib.so -o main
clean:
	rm -rf lib.o lib.so lib.o main.o main
