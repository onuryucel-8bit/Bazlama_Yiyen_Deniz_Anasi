all:
	nasm -f bin boot/boot.asm -o bin/boot.bin

	nasm -f elf boot/kernel_entry.asm -o bin/kernel_entry.o

	i686-elf-gcc -m32 -ffreestanding -c kernel/kernel.c -o bin/kernel.o

	i686-elf-ld -T linker.ld -o out/kernel.bin bin/kernel_entry.o bin/kernel.o --oformat binary

	copy /b bin\boot.bin + out\kernel.bin out\os.img

	qemu-system-x86_64 -drive format=raw,file=out/os.img
	
fs:
	qemu-system-x86_64 bin/os.bin -full-screen

disam:
	nasm -f bin boot/boot.asm -o bin/boot.bin
	ndisasm bin/boot.bin > debug/boot.txt