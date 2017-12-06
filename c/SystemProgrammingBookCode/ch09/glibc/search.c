#include <search.h>
#include <stdlib.h>
#include <stdio.h>

char *names[] = { "George", "Mary", 
"Bob", "Snoopy", "Mickey", "John", "Mike" };

typedef struct {
  char *name;
  int  id;
} person;

#define person_print(p) \
printf("id=%d name=%s\n", p->id, p->name)

int compare(const void *pa, const void *pb) {
  person *p1=(person*)pa, *p2=(person*)pb;
  return strcmp(p1->name, p2->name);
}

void action(const void *nodep, const VISIT which, 
            const int depth) {
  person *p; 
  switch(which) {
    case preorder:
      break;
    case postorder:
      p = *(person**)nodep;
      person_print(p);
      break;
    case endorder:
      break;
    case leaf:
      p = *(person**)nodep;
      person_print(p);
      break;
  }
}

void binaryTreeTest() {
  void *v, *root=NULL;
  int i; 
  for (i = 0; i < 7; i++) { 
    person *p = (person*) malloc(sizeof(person));
    p->name = strdup(names[i]);
    p->id = i;
    v = tsearch((void *)p, &root, compare); 
  } 
  twalk(root, action);
}

void hashTableTest() {
  void *v;
  int i; 
  ENTRY e, *ep;
  
  hcreate(30);
  for (i = 0; i < 5; i++) { 
    person *p = (person*) malloc(sizeof(person));
    p->name = strdup(names[i]);
    p->id = i;
    e.key = p->name;
    e.data = p;
    v = hsearch(e, ENTER); 
  }
  for (i=0; i<7; i++) {
    e.key = names[i];
    ep = hsearch(e, FIND);
    if (ep != NULL) {
      person *p = ep->data;
      person_print(p);
    } else
      printf("%s not found !\n", e.key);
  }
  hdestroy();
}

int main() {
  printf("=====binaryTreeTest()=======\n");
  binaryTreeTest();
  printf("=====hashTableTest()=======\n");
  hashTableTest();
  return 0;
}
