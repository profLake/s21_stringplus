#include <stdio.h>
#include "../s21_string.h"

int main() {
    char buff[500];
    char buff_right[500];

    int a, b;

    s21_sprintf(buff, "%.16g", 3122.55);
    sprintf(buff_right, "%.16g", 3122.55);

    printf("      MAIN: <%s>\n", buff);
    printf("MAIN RIGHT: <%s>\n", buff_right);

    return 0;
}
