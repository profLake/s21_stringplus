#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

// c s u d f i e E X x o g G

void d_u_chislo(const char *stra, int *i, int *p, int *erro);
void s_stroka(const char *stra, int *i, char *o);
void c_simvol(const char *stra, int *i, char *o);
int s21_sscanf(const char *stra, const char *format, ...);

// int main() {
//   char str[20] = "124 D", str1[20];  // str2[20];
//   int a;
//   s21_sscanf(str, "%d %c", &a, str1);
//   // sscanf(str, "%d %c", &a, str1);
//   //     scanf("%i", &a);
//   printf("%d %s", a, str1);
//   return 0;
// }

// c s u d f i e E X x o g G

int s21_sscanf(const char *stra, const char *format, ...) {
  va_list A;
  va_start(A, format);
  float fl, ql;
  int e = 0, i = 0, error = 0;
  int f, q, qi, w, ei, g;
  while (format[e] != '\0') {
    if (error != 0) break;
    if (format[e] == '%') {
      e++;
      if (format[e] == 'c') {
        char *o = va_arg(A, char *);
        c_simvol(stra, &i, o);
      }
      if (format[e] == 's') {
        char *o = va_arg(A, char *);
        s_stroka(stra, &i, o);
      }
      if (format[e] == 'd' || format[e] == 'u') {
        if (stra[i] != ' ' && stra[i] != '\0') {
          int *p = va_arg(A, int *);
          d_u_chislo(stra, &i, p, &error);
        }
      }
      if (format[e] == 'f' || format[e] == 'e' || format[e] == 'E' ||
          format[e] == 'g' || format[e] == 'G') {
        q = 1;
        qi = 0;
        f = 0;
        g = 0;
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
                g++;
              }
              if (format[e] == 'e' || format[e] == 'E')
                if ((stra[i] == 'e' || format[e] == 'E') &&
                    stra[i + 1] == '+') {
                  i++;
                  i++;
                  if (stra[i] == '0') i++;
                  if (stra[i] >= '1' && stra[i] <= '9') {
                    ei = stra[i] - '0';
                    i++;
                  }
                  if (stra[i] >= '1' && stra[i] <= '9') {
                    ei = ei * 10;
                    ei = ei + (stra[i] - '0');
                  }
                  for (int z = 0; z != ei; z++) {
                    fl = fl * 10;
                  }
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
      if (format[e] == 'i' || format[e] == 'o') {
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
              if (stra[i + 1] <= '0' || stra[i + 1] >= '9') {
                break;
              } else {
                if (stra[i + 1] <= 'A' && stra[i + 1] >= 'F') break;
              }
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
              if (stra[i] >= 'a' && stra[i] <= 'f') {
                w = stra[i] - 97;
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
            if (stra[i] == '0' && stra[i + 1] >= '0' && stra[i + 1] <= '7') {
              i++;
              while (stra[i] != ' ' && stra[i] != '\0') {
                if (stra[i + 1] <= '0' || stra[i + 1] >= '7') break;
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
    // if (format[e] == ' ') e++;
    e++;
  }
  va_end(A);
  return 0;
}

// c s u d f i e E X x o g G

void c_simvol(const char *stra, int *i, char *o) {
  int q = 0;
  o[q] = stra[*i];
}

void s_stroka(const char *stra, int *i, char *o) {
  int q = 0, iq = *i;
  while (stra[iq] != ' ' && stra[iq] != '\0') {
    o[q] = stra[iq];
    q++;
    iq++;
    *i = iq;
  }
}

void d_u_chislo(const char *stra, int *i, int *p, int *erro) {
  int q = 0, qi = 0, ii = *i, error = 0, f;
  if (stra[ii] == '-' && stra[ii + 1] >= '0' && stra[ii + 1] <= '9') {
    qi++;
    ii++;
    *i = ii;
  }
  if (stra[ii] == '+' && stra[ii + 1] >= '0' && stra[ii + 1] <= '9') i++;
  if (stra[ii] >= '0' && stra[ii] <= '9') {
    f = stra[ii] - '0';
    while (stra[ii + 1] >= '0' && stra[ii + 1] <= '9') {
      f = f * 10;
      q = stra[ii + 1] - '0';
      f = f + q;
      ii++;
      *i = ii;
    }
    if (qi != 0) f = -f;
    *p = f;
  } else {
    error++;
  }
  ii++;
  *i = ii;
  *erro = error;
}
