#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *new = s21_NULL;
  s21_size_t i = 0, firch = 0, endch = 0, nch = 0;

  while (src[endch]) {
    endch++;
  }

  while (src[firch] && trim_chars[i]) {
    i = 0;
    if (src[firch] != trim_chars[i]) {
      while (trim_chars[i] && trim_chars[i] != src[firch]) {
        i++;
      }
    }
    firch++;
  }
  i = 0;
  while (src[endch - 1] && trim_chars[i]) {
    i = 0;
    if (src[endch - 1] != trim_chars[i]) {
      while (trim_chars[i] && trim_chars[i] != src[endch - 1]) {
        i++;
      }
    }
    endch--;
  }
  if (endch != 0) {
    new = (char *)malloc(endch * sizeof(char));
  }
  while (firch - 1 < endch + 1) {
    new[nch] = src[firch - 1];
    firch++;
    nch++;
  }

  return new;
}
