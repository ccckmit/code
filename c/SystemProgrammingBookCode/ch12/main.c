#include "Assembler.h"
#include "Compiler.h"

#define TEST      1
#define C0C       2
#define AS0       3
#define VM0       4

void argError(char *msg) {
  printf("%s\n", msg);
  exit(1);
}

int main(int argc, char *argv[]) {
  char cFile0[]="test.c0", *cFile=cFile0;
  char asmFile0[]="test.asm0", *asmFile=asmFile0;
  char objFile0[]="test.obj0", *objFile=objFile0;
#if TARGET==TEST
  ArrayTest();
  HashTableTest();
  OpTableTest();
  compile(cFile, asmFile);
  assemble(asmFile, objFile);
  runObjFile(objFile);
  checkMemory();
#elif TARGET==C0C
  if (argc == 3) {
    cFile=argv[1]; asmFile=argv[2]; 
  } else
    argError("c0c <c0File> <asmFile>");
  compile(cFile, asmFile);
#elif TARGET==AS0
  if (argc == 3) { 
    asmFile=argv[1]; objFile=argv[2]; 
  } else 
    argError("as0 <asmFile> <objFile>");
  assemble(asmFile, objFile);
#elif TARGET==VM0
  if (argc == 2) 
    objFile=argv[1]; 
  else 
    argError("vm0 <objFile>");
  runObjFile(objFile);
#endif
  return 0;
}

