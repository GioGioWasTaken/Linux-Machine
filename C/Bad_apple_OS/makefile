all: bootloader kernel bootdisk

bootloader:
	nasm -f bin bootloader.asm -o bootloader.o

kernel:
	nasm -f bin kernel.asm -o kernel.o

bootdisk:
	dd if=/dev/zero of=disk.img bs=512 count=2880
	dd conv=notrunc if=bootloader.o of=disk.img bs=512 count=1 seek=0
	dd conv=notrunc if=kernel.o of=disk.img bs=512 count=1 seek=1


clean:
	rm bootloader.o kernel.o disk.img
