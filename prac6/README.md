tabify practice
===

In this practice, you will write a simple text processing utility to replace
ASCII SPACE characters with the appropriate number of ASCII TAB
characters.  This will introduce the concept of data alignment in a context
other than memory addresses, introduce the concept of "filter" programs on
Unix, and further explore the standard I/O library.

Requirements
---

Your program must read its input from _standard input_, the Unix "file"
typically associated with the terminal, and write its output to
_standard output_, also typically associated with the terminal.  Both
standard input and standard output can be replaced with a file on disk
using the shell, however.  Your program will read its input, replacing
ASCII SPACE characters with a number of ASCII TABS that depends on where they
occur on the line, and write the modified data to its output.

The number of TABS to be used for each SPACE is determined by the number
of consecutive SPACE characters. If there is more than one consecutive
SPACE characters, replace them with one or more tabs using the formula:

tabs = (spaces%8 == 0) ? spaces/8 : 1 + spaces/8

If there is only one space before a non-space character, then copy the
SPACE character as is.

For example, if the first character on a line is SPACE, followed by the
character `'a'`, when the file was processed by your program it would
output the same way - a SPACE character followed by the character 'a'.
If the line starts with `'a'`, then nine spaces, then `'b'`, your program
would output the `'a'` character, then two tabs, then the `'b'`.

Your program should make _no other changes_ to its input.  All
characters that are not ASCII SPACE should be passed through unchanged.

Hints
---

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
can cause your `tabify` program to read from the file `input.txt` and
write to the file `output.txt` as follows:

```sh
tabify < input.txt > output.txt
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

Building, Running, and Testing
---

`make` will build your project, and `make test` will run a
simple test suite.

