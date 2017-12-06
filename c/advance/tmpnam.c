// tmpnam: generates a unique filename
//Declaration:  char *tmpnam(char *name); 
//Parameters:   *name should be at least L_tmpnam characters long. L_tmpnam is 
//Return:       the unique temp name on success or a null pointer on error. 
#include <stdio.h>

int main(void) {
    char name[40];
    int i;

    for(i=0; i<3; i++) {
      tmpnam(name);
      printf("%s ", name);
    }
    return 0;
}
