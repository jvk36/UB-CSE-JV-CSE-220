untabify
===

In this lab you will write a simple text processing utility to replace
ASCII TAB characters with the appropriate number of ASCII SPACE
characters to reach the next "tab stop".  This will introduce the
concept of data alignment in a context other than memory addresses,
introduce the concept of "filter" programs on Unix, and further explore
the standard I/O library.

Requirements
---

Your program must read its input from _standard input_, the Unix "file"
typically associated with the terminal, and write its output to
_standard output_, also typically associated with the terminal.  Both
standard input and standard output can be replaced with a file on disk
using the shell, however.  Your program will read its input, replacing
ASCII TAB characters with a number of spaces that depends on where they
occur on the line, and write the modified data to its output.

The number of spaces to be used for each tab is determined by the number
of spaces since the beginning of the line (that is, either the beginning
of the file or the most recent ASCII NEWLINE character).  Tab "stops"
occur every 8 characters in an ASCII file; when an ASCII TAB occurs, the
next character printed should appear _at the next 8-byte boundary_.
Sound familiar?  This is very similar to memory padding for 8-byte
values, except that it is dependent on _line location_ instead of
_memory location_!  The major difference is that a TAB occurring on a
tab stop skips to the next tab stop (a full 8 spaces), whereas memory
padding would insert no padding at all.

For example, if the first character on a line is TAB, followed by the
character `'a'`, when the file was processed by your program it would
output _eight spaces_ at the beginning of the line, followed by the
`'a'`.  If the line contained `'a'`, then TAB, then `'b'`, your program
would output the `'a'` character, then 7 spaces, then the `'b'`.

Your program should make _no other changes_ to its input.  All
characters that are not ASCII TAB should be passed through unchanged.

Hints
---

You might find `man ascii` helpful, but remember that ASCII TAB is
represented in C as `'\t'` and that ASCII NEWLINE is represented in C as
`'\n'`.  It is better to use these character codes than to use their
ASCII integer values.

You may use any of the Unix or C Standard I/O functions to read from
standard input and standard output, but I recommend that you use
`getchar()` and `putchar()`.  These functions conveniently read and
write one character at a time without requiring a memory buffer, and
`getchar()` can easily signal end-of-file.  See `man getchar` and
`man putchar` for more information.

The shell `<` operator "redirects" standard input from a file, and the
`>` operator redirects standard output to a file.  Thus, if you have a
program that reads from standard input (which would normally be the user
typing at the keyboard in a terminal), you can cause it to read from a
file instead.  These operators each take a filename as an argument.  You
can cause your `untabify` program to read from the file `input.txt` and
write to the file `output.txt` as follows:

```sh
untabify < input.txt > output.txt
```

You will see this used in the given Makefile.

Emacs has the built-in commands `tabify` and `untabify`, which operate
on the current region (this is the visible text selection, which is
called the "region" in Emacs-speak).  They can be run by pressing M-x
(hold down the "Meta" key, probably labeled "Alt" on your keyboard, end
press the X key; alternately, press and release the Escape key and then
press the X key) and then typing `tabify` or `untabify` and pressing
Enter.  The `tabify` command will turn runs of spaces into ASCII TAB
where appropriate, and the `untabify` command will do exactly what your
`untabify` program should do.  Note that their correct operation (for
this project) depends on the fact that you have not configured Emacs to
use some spacing other than 8 for an ASCII TAB.  You may find these
functions useful during this project, if you are an Emacs user.

Both Emacs and vim are capable of viewing tabs as non-whitespace
characters for convenience.  In Emacs, you can turn this on (and off)
with `M-x whitespace-mode` (see the previous paragraph for details on
what this means).  In vim it is a bit more complicated, but you can run
(from command mode) `:set listchars=tab:>-`, and then `set list` will
turn on visible tabs and `set list!` will turn them off.

I have used the command `od` (octal dump) in class before, and you may
find the following incantation useful: `od -t x1 -a filename`.  This
will dump the file `filename` to the screen in hexadecimal, along with
the ASCII equivalent of each byte.  For the ASCII TAB character, it will
print `ht` (for horizontal tab).  The `od` command has many options, you
should explore its man page.  The `xxd` command, which is a native
hexadecimal dumping tool, may also be useful to you.

Building and Testing
---

As usual, `make` will build your project, and `make test` will run a
simple test suite.

Submission
---

Submit _only_ the file `untabify.c` to Autograder.

Grading
---

Points will be awarded as follows:

 * 1 pt: A single tab at the beginning of a line is correctly converted to spaces
 * 1 pt: Multiple tabs at the beginning of a line are correctly
   converted to spaces
 * 1 pt: A single tab at a location other than the beginning of the line
   is correctly converted to spaces
 * 2 pts: Tabs in various locations in the line are correctly converted
   to spaces
