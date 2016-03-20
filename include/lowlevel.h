#pragma once
// Input a byte from port
unsigned char in_byte(unsigned short port);
// Output a byte to port
void out_byte(unsigned short port, unsigned char data);
// Input a word from port
unsigned short in_short(unsigned short port);
// Output a word to port
void out_short(unsigned short port, unsigned short data);
// Disable interrupt
void cli();
// Enable interrupt
void sti();
// Halt
void hlt();