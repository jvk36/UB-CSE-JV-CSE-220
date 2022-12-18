#include <stdio.h>
#include <stdbool.h>

/*
 * The isinteger() function examines the string given as its first
 * argument, and returns true if and only if the string represents a
 * well-formed integer.  A well-formed integer consists only of an
 * optional leading - followed by one or more decimal digits.
 *
 * Returns true if the given string represents an integer, false
 * otherwise.
 */
bool isinteger(char *str);

/*
 * The parseint() function parses a well-formed string representation of
 * an integer (one which would return true from isinteger()) and returns
 * the integer value represented by the string.  For example, the string
 * "1234" would return the value 1234.  This function does not need to
 * handle badly-formed strings in any particular fashion, its operation
 * on badly-formed strings is undefined.
 *
 * Returns the integer value stored in the given string.
 */
int parseint(char *str);

/*
 * The main function is where C programs begin.
 *
 * This function parses its arguments and returns the value they
 * represent.  Its arguments are either:
 *
 *  - A single argument representing an integer
 *  - Three arguments, where the first and third are integers and the
 *    second is an operator to be performed on those integers
 *
 * Remember that the argument in argv[0] is the name of the program, so
 * a program passed exactly one argument on the command line will
 * receive _two_ arguments: its name in argv[0] and the provided
 * argument in argv[1].
 *
 * Arguments:
 * argc - The number of arguments received
 * argv - The arguments received as an array of C strings
 *
 * Returns 0 if the arguments are well-formed and the calculation could
 * be performed, non-zero otherwise.
 */
int main(int argc, char *argv[]) {
    /* Your main program logic should go here, with helper logic in the
     * functions isinteger() and parseint(), which you can place below
     * the closing brace of main() */

    return 0;
}

/* You should implement isinteger() and parseint() here */
