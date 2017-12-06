#include "chdl.h"

void testGate1() {
    printf("=========== test1Gate() =============\n");
    BIT table[2] = {0,1};

    for (int i=0; i<2; i++) {
        BIT in = table[i];
        BIT o;

        printf("in=%d\n", in);

        not(in, &o);
        ASSERT(o == !in);
    }
}

void testGate2() {
    printf("=========== testGate2() =============\n");
    BIT table[4][2] = {{0,0}, {0,1}, {1,0}, {1,1}};
    
    for (int i=0; i<4; i++) {
        BIT a = table[i][0];
        BIT b = table[i][1];
        BIT o;

        printf("a=%d b=%d\n", a, b);

        nand(a, b, &o);
        ASSERT(o == !(a&&b));
    
        and(a, b, &o);
        ASSERT(o == (a&&b));
    
        or(a, b, &o);
        ASSERT(o == (a||b));
    
        xor(a, b, &o);
        ASSERT(o == (a^b));
    }        
}

void testFullAdder() {
    printf("=========== testFullAdder() =============\n");
    BIT table[8][3] = {{0,0,0}, {0,0,1}, {0,1,0}, {0,1,1},
                       {1,0,0}, {1,0,1}, {1,1,0}, {1,1,1}};
    
    for (int i=0; i<8; i++) {
        BIT a = table[i][0];
        BIT b = table[i][1];
        BIT c = table[i][2];
        BIT sum, carry;

        fullAdder(a, b, c, &sum, &carry);
        printf("a=%d b=%d c=%d sum=%d carry=%d\n", a, b, c, sum, carry);
        ASSERT(sum == (a+b+c)%2);
        ASSERT(carry == (a+b+c)/2);
    }
}

void testMux() {
    printf("=========== testMux() =============\n");
    BIT table[8][3] = {{0,0,0}, {0,0,1}, {0,1,0}, {0,1,1},
                       {1,0,0}, {1,0,1}, {1,1,0}, {1,1,1}};
    
    for (int i=0; i<8; i++) {
        BIT a = table[i][0];
        BIT b = table[i][1];
        BIT s = table[i][2];
        BIT o;

        mux(a, b, s, &o);
        printf("a=%d b=%d s=%d o=%d\n", a, b, s, o);
    }
}

void testDmux() {
    printf("=========== testDmux() =============\n");
    BIT table[4][4] = {{0,0,0,0}, {0,1,0,0}, {1,0,1,0}, {1,1,0,1}};
    for (int i=0; i<4; i++) {
        BIT in = table[i][0];
        BIT s  = table[i][1];
        BIT oa  = table[i][2];
        BIT ob  = table[i][3];
        BIT a,b;
        
        dmux(in, s, &a, &b);
        printf("in=%d s=%d a=%d b=%d\n", in, s, a, b);
        ASSERT(oa==a && ob==b);
    }    
}

void testDmux8way() {
    printf("=========== testDmux8way() =============\n");
    BIT e[8];
    for (int addr = 0; addr < 8; addr++) {
        BIT address[3];
        char estr[9];
        int2bits(addr, address, 3);
        dmux8way(1, address, &e[0], &e[1], &e[2], &e[3], &e[4], &e[5], &e[6], &e[7]);
        bits2str(e, estr, 8);
        printf("dmux8way:addr=%d e=%s\n", addr, estr);
        assert(e[addr] == 1);
    }   
}
    

#define ADDS 2

void testAdd16() {
    printf("=========== testAdd16() =============\n");

    int table[ADDS][3] = {{3,11,14}, {3000,2000,5000}};

    for (int i=0; i<ADDS; i++) {
        BIT a[16], b[16], c[16];
        int2bits(table[i][0], a, 16);
        int2bits(table[i][1], b, 16);
        add16(a, b, c);
        ASSERT(bits2int(c, 16) == table[i][2]);
        printf("a+b = %d\n", bits2int(c, 16));
    }
}

void testAlu() {
    printf("=========== testAlu() =============\n");

    int ia = 35, ib = 20;
    BIT a[W], b[W];
    int2bits(ia, a, W);
    int2bits(ib, b, W);
    printf("alu(35, 20) : 35=100011 20=010100\n");
    for (int i=0; i<AOPS; i++) {
        BIT out[W];
        BIT zr, ng;
        AOP p = aop[i];
        alu(a, b, p.zx, p.nx, p.zy, p.ny, p.f, p.no, out, &zr, &ng);
        WORD iout = bits2int(out, W);
        printf("alu:out= %04hx % 4d zr=%d ng=%d op=%s\n", iout, iout, zr, ng, p.op);
    }
}

void testBit() {
    printf("=========== testBit() =============\n");
    BIT in[]={1,1,1,0,1,1,0}, load[]={0,1,1,1,1,0,0}, out;
    WORD r;
    int i = 0;
    for (timer = 5; timer < 40; timer+=5, i++) {
        bit(&r, 0, in[i], load[i], &out);
        printf("%02d:r=%d in=%d load=%d out=%d\n", timer, r, in[i], load[i], out);
    }
}

void testRegister() {
    printf("=========== testRegister() =============\n");
    WORD in[] = {1,2,3,4,5,6,7,8}, load[]={0,1,1,1,1,0,0};
    WORD r = 374; // 0xFB07;
    int i = 0;
    for (timer = 5; timer < 40; timer+=5, i++) {
        BIT rin[W], rout[W];
        char rinStr[W+1];
        int2bits(in[i], rin, W);
        reg(&r, rin, load[i], rout);
        WORD routInt = bits2int(rout, W);
        WORD rinInt  = bits2int(rin, W);
        printf("%02d:r=%d rin=%d load=%d rout=%d\n", timer, r, rinInt, load[i], routInt);
    }
}

