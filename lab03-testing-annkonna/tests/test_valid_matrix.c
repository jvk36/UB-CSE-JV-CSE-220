#include <stdbool.h>

#include "test_matrix.h"

const bool testmatrix_expected_result = true;

int testmatrix_x = 3;
int testmatrix_y = 3;

/* See the comments in test_nonsquare_matrix.c for why this looks
 * weird. */
int **testmatrix_data = (int **)(int *[]){
    (int *)(int []){ 1, 2, 3 },
    (int *)(int []){ 2, 3, 4 },
    (int *)(int []){ 3, 4, 5 } };
