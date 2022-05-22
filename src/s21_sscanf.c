#include <math.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

#include "s21_string.h"

// c s u d f i e E X x o g G p

void p_po(const char *st, int *i, va_list A);
void i_chislo(const char *stra, int *i, int *p, int *erro);
void f_ch(const char *st, int *i, float *p, int *er, const char *fo, int *e);
void d_u_chislo(const char *stra, int *i, int *p, int *erro);
void s_stroka(const char *stra, int *i, char *o);
void c_simvol(const char *stra, int *i, char *o);
int s21_sscanf(const char *stra, const char *format, ...);

// int main() {
//   char str[20] = "1234567890";  // str1[20];  // str2[20];
//   float a;
//   // s21_sscanf(str, "%f", &a);
//   // printf("%f\n", a);
//   sscanf(str, "%f", &a);
//   printf("%f", a);
//   return 0;
// }

// c s u d f i e E X x o g G p

int s21_sscanf(const char *stra, const char *format, ...) {
  va_list A;
  va_start(A, format);
  int e = 0, i = 0, error = 0;
  while (format[e] != '\0') {
    if (error != 0) break;
    if (format[e] == '%') {
      e++;
      if (format[e] == 'c') {
        char *o = va_arg(A, char *);
        c_simvol(stra, &i, o);
        e++;
      }
      if (format[e] == 's') {
        char *o = va_arg(A, char *);
        s_stroka(stra, &i, o);
        e++;
      }
      if (format[e] == 'd' || format[e] == 'u') {
        int *p = va_arg(A, int *);
        d_u_chislo(stra, &i, p, &error);
        e++;
      }
      if (format[e] == 'f' || format[e] == 'e' || format[e] == 'E' ||
          format[e] == 'g' || format[e] == 'G') {
        float *p = va_arg(A, float *);
        f_ch(stra, &i, p, &error, format, &e);
        e++;
      }
      if (format[e] == 'i' || format[e] == 'o') {
        int *p = va_arg(A, int *);
        i_chislo(stra, &i, p, &error);
        e++;
      }
      if (format[e] == 'n') {
        int *p = va_arg(A, int *);
        *p = i;
        e++;
      }
      if (format[e] == 'p') {
        // void *v = va_arg(A, void *);
        p_po(stra, &i, A);
        e++;
      }
    }
    if (stra[i] == ' ') i++;
    if (format[e] == ' ') e++;
    // e++;
  }
  va_end(A);
  return 0;
}

// c s u d f i e E X x o g G p

void c_simvol(const char *stra, int *i, char *o) {
  size_t q = 0;
  o[q] = stra[*i];
}

void s_stroka(const char *stra, int *i, char *o) {
  size_t q = 0, ii = *i;
  while (stra[ii] != ' ' && stra[ii] != '\0') {
    o[q] = stra[ii];
    q++;
    ii++;
  }
  *i = ii;
}

