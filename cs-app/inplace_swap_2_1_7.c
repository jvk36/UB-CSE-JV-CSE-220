#include <stdio.h>

void inplace_swap(int *x, int *y) {
    *y = *x ^ *y;
    *x = *x ^ *y;
    *y = *x ^ *y;
}

int main(int argc, char *argv[]) {
    int a=23, b=46;
    printf("\nBefore in-place swap: a=%d, b=%d\n", a, b);
    inplace_swap(&a, &b);
    printf("\nAfter in-place swap: a=%d, b=%d\n", a, b);
}
