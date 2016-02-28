#ifndef KEYBOARD_H
#define KEYBOARD_H
#include <lowlevel.h>
#define KBD_DATA_PORT 0x60

/** read_scan_code:
 *  Reads a scan code from the keyboard
 *
 *  @return The scan code (NOT an ASCII character!)
 */
unsigned char read_scan_code(void);
#endif