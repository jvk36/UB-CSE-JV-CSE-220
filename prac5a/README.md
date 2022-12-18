Pointer Math Practice
===

In this practice, you will implement a decoding function that uses
pointer math to interpret bytes stored in memory.

Requirements
---

You must implement the `decode_data()` function in `decode.c`.  This
function will be passed a buffer of type `void *` containing input data
called 'data' and a character array that you will fill using the
input data called 'decode'.

The input data stores a sequence of characters that are split into
several chunks.  Each chunk consists of an unsigned integer of type
`int` which stores the number of characters in the chunk followed
immediately by character data consisting of the number of characters
stored in the int. An example chunk would be:

| (int)5 | 'H' | 'e' | 'l' | 'l' | 'o' 

The final chunk will consist of a `int` containing the value `0` and
no other character data.

To decode this information, you should copy the _character data_ from
each chunk into the given character array, followed by an ASCII NUL byte
to produce a properly terminated C string.  Note that the termination
byte does _not_ appear in the input chunks!

Building, Running, and Testing
---

The command `make` will build a binary called `decode` that you can
run.

You can test your program against the provided `encode.out` file by
running:

`./decode < encode.out > decode.out`

You should see three lines of text if your function is working
correctly on the provided input.  If it is not, you will see junk,
whitespace, your program will crash, etc.

Hints
---

Remember that pointer math on a `void *` pointer is in terms of _bytes_,
while many data types (such as `size_t`!) are larger than one byte.  You
can add increments of `sizeof(type)` to adjust a `void` pointer by the
size of another type.

Pointer casting works like casting of any other type.  For example:

```C
int readptr(void *ptr) {
    return *(int *)ptr;
}
```

This function accepts a `void` pointer argument, but interprets the data
stored at the pointer as an `int` pointer.  A `void` pointer _cannot be
directly dereferenced_, you will _have_ to cast it in order to read the
data to which it points.


