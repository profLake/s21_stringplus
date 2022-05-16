#include <stdlib.h>

#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *new = (char *)src;
  s21_size_t i = 0, firch = 0, endch = 0, nch = 0;
  if (trim_chars != s21_NULL && *trim_chars) {
    endch = s21_strlen(src);
    while (src[firch] && trim_chars[i]) {
      i = 0;
      if (src[firch] != trim_chars[i]) {
        while (trim_chars[i] && trim_chars[i] != src[firch]) {
          i++;
        }
      }
      firch++;
    }
    if (firch < endch) {
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
      new = (char *)malloc((endch + 1) * sizeof(char));
      while (firch - 1 < endch + 1) {
        new[nch] = src[firch - 1];
        firch++;
        nch++;
      }
      new[nch] = '\0';
    } else {
      new = s21_NULL;
      new = "";
    }
  }
  return new;
}
