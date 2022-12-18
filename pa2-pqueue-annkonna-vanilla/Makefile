# These variables configure the build.
# We want to use gcc, of course.
CC := gcc
# These CFLAGS are reasonable for a debugging build for C99.
CFLAGS := -g -Wall -Werror -O -std=c99 -D_DEFAULT_SOURCE
# This variable is used to link libraries to tests; you almost certainly
# don't need it, but it's here in case you do.  We'll help you use it on
# Piazza, if you need it.
LDFLAGS :=

# This is the list of tests that should be compiled.  Each test is
# specified by its executable name, which will be test_something.  This
# corresponds to a C file named tests/something.c; see the rule below
# for test_% for more information.
TESTS := test_null test_insert_empty

# This is the first rule in the file, so it's what runs when you type
# make with no arguments.  It will build list.o and validate.o, which
# makes sure your code compiles, but doesn't do anything to test it.
all: src/priority_queue.o src/validate.o

# This rule will run all of the tests defined in TESTS, above.  It
# prints the name of the test, and then runs the test.  If the test
# prints "passed", "failed", or some useful message, then this will
# produce a neat column of output showing the status of your tests.
#
# The for loop here is just a regular shell for loop (see man bash if
# you are interested), but there's some extra weirdness because of make.
# In particular, the leading @ tells make not to print the command
# before it runs it, and the extra semicolons and backslashes are
# because of the way make rules work.
test: $(TESTS)
	@echo
	@for test in $(TESTS); do               \
	    printf "running %-40s ... " $$test; \
	    ./$$test;                           \
	done; echo

# This, and the submission.tar rule, build the submission tarball.  You
# should not change these rules.
submission: submission.tar

submission.tar: src/priority_queue.c src/validate.c
	tar cf submission.tar $^

# This rule should compile any test that:
# * Has its own main function
# * Is in a .c file in tests/
# * Requires only functions from src/list.c and src/validate.c,
#   and C library functions
#
# The filename of the .c file determines the name of the test binary.
# If the file is named sometest.c, then the resulting test binary will
# be test_sometest.
test_%: tests/%.o src/priority_queue.o src/validate.o
	$(CC) -o $@ $^ $(LDFLAGS)

# This compiles a .c source file into a .o object file.  You don't need
# to understand or change this rule.
%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

# This removes stuff that we don't want, and makes sure to remove any
# compiled outputs that might need to be cleaned up to ensure a full
# build.
clean:
	rm -f *~ src/*~ src/*.o tests/*~ tests/*.o submission.tar
	rm -f $(TESTS)

# This is just a bit of make magic that you don't need to worry about.
# It tells make that the rules all, submission, and clean won't actually
# build a file of the same name.
.PHONY: all submission test clean
