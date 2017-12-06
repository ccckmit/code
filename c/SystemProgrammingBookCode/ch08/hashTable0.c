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

  hcreate(30); // 建立一個 30 格的 HashTable
  for (i = 0; i < 24; i++) {// 將 data[0..23][ 放入 hashTable 中
      e.key = data[i];
      e.data = (void *)i; // 將整數 i 放入 e.data 中。
      ep = hsearch(e, ENTER); // 將 e=(key, data) 放入HashTable 中
      if (ep == NULL) {
        fprintf(stderr, "entry failed\n");
        exit(1);
      }
  }
  for (i = 22; i < 26; i++) { // 列印出 hashTable 中的 data[22..25]
      e.key = data[i];
      ep = hsearch(e, FIND);
      printf("%9.9s -> %9.9s:%d\n", e.key,
             ep ? ep->key : "NULL",
             ep ? (int)(ep->data) : 0);
  }
  return 0;
}
