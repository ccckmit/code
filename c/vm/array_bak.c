#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//======================== Obj, Str, Map ======================
#define TRUE	1
#define FALSE	0
#define BIT		char
#define BYTE 	char
#define INT  	int
#define FLOAT 	float
#define WORD 	int
#define BASE	Base
#define PTR		char*
#define COMPARE(a, b) ((a > b)? 1 : ((a < b)? -1 : 0))

// ================================ Object ========================================
typedef union {
  FLOAT floatValue;
  INT   intValue;
  BYTE  byteValue;
  BIT	bitValue;
  PTR	ptr;
} BaseType;

typedef struct
{
  char type;
  BaseType value;
} Obj;

Obj* ObjNew()
{
  Obj* o=malloc(sizeof(Obj));
  o->type = '?';
}

int ObjCompare(Obj* o1, Obj* o2) {
  assert(o1->type != '?');
  if (o1->type < o2->type)
    return -1;
  else if (o1->type > o2->type)
    return 1;
  else { // if (o1->type == o2->type)
    switch(o1->type) 
    {
      case 'b' : return COMPARE(o1->value.byteValue, o2->value.byteValue);		// byte
      case 'i' : return COMPARE(o1->value.intValue, o2->value.intValue);		// int
      case 'f' : return COMPARE(o1->value.floatValue, o2->value.floatValue);	// float
      case 'o' : return COMPARE(o1->value.ptr, o2->value.ptr);					// pointer to object
    }
    return 0;
  }
}

Obj* ObjClone(Obj* o) {
  Obj* obj = ObjNew();
  obj->type = o->type;
  obj->value = o->value;
  return obj;
}

Obj* ObjFree(Obj* obj)
{
  if (obj->type == 'o')
  	free(obj->value.ptr);
  free(obj);
}

// ================================ Int ========================================
Obj* IntNew(int n)
{
  Obj* o = ObjNew();
  o->type = 'i';
  o->value.intValue = n;
  return o;
}

// ================================ Str ========================================
#define CharAt(s, i) (s[i])
#define Len(s) (strlen(s))
#define StrOf(o) ((Str) o->value.ptr)

typedef char* Str;

Obj* StrAlloc(int size)
{
  Obj* o = ObjNew();
  Str str = malloc(size);
  o->value.ptr = str;
  return o;  
}

Obj* StrNew(char *s)
{
  Obj* o = StrAlloc(strlen(s)+1);
  strcpy(o->value.ptr, s);
  return o;
}

int StrCompare(Obj *o1, Obj *o2)
{
  Str s1 = StrOf(o1);
  Str s2 = StrOf(o2);
  return strcmp(s1, s2);
}

int StrLen(Obj *o) {
  Str str = StrOf(o);
  return Len(str);
}

char StrCharAt(Obj *o, int i) {
  Str str = StrOf(o);
  return CharAt(str, i);
}

int StrIndexOf(Obj *o, char c) {
  int i;
  Str str = StrOf(o);
  for (i=0; i<Len(str); i++)
    if (CharAt(str,i) == c)
       return i;
  return -1;
}

Obj* StrSubstr(Obj* o, int from, int len)
{
  int i;
  Str str = StrOf(o);
  Str substr = malloc(len+1);
  Obj* oSubstr = ObjNew();
  for (i=0; i<len; i++)
    substr[i] = CharAt(str, from+i);
  substr[len] = '\0';
  oSubstr->value.ptr = substr;
  return oSubstr;
}

Obj* StrHead(Obj* o, char c) 
{
  int cidx = StrIndexOf(o, c);
  return StrSubstr(o, 0, cidx);
}

Obj* StrTail(Obj* o, char c) 
{
  int cidx = StrIndexOf(o, c);
  int len = StrLen(o);
  return StrSubstr(o, cidx+1, len-(cidx+1));
}

void StrPrint(Obj* o) 
{
  printf("%s", StrOf(o));
}

// ================================ Array ========================================
typedef struct 
{
  char type;
  int  size, count;
  PTR  ptr;
} Array;

typedef int(*Comparator)(Obj*,Obj*);

Array* ArrayNew(char pType, int pSize)
{
  int size;
  switch(pType) 
  {
    case 'b' : size = pSize; break;					// byte
    case 'i' : size = pSize*sizeof(int); break;		// int
    case 'f' : size = pSize*sizeof(float); break;	// float
    case 'o' : size = pSize*sizeof(Obj*); break;	// pointer to object
  }
  Array* a = malloc(sizeof(Array));
  a->size = size;
  a->type = pType;
  a->ptr = malloc(size);
  memset(a->ptr, 0, size);
  return a;
}

void ArraySet(Array* array, int i, Obj* o) {
  BYTE *bptr; INT *iptr; FLOAT *fptr; Obj **opptr;
  switch(array->type) {
    case 'b' : 					// byte
        bptr = (BYTE*) array->ptr;
    	bptr[i] = o->value.byteValue;
  		printf("i=%d c=%c\n", i, bptr[i]);
    	break;
    case 'i' : 					// int
    	iptr = (INT*) array->ptr;
    	iptr[i] = o->value.intValue;
    	break;
    case 'f' : 					// float
    	fptr = (FLOAT*) array->ptr;
    	fptr[i] = o->value.floatValue;
    	break;
    case 'o' : 					// Object Pointer
    	opptr = (Obj**) array->ptr;
    	opptr[i] = ((Obj*) o->value.ptr);
    	break;
  }
}

