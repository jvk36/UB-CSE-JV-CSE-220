#include <stdio.h>
#include <stdlib.h>

#define FILENAME "data.bin"
#define MAX_SIZE 80

/* Decode the data provided in databuf into the array data.
 *
 * The format of the data in databuf is as described in the README.  You
 * may assume that the data is well-formed, and need not perform any
 * error checking.
 */
void decode_buffer(void *databuf, char *data) {
    /* Your implementation should appear here */
}

/* You should not modify this main function.  Modification of main may
 * cause your program to fail autograding.
 */
int main(int argc, char *argv[]) {
    FILE *f;
    size_t file_size;
    void *databuf;
    char data[MAX_SIZE + 1];            // 80 chars plus NUL

    if (argc == 1) {
        f = fopen(FILENAME, "rb");
    } else {
        if ((f = fopen(argv[1], "rb")) == NULL) {
            fprintf(stderr, "Error opening named input file\n");
            return -1;
        }
    }
    if (f == NULL) {
	printf("Error opening data file.  Is your checkout complete?\n");
	return -1;
    }
    fseek(f, 0, SEEK_END);
    file_size = ftell(f);
    rewind(f);

    databuf = malloc(file_size);

    fread(databuf, sizeof(char), file_size, f);

    decode_buffer(databuf, data);
    printf("%s\n", data);

    free(databuf);
}
