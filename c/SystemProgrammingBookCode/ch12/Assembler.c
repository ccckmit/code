#include "Assembler.h"

void assemble(char *asmFile, char *objFile) {
  printf("Assembler:asmFile=%s objFile=%s\n",asmFile,objFile);
  printf("===============Assemble=============\n");
  char *text = newFileStr(asmFile);
  Assembler *a = AsmNew();
  AsmPass1(a, text);
  printf("===============SYMBOL TABLE=========\n");  
  HashTableEach(a->symTable, (FuncPtr1) AsmCodePrintln);
  AsmPass2(a);
  AsmSaveObjFile(a, objFile);
  AsmFree(a); 
  freeMemory(text);
}

Assembler* AsmNew() {
  Assembler *a=ObjNew(Assembler, 1);
  a->codes = ArrayNew(10);
  a->symTable = HashTableNew(127);
  a->opTable = OpTableNew();
  return a;
}

void AsmFree(Assembler *a) {
  ArrayFree(a->codes, (FuncPtr1) AsmCodeFree);
  HashTableFree(a->symTable);
  OpTableFree();
  ObjFree(a);
}

void AsmPass1(Assembler *a, char *text) {
  int i, address = 0, number;
  Array* lines = split(text, "\r\n", REMOVE_SPLITER);
  ArrayEach(lines, strPrintln);
  printf("=================PASS1================\n");
  for (i=0; i<lines->count; i++) {
      strReplace(lines->item[i], SPACE, ' ');
      AsmCode *code = AsmCodeNew(lines->item[i]);
      code->address = address;
      Op *op = HashTableGet(opTable, code->op);
      if (op != NULL) {
        code->opCode = op->code;
        code->type = op->type;
      }
      if (strlen(code->label)>0)
        HashTablePut(a->symTable, code->label, code);
      ArrayAdd(a->codes, code);
      AsmCodePrintln(code);
      code->size = AsmCodeSize(code);
      address += code->size;
  }
  ArrayFree(lines, strFree);
}

void AsmPass2(Assembler *a) {
  printf("=============PASS2==============\n");
  int i;
  for (i=0; i<a->codes->count; i++) {
    AsmCode *code = a->codes->item[i];
    AsmTranslateCode(a, code);
    AsmCodePrintln(code);
  }
}

void AsmTranslateCode(Assembler *a, AsmCode *code) {
  char p1[100], p2[100], p3[100], pt[100];
  int ra=0, rb=0, rc=0, cx=0;
  char cxCode[9]="00000000", objCode[100]="", args[100]="";
  strcpy(args, code->args);
  strReplace(args, ",", ' ');
  int pc = code->address + 4;
  switch (code->type) {
    case 'J' :
      if (!strEqual(args, "")) {
        AsmCode *labelCode = HashTableGet(a->symTable,args);
        cx = labelCode->address - pc;
        sprintf(cxCode, "%8x", cx);
      }
      sprintf(objCode, "%2x%s", code->opCode, &cxCode[2]);
      break;
    case 'L' :
      sscanf(args, "R%d %s", &ra, p2);
      if (strHead(p2, "[")) {
        sscanf(p2, "[R%d+%s]", &rb, pt);
        if (sscanf(pt, "R%d", &rc)<=0)
          sscanf(pt, "%d", &cx);
      } else if (sscanf(p2, "%d", &cx)>0) {
      } else {
        AsmCode *labelCode = HashTableGet(a->symTable, p2);
        cx = labelCode->address - pc;
        rb = 15; // R[15] is PC
      }
      sprintf(cxCode, "%8x", cx);
      sprintf(objCode, "%2x%x%x%s", code->opCode, ra, rb, &cxCode[4]);
      break;
    case 'A' : 
      sscanf(args, "%s %s %s", p1, p2, p3);
      sscanf(p1, "R%d", &ra);
      sscanf(p2, "R%d", &rb);
      if (sscanf(p3, "R%d", &rc)<=0)
        sscanf(p3, "%d", &cx);
      sprintf(cxCode, "%8x", cx);
      sprintf(objCode, "%2x%x%x%x%s", code->opCode,ra,rb,rc,&cxCode[5]);
      break;
    case 'D' : {
      char format4[]="%8x", format1[]="%2x", *format = format1;
      switch (code->opCode) {
        case OP_RESW:
        case OP_RESB:
          memset(objCode, '0', code->size*2);
          objCode[code->size*2] = '\0';
          break;
        case OP_WORD:
          format = format4;
        case OP_BYTE: {
          Array *array = split(args, " ", REMOVE_SPLITER);
          char *objPtr = objCode;
          int i=0;
          for (i=0; i<array->count; i++) {
              char *item = array->item[i];
              if (isdigit(item[0]))
                sprintf(objPtr, format, atoi(item));
              else {
                AsmCode *itemCode = HashTableGet(a->symTable, item);
                sprintf(objPtr, format, itemCode->address);
              }
              objPtr += strlen(objPtr);
          }
          ArrayFree(array, strFree);
          break;
        } // case OP_BYTE:
      } // switch
      break;
    } // case 'D'
    default: 
      strcpy(objCode, "");
      break;
  }
  strReplace(objCode, " ", '0');
  code->objCode = newStr(objCode);
}

