#ifndef GENERATOR_H
#define GENERATOR_H

#include "Tree.h"
#include "HashTable.h"

typedef struct {
  HashTable *symTable;
  Tree *tree;
  FILE *asmFile;
  int forCount, varCount;
} Generator;

void generate(Tree *tree, char *asmFile);

Generator *GenNew();
void GenFree(Generator *g);
Tree* GenCode(Generator *g, Tree *node, char *rzVar);
void GenData(Generator *g);
void GenPcode(Generator *g, char* label, char* op, char* p1, char* p2, char* pTo);
void GenPcodeToAsm(Generator *g, char* label, char* op, char* p1, char* p2, char* pTo);
void GenAsmCode(Generator *g, char* label, char* op, char* p1, char* p2, char* pTo);
void GenTempVar(Generator *g, char *tempVar);
void negateOp(char *condOp, char *negOp);

#endif
