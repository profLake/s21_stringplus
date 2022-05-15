#include <stdio.h>
#include "../s21_string.h"

int main() {
    /*
    char buff[500];
    char buff_right[500];

    int a, b;

    sprintf(buff_right, "|%-*.*i|\n", 3, 15, -152352352);
    s21_sprintf(buff, "|%-*.*i|\n", 3, 15, -152352352);

    printf("MAIN RIGHT: <%s>\n", buff_right);
    printf("      MAIN: <%s>\n", buff);
    */

    /*
    char str[100];
    char str1[100];
    sprintf(str, "|%-*.*i|\n", 3, 15, -152352352);
    s21_sprintf(str1, "|%-*.*i|\n", 3, 15, -152352352);
    */

    /*
    char str[100];
    char str1[100];
    sprintf(str, "|%5.d|\n", 0);
    s21_sprintf(str1, "|%5.d|\n", 0);
    */

    /*
    char data[100];
    char data1[100];
    s21_sprintf(data, "02) standart PRINTF : |%.d|\n", 0);
    sprintf(data1, "02) standart PRINTF : |%.d|\n", 0);
    */

    char str[100];
    char str1[100];
    sprintf(str, "|%p|\n", NULL);
    s21_sprintf(str1, "|%p|\n", NULL);

    printf("str:  <%s>\n", str);
    printf("str1: <%s>\n", str1);

    /*
    printf("data:  <%s>\n", data);
    printf("data1: <%s>\n", data1);
    */

    return 0;
}
