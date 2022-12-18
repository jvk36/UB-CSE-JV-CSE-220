#include <stdio.h>
#include <string.h>

char *month_name(int n) {
    static char *months[] = {
        "Illegal Month",
        "January",
        "February",
        "March",
        "April",
        "May",
        "June",
        "July",
        "August",
        "September",
        "October",
        "November",
        "December"
    };

    return ((n<1 || n>12)? months[0]: months[n]);
}

int main(int argc, char *argv[]) {
    printf("\nMonths of the year: \n");
    for (int i=1; i<=12; i++)
        printf("%s\n", month_name(i));

    return 0;
}

