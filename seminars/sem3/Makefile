NASM = nasm
FLAGS = -felf64
LD=ld

%.o: %.asm
	$(NASM) $(FLAGS) $< -o $@

main: main.o
	$(LD) $< -o $@

clean:
	rm -rf main *.o
