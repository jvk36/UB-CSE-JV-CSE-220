#include <stdlib.h>

#include "list.h"

struct ListNode *list_prepend(struct ListNode *list, long value) {
    struct ListNode *node = malloc(sizeof(struct ListNode));
    node->value = value;
    node->next = list;

    return node;
}
