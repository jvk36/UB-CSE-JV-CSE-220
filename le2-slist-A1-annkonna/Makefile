CC := gcc
CFLAGS := -g -Wall -Werror -O -std=c99 -D_DEFAULT_SOURCE

all: list.o

test: testlist
	./testlist

testlist: testlist.o list.o given.o
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

submission:
	echo "Make submission is not used for this lab, read the handout."
	false

clean:
	rm -f *.o *~ testlist

.PHONY: all submission test clean
