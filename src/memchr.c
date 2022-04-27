#include <stdio.h>
#include <string.h>
void *s21_memchr(const void *str, int c, s21_size_t n) {
    void *ret = NULL;
    for (int i = 0; i < n ; i++) {
        if (c == *((char*)str + i)) {
            ret = ((char*)str + i);
            break;
        }
    }
    return ret;
}

int main() {
    char str[] = "ityuq";
    char *c = s21_memchr(str,'q', 5);
    printf ("%s\n",str);
    if (c != NULL) {
        *c = '3';}
    printf ("%s\n",str);
      return 0;
}
