#ifndef ASSEMBLER_H
#define ASSEMBLER_H

#include "Cpu0.h"

typedef struct {
  Array *codes;
  HashTable *symTable;
  HashTable *opTable;
} Assembler;

typedef struct {
  int address, opCode, size;
  char *label, *op, *args, type;
  char *objCode;
} AsmCode;

void assemble(char *asmFile, char *objFile); // 組譯器的主要函數 

Assembler* AsmNew();
void AsmFree(Assembler *a);

void AsmPass1(Assembler *a, char *text);
void AsmPass2(Assembler *a);
void AsmSaveObjFile(Assembler *a, char *objFile);
void AsmTranslateCode(Assembler *a, AsmCode *code);

AsmCode* AsmCodeNew(char *line);
void AsmCodeFree(AsmCode *code);
int AsmCodePrintln(AsmCode *code);

#endif
