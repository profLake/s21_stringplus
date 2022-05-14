#include <stdio.h>
#include <string.h>

#include "s21_string.h"

void *s21_insert(const char *src, const char *str, s21_size_t start_index) {
  s21_size_t i = 0;
  s21_size_t q = 0;
  s21_size_t r;
  s21_size_t k = 0;
  char *m = s21_NULL;

  while (src[i] != '\0') {
    i++;
  }

  while (str[q] != '\0') {
    q++;
  }

  if (i >= start_index) {
    m = malloc((i + q + 1) * sizeof(char));

    for (r = 0; r < i + q; r++) {
      if (r < start_index) {
        m[r] = src[r];

      } else if (r >= start_index && str[k] != '\0') {
        m[r] = str[k];
        k++;
      }
      if (r >= (start_index + q) && src[r - k] != '\0') {
        m[r] = src[r - k];
      }
    }
  }
  m[r] = '\0';

  return m;
}
/*
int main() {
  char *s1 = "School-21 test";
  char *s3 = s21_insert(s1, " ", 3);
  char *fr = s3;
  for (int i = 0; *s3; i++) {
    printf("%c", *s3++);
  }

  free(fr);
  fr = s21_NULL;
  s3 = s21_NULL;
  return 0;
}
*/