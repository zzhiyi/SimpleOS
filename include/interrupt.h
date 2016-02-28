#ifndef INTERRUPT_H
#define INTERRUPT_H
#include <lowlevel.h>
#include <drivers/pic.h>
#include <drivers/screen.h>
struct interrupt_entry {
	unsigned short low;      // offset bits 0..15
	unsigned short selector; // a code segment selector in GDT or LDT
	unsigned char zero;      // unused, set to 0
	unsigned char type_attr; // type and attributes
	unsigned short high;     // offset bits 16..31
} __attribute__((packed));

struct interrupt_idtr {
	unsigned short size;
	struct interrupt_entry *idt;
} __attribute__((packed));

struct cpu_state {
	unsigned int eax;
	unsigned int ebx;
	unsigned int ecx;
	unsigned int edx;
	unsigned int edi;
	unsigned int esi;
	unsigned int ebp;
	unsigned int esp;
} __attribute__((packed));

struct stack_state {
	unsigned int error_code;
	unsigned int eip;
	unsigned int cs;
	unsigned int eflags;
} __attribute__((packed));

void set_handler(struct interrupt_entry *entry, void *handler);
void set_handler_default(struct interrupt_entry *entry);
void interrupt_handler(struct cpu_state cpu, unsigned int interrupt_number,
		       struct stack_state stack);
void interrupt_init();
#endif