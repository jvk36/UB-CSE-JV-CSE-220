/* tabify: Read standard input, converting spaces to tabs and writing
 *           to standard output. */

#include <stdio.h>

int main(int argc, char *argv[])
{
    /* Your implementation should appear here */
    char input = getchar();
    int count = 0;
    while(input != EOF){
        if(input == ' '){
            count = count + 1;
            input = getchar();
        }
        else{
            if(count == 1){
                putchar(' ');
                putchar(input);
            }
            else{
                for(int i = 0; i < ((count%8 == 0) ? count/8 : 1 + count/8); i++){
                    putchar('\t');
                }
                putchar(input);
            }
            count = 0;
            input = getchar();
        }
    }
    return 0;
}
