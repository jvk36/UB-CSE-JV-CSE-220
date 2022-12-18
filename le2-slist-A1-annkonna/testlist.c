#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "list.h"

int main(int argc, char *argv[])
{
    struct ListNode *list = NULL;
    bool correct = true;
    int len;

    /* This should build a list of 3 elements, containing [ 10 20 30 ] */
    list = list_prepend(list_prepend(list_prepend(NULL, 30), 20), 10);

    /* Check the list count, recording the length */
    if ((len = list_length(list)) != 3) {
        printf("List of length 3 was counted as %d\n", len);
        correct = false;
    }

    /* Remove the middle list element */
    list = list_remove(list, 20);

    /* Repeat the count, and check that the node was removed */
    if ((len = list_length(list)) != 2) {
        printf("List element was not removed or list of length 2 was miscounted as %d\n", len);
        correct = false;
    }

    /* Invert correct since a return value of 0 means success */
    return !correct;
}