void testRam8() {
    printf("=========== testRam8() =============\n");
    WORD in[]   = {0,1,2,3,4,5,6,7,8,9};
    WORD addr[] = {3,2,1,0,7,3,2,1,0,5,6}; // {0,1,2,3,4,5,6,7,0,1,2}; // {1,4,7,1,4,7,1,4,7,1};
    WORD r[8]   = {90,91,92,93,94,95,96,97};
    BIT load[]  = {0,1,1,1,1,0,0,1,1,0}; // {0,0,0,0,0,0,0,0,0,0}; 
    int i = 0;
    dumpRam(r, 8);
    for (timer = 5; timer <= 50; timer+=5, i++) {
        BIT rin[W], rout[W], raddr[3];
        char rinStr[W+1], raddrStr[4];
        int2bits(in[i], rin, W);
        int2bits(addr[i], raddr, 3);
//        bits2str(raddr, raddrStr, 3);
//        printf("  raddrStr=%s\n", raddrStr);
        ram8(r, rin, load[i], raddr, rout);
        WORD routInt = bits2int(rout, W);
        WORD rinInt  = bits2int(rin, W);
        printf("%02d:rin=%2d load=%d addr=%d rout=%d\n", timer, rinInt, load[i], addr[i], routInt);
        dumpRam(r, 8);
    }
}

void testRam16K() {
    printf("=========== testRam16K() =============\n");
    WORD in[]   = {0,1,2,3,4,5,6,7,8,9};
    WORD addr[] = {11,12,13,0,7,13,12,11,0,6,6}; // {0,1,2,3,4,5,6,7,0,1,2}; // {1,4,7,1,4,7,1,4,7,1};
    WORD r[16*K]   = {90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105};
    BIT load[]  = {0,1,1,1,1,0,0,1,1,0}; // {0,0,0,0,0,0,0,0,0,0}; 
    int i = 0;
    dumpRam(r, 15);
    for (timer = 5; timer <= 50; timer+=5, i++) {
        BIT rin[W], rout[W], raddr[14];
        char rinStr[W+1], raddrStr[15];
        int2bits(in[i], rin, W);
        int2bits(addr[i], raddr, 14);
//        bits2str(raddr, raddrStr, 3);
//        printf("  raddrStr=%s\n", raddrStr);
        ram16K(r, rin, load[i], raddr, rout);
        WORD routInt = bits2int(rout, W);
        WORD rinInt  = bits2int(rin, W);
        printf("%02d:rin=%2d load=%d addr=%d rout=%d\n", timer, rinInt, load[i], addr[i], routInt);
        dumpRam(r, 15);
    }
}

void testRom32K() {
    printf("=========== testRom32K() =============\n");
    int size = loadRam(ROM, "hack/add.hack");
    dumpRam(ROM, size);
    printf("size=%d\n", size);
    int i = 0;
    for (timer = 5; timer < 40; timer+=5, i++) {
        BIT address[15], rout[W];
        int2bits(i, address, 15);
        rom32K(ROM, address, rout);
        WORD routInt = bits2int(rout, W);
        printf("%02d:address=%d rout=%04hx %hd\n", timer, i, routInt, routInt);
    }
}

void testPC() {
    printf("=========== testPC() =============\n");
    BIT reset[] ={0,1,1,1,0,0,0,0,0,0,0,0,0,0, 0, 0, 0, 0, 0, 0, 0};
    BIT inc[]   ={1,1,1,1,1,1,1,1,1,1,1, 1, 1, 1, 1, 1, 1, 1, 1, 1};
    BIT load[]  ={0,0,0,0,0,0,0,0,0,0,0, 1, 1, 1, 1, 0, 0, 0, 0, 0};
    WORD inInt[]={0,0,0,0,0,0,0,0,0,0,0,37,24,15,33,92,74,20,13,19};
    int i=0;
    *PC = 100;
    for (timer = 5; timer < 100; timer+=5, i++) {
        BIT in[16], out[16];
        int2bits(inInt[i], in, 16);
        pc(PC, in, load[i], inc[i], reset[i], out);
        int outInt = bits2int(out, 16);
        printf("%d:PC=%04d reset=%d inc=%d load=%d in=%04hx out=%d\n", timer, *PC, reset[i], inc[i], load[i], inInt[i], outInt);
    }   
}

void testComputer(char *binFile) {
    RAM[0] = 13; RAM[1] = 9; RAM[2] = 0x8FF;
    printf("=========== testComputer() =============\n");
    int size = loadRam(ROM, binFile);
    dumpRam(ROM, size);
    BIT resets[] ={1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int i = 0;
    for (timer=5; ; timer +=5, i++) { // timer < 90
        BIT reset = (i < (sizeof(resets)/sizeof(resets[0]))) ? resets[i] : 0;
        computer(reset);
        printf("%d:PC=%04d A=%04d D=%04d reset=%d\n", timer, *PC, *A, *D, reset);
        if (*PC > size || timer > 500) break;
    }
    dumpRam(RAM, 10);
}

void testChapter1() {
    testGate1();
    testGate2();
    testFullAdder();
    testMux();
    testDmux();
    testDmux8way();
}

void testChapter2() {
    testAdd16();
    testAlu();
}

void testChapter3() {
    testBit();
    testRegister();
    testRam8();
    testRam16K();
    testRom32K();
    testPC();
}

void testChapter5() {
//    testComputer("hack/add.hack");
    testComputer("hack/max.hack");
//    testComputer("hack/rect.hack");
}

void test() {
//    testChapter1();
//    testChapter2();
//    testChapter3();
    testChapter5();
}

int main() {
    init();
    test();
}
