# Automatically generate lists of sources using wildcards.
C_SOURCES = $(wildcard kernel/*.c drivers/*.c lib/*.c)
HEADERS = $(wildcard include/*.h include/drivers/*.h)
ARCH = 32

# TODO : Make sources dep on all header files.
# 
# Convert the *.c filenames to *.o to give a list of object files to build
OBJ = ${C_SOURCES:.c=.o}

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

# This builds the binary of our kernel from two object files :
# 	- the kernel_entry,which jumps to main() in our kernel
# 	- the compiled C kernel
kernel.bin : kernel/kernel_entry.o ${OBJ}
	ld -m elf_i386 -o $@ -Ttext 0x1000 $^ --oformat binary

# Generic rule for compiling C code to an object file
# For simplicity , we C files depend on all header files .
%.o : %.c ${HEADERS}
	gcc -m${ARCH} -ffreestanding -I./include -c $< -o $@

# Assemble the kernel_entry.
%.o : %.asm
	nasm $< -f elf -o $@
	
%.bin : %.asm
	nasm $< -f bin -I 'boot/' -o $@

.PHONY : clean
clean :
		rm -rf *.bin *.dis *.o os-image os-image.img
		rm -rf kernel/*.o boot/*.bin drivers/*.o lib/*.o