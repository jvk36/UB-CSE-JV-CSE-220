#include <stdio.h>
#include <stdbool.h>

static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

bool isLeapYear(int year) {
    return ((year%4==0 && year%100!=0) || (year%400==0));
}

int day_of_year(int year, int month, int day) {
    int leap = isLeapYear(year);
    int i;
    for (i=1; i<month; i++) {
        day += daytab[leap][month];
    }

    return day;
}

int main(int argc, char *argv[]) {
    printf("Day of year today is: %d\n", day_of_year(2019, 9, 21));
}
