int main() {
  int x = f();
  printf("x=%d\n", x);
}

int f() {
  int a=3, b=4, c, d;
  c=a+b;
  d=a+b;
  return c+d;
}
