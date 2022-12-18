Lab Exam: Singly-Linked List
===

In this lab exam, you will use the things you have learned in class and
from your current homework to implement two operations on a
singly-linked list.  Note that your homework is a _doubly_-linked list,
which has slightly different semantics!

Academic Integrity
---

_**THIS IS AN EXAMINATION**_.  You *MUST NOT* use any unauthorized
resources for this examination.  You are not permitted to consult _any
person other than your lab TAs_ for assistance with this examination.
Receiving code from any other person or source is a violation of the
course academic integrity policies, and discovery of this will result in
failure in this course.  All other course academic integrity policies
apply.

You must complete and submit this examination during your scheduled lab
session, in lab.

The specific resources allowed for this examination appear below, in the
section _Resources_.

Resources
---

You may use any Unix man pages on the lab machines for reference.  As a
reminder, you can access man pages with the command `man <topic>` at the
prompt; for example, the manual page for the functions in `string.h`
(which you _MAY NOT USE_ in your implementation, but you might find the
documentation useful) is available via `man string`.  Manual pages are
also available via `M-x man` in Emacs.

You may use info pages, accessible via `info <topic>` at the prompt.  In
particular, you may use `info gcc`.

You may _NOT_ use your previous lab submissions or assignments for
reference, and you may not use the course texts.

Online resources such as Stack Overflow, GitHub repositories, or any
Google searches are forbidden for this examination.  You should use your
web browser _only_ to accept the GitHub Classroom invitation for this
repository, and to view this repository (including this README) on
GitHub if desired.

List Structure
---

The singly-linked list structure is defined in `list.h`, and it
looks like:

```c
struct ListNode {
    long value;
    struct ListNode *next;
};
```

The empty list is represented by `NULL`, and a well-formed list is
either:

 * `NULL`
 * One or more `struct ListNode`s with a `next` pointer pointing either
   to another valid `struct ListNode` or, for the final node, `NULL`.

Given Code
---

You have been given the following function, in `given.c`:

 * `struct ListNode *list_prepend(struct ListNode *list, long value)`:
   Allocates a single list node containing the given value, and prepends
   it to the given list.

This function will allow you to build a well-formed list for testing and
provides a reference for using the list structure.

You have also been given a single test, in `testlist.c` (compiled using
`make test`), which builds a short list, counts its elements, and then
removes an element and counts the elements again.  _You must implement
any other testing you wish to use._ You may find it helpful to use the
given test in conjunction with `gdb` to explore the behavior of your
functions.

Requirements
---

You must implement the following functions in `list.c`, which are
defined in `list.h` but not implemented:

 * `int list_length(struct ListNode *list)`:
   Counts the number of nodes in the given list, and returns the result.
 * `struct ListNode *list_remove(struct ListNode *list, long value)`:
   Find the first list node containing the value `value`, remove it from
   the list, free it, and return the resulting list.  If no list node
   contains the given value, the list is returned unchanged.

Remember that this is a _singly linked list_, so the logic for removing
a list element will differ somewhat from your assignment!  It is,
however, substantially similar.

You can expect that every list passed to your function will be well-formed.

Submission
---

Submit only the file `list.c` to Autograder.

You must complete and submit this project during your scheduled lab
session.

Grading
---

Points will be awarded as follows:

 * 2 pts: `list_length()` works correctly on lists of differing length.
 * 3 pts: `list_remove()` works correctly in various circumstances.

Crashes in the Autograder _almost certainly indicate bugs in your
program_.  The Autograder scripts try to defend themselves against
erroneous implementations, but an incorrect implementation of list
operations can still cause crashes.
