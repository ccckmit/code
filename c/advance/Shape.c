#include <stdio.h>
#include <stddef.h>
#include <assert.h>

enum bool { TRUE=1, FALSE=0} BOOL;

typedef struct { // Shape ����A�S�����
} Shape;

typedef struct { // Shape ���O�A���@�� area() ���
  int (*area)(Shape*); // �Ĥ@�ӰѼƥû��O�Ӫ���
} ShapeClass;

int ShapeArea(Shape *obj);

ShapeClass shapeClass = {
  .area = ShapeArea
};

int ShapeArea(Shape *obj) {
  printf("&ShapeObject=%p &shapeClass=%p\n", obj, &shapeClass);
  assert(FALSE);
}

int main() {
  Shape s;
  ShapeArea(&s);
}

