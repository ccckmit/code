#include "Generator.h"

// 程式產生器的主要函數。
void generate(Tree *tree, char *asmFile) { 
  char nullVar[100]="";
  Generator *g = GenNew();
  g->asmFile = fopen(asmFile, "w");
  printf("=====PCODE=====\n");
  GenCode(g, tree, nullVar);
  GenData(g);
  fclose(g->asmFile);
  GenFree(g);
  char *asmText = newFileStr(asmFile);
  printf("=====AsmFile:%s======\n", asmFile);  
  printf("%s\n", asmText);
  freeMemory(asmText);
}

Generator *GenNew() {
  Generator *g = ObjNew(Generator, 1);
  g->symTable = HashTableNew(127);
  return g;
}

void GenFree(Generator *g) {
  HashTableFree(g->symTable);
  ObjFree(g);
}

char nullVar[100]="";

Tree* GenCode(Generator *g, Tree *node, char *rzVar) {
  strcpy(nullVar, "");
  strcpy(rzVar, "");
  if (node == NULL) return NULL; // 遞迴終止條件。

  if (strEqual(node->type, "FOR")) {
    // 處理 FOR 迴圈，<FOR> ::= "for" "(" <STMT> ";" <COND> ";" <STMT> ")" <BLOCK>
    char forBeginLabel[100], forEndLabel[100], condOp[100];
    Tree *stmt1 = node->childs->item[2], 
         *cond  = node->childs->item[4], 
         *stmt2 = node->childs->item[6], 
         *block = node->childs->item[8];
    GenCode(g, stmt1, nullVar);
    int tempForCount = g->forCount++;
    sprintf(forBeginLabel, "FOR%d", tempForCount);
    sprintf(forEndLabel, "_FOR%d", tempForCount);
    GenPcode(g, forBeginLabel, "", "", "", "");
    GenCode(g, cond, condOp);
    char negOp[100];
    negateOp(condOp, negOp);
    GenPcode(g, "", "J", negOp, "", forEndLabel);
    GenCode(g, block, nullVar);
    GenCode(g, stmt2, nullVar);
    GenPcode(g, "", "J", "", "", forBeginLabel);
    GenPcode(g, forEndLabel, "", "", "", "");
    return NULL;
  } else if (strEqual(node->type, "STMT")) {
    // 處理 STMT (Statement 陳述), <STMT>::= return id | id "=" <EXP> | id ["++"|"--"]
    Tree *c1 = node->childs->item[0];
    if (strEqual(c1->type, "return")) {
      Tree *id = node->childs->item[1];
      GenPcode(g, "", "RET", "", "", id->value);
    } else {
      Tree *id = node->childs->item[0];
      Tree *op = node->childs->item[1];
      if (strEqual(op->type, "=")) { // STMT 是一種 ASSIGN (指定) --> id '=' EXP
        Tree *exp = node->childs->item[2];
        char expVar[100];
        GenCode(g, exp, expVar);
        GenPcode(g, "", "=", expVar, "", id->value);
        HashTablePut(g->symTable, id->value, id->value);
        strcpy(rzVar, expVar);
      } else { // STMT 是 id++ 或 id--，--> id OP1
        char addsub[100];
        if (strEqual(op->value, "++"))
          strcpy(addsub, "+");
        else
          strcpy(addsub, "-");
        GenPcode(g, "", addsub, id->value, "1", id->value);
        strcpy(rzVar, id->value);
      }
    }
  } else if (strEqual(node->type, "COND")) {
    // 處理布林判斷式 <COND> ::= <EXP> ["=="|"!="|"<="|">="|"<"|">"] <EXP>
    Tree* op = node->childs->item[1];
    char expVar1[100], expVar2[100];
    GenCode(g, node->childs->item[0], expVar1);
    GenCode(g, node->childs->item[2], expVar2);
    GenPcode(g, "", "CMP", expVar1, expVar2, nullVar);
    strcpy(rzVar, op->value); // 傳回布林運算子 
  } else if (strPartOf(node->type, "|EXP|TERM|")) {
    // 處理運算式 <EXP> ::= <TERM> { ["+"|"-"] <TERM> } 與 <TERM> ::= <FACTOR> { ["*"|"/"] <FACTOR> }
    Tree *item1 = node->childs->item[0];
    char var1[100], var2[100], tempVar[100];
    GenCode(g, item1, var1);
    int ti;
    for (ti = 1; ti < node->childs->count; ti += 2) {
      Tree* op = node->childs->item[ti];
      Tree* item2 = node->childs->item[ti+1];
      GenCode(g, item2, var2);
      GenTempVar(g, tempVar);
      GenPcode(g, "", op->value, var1, var2, tempVar);
      strcpy(var1, tempVar);
    }
    strcpy(rzVar, var1);
  } else if (strEqual(node->type, "FACTOR")) {
    // 處理 <FACTOR> ::= <ITEM> | "(" <EXP> ")"         
    if (node->childs->count == 1)
      return GenCode(g, node->childs->item[0], nullVar);
    else
      return GenCode(g, node->childs->item[1], nullVar);
  } else if (strEqual(node->type, "ITEM")) {
    // 處理 <ITEM>::= id | number         
    return GenCode(g, node->childs->item[0], nullVar);
  } else if (strPartOf(node->type, "|number|id|")) {
    // 遇到變數或常數，傳回其 value 名稱。         
    strcpy(rzVar, node->value);
  } else if (node->childs != NULL) { 
    // 其他狀況，若有子代則遞回處理
    int i;
    for (i=0; i<node->childs->count; i++)
      GenCode(g, node->childs->item[i], nullVar);
  }
  return NULL;
}

