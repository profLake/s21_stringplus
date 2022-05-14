#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  char *new = (char *)src;
  s21_size_t i = 0, firch = 0, endch = 0, nch = 0;

  if (trim_chars != s21_NULL && *trim_chars) {
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
      if (endch != 0) {
        new = (char *)malloc((endch + 1) * sizeof(char));
      }
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
/*
int main() {
  char *s1 = "School-21";
  char *s2 = "";
  char *s3 = "S";
  char *s4 = "Sch";
  char *s5 = "School";
  char *s6 = "School-21";
  char *s7 = NULL;
  char *r1 = s21_trim(s1, s2);
  char *r2 = s21_trim(s1, s3);
  char *r3 = s21_trim(s1, s4);
  char *r4 = s21_trim(s1, s5);
  char *r5 = s21_trim(s1, s6);
  char *r6 = s21_trim(s1, s7);
  printf("%s\n", r1);
  printf("%s\n", r2);
  printf("%s\n", r3);
  printf("%s\n", r4);
  printf("%s\n", r5);
  printf("%s\n", r6);
  free(r2);
  free(r3);
  free(r4);
  // free(r5);
}
*/