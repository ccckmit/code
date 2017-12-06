#define W 16
#define K 1024
// #define KW (K*W)
#define MMAX (64*K)

WORD M[MMAX];
WORD *A, *D, *PC, *MEMORY, *RAM, *SCREEN, *KEYBOARD, *ROM;

void init() {
    A = &M[0];
    D = &A[1];
    PC= &D[1];
    
    MEMORY = &PC[1];
    RAM = MEMORY;
    SCREEN = &MEMORY[16*K];
    KEYBOARD = &SCREEN[8*K];
    
    ROM = &KEYBOARD[1];
}

#define AOPS 18
typedef struct {
    BIT zx, nx, zy, ny, f, no;
    char *op;
} AOP;

AOP aop[AOPS] = {
    {1,0,1,0,1,0, "0"}, //  
    {1,1,1,1,1,1, "1"}, //  1
    {1,1,1,0,1,0, "-1"}, // -1
    {0,0,1,1,0,0, "x"}, //  x
    {1,1,0,0,0,0, "y"}, //  y
    {0,0,1,1,0,1, "!x"}, // !x
    {1,1,0,0,0,1, "!y"}, // !y
    {0,0,1,1,1,1, "-x"}, // -x
    {1,1,0,0,1,1, "-y"}, // -y
    {0,1,1,1,1,1, "x+1"}, // x+1
    {1,1,0,1,1,1, "y+1"}, // y+1
    {0,0,1,1,1,0, "x-1"}, // x-1
    {1,1,0,0,1,0, "y-1"}, // y-1
    {0,0,0,0,1,0, "x+y"}, // x+y
    {0,1,0,0,1,1, "x-y"}, // x-y
    {0,0,0,1,1,1, "y-x"}, // y-x
    {0,0,0,0,0,0, "x&y"}, // x&y
    {0,1,0,1,0,1, "x|y"}, // x|y    
};

#include "chapter1.c"
#include "chapter2.c"
#include "chapter3.c"
#include "chapter5.c"
