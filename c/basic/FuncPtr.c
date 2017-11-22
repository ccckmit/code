#include <stdio.h>
#include <stdlib.h>

float Plus	  (float a, float b) { return a+b; }
float Minus   (float a, float b) { return a-b; }
float Multiply(float a, float b) { return a*b; }
float Divide  (float a, float b) { return a/b; }

float call(float a, float b, float (*pt2Func)(float, float))
{
   float result = pt2Func(a, b);    // call using function pointer
   return result;
}

int main(void) {
   float result;
   result = call(2, 5, &Plus);
   printf("Switch: Plus(2,5)=%f\n", result);
   result = call(2, 5, &Minus);
   printf("Switch: Minus(2,5)=%f\n", result);
   return 1;
}

