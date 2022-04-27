

typedef unsigned long s21_size_t;
#define s21_NULL 0

int s21_memcmp(const void *str1, const void *str2, s21_size_t n);
char* s21_strchr(const char *str, int c);
void *s21_memcpy(void *dest, const void *src, s21_size_t n);
int s21_strncmp(const char *str1, const char *str2, s21_size_t n);
char *s21_strstr(const char *haystack, const char *needle);
