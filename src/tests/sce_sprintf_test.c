#include <stdio.h>
#include "../s21_string.h"

int main() {
    char buff[500];
    char buff_right[500];

    int a, b;
    s21_sprintf(buff, "%----24p et hello %2p %12p\n", &a, &b, NULL);
    sprintf(buff_right, "%----24p et hello %2p %12p\n", &a, &b, NULL);

    printf("      MAIN: <%s>", buff);
    printf("MAIN RIGHT: <%s>", buff_right);

    return 0;
}
