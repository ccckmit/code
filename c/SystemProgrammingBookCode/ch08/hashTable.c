#include <stdio.h>
#include <stdlib.h>
#include <search.h>

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

int main() {
  void *v, *root=NULL;
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
    if(v == NULL) 
      exit(1); 
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
  return 0; 
}
/*(

char *data[] = { "alpha", "bravo", "charlie", "delta",
     "echo", "foxtrot", "golf", "hotel", "india", "juliet",
     "kilo", "lima", "mike", "november", "oscar", "papa",
     "quebec", "romeo", "sierra", "tango", "uniform",
     "victor", "whisky", "x-ray", "yankee", "zulu"
};
int main() {
  ENTRY e, *ep;
  int i;

  hcreate(30); // �إߤ@�� 30 �檺 HashTable
  for (i = 0; i < 24; i++) {// �N data[0..23][ ��J hashTable ��
      e.key = data[i];
      e.data = (void *)i; // �N��� i ��J e.data ���C
      ep = hsearch(e, ENTER); // �N e=(key, data) ��JHashTable ��
      if (ep == NULL) {
        fprintf(stderr, "entry failed\n");
        exit(1);
      }
  }
  for (i = 22; i < 26; i++) { // �C�L�X hashTable ���� data[22..25]
      e.key = data[i];
      ep = hsearch(e, FIND);
      printf("%9.9s -> %9.9s:%d\n", e.key,
             ep ? ep->key : "NULL",
             ep ? (int)(ep->data) : 0);
  }
  return 0;
}
*/
