#include <stdio.h>
#include "../s21_string.h"

int main() {
    char buff[500];
    char buff_right[500];

    int a, b;
    /*
    s21_sprintf(buff, "|test %-12i et %24s !|\n", 0, "coco");
    sprintf(buff_right, "|test %-12i et %24s !|\n", 0, "coco");
    */

    /*
    s21_sprintf(buff, "02) standart PRINTF : |%.d|\n", 0);
    sprintf(buff_right, "02) standart PRINTF : |%.d|\n", 0);
    */

    /*
    s21_sprintf(buff, "|% 10f|\n", 324.1);
    sprintf(buff_right, "|% 10f|\n", 324.1);
    */

    /*
    s21_sprintf(buff, "|%#10.0f|\n", 3.14);
    sprintf(buff_right, "|%#10.0f|\n", 3.14);
    */

    /*
    s21_sprintf(buff, "|% -5.1f|\n", 0.001);
    sprintf(buff_right, "|% -5.1f|\n", 0.001);
    */

    /*
    s21_sprintf(buff, "|%5.*f|\n", -10, 0.0001);
    sprintf(buff_right, "|%5.*f|\n", -10, 0.0001);
    */

    s21_sprintf(buff, "|%*.*f|\n", -23, -10 , 0.0001);
    sprintf(buff_right, "|%*.*f|\n", -23, -10 , 0.0001);

    printf("      MAIN: <%s>\n", buff);
    printf("MAIN RIGHT: <%s>\n", buff_right);

    return 0;
}
