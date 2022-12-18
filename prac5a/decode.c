#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#define MAX_SIZE 10000
#define MAX_LINE_SIZE 80

void dump_characters(void *databuf, int size) {
    if (size<0 || size>MAX_SIZE) return;
    
    for (int i=0; i<size; i++) {
        putchar(*(char*)databuf);
        databuf++;
    }
}

/* 
 * Decode the text in 'data' and copy to 'decode'. Terminate with '\0'.
 *
 * The data consists of chunks. Each chunk consists of an integer
 * identifying the number of characters followed by the characters. 
 *
 * The last chunk has integer value as 0.
 * 
 * You may assume that 'decode' is pointing to a buffer large enough
 * to hold the decoded text.
 */
int decode_data(char *decode, void *data) {
    int num;
    num = *(int *)data;
    while(num != 0){
        data = data + sizeof(int);
        //printf("%c\n", *(char *)data);
        for (int i = 0; i < num; i++){
            *decode++ = *(char *)data++;
        }
        num = *(int *)data;
    }
    *decode = '\0';
    //printf("%c\n", *(char *)decode);
    return 0;
}

/* 
 * Run the program with the command line below:
 *
 *   ./decode <encode.out > decode.out
 *
 * Expected Output: decode.out will contain three lines.
 */
int main(int argc, char *argv[]) {

    void *data = malloc(MAX_SIZE);
    void *decode = malloc(MAX_SIZE);

    int c;
    char *temp = (char *)data;
    while ( (c=getchar()) != EOF ) {
        *temp = (unsigned char)c;
        temp++;
    }
    *temp = '\0';

    int ret = decode_data(decode, data);
    if ( ret == -1 ) {
        printf("\n Failed: size overflow.\n");
        return -1;
    }

    dump_characters(decode, strlen(decode));
}
