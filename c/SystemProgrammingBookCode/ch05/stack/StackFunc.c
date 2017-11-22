#include <assert.h>
#include <Stack.h>

void push(int x) {
  assert(top < STACK_SIZE);
  stack[top++] = x;
}

int pop() {
  assert(top > 0);
  return stack[--top];
}
