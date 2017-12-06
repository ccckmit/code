#include <stdlib.h>
#include <mcheck.h>

int main(){
        mtrace();
        for(int i =0;i<2;i++){
                int * p  = (int*) malloc(sizeof(int));
                p[1] = 1;
                free(p);
        }
        return 0;
}