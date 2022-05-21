#include <stdlib.h>

#include "s21_string.h"

void *s21_to_upper(const char *str) {
  s21_size_t t = 0;
  while (str[t] != 0) {
    t++;
  }
  char *srr = (char *)malloc(t * sizeof(char));
  for (s21_size_t q = 0; str[q] != 0; q++) {
    srr[q] = str[q];
    if (srr[q] >= 97 && srr[q] <= 122) {
      srr[q] -= 'a' - 'A';
    }
  }
  return srr;
}