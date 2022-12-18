#include <stdio.h>
#include <stdlib.h>

#define MAX_DATABUF_SIZE 5000

/* Encode the text in data and copy to databuf.
 *
 * Encodes each line of text in data using the format for a chunk in the README.
 * Each chunk consists of an integer identifying the number of characters, the 
 * characters in the line, followed by a number of spaces of padding to get the 
 * chunk to be a multiple of 8 bytes. The final chunk will be an integer containing 0.
 *
 * Note: Notice that databuf is pointing to MAX_DATABUF_SIZE bytes of memory that
 * was allocated using malloc. If databuf overflows this size, the function should
 * return -1, otherwise the size of the data encoded in bytes. 
 *
 */
int encode(void *databuf, char *data) {
    /* Your implementation should appear here */
    strncpy(databuf, data, MAX_DATABUF_SIZE);
    return MAX_DATABUF_SIZE;
}

int main(int argc, char *argv[]) {

    void *databuf = malloc(MAX_DATABUF_SIZE);
    void *data = malloc(DATABUF_SIZE);

    int c;
    char *temp = (char *)data;
    while ( (c=getchar()) != EOF ) {
        *temp = *(char *)c;
    }
 
    int ret = encode(databuf, data);
    if ( ret == -1 ) {
        printf("\n Failed: Buffer overflow.\n");
        return -1;
    }

    for ( int i=0; i<ret; i++) {
        putchar(*databuf);
        databuf++;
    }
}
