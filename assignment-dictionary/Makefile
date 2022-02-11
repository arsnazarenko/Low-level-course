ASM=nasm
ASMFLAGS=-f elf64
LD=ld
OBJECTS = $(patsubst %.asm,%.o,$(wildcard *.asm))

all: main

%.o: %.asm
	$(ASM) $(ASMFLAGS) $^ -o $@

main: $(OBJECTS)
	$(LD) $^ -o $@

clean:
	rm -rf *.o main

.PHONY: clean
