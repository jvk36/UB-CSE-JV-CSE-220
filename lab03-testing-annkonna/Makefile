CC := gcc
CFLAGS := -g -Wall -Werror -O -std=c99 -D_DEFAULT_SOURCE

TESTS := test_valid_matrix test_nonsquare_matrix test_valid_sort test_null_sort

all: src/sort.o src/matrix.o

test_%_matrix: src/matrix.o tests/test_matrix.o tests/test_%_matrix.o
	$(CC) -o $@ $^ $(LDFLAGS)

test_%_sort: src/sort.o tests/test_sort.o tests/test_%_sort.o
	$(CC) -o $@ $^ $(LDFLAGS)

tests/test_sort.o: tests/test_sort.h

tests/test_%_sort.o: tests/test_matrix.h

tests/test_matrix.o: tests/test_matrix.h

tests/test_%_matrix.o: tests/test_matrix.h

test: $(TESTS)
	@for test in $(TESTS); do        \
	    printf "%-30s ... " $$test;  \
	    ./$$test;                    \
	done || true

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

submission: submission.tar

submission.tar: src/matrix.c src/sort.c
	tar cf submission.tar $^

clean:
	rm -f *~ src/*~ tests/*~ src/*.o tests/*.o submission.tar
	rm -f test_*_matrix test_*_sort

.PHONY: all clean test submission
