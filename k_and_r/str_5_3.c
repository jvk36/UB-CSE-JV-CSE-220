#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

int my_strlen(char *s) {
    int len=0;
    while (*s++) len++;
    return len;
}

void my_strcpy(char *in, char *out) {
    while ((*out++=*in++));
}

bool my_strcmp(char *a, char *b) {
    while (*a++==*b++)
        if (*a=='\0') return true;
    return false;
}

// standard version
int my_strcmp_1(char *s, char *t) {
    for ( ; *s == *t; s++, t++)
        if (*s == '\0')
            return 0;
    return *s - *t;
}

int main(int argc, char *argv[]) {

    if (argc!=2) {
        printf("\nThe program requires exactly one command-line argument.\n");
        return 1;
    }
    
    printf("\nThe length of the string '%s' is %d.\n", argv[1], my_strlen(argv[1]));

    char string[30];
    my_strcpy(argv[1], string);
    printf("String copied: '%s'.\n", string);

    if (my_strcmp(argv[1], string)) {
        printf("The copied string compared successfully.\n");
    }

    if (!my_strcmp(argv[1], "arbitrary")) {
        printf("Comparison of '%s' to '%s' returned false.\n", argv[1], "arbitrary");
    }
    
    return 0;
}
