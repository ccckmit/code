#include <string.h>
#include "Scanner.h"

char STRING[] = "string";
char NUMBER[] = "number";
char ID[]  = "id";
char KEYWORDS[] = "|if|for|while|return|";
char OP1[] = "|++|--|";
char OP2[] = "|+|-|*|/|";
char COND_OP[] = "|==|!=|<=|>=|<|>|";
char ITEM[]= "|id|number|string|";
char OP[]  = "+-*/<=>!";

#define ch() (scanner->text[scanner->textIdx])
#define next() (scanner->textIdx++)

Scanner* ScannerNew(char *pText) {
  Scanner *scanner = ObjNew(Scanner, 1);
  scanner->text = pText;
  scanner->textLen = strlen(pText);
  scanner->textIdx = 0;
  return scanner;
}

void ScannerFree(Scanner *scanner) {
  ObjFree(scanner);
}

char *ScannerScan(Scanner *scanner) {
  while (strMember(ch(), SPACE))
    next();
  if (scanner->textIdx >= scanner->textLen) 
    return NULL;
  char c = ch();
  int begin = scanner->textIdx;
  if (c == '\"') { // string = ".."
    next(); // skip begin quote "
    while (ch() != '\"') next();
    next(); // skip end quote "
  } else if (strMember(c, OP)) { // OP , ex : ++, --, <=, >=, ...
    while (strMember(ch(), OP)) next();
  } else if (strMember(c, DIGIT)) { // number, ex : 312, 77568, ...
    while (strMember(ch(), DIGIT)) next();
  } else if (strMember(c, ALPHA)) { // name, ex : int, sum, i, for, if, ....
    while (strMember(ch(), ALPHA) || strMember(ch(), DIGIT)) next();
  } else // some other symbol, such as #
    next();
  strSubstr(scanner->token, scanner->text, begin, scanner->textIdx-begin);
  return scanner->token;
}

Array* tokenize(char *text) {
  Array *tokens = ArrayNew(10);
  Scanner *scanner = ScannerNew(text);
  char *token = NULL;
  while ((token = ScannerScan(scanner))!= NULL) {
    ArrayAdd(tokens, newStr(token));
    printf("token=%s\n", token);
  }
  ScannerFree(scanner);
  return tokens;
}

char *tokenToType(char *token) {
  if (strPartOf(token, KEYWORDS))
    return token;
  else if (token[0] == '\"')
    return STRING;
  else if (strMember(token[0], DIGIT))
    return NUMBER;
  else if (strMember(token[0], ALPHA))
    return ID;
  else
    return token;
}

void printTokens(Array *tokens) {
  printf("tokens->count = %d\n", tokens->count);
  int i;
  for (i=0; i<tokens->count; i++) {
    char *token = tokens->item[i];
    printf("token=%s , type=%s\n", token, tokenToType(token));
  }
}