void GenData(Generator *g) { // 產生組合語言的變數宣告 
  Array *symArray = HashTableToArray(g->symTable);
  int i;
  for (i=0; i<symArray->count; i++) { // 產生符號表 
    char *varName = symArray->item[i];
    char varLabel[100];
    sprintf(varLabel, "%s:", varName);
    GenAsmCode(g, varLabel, "RESW", "1", "", "");
  }
  for (i=0; i<g->varCount; i++) { // 產生臨時變數 
    char tVarLabel[100];
    sprintf(tVarLabel, "T%d:", i);
    GenAsmCode(g, tVarLabel, "RESW", "1", "", "");
  }
  ArrayFree(symArray, NULL);
}

void GenPcode(Generator *g, char* label, char* op, char* p1, char* p2, char* pTo) {
  char labelTemp[100];
  if (strlen(label)>0)
    sprintf(labelTemp, "%s:", label);
  else
    strcpy(labelTemp, "");
  printf("%-8s %-4s %-4s %-4s %-4s\n", labelTemp, op, p1, p2, pTo);
  GenPcodeToAsm(g, labelTemp, op, p1, p2, pTo);
}

void GenPcodeToAsm(Generator *g, char* label, char* op, char* p1, char* p2, char* pTo) {
  if (strlen(label)>0)
    GenAsmCode(g, label, "", "", "", "");
  if (strEqual(op, "=")) { // pTo = p1
    GenAsmCode(g, "", "LD", "R1", p1, "");
    GenAsmCode(g, "", "ST", "R1", pTo, "");
  } else if (strPartOf(op, "|+|-|*|/|")) { // pTo = p1 op p2
    char asmOp[100]; 
    if (strEqual(op, "+")) strcpy(asmOp, "ADD");
    else if (strEqual(op, "-")) strcpy(asmOp, "SUB");
    else if (strEqual(op, "*")) strcpy(asmOp, "MUL");
    else if (strEqual(op, "/")) strcpy(asmOp, "DIV");
    GenAsmCode(g, "", "LD", "R1", p1, "");
    GenAsmCode(g, "", "LD", "R2", p2, "");
    GenAsmCode(g, "", asmOp,"R3", "R2", "R1");
    GenAsmCode(g, "", "ST", "R3", pTo, "");
  } else if (strEqual(op, "CMP")) { // CMP p1, p2
    GenAsmCode(g, "", "LD", "R1", p1, "");
    GenAsmCode(g, "", "LD", "R2", p2, "");
    GenAsmCode(g, "", "CMP", "R1", "R2", "");
  } else if (strEqual(op, "J")) { // J op label
    char asmOp[100];
    if (strEqual(p1, "=")) strcpy(asmOp, "JEQ");
    else if (strEqual(p1, "!=")) strcpy(asmOp, "JNE");
    else if (strEqual(p1, "<")) strcpy(asmOp, "JLT");
    else if (strEqual(p1, ">")) strcpy(asmOp, "JGT");
    else if (strEqual(p1, "<=")) strcpy(asmOp, "JLE");
    else if (strEqual(p1, ">=")) strcpy(asmOp, "JGE");
    else strcpy(asmOp, "JMP");
    GenAsmCode(g, "", asmOp, pTo, "", "");
  } else if (strEqual(op, "RET")) {
    GenAsmCode(g, "", "LD", "R1", pTo, "");
    GenAsmCode(g, "", "RET", "", "", "");
  }
}

void GenAsmCode(Generator *g, char* label, char* op, char* p1, char* p2, char* pTo) {
  char *realOp = op;
  if (strEqual(op, "LD"))
    if (isdigit(p2[0]))
      realOp = "LDI";
  fprintf(g->asmFile, "%-8s %-4s %-4s %-4s %-4s\n", label, realOp, p1, p2, pTo);
}

void GenTempVar(Generator *g, char *tempVar) {
  sprintf(tempVar, "T%d", g->varCount++);
}

void negateOp(char *condOp, char *negOp) {
  if (strEqual(condOp, "==")) strcpy(negOp, "!=");
  if (strEqual(condOp, "!=")) strcpy(negOp, "==");
  if (strEqual(condOp, ">=")) strcpy(negOp, "<");
  if (strEqual(condOp, "<=")) strcpy(negOp, ">");
  if (strEqual(condOp, ">")) strcpy(negOp, "<=");
  if (strEqual(condOp, "<")) strcpy(negOp, ">=");
}
