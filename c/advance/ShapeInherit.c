#include <stdio.h>

typedef struct _Shape { // Shape 物件，沒有欄位
  void (*new)(struct _Shape*);
  float (*area)(struct _Shape*); // 第一個參數永遠是該物件
} Shape;

float ShapeArea(Shape *obj) { return 0; }

void ShapeNew(Shape *obj) {
  obj->new = ShapeNew;
  obj->area = ShapeArea;
}

// 請注意，使用繼承時，父類別中擁有的欄位之宣告的順序，一定要和父類別一樣。
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
  printf("s.area()=%G\n", s.area(&s));
  
  Circle c;
  CircleNew(&c, 3.0);
  printf("c.area()=%G\n", c.area(&c));
}