void AsmSaveObjFile(Assembler *a, char *objFile) {
  printf("==========Save to ObjFile:%s==========\n", objFile);
  FILE *file = fopen(objFile, "wb");
  int i;
  for (i=0; i<a->codes->count; i++) {
    AsmCode *code = a->codes->item[i];
    char *objPtr = code->objCode;
    while (*objPtr != '\0') {
      int x;
      sscanf(objPtr, "%2x", &x);
      assert(x >= 0 && x < 256);
      BYTE b = (BYTE) x;
      fwrite(&b, sizeof(BYTE), 1, file);
      objPtr += 2;
      char bstr[3];
      sprintf(bstr, "%2x", b);
      strReplace(bstr, " ", '0');
      printf("%s", bstr);
    }
  }
  printf("\n");
  fclose(file);
}

int AsmCodePrintln(AsmCode *code) {
  char label[100] = "";
  if (strlen(code->label)>0)
    sprintf(label, "%s:", code->label);
  printf("%4x %-8s %-4s %-14s %c %2x %s\n", code->address, label, code->op, code->args, code->type, code->opCode, code->objCode);
}

AsmCode* AsmCodeNew(char *line) {
  AsmCode* code = ObjNew(AsmCode,1);
  char label[100]="", op[100]="", args[100]="", temp[100];
  int count = sscanf(line, "%s %s %[^;]", label, op, args);
  if (strTail(label, ":")) {
    strTrim(temp, label, ":");
    strcpy(label, temp);
  } else {
    strcpy(label, "");
    sscanf(line, "%s %[^;]", op, args);
  }
//  printf("label=%s op=%s args=%s\n", code->label, op, args);
  code->label = newStr(label);
  code->op = newStr(op);
  strTrim(temp, args, SPACE);
  code->args = newStr(temp);
  code->type = ' ';
  code->opCode = OP_NULL;
//  AsmCodePrintln(code);
  return code;
}

void AsmCodeFree(AsmCode *code) {
  freeMemory(code->label);
  freeMemory(code->op);
  freeMemory(code->args);
  freeMemory(code->objCode);
  freeMemory(code);
}

int AsmCodeSize(AsmCode *code) {
  int number;
  switch (code->opCode) {
    case OP_RESW : 
      return 4 * atoi(code->args);
    case OP_RESB : 
      return atoi(code->args);
    case OP_WORD : 
      number = atoi(code->args);
      return 4 * (strCountChar(code->args, ",")+1);
    case OP_BYTE : 
      number = atoi(code->args);
      return strCountChar(code->args, ",")+1;
    case OP_NULL :
      return 0;
    default :
      return 4;
  }
}    
