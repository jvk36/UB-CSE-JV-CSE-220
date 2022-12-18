#include <stdlib.h>

#include "../src/sort.h"

const bool testsort_expected_result = true;

/* qsort() requires a compare function that returns -1 if x is < y, 0 if
 * x == y, and 1 if x > 1.  For integers, conveniently, this is provided
 * by the - operator.
 *
 * This requires pointers and pointer casting that we haven't covered
 * yet, you are not expected to understand this function (or the usage
 * of qsort() in general). */
static int compare_ints(const void *x, const void *y) {
    return ((long)*(const int *)x) - *(const int *)y;
}

void cse_sort(int array[]) {
    int len;

    /* Count the number of non-zero elements in the array */
    for (len = 0; array[len] != 0; len++)
        ;

    /* Use the C standard library qsort function to sort the array.  See
     * man 3 qsort for more information.  Understanding this function
     * requires an understanding of pointers. */
    qsort(array, len, sizeof(int), compare_ints);
}
