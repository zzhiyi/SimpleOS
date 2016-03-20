#include <interrupt.h>
#include <drivers/screen.h>
#include <drivers/keyboard.h>

// interrupt has been remap, so it starts from 0x20
extern void null_handler();
extern void interrupt_handler_0x20();
extern void interrupt_handler_0x21();
extern void interrupt_load_idt(struct interrupt_idtr *idtr);

struct interrupt_entry idt[256];
struct interrupt_idtr idtr;

void set_handler(struct interrupt_entry *entry, void *handler)
{
	entry->high = ((unsigned int)handler & 0xffff0000) >> 16;
	entry->low = (unsigned int)handler & 0xffff;
}
void set_handler_default(struct interrupt_entry *entry)
{
	entry->selector = 0x0008;
	entry->zero = 0;
	entry->type_attr = 0x8E;
}

void interrupt_handler(struct cpu_state cpu, unsigned int interrupt_number,
		       struct stack_state stack)
{
	print("caught interrupt:");
	print_hex(interrupt_number);
	print("\n");
	switch (interrupt_number) {
	// keyboard interrupt
	case 0x21:
		print("scan code:");
		print_hex(read_scan_code());
		print("\n");
		break;
	default:
		break;
	}
	if (interrupt_number >= 0x20 && interrupt_number <= 0x2F)
		PIC_acknowledge(interrupt_number);
}

void interrupt_setup()
{
	// set all handler to the same
	for (int i = 0; i < 256; i++) {
		set_handler(&idt[i], null_handler);
		set_handler_default(&idt[i]);
	}
	// set timer handler
	set_handler(&idt[0x20], interrupt_handler_0x20);
	set_handler_default(&idt[0x20]);
	// set keyboard handler
	set_handler(&idt[0x21], interrupt_handler_0x21);
	set_handler_default(&idt[0x21]);
	idtr.size = sizeof(idt) - 1;
	idtr.idt = idt;
	/*print("\nidtr.size :");
	print_hex(idtr.size);
	print("\n");
	print("&idtr:");
	print_hex(&idtr);
	print("\n");
	print("idt:");
	print_hex(idt);
	print("\n");*/
}

void interrupt_init()
{
	interrupt_setup();
	interrupt_load_idt(&idtr);
	PIC_init();
	sti();
}