CC := gcc
CFLAGS := -g -Wall -Werror -O -std=c99 -D_DEFAULT_SOURCE

OUT := mytest
IN := ptr_arith_3_8_2.o

all: $(OUT)

$(OUT): $(IN)
	$(CC) -o $@ $^ 
#	$(CC) -o $@ $^ $(LDFLAGS) -lcurses

%.o: %.c
	$(CC) -c $< -o $@ $(CFLAGS)

clean:
	rm -f *~ *.o
	rm -f $(OUT)

.PHONY: all clean
