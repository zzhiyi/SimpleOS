/* copy bytes from src to dst */
void memcpy(char *dst, const char *src, int size)
{
	int i;
	for (i = 0; i < size; i++) {
		*(dst + i) = *(src + i);
	}
}
/* wait for slower hardware to catch up to CPU */
void io_wait()
{
	for (int i = 0; i < 1000000; i++)
		;
}