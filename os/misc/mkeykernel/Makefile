all:
	nasm -f elf32 kernel.asm -o kasm.o
	i386-elf-gcc -m32 -c kernel.c -o kc.o
	i386-elf-ld -m elf_i386 -T link.ld -o kernel kasm.o kc.o
	rm *.o
	/Users/nick/qemu-2.9.1/i386-softmmu/qemu-system-i386 -kernel kernel


