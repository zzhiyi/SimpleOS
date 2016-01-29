/* Copy bytes from one place to another . */
void memcpy(char *dst, const char *src, int size) {
  int i;
  for (i = 0; i < size; i++) {
    *(dst + i) = *(src + i);
  }
}