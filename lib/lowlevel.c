unsigned char in_byte(unsigned short port)
{
  // A handy C wrapper function that reads a byte from the specified port
  // "=a" ( result ) means : put AL register in variable RESULT when
  // finished
  // "d" ( port ) means : load DX with port
  unsigned char result;
  __asm__("in %%dx , %%al" : "=a"(result) : "d"(port));
  return result;
}
void out_byte(unsigned short port, unsigned char data)
{
  // "a" ( data ) means : load AL with data
  // "d" ( port ) means : load DX with port
  __asm__("out %%al , %%dx" : : "a"(data), "d"(port));
}
unsigned short in_short(unsigned short port)
{
  unsigned short result;
  __asm__("in %%dx , %%ax" : "=a"(result) : "d"(port));
  return result;
}
void out_short(unsigned short port, unsigned short data)
{
  __asm__(" out %%ax , %%dx" : : "a"(data), "d"(port));
}
void cli() { __asm__("cli"); }
void sti() { __asm__("sti"); }
void hlt() { __asm__("hlt"); }