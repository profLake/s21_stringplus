#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

int s21_sscanf(const char *stra, const char *format, ...);

/*
int main() {
  char str[20] = "hello World", str1[20], str2[20];
  s21_sscanf(str, "%s %s", str1, str2);
  printf("%s %s\n", str1, str2);
  sscanf(str, "%s %s", str1, str2);
  printf("%s %s", str1, str2);
  return 0;
}
*/

int s21_sscanf(const char *stra, const char *format, ...) {
  int q;
  va_list A;
  va_start(A, format);
  int e = 0, i = 0;
  while (format[e] != '\0') {
    char *o = va_arg(A, char *);
    if (format[e] == '%') {
      e++;
    }
    if (format[e] == 's') {
      e++;
      q = 0;
      while (stra[i] != ' ' && stra[i] != '\0') {
        o[q] = stra[i];
        q++;
        i++;
      }
      if (stra[i] == ' ') i++;
      if (format[e] == ' ') e++;
    }
  }
  va_end(A);
  return 0;
}

/*void fink(const char *stra, const char *format, char *str1) {
  s21_size_t a = s21_strlen(format), b = s21_strlen(stra);
  int w = b, q = a;
  char str[w], f[q];
  s21_strcpy(str, stra);
  s21_strcpy(f, format);
  int e = 0;
  while (f[e]) {
    if (f[e] == '%') {
      e++;
    } else {
      e++;
    }
    if (f[e] == 's') {
      q = 0;
      while (str[q] != ' ') {
        str1[q] = str[q];
        q++;
      }
    }
  }
}*/
