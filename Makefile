all:
	nasm -f bin boot.asm -o boot.bin

	qemu-system-x86_64 -drive format=raw,file=boot.bin
	
fs:
	qemu-system-x86_64 boot.bin -full-screen

disam:
	nasm -f bin boot.asm -o boot.bin
	ndisasm boot.bin > debug/boot.txt