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
<<<<<<< HEAD

    m = malloc((i + q + 1) * sizeof(char));

    for (r = 0; src[r - k]; r++) {
        if (r < start_index) {

          m[r] = src[r];

        } else if (r >= start_index && str[k] != '\0') {
              m[r] = str[k];
              k++;
          }
       if (r >= (start_index + q) && src[r - k - 1] != '\0') {
          m[r] = src[r - k];
       }
      }
  }
  
  return m;
}


/*int main() {
=======
    m = malloc((i + q + 1) * sizeof(char));

    for (r = 0; r < i + q + 1; r++) {
      if (r < start_index) {
        m[r] = src[r];

      } else if (r >= start_index && str[k] != '\0') {
        m[r] = str[k];
        k++;
      }
      if (r >= (start_index + q) && src[r - k - 1] != '\0') {
        m[r] = src[r - k];
      }
    }
  }

  return m;
}
/*
int main() {
  char *q = "geronimo";
>>>>>>> 326fefca40476ed29c0a6628f46a7175db311fc2

  char *k = "bazinga";

  char *z = s21_insert(q, k, 0);

<<<<<<< HEAD
    char * q = "geronimo";

    char * k = "bazinga";

    char * z = s21_insert(q, k, 0);

    printf("%s", z);

    free(z);
    z = NULL;

}

=======
  printf("%s", z);

  free(z);
  z = NULL;
}
>>>>>>> 326fefca40476ed29c0a6628f46a7175db311fc2
*/