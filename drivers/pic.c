#include <lowlevel.h>
#include <drivers/pic.h>

/* initialize the PIC controllers, giving them specified vector offsets
   rather than 8h and 70h, as configured by default */
/*
arguments:
  offset1 - vector offset for master PIC
    vectors on the master become offset1..offset1+7
  offset2 - same for slave PIC: offset2..offset2+7
*/
void PIC_remap(int offset1, int offset2)
{
  unsigned char a1, a2;

  a1 = in_byte(PIC1_DATA); // save masks
  a2 = in_byte(PIC2_DATA);

  out_byte(PIC1_COMMAND,
     ICW1_INIT + ICW1_ICW4); // starts the initialization
           // sequence (in cascade mode)
  io_wait();
  out_byte(PIC2_COMMAND, ICW1_INIT + ICW1_ICW4);
  io_wait();
  out_byte(PIC1_DATA, offset1); // ICW2: Master PIC vector offset
  io_wait();
  out_byte(PIC2_DATA, offset2); // ICW2: Slave PIC vector offset
  io_wait();
  out_byte(PIC1_DATA, 4); // ICW3: tell Master PIC that there is
        // a slave PIC at IRQ2 (0000 0100)
  io_wait();
  out_byte(PIC2_DATA,
     2); // ICW3: tell Slave PIC its cascade identity (0000 0010)
  io_wait();

  out_byte(PIC1_DATA, ICW4_8086);
  io_wait();
  out_byte(PIC2_DATA, ICW4_8086);
  io_wait();

  out_byte(PIC1_DATA, a1); // restore saved masks.
  out_byte(PIC2_DATA, a2);
}

/** pic_acknowledge:
 *  Acknowledges an interrupt from either PIC 1 or PIC 2.
 *
 *  @param num The number of the interrupt
 */
void PIC_acknowledge(unsigned int interrupt_number)
{
  print(__FUNCTION__);
  print("\n");
  if (interrupt_number < PIC1_START_INTERRUPT ||
      interrupt_number > PIC2_END_INTERRUPT) {
    return;
  }

  out_byte(PIC1_COMMAND, PIC_ACK);
  if (interrupt_number >= PIC2_START_INTERRUPT) {
    out_byte(PIC2_COMMAND, PIC_ACK);
  }
}

void PIC_init()
{
  PIC_remap(PIC1_START_INTERRUPT, PIC2_START_INTERRUPT);
  // Enable only kerboard interrupt
  out_byte(PIC1_DATA, 0xfd);
  out_byte(PIC2_DATA, 0xff);
}
void io_wait()
{
  for (int i = 0; i < 1000000; i++)
    ;
}