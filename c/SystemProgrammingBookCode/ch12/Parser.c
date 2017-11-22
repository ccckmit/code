#include "Parser.h"

Parser *parse(char *text) {
  Parser *p=ParserNew();
  ParserParse(p, text);
  return p;
}

char* nextToken(Parser *p);
char *tokenToType(char *token);
Tree* push(Parser *p, char* term);
Tree* pop(Parser *p, char* term);
Tree* parseProg(Parser *p);
void parseBlock(Parser *p);
void parseFor(Parser *p);
void parseBaseList(Parser *p);
void parseBase(Parser *p);
void parseStmt(Parser *p);
void parseArgList(Parser *p);
void parseExp(Parser *p);
void parseCond(Parser *p);
void error();
BOOL isEnd(Parser *p);
BOOL isNext(Parser *p, char *pTypes);
char *next(Parser *p, char *pTypes);

Parser *ParserNew() {
  Parser *parser = ObjNew(Parser, 1);
  parser->tokens = NULL;
  parser->tree = NULL;
  parser->stack = ArrayNew(10);
  return parser;
}

void ParserFree(Parser *parser) {
  ArrayFree(parser->tokens, strFree);
  ArrayFree(parser->stack, NULL);
  TreeFree(parser->tree);
  ObjFree(parser);
}

void ParserParse(Parser *p, char *text) {
  printf("======= tokenize =======\n");
  p->tokens = tokenize(text);
  printTokens(p->tokens);
  p->tokenIdx = 0;
  printf("======= parsing ========\n");
  p->tree = parseProg(p); 
  if (p->stack->count != 0) {
    printf("parse fail:stack.count=%d", p->stack->count);
    error();
  }
}

void error() {
  printf("error()!\n");
  exit(1);
}

// PROG = BaseList
Tree *parseProg(Parser *p) {
  push(p, "PROG");
  parseBaseList(p);
  return pop(p, "PROG");
}

// BaseList= { BASE }
void parseBaseList(Parser *p) {
  push(p, "BaseList");
  while (!isEnd(p) && !isNext(p, "}"))
      parseBase(p);
  pop(p, "BaseList");
}

// BASE = FOR | STMT;
void parseBase(Parser *p) {
  push(p, "BASE");
  if (isNext(p, "for"))
      parseFor(p);
  else {
      parseStmt(p);
      next(p, ";");
  }
  pop(p, "BASE");
}

// FOR = for (STMT; COND; STMT) BLOCK
void parseFor(Parser *p) {
  push(p, "FOR");
  next(p, "for");
  next(p, "(");
  parseStmt(p);
  next(p, ";");
  parseCond(p);
  next(p, ";");
  parseStmt(p);
  next(p, ")");
  parseBlock(p);
  pop(p, "FOR");
}

// BLOCK = '{' BaseList '}'
void parseBlock(Parser *p) {
  push(p, "BLOCK");
  next(p, "{");
  parseBaseList(p);
  next(p, "}");
  pop(p, "BLOCK");
}

// STMT = return id | id '=' EXP  | id '(' ArgList ')' | id OP1
void parseStmt(Parser *p) {
  push(p, "STMT");
  if (isNext(p, "return")) {
    next(p, "return");
    next(p, "id");
  } else {
    next(p, "id");
    if (isNext(p, "="))  { // id '=' EXP   --> ASSIGN
      next(p, "=");
      parseExp(p);
    } else if (isNext(p, "("))  {  // id '(' ArgList ')'     --> Function Call
      next(p, "(");
      if (!isNext(p, ")"))
          parseArgList(p);
      next(p, ")");
    } else              // id OP1
      next(p, OP1);
  }
//  printf("Exit parseStmt\n");
  pop(p, "STMT");
}

// ArgList = EXP { ',' EXP }
void parseArgList(Parser *p) {
  push(p, "ArgList");
  parseExp(p);
  while (isNext(p, ",")) {
      next(p, ",");
      parseExp(p);
  }
  pop(p, "ArgList");
}

// EXP = ITEM OP2 ITEM | ITEM
void parseExp(Parser *p) {
  push(p, "EXP");
  next(p, ITEM);
  if (isNext(p, OP2)) {
      next(p, OP2);
      next(p, ITEM);
  }
  pop(p, "EXP");
}

// COND = EXP COND_OP EXP
void parseCond(Parser *p) {
  push(p, "COND");
  parseExp(p);
  next(p, COND_OP);
  parseExp(p);
  pop(p, "COND");
}

char* level(Parser *p) {
  return strSpaces(p->stack->count);
}

char* nextToken(Parser *p) {
  return (char*) p->tokens->item[p->tokenIdx];
}

BOOL isEnd(Parser *p) {
  return (p->tokenIdx >= p->tokens->count);
}

BOOL isNext(Parser *p, char *pTypes) {
  char *token = nextToken(p); 
  if (token == NULL) return FALSE;
  char *type = tokenToType(token);
  char tTypes[MAX_LEN+1];
  sprintf(tTypes, "|%s|", pTypes);
  if (strPartOf(type, tTypes))
    return TRUE;
  else
    return FALSE;
}

char *next(Parser *p, char *pTypes) {
  char *token = nextToken(p);
  if (isNext(p, pTypes)) {
    char *type = tokenToType(token);
    Tree *child = TreeNew(type, token);
    Tree *parentTree = ArrayPeek(p->stack);
    TreeAddChild(parentTree, child);
    printf("%s idx=%d, token=%s, type=%s\n", 
      level(p),p->tokenIdx,token,type);
    p->tokenIdx++;
    return token;
  } else {
    printf("next():%s is not type(%s)\n", token, pTypes);
    error();
    p->tokenIdx++;
    return NULL;
  }
}

Tree* push(Parser *p, char* pType) {
  printf("%s+%s\n", level(p), pType);
  Tree* tree = TreeNew(pType, "");
  ArrayPush(p->stack, tree);
  return tree;
}

Tree* pop(Parser *p, char* pType) {
  Tree *tree = ArrayPop(p->stack);
  printf("%s-%s\n", level(p), tree->type);
  if (strcmp(tree->type, pType)!=0) {
    printf("pop(%s):should be %s\n",tree->type,pType);
	error();
  }
  if (p->stack->count > 0) {
    Tree *parentTree = ArrayPeek(p->stack);
    TreeAddChild(parentTree, tree);
  }
  return tree;
}

