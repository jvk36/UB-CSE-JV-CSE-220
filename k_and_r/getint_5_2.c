#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

bool getint(char *input, int *output) {
    int sign=1;
    bool bFirst=true;

    *output = 0;
    for ( ; *input!='\0'; input++) {
        if (bFirst) {
            bFirst = false;
            sign = (*input=='-')?-1:1;
            if (*input=='-' || *input=='+') continue;
        }
        
        if (!isdigit(*input)) return false;
        *output = 10 * *output + (*input-'0');
    }

    *output = *output * sign;
    return true;
}

int main(int argc, char *argv[]) {
    int num;

    if (argc!=2) {
        printf("\nThe program requires exactly one command-line argument.\n");
        return 1;
    }
    
    if (!getint(argv[1], &num)) {
        printf("\nThe input in the command-line '%s' is not a number.\n", argv[1]);
        return 1;
    }

    printf("\nThe number in the command-line is '%d'.\n", num);
    return 0;
}
