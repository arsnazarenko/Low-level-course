all: test_main

test_main.o: test_main.asm
	nasm -f elf64 test_main.asm -o test_main.o

test_main: test_main.o
	ld test_main.o -o test_main

clean:
	rm -rf test_main test_main.o
