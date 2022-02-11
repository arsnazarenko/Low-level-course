# использование функций написанных на ассемблере через C

CFLAGS     = -g -O2 -Wall -Werror -std=c17 -Wdiscarded-qualifiers -Wincompatible-pointer-types -Wint-conversion
CC         = gcc
ASM        = nasm
ASMFLAGS   =-felf64 -g

hello: hello.o string.o
	gcc -o $@ $^

hello.o: hello.c
	$(CC) -c $(CFLAGS) -o $@ $<

string.o: string.asm
	$(ASM) $(ASMFLAGS) -o $@ $<


clean: 
	rm hello hello.o string.o

.PHONY: clean

