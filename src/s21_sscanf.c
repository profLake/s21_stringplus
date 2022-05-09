#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

int s21_sscanf(const char *stra, const char *format, ...);

// int main() {
//   char str[20] = "123.456";  // str1[20], str2[20];
//   float a;
//   s21_sscanf(str, "%f", &a);
//   // sscanf(str, "%f", &a);
//   printf("%f", a);
//   return 0;
// }

int s21_sscanf(const char *stra, const char *format, ...) {
  va_list A;
  va_start(A, format);
  float fl, ql;
  int e = 0, i = 0, f, q, error = 0;
  while (format[e] != '\0') {
    if (error != 0) break;
    if (format[e] == '%') {
      e++;
      if (format[e] == 'c') {
        char *o = va_arg(A, char *);
        q = 0;
        o[q] = stra[i];
        e++;
      }
      if (format[e] == 's') {
        char *o = va_arg(A, char *);
        q = 0;
        while (stra[i] != ' ' && stra[i] != '\0') {
          o[q] = stra[i];
          q++;
          i++;
        }
        e++;
      }
      if (format[e] == 'd') {
        if (stra[i] != ' ' && stra[i] != '\0') {
          int *p = va_arg(A, int *);
          if (stra[i] >= '0' && stra[i] <= '9') {
            f = stra[i] - '0';
            while (stra[i + 1] >= '0' && stra[i + 1] <= '9') {
              f = f * 10;
              q = stra[i + 1] - '0';
              f = f + q;
              i++;
            }
            *p = f;
          } else {
            error++;
          }
          i++;
        }
        e++;
      }
      if (format[e] == 'f') {
        q = 1;
        if (stra[i] != ' ' && stra[i] != '\0') {
          float *p = va_arg(A, float *);
          if (stra[i] >= '0' && stra[i] <= '9') {
            fl = stra[i] - '0';
            while (stra[i + 1] >= '0' && stra[i + 1] <= '9') {
              fl = fl * 10;
              ql = stra[i + 1] - '0';
              fl = fl + ql;
              i++;
            }
            if (stra[i + 1] == '.') {
              i++;
              i++;
              while (stra[i] >= '0' && stra[i] <= '9') {
                ql = stra[i] - '0';
                ql = ql / (pow(10, q));
                fl = fl + ql;
                q++;
                i++;
              }
            }
            *p = fl;
          } else {
            error++;
          }
          i++;
        }
        e++;
      }
    }
    if (stra[i] == ' ') i++;
    if (format[e] == ' ') e++;
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
