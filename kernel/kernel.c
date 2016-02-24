#include <drivers/screen.h>
#include <interrupt.h>
void main()
{
	clear_screen();
	print("Loading kernel:\n");
	print("->Initializing interrupt ");
	interrupt_init();
	print("done\n");
}