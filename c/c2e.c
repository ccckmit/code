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

// �`�N�A�@�Ӥ���r����� byte�A�]�N�O��� char
void mt(char *s) {
  int i, len;
  for (i=0; i<strlen(s); ) {  
    for (len=8; len>0; len-=2) {
	  char word[9];
	  strncpy(word, &s[i], 9);
	  word[len] = '\0';
	  int ci = find(c, word);
	  if (ci >= 0) {
	    printf(" %s ", e[ci]);
		i+=len;
		break;
	  }
	}
	if (len <=0) {
      printf(" _ ");
	  i+=2; // ���L�@�Ӥ���r
	}
  }
}

int main(int argc, char *argv[]) {
  mt(argv[1]); // �q argv (�Ҧp�Gmt �@�����l�@����) �����X�ѼƤ@ (�Ҧp�G�@�����l�@����)
}