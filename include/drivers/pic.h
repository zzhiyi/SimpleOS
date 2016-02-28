#ifndef PIC_H
#define PIC_H
#include <lowlevel.h>
#include <drivers/screen.h>
#define ICW1_ICW4 0x01      /* ICW4 (not) needed */
#define ICW1_SINGLE 0x02    /* Single (cascade) mode */
#define ICW1_INTERVAL4 0x04 /* Call address interval 4 (8) */
#define ICW1_LEVEL 0x08     /* Level triggered (edge) mode */
#define ICW1_INIT 0x10      /* Initialization - required! */

#define ICW4_8086 0x01       /* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO 0x02       /* Auto (normal) EOI */
#define ICW4_BUF_SLAVE 0x08  /* Buffered mode/slave */
#define ICW4_BUF_MASTER 0x0C /* Buffered mode/master */
#define ICW4_SFNM 0x10       /* Special fully nested (not) */

#define PIC1_COMMAND 0x20	    /*PIC1 command port*/
#define PIC1_DATA (PIC1_COMMAND + 1) /*PIC1 data port*/
#define PIC2_COMMAND 0xA0	    /*PIC2 command port*/
#define PIC2_DATA (PIC2_COMMAND + 1) /*PIC2 data port*/

/* The PIC interrupts have been remapped */
#define PIC1_START_INTERRUPT 0x20
#define PIC2_START_INTERRUPT 0x28
#define PIC2_END_INTERRUPT PIC2_START_INTERRUPT + 7

#define PIC_ACK 0x20

void PIC_remap(int offset1, int offset2);
void PIC_acknowledge(unsigned int interrupt_number);
void PIC_init();
void io_wait();
#endif