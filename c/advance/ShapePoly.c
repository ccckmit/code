#include <stdio.h>

typedef struct _Shape { // Shape ����A�S�����
  void (*new)(struct _Shape*);
  float (*area)(struct _Shape*); // �Ĥ@�ӰѼƥû��O�Ӫ���
} Shape;

float ShapeArea(Shape *obj) { return 0; }

void ShapeNew(Shape *obj) {
  obj->new = ShapeNew;
  obj->area = ShapeArea;
}

// �Ъ`�N�A�ϥ��~�ӮɡA�����O���֦�����줧�ŧi�����ǡA�@�w�n�M�����O�@�ˡC
typedef struct _Circle {
  void (*new)(struct _Circle*, float); 
  float (*area)(struct _Circle*);
  float r;
} Circle;

float CircleArea(Circle *obj) { return 3.14 * obj->r * obj->r; }

void CircleNew(Circle *obj, float r) {
  obj->new = CircleNew;
  obj->area = CircleArea;
  obj->r = r;
}

int main() {
  Shape s;
  ShapeNew(&s);
  printf(("s.area()=%G\n", s.area(s));
  
  Circle c;
  CircleNew(&c, 3.0);
  printf(("c.area()=%G\n", c.area(s));
}
