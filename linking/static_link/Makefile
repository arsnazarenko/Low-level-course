ASM=nasm
ASMFLAGS=-f elf64
LD=ld

all: symb

st_lib.o: st_lib.asm
	$(ASM) $(ASMFLAGS) -o st_lib.o st_lib.asm

symb.o: symb.asm
	$(ASM) $(ASMFLAGS) -o symb.o symb.asm

symb: symb.o st_lib.o
	$(LD) -o symb symb.o st_lib.o

clean:
	rm -rf st_lib.o symb.o symb
