#include <stdio.h>
#include "../s21_string.h"

int main() {
    char buff[500];
    char buff_right[500];

    int a, b;

    s21_sprintf(buff, "|%+*.*g|\n", 10, 10, 0.0000001);
    sprintf(buff_right, "|%+*.*g|\n", 10, 10, 0.0000001);

    printf("      MAIN: <%s>\n", buff);
    printf("MAIN RIGHT: <%s>\n", buff_right);

    return 0;
}
