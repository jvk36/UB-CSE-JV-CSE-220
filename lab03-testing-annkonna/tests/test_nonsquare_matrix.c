#include <stdbool.h>

#include "test_matrix.h"

const bool testmatrix_expected_result = false;

int testmatrix_x = 3;
int testmatrix_y = 4;

/* The casting here (types in parentheses) is to allow us to create a
 * type of two-dimensional matrix that is different from the type of
 * two-dimensional matrix declared as int testmatrix_data[][].  This is
 * necessary because of the fact that the inner dimension of this matrix
 * (the X dimension) is not a constant size.  Remember that C requires
 * multi-dimensional array indices to be explicit for all but the
 * outermost dimension.  This would prevent us from testing matrices of
 * differing sizes.
 *
 * The matrix created in this fashion is an array of pointers to arrays,
 * each of which contains integers.  If we created a simple
 * two-dimensional matrix, it would not include the pointers in the
 * outer array, which would be problematic for us for reasons that are
 * not important right now.
 *
 * You don't have to understand the details of this casting, we'll get
 * to it later.  You can see the structure of the matrix by looking only
 * at the values in the matrix. */
int **testmatrix_data = (int **)(int *[]){
    (int *)(int []){ 1, 2, 3 },
    (int *)(int []){ 2, 3, 4 },
    (int *)(int []){ 3, 4, 5 },
    (int *)(int []){ 4, 5, 6 }
};
