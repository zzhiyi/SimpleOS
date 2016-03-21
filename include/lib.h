#pragma once
/* copy bytes from src to dst */
void memcpy(char *dst, const char *src, int size);
/* wait for slower hardware to catch up to CPU */
void io_wait();