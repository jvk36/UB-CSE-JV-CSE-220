#include <stdio.h>

/* This is the function prototype for the parseint() function that is
 * defined in calc.c.  It appears here so that functions in this file
 * know how to call parseint() correctly.  The prototype for this
 * function must match the prototype of parseint() in calc.c
 * exactly. */
int parseint(char *str);

/* This program runs a series of tests on the parseint() function that
 * you have defined.  If it detects any errors, it will print a message.
 * If it does not detect any errors, it will complete with no output.
 * It uses fprintf(stderr, ...) because this construction ensures that
 * the messages that it prints are sent to the terminal immediately.
 * This is important because it helps make sure that any errors printed
 * by a test are visible to the user even if a later test crashes.  We
 * will discuss fprintf(stderr, ...) in greater detail at a future
 * time. */
int main(int argc, char *argv[])
{
    /* We only have to check valid inputs, because the behavior of
     * parseint() is explicitly undefined for invalid inputs.  Check
     * zero, a small positive integer, a large positive integer, a small
     * negative integer, and a large negative integer. */
    if (parseint("0") != 0) {
        fprintf(stderr, "Failed to parse 0\n");
    }
    if (parseint("1024") != 1024) {
        fprintf(stderr, "Failed to parse 1024\n");
    }
    if (parseint("-32") != -32) {
        fprintf(stderr, "Failed to parse -32\n");
    }
    /* These should not be materially different, but bugs may show up in
     * integers with more digits, or at boundary conditions. */
    if (parseint("2147483647") != 2147483647) {
        fprintf(stderr, "Failed to parse 2147483647 (2^31 - 1)\n");
    }
    if (parseint("-2147483648") != -2147483648) {
        fprintf(stderr, "failed to parse -2147483648 (-2^31)\n");
    }
    
    return 0;
}

