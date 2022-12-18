#include <stdio.h>
#include <stdbool.h>

/* This is the function prototype for the isinteger() function that is
 * defined in calc.c.  It appears here so that functions in this file
 * know how to call isinteger() correctly.  The prototype for this
 * function must match the prototype of isinteger() in calc.c
 * exactly. */
extern bool isinteger(char *str);

/* This program runs a series of tests against isinteger().  It uses
 * fprintf(stderr, ...) because this construction ensures that the
 * messages that it prints are sent to the terminal immediately.  This
 * is important because it helps make sure that any errors printed by a
 * test are visible to the user even if a later test crashes.  We will
 * discuss fprintf(stderr, ...) in greater detail at a future time. */
int main(int argc, char *argv[])
{
    /* First, test checking a correct, positive integer.  This test
     * checks a negative (using !) because isinteger() should return
     * true for a correct integer.  If it returns false (the negative of
     * which is true), that means the test detected a bug. */
    if (!isinteger("42")) {
        fprintf(stderr, "error: isinteger() did not accept 42\n");
    }
    /* Ditto a correct, negative integer */
    if (!isinteger("-31337")) {
        fprintf(stderr, "error: isinteger() did not accept -31337\n");
    }

    /* Now try checking a word that is not an integer.  This should
     * return false if isinteger() works correctly, so it is not
     * negated. */
    if (isinteger("systems")) {
        fprintf(stderr, "error: isinteger() accepted the word systems\n");
    }

    /* Try checking a valid integer followed by a minus sign */
    if (isinteger("31337-")) {
        fprintf(stderr, "error: isinteger() accepted the non-number 31337-\n");
    }

    /* Try checking a valid integer followed by a letter */
    if (isinteger("42a")) {
        fprintf(stderr, "error: isinteger accepted the non-number 42a\n");
    }
    return 0;
}
