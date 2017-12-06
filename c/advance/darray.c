#include <stdlib.h>
#include <string.h>

typedef struct {
  int size;    // �}�C�ثe���W�� 
  int count;   // �}�C�ثe�������Ӽ� 
  void **item; // �C�Ӱ}�C����������
} Array;       // �ʺA�}�C����Ƶ��c 

void ArrayNew(Array *array, int size) {
  array->count = 0;
  array->size = size;
  array->item = malloc(array->size*sizeof(void*));
}

void ArrayAdd(Array *array, void *item) {
  if (array->count == array->size) {
    int newSize = array->size*2;
    void **newItems = malloc(newSize*sizeof(void*));
    memcpy(newItems, array->item, array->size*sizeof(void*));
    free(array->item);
    array->item = newItems;
    array->size = newSize;
	printf("Array growing : size = %d\n", array->size);
  }
  array->item[array->count++] = item;
}

#define ArrayEach(a, i, o) for (i=0, o=(a)->item[i]; i<(a)->count; o=(a)->item[i],i++) 

int main() {
  char *names[] = { "John", "Mary", "George", "Bob", "Tony" };
  int i;
  Array array;
  ArrayNew(&array, 1);
  for (i=0; i<5; i++)
    ArrayAdd(&array, names[i]);
  for (i=0; i<array.count; i++)
    printf("name[%d]=%s\n", i, (char*) array.item[i]);
  void *obj;
  ArrayEach(&array, i, obj) {
    printf("name[%d]=%s\n", i, (char*) obj);
  }
}
