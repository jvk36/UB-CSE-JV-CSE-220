#include <stdio.h>

void swap(int *x, int *y) {
    int temp;

    temp = *x;
    *x = *y;
    *y = temp;
}

int main(int argc, char *argv[]) {
    int a=35, b=44;
    
    printf("\nBefore swap: a=%d, b=%d\n", a, b);
    swap(&a,&b);
    printf("After swap: a=%d, b=%d\n", a, b);
    
}
