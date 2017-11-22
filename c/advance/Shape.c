#include <stdio.h>
#include <stddef.h>
#include <assert.h>

enum bool { TRUE=1, FALSE=0} BOOL;

typedef struct { // Shape ン⊿Τ逆
} Shape;

typedef struct { // Shape 摸Τ area() ㄧ计
  int (*area)(Shape*); // 材把计ッ环琌赣ン
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

