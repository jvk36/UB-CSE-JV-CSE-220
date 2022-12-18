#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes(byte_pointer start, size_t len) {
    int i;

    for (i=0; i<len; i++) 
        printf("%.2x ", start[i]);
    printf("\n");
}

void show_int(int x) {
    show_bytes((byte_pointer)&x, sizeof(int));
}

void show_float(float x) {
    show_bytes((byte_pointer)&x, sizeof(float));
}

void show_pointer(void *x) {
    show_bytes((byte_pointer)x, sizeof(void *));
}

void show_double(double x) {
    show_bytes((byte_pointer)&x, sizeof(double));
}

void sign_extension() {
    short sx = -12345; /* -12345 */
    unsigned short usx = sx; /* 53191 */
    int x = sx; /* -12345 */
    unsigned ux = usx; /* 53191 */

    printf("sx = %d:\t", sx);
    show_bytes((byte_pointer)&sx, sizeof(short));
    printf("usx = %u: \t", usx);
    show_bytes((byte_pointer)&usx, sizeof(unsigned short));
    printf("x = %d: \t", x);
    show_bytes((byte_pointer)&x, sizeof(int));
    printf("ux = %u: \t", ux);
    show_bytes((byte_pointer)&ux, sizeof(unsigned));

    /* when casting from short to unsigned, the program first does
       short to int and then int to unsigned int resulting in 
       4,294,954,951 rather than 53191.
    */
    unsigned uy = sx; /* MYSTERY */
    printf("uy = %u:\t", uy);
    show_bytes((byte_pointer)&uy, sizeof(unsigned));
}

int main(int argc, char *argv[]) {
    show_bytes((byte_pointer)"test", 4);
    show_int(25);
    show_int(-25);
    show_float(0.25);
    show_pointer((void *)&argc);
    show_double(0.25);


    // cs-app pg104 - verify the 2s complement in little-endian machine in our VM.
    short x=12345;
    short mx=-12345;
    show_bytes((byte_pointer)&x, sizeof(short));
    show_bytes((byte_pointer)&mx, sizeof(short));

    // cs-app pg106 - underlying bit representation stays the same when casting -
    // only interpretation is different. This is true with implicit casting as well.
    short int v=-12345;
    unsigned short uv = (unsigned short)v;
    printf("v = %d, uv = %u\n", v, uv);
    unsigned u = 4294967295u; /* UMax */
    int tu = (int)u;
    printf("u=%u, tu=%d\n", u, tu);

    // cs-app pg111 - printf directives %d, %u, and %x can be used like casting to print
    // unsigned interpretted as int and such.
    int p = -1;
    unsigned up = 2147483648; /* 2^31 */
    printf("p = %u = %d\n", p, p);
    printf("up = %u - %d\n", up, up);

    // cs-app pg113 - sign-extension example
    sign_extension();
    
    
    return 0;
}