void ArrayAdd(Array* array, Obj* o) {
  ArraySet(array, array->count++, o);
}

void ArrayGet(Array* array, int i, Obj* o) {
  BYTE *bptr; INT *iptr; FLOAT *fptr; Obj **opptr;
  
  switch(array->type) {
    case 'b' : 					// byte
    	bptr = (BYTE*)array->ptr;
    	o->value.byteValue = bptr[i];
    	break;
    case 'i' : 					// int
    	iptr = (INT*)array->ptr;
    	o->value.intValue = iptr[i];
    	break;
    case 'f' : 					// float
    	fptr = (FLOAT*)array->ptr;
    	o->value.floatValue = fptr[i];
    	break;
    case 'o' : 					// int
    	opptr = (Obj**)array->ptr;
    	o->value.ptr = (PTR) opptr[i];
    	break;
  }
}

Array* ArrayFree(Array* array)
{
  free(array->ptr);
  free(array);
}

int ArrayFind(Array* array, Obj* o, Comparator cp) {
  int i;
  Obj t;
  t.type = array->type;
  Comparator fcp = cp;
  if (fcp == NULL) fcp = &ObjCompare;
  for (i=0; i<array->count; i++) {
    ArrayGet(array, i, &t);
    if (fcp(&t, o)==0)
      return i;
  }
  return -1;
}

#define StrArrayFind(a, o) (ArrayFind(a, o, &StrCompare))

void ArrayTest() {
  printf("===============ArrayTest================\n");
  Array* array = ArrayNew('b', 100);
  Obj* o = ObjNew();
  o->type='b';
  o->value.byteValue = 'a';
  Obj* t = ObjNew();
  t->type='b';
  ArraySet(array, 3, o);
  array->count = 10;
  ArrayGet(array, 3, t);
  printf("t->value.byteValue=%c\n", t->value.byteValue);
  int i = ArrayFind(array, t, NULL);
  printf("i=%d\n", i);
}

// ================================ Map ========================================
typedef struct 
{
  Array *keys;
  Array *values;
} Map;

#define MapFind(map, key) (MapGet(map,key)!=NULL)

Map* MapNew(int size)
{
  Map *map = malloc(sizeof(Map));
  map->keys = ArrayNew('o', size);
  map->values = ArrayNew('o', size);
  return map;
}

Obj* MapGet(Map* map, Obj* key)
{
  int i = StrArrayFind(map->keys, key);
  if (i==-1) return NULL;
  Obj *value = ObjNew();
  ArrayGet(map->values, i, value);
  return value;
}

int MapPut(Map* map, Obj* key, Obj* value) 
{
  if (MapFind(map, key)) return -1;
  ArrayAdd(map->keys, key);
  ArrayAdd(map->values, value);
  return map->keys->count-1;
}

Obj* MapFree(Map* map)
{
  ArrayFree(map->keys);
  ArrayFree(map->values);
  free(map);
  return NULL;
}

void MapTest() 
{
  printf("===============MapTest==================\n");
  Map *map = MapNew(10);
  MapPut(map, StrNew("ccc"), StrNew("082-313532"));
  MapPut(map, StrNew("fanny"), StrNew("082-325645"));
  Obj *o = MapGet(map, StrNew("fanny"));
  if (o != NULL)
  	printf("%s\n", StrOf(o));
  else
    printf("o=NULL\n");
}

//==================================== Virtual Machine ====================================================
typedef struct {
  int pc, size;
  Array* cmds;
  Map *labelMap;
} Code;

Code* CodeNew(int size)
{
  Code* code = malloc(sizeof(Code));
  code->pc = 0;
  code->size = size;
  code->cmds = ArrayNew('o', size);
  code->labelMap = MapNew(size);
  return code;
}

Code* CodeLoad(char *cmds[], int size)
{
  int i;
  Obj *label, *cmd, *tail;
  Code* code = CodeNew(size);
  for (i=0; i<size; i++)
  {
    cmd = StrNew(cmds[i]);
    if (StrIndexOf(cmd, ':')>=0)
    {
      label = StrHead(cmd, ':');
      tail  = StrTail(cmd, ':');
      ObjFree(cmd);
      cmd = tail;
      printf("%s:\t", StrOf(label));
      MapPut(code->labelMap, label, IntNew(i));
    }
    else
      printf("\t");
    printf("%d:%s\n", i, StrOf(cmd));
    ArrayAdd(code->cmds, cmd);
  }
  return code;
}

Obj* CodeRun(Code* code) {
  return NULL;
}

int VmTest(void) {
  printf("===============VmTest==================\n");  
  char *cmds[] = {"sum=0", "i=1", "loop:i.cmp 10", "jmp < exit", "i=i.add 1", "jmp loop", "exit:print i"};
  Code* code = CodeLoad(cmds, 7);
  CodeRun(code);
}

//============================ MAIN ======================================
int main(void) {
  ArrayTest();
  MapTest();
  VmTest();
  return 0;
}




/*
*/
