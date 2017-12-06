#include "Parser.h"
#include "Generator.h"

void compile(char *cFile, char *asmFile) {
  printf("compile file:%s\n", cFile, asmFile);
  char *cText = newFileStr(cFile);
  Parser *parser = parse(cText);
  generate(parser->tree, asmFile);
  ParserFree(parser);
  freeMemory(cText);
}
