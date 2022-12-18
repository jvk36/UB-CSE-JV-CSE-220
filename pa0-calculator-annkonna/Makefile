CC := gcc
CFLAGS := -O -Wall -Werror -std=c99 -D_DEFAULT_SOURCE

TESTS := test-isinteger test-parseint

all: calc

test: $(TESTS)
	./test-isinteger
	./test-parseint

calc: calc.o
	$(CC) -o calc $^

calc-nomain.o: calc.c
	$(CC) -c $< -o calc-nomain.o $(CFLAGS) -Dmain='__attribute__((unused)) nomain'

test-%: tests/test-%.c calc-nomain.o
	$(CC) -o $@ $^ $(CFLAGS)

%.o: %.c
	$(CC) -c $< $(CFLAGS)

clean:
	rm -f calc *.o *~ submission.tar $(TESTS)

submission: submission.tar

submission.tar: calc.c
	tar cf submission.tar $^

.PHONY: all clean submission
