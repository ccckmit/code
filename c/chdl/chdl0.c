#include <stdio.h>

typedef struct 
{               
   unsigned a:1;
   unsigned b:1;
   unsigned o:1;
} abo;

typedef struct
{
    unsigned i:1;
    unsigned o:1;
} io;

void nand(abo* p) {
    p->o = !(p->a & p->b);
}

void not(io* p) {
    abo p1 = {.a=p->i, .b=p->i};
    nand(&p1);
    p->o = p1.o;
}

void and(abo* p) {
    abo pnand = {.a=p->a, .b=p->b};
    nand(&pnand);
    io pnot = {.i=pnand.o};
    not(&pnot);
    p->o = pnot.o;
}

typedef struct
{
    unsigned b:1;
    unsigned clock:1;
} BIT;

void posEdge(unsigned int clock) {
    
}

void dff(BIT *p) {
    io bit;
    if (p->clock == 1)
}

int main() {
    abo x = {.a=0, .b=0};
    printf("x.a=%d x.b=%d\n", x.a, x.b);
    nand(&x);
    printf("x.o=%d\n", x.o);

    io y = {.i=0};
    not(&y);
    printf("y.o=%d\n", y.o);

    and(&x);
    printf("x.o=%d\n", x.o);
}

