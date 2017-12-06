#ifndef PARSER_H
#define PARSER_H

#include "Scanner.h"
#include "Tree.h"

typedef struct {
  Array *tokens;
  Tree *tree;
  Array* stack;
  int tokenIdx;
} Parser;

Parser *parse(char *text);

Parser *ParserNew();
void ParserParse(Parser *p, char *text);
void ParserFree(Parser *parser);

#endif
