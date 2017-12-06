#include <stdio.h>
#include <stdlib.h>
#include "obj.h"

//======================== Dynamic Object Define ======================
void ClassNew(Class* c, char *cNames[], void *cValues[], int cSize, char *oNames[], int oSize) {
  int i;
  c->cSize = cSize;
  c->cMembers=malloc(sizeof(Field)*cSize);
  c->oSize = oSize;
  c->oMembers=malloc(sizeof(Field)*oSize);  
  for (i=0; i<c->cSize; i++) {
    c->cMembers[i].name = malloc(strlen(cNames[i])+1);
    strcpy(c->cMembers[i].name, cNames[i]);
    c->cMembers[i].value = cValues[i];
  }
  for (i=0; i<c->oSize; i++) {
    c->oMembers[i].name = malloc(strlen(oNames[i])+1);
    strcpy(c->oMembers[i].name, oNames[i]);
    c->oMembers[i].value = NULL;
  }
}

FieldId findFieldIdx(Field fields[], int fieldSize, char *name) {
  int i;
  for (i=0; i<fieldSize; i++) {
    if (strcmp(name, fields[i].name)==0)
    	return i;
  }
  return -1;
}

Obj* execMethod(Class *c, Obj* o, char *methodName, Obj *params[], int paramSize) {
  FieldId fieldIdx = findFieldIdx(c->cMembers, c->cSize, "print");
  Method method = (Method) c->cMembers[fieldIdx].value;
  return method(o, params, paramSize);
}

Obj* ObjSetField(Class *c, Obj* o, char *name, void *ptr) {
  FieldId fieldIdx = findFieldIdx(c->oMembers, c->oSize, name);
  o->members[fieldIdx] = ptr;
  return o;
}

// ====================== Object =================================
Class ObjClass;
DefMethodAndPtr(ObjPrint, ObjPrintPtr)

void ObjClassInit() {
// class
  char* cNames[]  = {"Parent",	"Class",	"print" };
  void* cValues[] = { NULL,		&ObjClass,	&ObjPrint };
// object
  char* oNames[]  = {};
  void* oValues[] = {};
  
  ClassNew(&ObjClass, cNames, cValues, 3, oNames, 0);
}

Obj* ObjNew(Class *c) {
  Obj* o = malloc(sizeof(Obj));
  o->members = malloc(sizeof(void*)*c->oSize);
  return o;
}

Obj* ObjPrint(Obj* o, Obj* params[], int pcount) {
  Printf("%d", o);
  return o;
}

Class StrClass;
DefMethodAndPtr(StrPrint, StrPrintPtr)
// DefMethodAndPtr(StrLength, StrLengthPtr)

void StrClassInit() {
// class
  char* cNames[]  = { "print" };
  void* cValues[] = { &StrPrint };
// object
  char* oNames[]  = {"cptr"};
  void* oValues[] = { NULL };
  
  ClassNew(&StrClass, cNames, cValues, 1, oNames, 1);
}

Obj* StrPrint(Obj* o, Obj* params[], int pcount) {
  FieldId fieldIdx = findFieldIdx(StrClass.oMembers, StrClass.oSize, "cptr");
  Printf("%s", o->members[fieldIdx]);
  return o;
}

void ClassesInit() {
  ObjClassInit();
  StrClassInit();
}

//========================= Main Program =======================
void ObjTest() {
  Obj *obj, *str;
  
  ClassesInit();
  obj=ObjNew(&ObjClass);
  execMethod(&ObjClass, obj, "print", NULL, 0);
  str=ObjNew(&StrClass);
  ObjSetField(&StrClass, str, "cptr", (void*) strdup("hello!"));
  execMethod(&StrClass, str, "print", NULL, 0);
}




