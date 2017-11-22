#include <stdio.h>

char **split(char *str, char *spliter, int *tokenCount)
{
  int i, len=0;
  char **tokens;
  
  *tokenCount=0;
  
  for (i=0; i<strlen(str); i++)
  {
    if (strchr(spliter, str[i]) != NULL)
	{
//	  printf("i=%d\n", i);
	  (*tokenCount)++;
	}
  }
  (*tokenCount)++;
//  printf("tokenCount=%d\n", *tokenCount);
  tokens = (char**) malloc((*tokenCount)*sizeof(char*));
  int tokenIdx = 0;
  for (i=0; i<strlen(str)+1; i++)
  {
    if (strchr(spliter, str[i]) != NULL || str[i] == '\0')
	{
	  tokens[tokenIdx] = (char*) malloc(len+1);
	  strncpy(tokens[tokenIdx], &(str[i-len]), len);
	  tokens[tokenIdx][len] = '\0';
	  len = 0;
//	  printf("tokens[%d]=%s\n", tokenIdx, tokens[tokenIdx]);
	  tokenIdx ++;
	}
	len ++;
  }
  return tokens;
}

int main() 
{
  char **tokens, *str = "hello ! How are you !";
  int tokenCount, i;
  tokens = split(str, " ", &tokenCount);
  for (i=0; i<tokenCount; i++)
  {
    printf("token[%d]=%s\n", i, tokens[i]);
  }
}

