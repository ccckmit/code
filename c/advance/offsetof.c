#include <stddef.h>

typedef struct {
     char name[20];
     int age;
} Person;

int main() {
	printf ("offsetof(Person, age)=%d\n", offsetof(Person, age));
}
