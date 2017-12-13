#include <stdio.h>
#include <string.h>

char *e[] = {"dog", "cat", "a",    "chase",  "eat", NULL};
char *c[] = {"��",  "��",  "�@��", "�l",     "�Y" , NULL};

int find(char *nameArray[], char *name) {
  int i;
  for (i=0; nameArray[i] != NULL; i++) {
	if (strcmp(nameArray[i], name)==0) {
	  return i;
	}
  }
  return -1;
}

void mt(char *words[], int len) {
  int i;
  for (i=0; i<len; i++) {
    int ei = find(e, words[i]);
	if (ei < 0) {
	  printf(" _ ");
	} else {
	  printf(" %s ", c[ei]);
	}
  }
}

int main(int argc, char *argv[]) {
//  int ci = find(e, "chase");
//  printf("ci=%d\n", ci);
  mt(&argv[1], argc-1); // �q argv (�Ҧp�Gmt a dog chase a cat) �����X��������} (�Ҧp�Ga dog chase a cat)�C
}