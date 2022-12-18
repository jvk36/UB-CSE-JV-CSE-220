Command-Line Calculator
===

You should have received a detailed handout for this project.  It
contains the project requirements and specific instructions for
completing this exercise.

This project requires you to implement a calculator program that accepts
operations as command line arguments and prints its result to standard
output.

Academic Integrity
---

Sharing this source code with anyone but course staff, or showing any
part of this source code to anyone but course staff, is a violation of
the course academic integrity policy and may result in sanctions.

Repository Layout
---

The only file you should modify in this repository is `calc.c`, which
contains given code and will be the implementation of your program.

The file `Makefile`, a configuration file for the `make` utility,
described below, and this README are the only other files in this
top-level directory as given.

The `tests` directory contains sources for several test programs that
can be used to test your code.  You may examine the source files in this
directory if you like, but you do not need to modify them.

Building and Submitting Your Project
---

This repository uses `make`, a program to manage the build process for
other programs.  You will learn more about Make later in the semester.
You will need to know three Make commands to complete this project, and
one will help you test your program.  You do not need to modify the
Makefile (this project's configuration for Make) for this assignment.
All four of these commands should be run from the same directory
containing this README, the Makefile, and `calc.c`.

 * `make` or `make calc`: Both of these commands will build the program
   `calc` from the file `calc.c`.
 * `make test`: This command will run a set of tests against your
   program.
 * `make clean`: This command will clean up the build products from
   building the program `calc` or a submission tarball.
 * `make submission`: This command will create the file
   `submission.tar`, which is the file that you should submit to
   Autograder.

Note that you must run `make` or `make calc` to rebuild your project
each time you make changes, and that you must run `make submission`
every time you want to submit a new version to Autograder to build a new
submission tarball.

Running Your Project
---

Unlike many other operating systems, the default configuration of most
Unix systems does not include the current directory in the shell's
command search path.  Therefore, you must provide a _relative_ or
_absolute_ path to a binary in the current directory in order to run it.
The special directory entry `.` represents the current directory, so a
relative path to the `calc` binary created by `make calc` is `./calc`.
You can type `./calc` at the command prompt to run your built binary.
(You will need to provide command line arguments to run it properly!)

Testing Your Project
---

As described above, `make test` will run some tests against your
project.  They will, however, test _only_ `isinteger()` and
`parseint()`.  You are responsible for designing and running your own
tests against the calculator functionality of your project.

Note that `make test` will not compile run correctly until you have at
least a minimal implementation of `isinteger()` and `parseint()` (they
can simply return immediately, and the tests will compile).  If you get
an error like the following (or a similar error for `parseint`), it is
because your implementation is not complete enough to test:

```
test-isinteger.c:(.text+0xc): undefined reference to `isinteger'
```
