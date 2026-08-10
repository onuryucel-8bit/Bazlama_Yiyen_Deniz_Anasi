FLAGS = -m32 -ffreestanding -c -I kernel

OBJ_FILES = \
	bin/kernel_entry.o \
	bin/kernel.o \
	bin/utils.o \
	bin/stdio.o \
	bin/portio.o \
	bin/idt.o \
	bin/idt_asm.o \
	bin/idtKey.o \
	bin/font.o \
	bin/stdlib.o
#	bin/vga.o

all:

	nasm -f elf boot/kernel_entry.asm -o bin/kernel_entry.o
	nasm -f elf kernel/idt/idt_asm.asm -o bin/idt_asm.o
#kabak cekirdegini derle
	i686-elf-gcc ${FLAGS} kernel/kernel.c -o bin/kernel.o

	@echo ======================================
	@echo =========Kutuphaneler=================
	@echo ======================================

#kutuphaneleri derle	
	i686-elf-gcc ${FLAGS} kernel/utils.c -o bin/utils.o
	i686-elf-gcc ${FLAGS} kernel/stdio.c -o bin/stdio.o
	i686-elf-gcc ${FLAGS} kernel/stdlib.c -o bin/stdlib.o
	i686-elf-gcc ${FLAGS} kernel/portio.c -o bin/portio.o

	i686-elf-gcc ${FLAGS} kernel/idt/idt.c -o bin/idt.o
	i686-elf-gcc ${FLAGS} kernel/idt/idtKey.c -o bin/idtKey.o
	i686-elf-gcc ${FLAGS} kernel/font/font.c -o bin/font.o
#i686-elf-gcc ${FLAGS} kernel/vga.c -o bin/vga.o

	@echo ==================================
	@echo ======LINKER======================
	@echo ==================================
	
#kabak cekirdegi ve diger dosyalari japon yapistirici ile birlestir
	i686-elf-ld -T linker.ld \
	-o out/kernel.bin \
	${OBJ_FILES} \
	--oformat binary

#sektor sayisini hesapla
	python boot/sektorHesaplayici.py

	@echo ========================================================
	@echo ============BOOTLOADER==================================
	@echo ========================================================
	nasm -f bin boot/boot.asm -o out/boot.bin
	@echo ========================================================
	
	@echo ========================================================
	@echo ============COPY========================================
	@echo ========================================================
#bootloader ile kabak cekirdeginin birlestir => os.img
	copy /b out\boot.bin + out\kernel.bin out\os.img
	
	@echo ========================================================
	@echo ============QEMU========================================
	@echo ========================================================
#calistir
	qemu-system-x86_64 -serial stdio -drive format=raw,file=out/os.img
	
	
fs:
#tam ekran calistir
	qemu-system-x86_64 -serial stdio out/os.img -full-screen

disam:
#bootloader disassembly ciktisi
	nasm -f bin boot/boot.asm -o bin/boot.bin
	ndisasm bin/boot.bin > debug/boot.txt

precomp:
	i686-elf-gcc ${FLAGS} -S kernel/kernel.c

#kel barkodlu temizlikci .o .bin temizler
ifeq ($(OS),Windows_NT)
    ObjKiller = del /Q
else
    ObjKiller = rm -f
endif

clean:
	$(ObjKiller) bin\*.o
	$(ObjKiller) bin\*.bin