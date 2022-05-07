#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "s21_string.h"

void *s21_trim(const char *src, const char *trim_chars) {
  int srck = 0, tchk = 0, sch = 0, schk, l;

  while (*(src + srck)) {
    srck++;
  }
  char *correct_str = (char *)malloc(srck * sizeof(char));
  while (*(trim_chars + tchk)) {
    tchk++;
  }
  for (int k = 0; k < srck; k++) {
    for (l = 0; l < tchk; l++) {
      if (*(src + k) == *(trim_chars + l)) {
        sch++;
        break;
      }
    }
    if (l == tchk) {
      break;
    }
  }
  for (int o = srck - 1; o > sch - 1; o--) {
    for (l = 0; l < tchk; l++) {
      if (*(src + o) == *(trim_chars + l)) {
        schk++;
        break;
      }
    }
    if (l == tchk) {
      break;
    }
  }
  for (int m = sch, n = 0; m < (srck - schk); m++, n++) {
    correct_str[n] = src[m];
  }
  if (src[0] == '\0') {
    correct_str = s21_NULL;
  }
  return (char *)correct_str;
}

int main() {
  char *z = "1 2";
  char *str = "2 2 1 11vvvvv  1 2 12";
  char *res = s21_trim(str, z);
  for (int i = 0; *(res + i) != '\0'; i++) {
    printf("%c", *(res + i));
  }
  free(res);
  return 0;
}
