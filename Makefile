# Automatically generate lists of sources using wildcards.
C_SOURCES = $(wildcard kernel/*.c drivers/*.c lib/*.c)
ASM_SOURCES= $(wildcard kernel/*.asm)
HEADERS = $(wildcard include/*.h include/drivers/*.h)
OBJS = ${C_SOURCES:.c=.o}
OBJS += ${ASM_SOURCES:.asm=.o}
ARCH = 32
CFLAGS = -std=c99 -Wall -Wextra -m${ARCH} -ffreestanding

# Defaul build target
all : os-image.img

# Run bochs to simulate booting of our code.
run : all
		bochs

# This is the actual disk image that the computer loads
# which is the combination of our compiled bootsector and kernel
os-image.img : boot/boot_sector.bin kernel.bin
	cat $^ > os-image
	dd if=os-image of=os-image.img bs=512 conv=sync

# This builds the binary of the kernel from two OBJSect files :
# 	- the kernel_entry,which jumps to main() in the kernel
# 	- the compiled C kernel
kernel.bin : kernel/kernel_entry.o ${OBJS}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

# Generic rule for compiling C code to an OBJSect file
%.o : %.c
	gcc ${CFLAGS} -I./include -I./include/dirvers -c $< -o $@

# Generic rule for compiling assembly code to an OBJSect file
%.o : %.asm
	nasm $< -f elf -o $@

# Generic rule for compiling assembly code to an binary file
%.bin : %.asm
	nasm $< -f bin -I./boot/ -o $@

.PHONY : clean
clean :
		rm -rf *.bin *.dis *.o os-image os-image.img
		rm -rf kernel/*.o boot/*.bin drivers/*.o lib/*.o