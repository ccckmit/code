#include <stdio.h>

int* equationAdd(int x[], int y[], int size);
void printArray(int x[], int size);

int main() {
    int A[]={0,5,4,1};
    int B[]={4,2,1,1};
    int *C;
    C = equationAdd(A, B, 4);
    printArray(A, 4);
    printArray(B, 4);
    printArray(C, 4);
    system("pause");
}

void printArray(int x[], int size) {
     int i;
     for (i=0; i<size; i++) {
         printf("%d ", x[i]);
     }
     printf("\n");
}

int* equationAdd(int x[], int y[], int size) {
     int *s = malloc(sizeof(int)*size);
     int i;
     for (i=0; i<size; i++) {
         s[i] = x[i] + y[i];
     }
     return s;
}
