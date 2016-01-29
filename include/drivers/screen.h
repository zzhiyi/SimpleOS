#include <drivers/port_io.h>
#include <lib.h>
#define VIDEO_ADDRESS 0xb8000
#define MAX_COLS 80
#define MAX_ROWS 25
// Attribute byte for our default colour scheme .
#define WHITE_ON_BLACK 0x0f
// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5
/* Print a char on the screen at col , row , or at cursor position */
void print_char(char character, int col, int row, char attribute_byte);

int get_cursor();

void set_cursor(int offset);

void print_at(char *message, int col, int row);

void print(char *message);

void clear_screen();

/* Advance the text cursor , scrolling the video buffer if necessary . */
int handle_scrolling(int cursor_offset);

int get_screen_offset(int col, int row);