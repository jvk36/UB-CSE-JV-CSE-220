CC := gcc
CFLAGS := -g -Wall -Werror -O2 -std=c99 -D_DEFAULT_SOURCE

all: test

test: test.o tolower.o
	$(CC) -o $@ $^

clean:
	rm -f test *.o *~

submission:
	echo "There is no make submission for this project, submit toupper.c"

%.o: %.c
	$(CC) -c $< $(CFLAGS)

.PHONY: all clean submission
