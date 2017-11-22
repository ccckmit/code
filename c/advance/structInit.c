#include <stdio.h>

typedef struct {
	char *name;
	int age;
} person;

int main() {
	person p = {
	  .name = "John",
	  .age = 40
	};
	
	printf("%s is %d years old", p.name, p.age);
	return 0;
}
