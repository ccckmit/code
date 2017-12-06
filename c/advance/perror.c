// perror: maps error message to the global variable errno and outputs that string to stderr
//Header file:     #include <stdio.h>  
//Declaration:     void perror(const char *str); 

#include <stdio.h>
#include <stdlib.h>

int main(void) {
    fopen("xxx.txt", "rb");
    perror("My file open error");
}
