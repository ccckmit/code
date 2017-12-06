#include <stdio.h>

typedef struct {
  char *name;
  int age;
} Person;

int main() {
  Person p1 = { "ccc", 41 };
  printf("ccc (p1) => name:%s, age:%d\n", p1.name, p1.age);
  Person p2 = { 
         .name = "ccc",
         .age = 41 };
  printf("ccc (p2) => name:%s, age:%d\n", p2.name, p2.age);         
  system("pause");
}
