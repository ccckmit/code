#include <stdio.h>
#include <stdlib.h>
#include <search.h>

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
