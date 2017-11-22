#ifndef STR_H
#define STR_H
 
typedef struct {
  char *s;
} Str;
 
extern void StrAppend(String*, char *);
 
#endif