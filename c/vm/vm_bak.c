#include <stdio.h>
#include <stdlib.h>

//======================== Obj, Str, Map ======================
#define BYTE char

typedef struct 
{
  char type;
  int  size;
  BYTE *ptr;
} Array;


typedef struct
{
  int  size;
  BYTE *ptr;
} Obj;

#define OBJP Obj*

OBJP ObjNew(int size)
{
  int i;
  OBJP obj = malloc(sizeof(Obj));
  obj->size = size;
  if (size == 0)
    obj->ptr = NULL;
  else
    obj->ptr = malloc(obj->size);
  if (size > 0)
    obj->ptr[0] = '\0';
  return obj;
}

int ObjCompare(OBJP o1, OBJP o2) {
  return memcmp(o1->ptr, o2->ptr, o2->size);
}

OBJP ObjClone(OBJP o) {
  OBJP obj = ObjNew(o->size);
  memcpy(obj->ptr, o->ptr, o->size);
  return obj;
}

OBJP ObjFree(OBJP obj)
{
  free(obj->ptr);
  free(obj);
}

OBJP IntNew(int n)
{
  OBJP o = ObjNew(0);
  o->size = n;
  return o;
}

OBJP StrNew(char *str)
{
  int i;
  int len = strlen(str);
  OBJP s = ObjNew(len+1);
  for (i=0; i<len; i++)
    s->ptr[i] = str[i];
  s->ptr[len] = '\0';
  return s;
}


int StrIndexOf(OBJP s, char c) {
  int i;
  for (i=0; i<s->size; i++)
    if (s->ptr[i] == c)
       return i;
  return -1;
}

OBJP StrSubstr(OBJP s, int from, int len)
{
  int i;
  OBJP substr = ObjNew(len+1);
  for (i=0; i<len; i++)
    substr->ptr[i] = s->ptr[from+i];
  substr->ptr[len] = '\0';
  return substr;
}

OBJP StrHead(OBJP s, char c) 
{
  int cidx = StrIndexOf(s, c);
  return StrSubstr(s, 0, cidx);
}

OBJP StrTail(OBJP s, char c) 
{
  int cidx = StrIndexOf(s, c);
  return StrSubstr(s, cidx, s->size-cidx);
}

OBJP StrPrint(OBJP s) 
{
  printf("%s", s->ptr);
}

typedef struct 
{
  int  size, count;
  OBJP  *keys;
  OBJP  *values;
} Map;

#define MAP Map*

MAP MapNew(int size)
{
  int i;
  Map* map = malloc(sizeof(Map));
  map->values = malloc(sizeof(OBJP)*size);
  map->keys = malloc(sizeof(OBJP)*size);
  for (i=0; i<size; i++)
  {
    map->keys[i] = NULL;
    map->values[i] = NULL;
  }
  map->size = size;
  map->count = 0;
  return map;
}

#define MapFind(map, key) (MapGet(map,key)!=NULL)

OBJP MapGet(MAP map, OBJP key) 
{
  int i;
  for (i=0; i<map->count; i++) 
  {
    if (ObjCompare(map->keys[i], key)==0)
      return map->values[i];
  }
  return NULL;
}

OBJP mapGet(MAP map, char *key) 
{
  OBJP k = StrNew(key);
  OBJP v = MapGet(map, k);
  ObjFree(k);
  return v;
}

int MapPut(MAP map, OBJP key, OBJP value) 
{
  if (MapFind(map, key)) return -1;
  map->keys[map->count] = key;
  map->values[map->count] = value;
  return map->count++;
}

int mapPut(MAP map, char *key, char *value) 
{
  return MapPut(map, StrNew(key), StrNew(value));
}

OBJP MapFree(MAP map)
{
  free(map->keys);
  free(map->values);
  free(map);
  return NULL;
}

OBJP ObjTest() {
  OBJP s;
  OBJP ccc;
  MAP map;
  
  s = StrNew("hello!");
  StrPrint(s);
  map = MapNew(100);
  mapPut(map, "ccc", "082-313532");
  mapPut(map, "fanny", "082-325645");
  ccc = mapGet(map, "ccc");
  StrPrint(ccc);
  printf("\n");
  return NULL;
}

//==================================== Virtual Machine ====================================================
#define Printf printf

typedef struct {
  int pc, size;
  OBJP *cmds;
  MAP labelMap;
} Code;

#define CODE Code*

CODE CodeNew(int size)
{
  CODE code = malloc(sizeof(Code));
  code->pc = 0;
  code->size = size;
  code->cmds = malloc(sizeof(OBJP)*size);
  return code;
}

CODE CodeLoad(char *cmds[], int size)
{
  int i;
  OBJP label;
  CODE code = CodeNew(size);
  for (i=0; i<size; i++)
  {
    code->cmds[i] = StrNew(cmds[i]);
    if (StrIndexOf(code->cmds[i], ':')>=0)
    {
      label = StrHead(code->cmds[i], ':');
      Printf("label-->%s -- ", label->ptr);
      MapPut(code->labelMap, label, IntNew(i));
    }
    Printf("%d:%s\n", i, code->cmds[i]->ptr);
  }
  return code;
}

OBJP CodeRun(CODE code) {
  return NULL;
}

char *testProg[] = {"sum=0", "i=1", "loop:i.cmp(10)", "j < exit", "i=i.add(1)", "jmp loop", "exit:print i"};
int main(void) {
  ObjTest();
  CODE code = CodeLoad(testProg, 7);
  CodeRun(code);
}


