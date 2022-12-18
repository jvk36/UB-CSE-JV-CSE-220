Testing
===

This lab will require you to write several tests that are similar to
tests that you might write to verify the correctness of your
applications or assignments.  Testing is a key part of software
development, and something that should be approached with forethought
and planning.  For the remainder of this course, complete testing suites
will not be provided during the development phase of projects, and you
will have to write your own tests if you wish to ensure full credit on
assignments.

You will write two types of test for this assignment:

 * A _data structure_ verification, that carefully checks a data
   structure to ensure that it meets the specification for its
   characteristics.  This sort of test is very useful to catch errors in
   the manipulation of either internal structures or final outputs of
   your program.  You will almost certainly wish to employ this sort of
   testing in all future projects in this course.

 * A _function_ verification, which calls a function with controlled
   inputs and observes its output to ensure correct operation.  This
   sort of test is often called a _unit test_, and it checks a single
   function to verify that it meets its specification.  Unit tests are a
   powerful tool for isolating bugs and ensuring that currently-working
   code does not develop problems as changes are introduced (such
   problems or introduced bugs are called _regressions_, and regular
   verification of unit or other tests to ensure that no regressions
   have occurred is called _regression testing_).  You will also want to
   write unit or other functionality tests for all future projects in
   this course.

Note that you are _not generating any matrices_ and that you _do not
need to sort anything_.  You are merely verifying the correctness of
data structures or function operation!

Repository Layout
---

The source for this project is in `src/`, in the form of two header
files and two C files.  The two C files in `src/` are the only files you
should need to modify, and the only files submitted to Autograder; your
complete solution must be in those files.

Several tests to verify the correctness of your tests are provided in
`tests/`.  You may find it helpful to look at these tests, which are
commented for your benefit.  You do not need to change them.

Requirements
---

You must implement two functions for this project.  The details of the
two functions follow, but the functions are `verify_matrix()` in
`src/matrix.c` and `test_sort()` in `src/sort.c`.  You should not modify
any files other than these two files for this assignment.  The
`verify_matrix()` function implements a data structure verification for
the data structure described in Structural Verification, below.  The
`test_sort()` function implements functional verification for the sort
function `cse_sort()`, which will be provided by the test, and is
described in the section Functional Verification, below.

### Structural Verification

You must implement the function:

```c
bool verify_matrix(int x, int y, int **matrix);
```

This function accepts an X dimension, a Y dimension, and a `matrix` of
`y` rows and `x` columns; although it is declared as `int **`, this is
the same type of matrix as returned by `parse_life()` in PA1, and you
should access it as a two-dimensional array.  Note that it is stored in
Y-major orientation; that is, `matrix` ranges from `matrix[0][0]` to
`matrix[y - 1][x - 1]` (again, as in PA1).

You should verify the following properties:

 * The matrix is _square_.  That is, its x dimension and y dimension are
   the same.  Because there is no way in C to determine the size of an
   array, your function must consult its `x` and `y` arguments to verify
   this.
 * Every _row_ in the matrix is _sorted in non-decreasing order_.  This
   means that every element of each row is _greater than or equal to_
   the element in the previous index.
 * The _first element_ of every row forms a sequence _sorted in
   non-decreasing order_.  Like the individual rows, every element in the
   _first column_ is  greater than or equal to the element in the
   previous index.

Your function should return `true` if the matrix satisfies these
properties, and `false` if it does not.  Your function most not attempt
to access any array element that is outside of the specified dimensions
— _even if those dimensions are non-square_.

This matrix, for example, would satisfy the required properties:

```
x = 3, y = 3
```
<table>
<tr><td>1</td><td>2</td><td>3</td></tr>
<tr><td>2</td><td>7</td><td>7</td></tr>
<tr><td>97</td><td>98</td><td>99</td></tr>
</table>

Note that this matrix is square, that every row is in non-decreasing
order, and that the first column is in non-decreasing order as well.
Think about what this means in terms of cell indices.

This matrix would not meet the requirements due to its non-square
nature:

```
x = 3, y = 4
```
<table>
<tr><td>1</td><td>2</td><td>3</td></tr>
<tr><td>2</td><td>7</td><td>7</td></tr>
<tr><td>97</td><td>98</td><td>99</td></tr>
<tr><td>99</td><td>99</td><td>99</td></tr>
</table>

Note that every row and column is in non-decreasing order, but that it
has four rows and only three columns.

Similarly, this matrix is square, but its first column violates the
non-decreasing order requirement:

```
x = 3, y = 3
```
<table>
<tr><td>2</td><td>2</td><td>3</td></tr>
<tr><td>1</td><td>7</td><td>7</td></tr>
<tr><td>97</td><td>98</td><td>99</td></tr>
</table>

### Functional Verification

You must implement the function:

```
bool test_sort();
```

This function must call the function `cse_sort()`, which has the
following specification, and verify that it is correct:

```
void cse_sort(int array[]);
```

The `cse_sort()` function sorts the given array of integers into
non-decreasing order, storing the result in the given array.  The array
of integers may have any number of elements, but the last element of the
array **MUST** be zero, and the number zero **MUST NOT** appear anywhere
else in the array.

You must call `cse_sort()` with a range of valid inputs, and ensure that
it meets its specification.  If it behaves correctly, `test_sort()`
should return `true`.  If it is not correct, `test_sort()` should return
`false`.

The autograder will never attempt to test a `cse_sort()` function that
makes invalid memory accesses, provided that the array it is passed is
well-formed.  It may, however, do _anything else_, ranging from working
correctly to arbitrarily corrupting its input.

Hints
---

Your matrix verification will probably use a pair of nested `for` loops,
similar to the loops you used in PA1.  Think about what the loop indices
should be, and how you should ensure that you do not attempt to access
non-existent array elements.

Remember that you cannot declare an array initializer as an argument to
a function, but that you _can_ declare and initialize an array as the
value of a variable.  For example:

```
int testarray[] = { 3, 2, 1, 0 };
cse_sort(testarray);
```

Consider:

 * Edge cases
 * Very small and very large inputs
 * Entirely non-compliant behaviors

The `make test` command will run some local tests against your
imlementation.

Submission
---

Type `make submission` in the top-level directory of this project's Git
workspace to build the file `submission.tar`, which should be submitted
to Autograder.

Grading
---

You will be given 72 hours to complete this lab (rather than the usual
36).  That is because this lab has two parts, and you are unlikely to
complete both for full credit within lab time.  Plan your time wisely.

The grading rubric for this project will be as follows:

| Points | Requirement                                     |
|--------|-------------------------------------------------|
|      1 | `verify_matrix()` verifies a well-formed matrix |
|      4 | `verify_matrix()` identifies invalid matrices   |
|      1 | `test_sort()` verifies a correct `cse_sort()`   |
|      4 | `test_sort()` identifies bad sorts              |

Note that a _trivial implementation_ (that is, an implementation that
does not attempt to distinguish between valid and invalid conditions,
and simply returns `true` or `false`) will receive no credit.
