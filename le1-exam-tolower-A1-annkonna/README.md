Lab Exam: String Functions
===

This lab exam will test your understanding of C arrays, strings, and
character manipulations.  It will use techniques that you have
previously seen in lecture and practiced in the Command-Line Calculator
assignment.

For this exam, you will implement _two functions_ in the file
`tolower.c`.  The function prototypes for these functions, as well as
comment documentation, already appear in this file.  The requirements
for these functions appear later in this README.

Academic Integrity
---

_**THIS IS AN EXAMINATION**_.  You *MUST NOT* use any unauthorized
resources for this examination.  You are not permitted to consult _any
person other than your lab TAs_ for assistance with this examination.
Receiving code from any other person or source is a violation of the
course academic integrity policies, and discovery of this will result in
failure in this course.  All other course academic integrity policies
apply.

The specific resources allowed for this examination appear below, in the
section _Resources_.

Resources
---

You may use any Unix man pages on the lab machines for reference.  As a
reminder, you can access man pages with the command `man <topic>` at the
prompt; for example, the manual page for the functions in `string.h`
(which you _MAY NOT USE_ in your implementation, but you might find the
documentation useful) is available via `man string`.  Manual pages are
also available via `M-x man` in Emacs.

In particular, you will probably want to consult `man ascii`.

You may use info pages, accessible via `info <topic>` at the prompt.  In
particular, you may use `info gcc`.

You may _NOT_ use your previous lab submissions or assignments for
reference, and you may not use the course texts.

Online resources such as Stack Overflow, GitHub repositories, or any
Google searches are forbidden for this examination.  You should use your
web browser _only_ to accept the GitHub Classroom invitation for this
repository, and to view this repository (including this README) on
GitHub if desired.

Requirements
---

You must implement two functions that are equivalents of functions
provided by the C standard library.  You _MUST NOT USE_ the C standard
library equivalent or related functions in your implementation.  Your
implementation should not call any functions from the standard library.

The two functions you must implement are:

 * `bool cse_isupper(char c)`: This function returns true if the
   character in `c` is an uppercase character between A and Z
   (inclusive).  Note that the C standard library function `isupper()`
   both accepts and returns an `int`, not `char` or `bool`, but the
   behavior is equivalent.

 * `void cse_strlower(char str[])`: Change all uppercase ASCII
   characters in the C string `str` to their lowercase equivalents.  For
   example, A would become a, and G would become g.  All other
   characters in `str` remain unchanged.

Hints
---

Your `cse_strlower()` implementation is not required to use
`cse_isupper()`, but it is intended to be helpful.

Note that every ASCII lowercase character is in alphabetic order, as is
every ASCII uppercase character.  Recall how you converted an ASCII
digit to an integer in your calculator assignment.

Testing
---

The file `test.c` is provided to you with an empty `main()` function.
You may implement any tests that you like in `test.c`, compile and link
it with your string functions using the command `make test`, and then
run `./test` to run the tests.  No other tests will be provided to you.

You are permitted to submit to Autograder as many times as you need.
Autograder will only report your scores, however, it does not give
particular detailed output that would be useful for debugging.

Grading
---

You will submit only `tolower.c` to Autograder.

Points will be awarded as follows:

 * 4 pts: `cse_isupper()` correctly identifies uppercase ASCII
   characters and not other characters as uppercase.
 * 6 pts: `cse_strlower()` correctly converts every uppercase ASCII
   character in a C string to lowercase and leaves all other characters
   unchanged.

Full credit on this assignment will therefore report 10 points on Autograder.
