#include <stdio.h>

typedef struct lnode { 
  struct lnode *next;
} ListNode;

void ListNodePrint(ListNode *node) {
  ListNode *p;
  for (p = node; p != NULL; p=p->next)
    printf("%p-->", p);
}

int main() {
  ListNode node1, node2, node3;
  node1.next = &node2;
  node2.next = &node3;
  node3.next = NULL;
  ListNodePrint(&node1);
}

