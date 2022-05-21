#include <stdlib.h>

#include "s21_string.h"

void *s21_to_lower(const char *str) {
  s21_size_t i;
  i = 0;
  s21_size_t j;
  j = 0;
  while (str[i] != '\0') {
    i++;
  }
  char *scopy = calloc(i + 1, sizeof(char));
  if (scopy == s21_NULL) {
      return s21_NULL;
  }
  s21_size_t q;
  for (q = 0; str[q] != '\0'; q++) {
    scopy[q] = str[q];
  }
  scopy[q] = '\0';
  while (scopy[j]) {
    if (scopy[j] >= 65 && str[j] <= 90) {
      scopy[j] = scopy[j] + 32;
    }
    j++;
  }
  return scopy;
}
