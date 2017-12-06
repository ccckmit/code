// ============= Chapter 2 ==================
void halfAdder(BIT a, BIT b, BIT *sum, BIT *carry) {
    xor(a, b, sum);
    and(a, b, carry);
}

void fullAdder(BIT a, BIT b, BIT c, BIT *sum, BIT *carry) {
    BIT s1, c1, c2;
    xor(a, b, &s1);
    xor(s1, c, sum);
    and(a, b, &c1);
    and(s1, c, &c2);
    xor(c1, c2, carry);
}

void add16(BIT a[16], BIT b[16], BIT o[16]) {
    BIT c[16];
    fullAdder(a[0],  b[0],     0,  &o[0],  &c[0]);
    fullAdder(a[1],  b[1],  c[0],  &o[1],  &c[1]);
    fullAdder(a[2],  b[2],  c[1],  &o[2],  &c[2]);
    fullAdder(a[3],  b[3],  c[2],  &o[3],  &c[3]);
    fullAdder(a[4],  b[4],  c[3],  &o[4],  &c[4]);
    fullAdder(a[5],  b[5],  c[4],  &o[5],  &c[5]);
    fullAdder(a[6],  b[6],  c[5],  &o[6],  &c[6]);
    fullAdder(a[7],  b[7],  c[6],  &o[7],  &c[7]);
    fullAdder(a[8],  b[8],  c[7],  &o[8],  &c[8]);
    fullAdder(a[9],  b[9],  c[8],  &o[9],  &c[9]);
    fullAdder(a[10], b[10], c[9],  &o[10], &c[10]);
    fullAdder(a[11], b[11], c[10], &o[11], &c[11]);
    fullAdder(a[12], b[12], c[11], &o[12], &c[12]);
    fullAdder(a[13], b[13], c[12], &o[13], &c[13]);
    fullAdder(a[14], b[14], c[13], &o[14], &c[14]);
    fullAdder(a[15], b[15], c[14], &o[15], &c[15]);
}

void inc16(BIT in[16], BIT out[16]) {
    BIT one[16] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    add16(in, one, out);
}

void alu(BIT x[16], BIT y[16], 
         BIT zx, BIT nx, BIT zy, BIT ny, BIT f, BIT no, 
         BIT out[16], BIT* zr, BIT* ng) {
    BIT zero[16] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    BIT x1[16], x2[16], notx1[16], y1[16], y2[16], noty1[16];
    BIT addxy[16], andxy[16], o1[16], o2[16], noto1[16];
    BIT notzr;
    mux16(x, zero, zx, x1);     // if (zx == 1) set x = 0  
    not16(x1, notx1);
    mux16(x1, notx1, nx, x2);   // if (nx == 1) set x = !x

    mux16(y, zero, zy, y1);     // if (zy == 1) set y = 0
    not16(y1, noty1);
    mux16(y1, noty1, ny, y2);   // if (ny == 1) set y = !y

    add16(x2, y2, addxy);       // addxy = x + y
    and16(x2, y2, andxy);       // andxy = x & y

    mux16(andxy, addxy, f, o1); // if (f == 1)  set out = x + y else set out = x & y
    not16(o1, noto1);
    mux16(o1, noto1, no, out);
    or16way(out, &notzr);       // notzr = Or(out[0..15]);
    not(notzr, zr);             // zr = !notzr
    and(out[15], out[15], ng); // ng = out[15]
}
