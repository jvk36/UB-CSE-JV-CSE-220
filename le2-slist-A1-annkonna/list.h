#ifndef LIST_H_
#define LIST_H_

struct ListNode {
    long value;
    struct ListNode *next;
};

struct ListNode *list_prepend(struct ListNode *list, long value);

int list_length(struct ListNode *list);
struct ListNode *list_remove(struct ListNode *list, long value);

#endif /* LIST_H_ */
