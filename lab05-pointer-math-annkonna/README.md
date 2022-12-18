Pointer Math
===

In this recitation, you will implement a decoding function that uses
pointer math to interpret bytes stored in memory in an a regular but
unpredictable structure.  You will learn about pointer math, raw memory
access, and data representations.

Requirements
---

You must implement the `decode_buffer()` function in `ptrmath.c`.  This
function will be passed a buffer of type `void *` containing input data
and a character array that you will fill using the input data.

The input data stores a sequence of characters that are split into
several chunks.  Each chunk consists of an unsigned integer of type
`size_t` which stores the number of characters in the chunk followed
immediately by character data consisting of the number of characters
stored in the size_t, followed immediately by enough padding bytes to
round the chunk out to a multiple of 8 bytes.  An example chunk might
look like this:

| (size_t)5 | 'H' | 'e' | 'l' | 'l' | 'o' | pad | pad | pad |

The final chunk will consist of a `size_t` containing the value `0` and
no character data or padding.

To decode this information, you should copy the _character data_ from
each chunk into the given character array, followed by an ASCII NUL byte
to produce a properly terminated C string.  Note that the termination
byte does _not_ appear in the input chunks!

Building and Submission
---

The command `make` will build a binary called `ptrmath` that you can
run.  You should see a meaningful message if your decoder is working
correctly on the provided input.  If it is not, you will see junk,
whitespace, your program will crash, etc.

You should submit _only the file `ptrmath.c`_ to Auto grader.

Testing
---

You can test your program against the provided `data.bin` file by
running `./ptrmath`, as described above.  You can also create messages
of your own choosing by running `./encoder filename "message text"`,
which will write the given message text into the named file according to
the format specified in [Requirements](#requirements), and then test
decoding of the message with `./ptrmath filename`, where filename is the
same file given to `encoder`.

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

When calculating padding, consider the modulus operator (`%`).

Grading
---

Points will be awarded as follows:

 * 1 pt: A single chunk with no padding is correctly decoded
 * 2 pts: Multiple chunks with no padding are correctly decoded
 * 2 pts: Arbitrary chunks are correctly decoded
