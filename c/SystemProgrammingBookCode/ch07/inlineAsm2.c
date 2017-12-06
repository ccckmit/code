int main(void)
{
  int foo = 10, bar = 15;
  asm(
    "addl %2,%0"
    :"=r"(foo)
    :"0"(foo), "r"(bar)
	:"0"
  );
  printf("foo=%d\n", foo);
  return 0;
}