void d_u_chislo(const char *stra, int *i, int *p, int *erro) {
  size_t q = 0, qi = 0, ii = *i, error = 0, f;
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

void f_ch(const char *st, int *i, float *p, int *er, const char *fo, int *e) {
  size_t q = 1, qi = 0, g = 0, ii = *i, ei, error = *er, ee = *e;
  float fl, ql;
  if (st[ii] == '-' && st[ii + 1] >= '0' && st[ii + 1] <= '9') {
    qi++;
    ii++;
  }
  if (st[ii] == '+' && st[ii + 1] >= '0' && st[ii + 1] <= '9') ii++;
  if (st[ii] >= '0' && st[ii] <= '9') {
    fl = st[ii] - '0';
    while (st[ii + 1] >= '0' && st[ii + 1] <= '9') {
      fl = fl * 10;
      ql = st[ii + 1] - '0';
      fl = fl + ql;
      ii++;
    }
    if (st[ii + 1] == '.') {
      ii++;
      ii++;
      while (st[ii] >= '0' && st[ii] <= '9') {
        ql = st[ii] - '0';
        ql = ql / (pow(10, q));
        fl = fl + ql;
        q++;
        ii++;
        g++;
      }
      if (fo[ee] == 'e' || fo[ee] == 'E') {
        if ((st[ii] == 'e' || st[ii] == 'E') && st[ii + 1] == '+') {
          ii++;
          ii++;
          if (st[ii] == '0') ii++;
          if (st[ii] >= '1' && st[ii] <= '9') {
            ei = st[ii] - '0';
            ii++;
          }
          if (st[ii] >= '1' && st[ii] <= '9') {
            ei = ei * 10;
            ei = ei + (st[ii] - '0');
          }
          for (size_t z = 0; z != ei; z++) {
            fl = fl * 10;
          }
        }
        if ((st[ii] == 'e' || st[ii] == 'E') && st[ii + 1] == '-') {
          ii++;
          ii++;
          if (st[ii] == '0') ii++;
          if (st[ii] >= '1' && st[ii] <= '9') {
            ei = st[ii] - '0';
            ii++;
          }
          if (st[ii] >= '1' && st[ii] <= '9') {
            ei = ei / 10;
            ei = ei + (st[ii] - '0');
          }
          for (size_t z = 0; z != ei; z++) {
            fl = fl / 10;
          }
        }
      }
      if (qi != 0) fl = -fl;
    }
    *p = fl;
  } else {
    error++;
    *er = error;
  }
  ii++;
  *i = ii;
}

void i_chislo(const char *stra, int *i, int *p, int *erro) {
  size_t q = 0, qi = 0, ii = *i, w, f = 0, error = *erro;
  if (stra[ii] == '-') {
    q++;
    ii++;
  }
  if (stra[ii] == '+') ii++;
  if (stra[ii] == '0' && stra[ii + 1] == 'x') {
    ii++;
    ii++;
    while (stra[ii] != ' ' && stra[ii] != '\0') {
      if (stra[ii + 1] >= '0' || stra[ii + 1] <= '9') {
        ii++;
        qi++;
      } else {
        if (stra[ii + 1] >= 'A' && stra[ii + 1] <= 'F') {
          ii++;
          qi++;
        } else {
          if (stra[ii + 1] >= 'a' && stra[ii + 1] <= 'f') {
            ii++;
            qi++;
          } else {
            break;
          }
        }
      }
    }
    ii = ii - qi;
    qi--;
    while (stra[ii] != ' ' && stra[ii] != '\0') {
      if (stra[ii] >= '0' && stra[ii] <= '9') {
        w = stra[ii] - '0';
        w = w * (pow(16, qi));
        ii++;
        qi--;
        f = f + w;
      }
      if (stra[ii] >= 'A' && stra[ii] <= 'F') {
        w = stra[ii] - 65;
        w = w + 10;
        w = w * (pow(16, qi));
        ii++;
        qi--;
        f = f + w;
      }
      if (stra[ii] >= 'a' && stra[ii] <= 'f') {
        w = stra[ii] - 97;
        w = w + 10;
        w = w * (pow(16, qi));
        ii++;
        qi--;
        f = f + w;
      }
    }
    if (q != 0) f = -f;
    *p = f;
  } else {
    if (stra[ii] == '0' && stra[ii + 1] >= '0' && stra[ii + 1] <= '7') {
      ii++;
      while (stra[ii] != ' ' && stra[ii] != '\0') {
        if (stra[ii + 1] <= '0' || stra[ii + 1] >= '7') break;
        ii++;
        qi++;
      }
      ii = ii - qi;
      qi--;
      while (stra[ii] != ' ' && stra[ii] != '\0') {
        if (stra[ii] >= '0' && stra[ii] <= '9') {
          w = stra[ii] - '0';
          w = w * (pow(8, qi));
          ii++;
          qi--;
          f = f + w;
        }
      }
      if (q != 0) f = -f;
      *p = f;
    } else {
      error++;
    }
    ii++;
  }
  *i = ii;
}

void p_po(const char *stra, int *i, va_list A) {
  size_t q = 0, f = 0, qi = 0, ii = *i, w;
  if (stra[ii] == '-') {
    q++;
    ii++;
  }
  if (stra[ii] == '+') ii++;
  if (stra[ii] == '0' && stra[ii + 1] == 'x') {
    ii++;
    ii++;
  }
  while (stra[ii] != ' ' && stra[ii] != '\0') {
    if (stra[ii + 1] >= '0' || stra[ii + 1] <= '9') {
      ii++;
      qi++;
    } else {
      if (stra[ii + 1] >= 'A' && stra[ii + 1] <= 'F') {
        ii++;
        qi++;
      } else {
        if (stra[ii + 1] >= 'a' && stra[ii + 1] <= 'f') {
          ii++;
          qi++;
        } else {
          break;
        }
      }
    }
  }
  ii = ii - qi;
  qi--;
  while (stra[ii] != ' ' && stra[ii] != '\0') {
    if (stra[ii] >= '0' && stra[ii] <= '9') {
      w = stra[ii] - '0';
      w = w * (pow(16, qi));
      ii++;
      qi--;
      f = f + w;
    }
    if (stra[ii] >= 'A' && stra[ii] <= 'F') {
      w = stra[ii] - 65;
      w = w + 10;
      w = w * (pow(16, qi));
      ii++;
      qi--;
      f = f + w;
    }
    if (stra[ii] >= 'a' && stra[ii] <= 'f') {
      w = stra[ii] - 97;
      w = w + 10;
      w = w * (pow(16, qi));
      ii++;
      qi--;
      f = f + w;
    }
  }
  if (q != 0) f = -f;
  void **v = va_arg(A, void **);
  *v = (void *)(0x0 + f);
  *i = ii;
}
