CC := gcc
CFLAGS := -O -g -Wall -Werror -std=c99 -D_DEFAULT_SOURCE

TESTFILES := onetab twotab atabz qbf roster 3col

all: tabify

tabify: tabify.o
	$(CC) -o $@ $^

# This test rule represents a way to run a battery of tests effectively,
# but is more complicated than running a single test.  It requires
# understanding both shell scripting and the interaction between Make
# and the shell.  The next rule (testone) shows how you would
# individually run your program against a single file and then compare
# it.
test: tabify
	@for file in $(TESTFILES); do                                   \
	    printf "Testing %-15s: " $$file.txt;                        \
	    ./tabify < inputs/$$file.txt > outputs/$$file.txt;        \
	    cmp -s outputs/$$file.txt outputs/$$file.expected;          \
	    (test $$? -eq 0 && echo passed) || echo failed;             \
	done

# This is how you would run a single text.  Note that you may not want
# to redirect output (and may want to pipe into something like od or xxd
# instead) for your own testing, as follows:
#
# ./tabify < inputs/atabz.tzt | od -t x1 -a
#
# You could also, of course, just run the command as below and then
# examine the output file:
#
# od -t x1 -a outputs/atabz.txt
#
# The @ sign before the second line instructs Make not to print the
# command, but only the output of the command.
onetest: tabify
	./tabify < inputs/atabz.txt > outputs/atabz.txt
	@(cmp -s outputs/atabz.expected outputs/atabz.txt && echo passed) || echo failed

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -f *~ *.o tabify
	rm -f outputs/*.txt

.PHONY: all clean test
