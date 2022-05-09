#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

// c s u d f i

int s21_sscanf(const char *stra, const char *format, ...);

// int main() {
//   char str[20] = "077";  // str1[20], str2[20];
//   int a;
//   s21_sscanf(str, "%i", &a);
//   // sscanf(str, "%i", &a);
//   // scanf("%i", &a);
//   printf("%i", a);
//   return 0;
// }

int s21_sscanf(const char *stra, const char *format, ...) {
  va_list A;
  va_start(A, format);
  float fl, ql;
  int e = 0, i = 0, error = 0;
  int f, q, qi, w;
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
      if (format[e] == 'd' || format[e] == 'u') {
        if (stra[i] != ' ' && stra[i] != '\0') {
          int *p = va_arg(A, int *);
          q = 0;
          if (stra[i] == '-' && stra[i + 1] >= '0' && stra[i + 1] <= '9') {
            q++;
            i++;
          }
          if (stra[i] == '+' && stra[i + 1] >= '0' && stra[i + 1] <= '9') i++;
          if (stra[i] >= '0' && stra[i] <= '9') {
            f = stra[i] - '0';
            while (stra[i + 1] >= '0' && stra[i + 1] <= '9') {
              f = f * 10;
              q = stra[i + 1] - '0';
              f = f + q;
              i++;
            }
            if (q != 0) f = -f;
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
        qi = 0;
        f = 0;
        if (stra[i] != ' ' && stra[i] != '\0') {
          float *p = va_arg(A, float *);
          if (stra[i] == '-' && stra[i + 1] >= '0' && stra[i + 1] <= '9') {
            qi++;
            i++;
          }
          if (stra[i] == '+' && stra[i + 1] >= '0' && stra[i + 1] <= '9') i++;
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
            if (qi != 0) fl = -fl;
            *p = fl;
          } else {
            error++;
          }
          i++;
        }
        e++;
      }
      if (format[e] == 'i') {
        if (stra[i] != ' ' && stra[i] != '\0') {
          int *p = va_arg(A, int *);
          q = 0;
          qi = 0;
          if (stra[i] == '-') {
            q++;
            i++;
          }
          if (stra[i] == '+') i++;
          if (stra[i] == '0' && stra[i + 1] == 'x') {
            i++;
            i++;
            while (stra[i] != ' ' && stra[i] != '\0') {
              i++;
              qi++;
            }
            i = i - qi;
            qi--;
            while (stra[i] != ' ' && stra[i] != '\0') {
              if (stra[i] >= '0' && stra[i] <= '9') {
                w = stra[i] - '0';
                w = w * (pow(16, qi));
                i++;
                qi--;
                f = f + w;
              }
              if (stra[i] >= 'A' && stra[i] <= 'F') {
                w = stra[i] - 65;
                w = w + 10;
                w = w * (pow(16, qi));
                i++;
                qi--;
                f = f + w;
              }
            }
            if (q != 0) f = -f;
            *p = f;
          } else {
            if (stra[i] == '0' && stra[i] >= '0' && stra[i] <= '7') {
              i++;
              while (stra[i] != ' ' && stra[i] != '\0') {
                i++;
                qi++;
              }
              i = i - qi;
              qi--;
              while (stra[i] != ' ' && stra[i] != '\0') {
                if (stra[i] >= '0' && stra[i] <= '9') {
                  w = stra[i] - '0';
                  w = w * (pow(8, qi));
                  i++;
                  qi--;
                  f = f + w;
                }
              }
              if (q != 0) f = -f;
              *p = f;
            } else {
              error++;
            }
            i++;
          }
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
