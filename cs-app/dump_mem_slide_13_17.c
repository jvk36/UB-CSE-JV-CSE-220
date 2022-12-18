#include <stdio.h>
#include <string.h>

void dump_mem(const void *mem , size_t len) {
    const char *buffer = mem; // Cast to char *
    size_t i;

    for (i = 0; i < len; i++) {
        if (i > 0 && i % 8 == 0) {
            printf("\n");
        }
        // the bitwise & is needed because buffer[i] is interpretted as a hex integer
        // value by printf and so if the most-significant bit is 1, it will be
        // sign-extended,  it won't appear for 0s as the format string is 02x.
        printf("%02x ", buffer[i] & 0xff);
    }
    
    if (i > 1 && i % 8 != 1) {
        puts("");
    }
}

int main(int argc, char *argv[]) {
    char *str = "this is a test";
    dump_mem(str, strlen(str));
    int arr[] = {-23, 32};
    dump_mem(arr, 2*sizeof(int));
    return 0;
}
