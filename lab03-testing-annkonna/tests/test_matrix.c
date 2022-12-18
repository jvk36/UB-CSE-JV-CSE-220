#include <stdio.h>
#include <stdbool.h>

#include "../src/matrix.h"
#include "test_matrix.h"

int main(int argc, char *argv[])
{
    if (verify_matrix(testmatrix_x, testmatrix_y, testmatrix_data) == testmatrix_expected_result) {
        printf("passed\n");
        return 0;
    } else {
        printf("failed\n");
        return 1;
    }
}
