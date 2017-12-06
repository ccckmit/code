struct listNode { 
  struct listNode *next, *prev;
};

#define LIST_HEAD_INIT(name) { &(name), &(name) }
#define LIST_HEAD struct list_head name = LIST_HEAD_INIT(name)
#define INIT_LIST_HEAD(ptr) do { (ptr)->next = (ptr); ptr->prev = (ptr); } while (0)

static inline int list_empty(const struct list_head *head) {
  return head->next == head;
}

static inline void __list_add(struct list_head *new, struct list_head *prev, struct list_head *next) {
  next->prev = new;
  new->next = next;
  new->prev = prev;
  prev->next = new;
}

static inline void list_add_tail(struct list_head *new, struct list_head *head)

