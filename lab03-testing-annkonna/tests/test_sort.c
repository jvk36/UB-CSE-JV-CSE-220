#include <stdio.h>
#include <stdbool.h>

#include "../src/sort.h"
#include "test_sort.h"

int main(int argc, char *argv[])
{
    if (test_sort() == testsort_expected_result) {
        printf("passed\n");
        return 0;
    } else {
        printf("failed\n");
        return 1;
    }
    return 0;
}
