// ============= Chapter 1 ==================
void nand(BIT a, BIT b, BIT *o) {
    *o = !(a && b);
}

void not(BIT i, BIT *o) {
    nand(i, i, o);
}

void and(BIT a, BIT b, BIT *o) {
    BIT nab;
    nand(a, b, &nab);
    not(nab, o);
}

void or(BIT a, BIT b, BIT *o) {
    BIT na, nb;
    not(a, &na);
    not(b, &nb);
    nand(na, nb, o);
}

void xor(BIT a, BIT b, BIT *o) {
    BIT na, nb, nab, nba;
    not(a, &na);
    not(b, &nb);
    and(na, b, &nab);
    and(a, nb, &nba);
    or(nab, nba, o);
}

void mux(BIT a, BIT b, BIT s, BIT *o) {
    BIT ns, nsa, sb;
    not(s, &ns);
    and(a, ns, &nsa);
    and(b, s, &sb);
    or(nsa, sb, o);
//    printf("    mux:a=%d b=%d s=%d o=%d\n", a, b, s, *o);
}

void dmux(BIT in, BIT s, BIT *a, BIT *b) {
    BIT ns;
    not(s, &ns);
    and(ns, in, a);
    and(s, in, b);
}

void not16(BIT in[16], BIT out[16]) {
    not(in[0], &out[0]);
    not(in[1], &out[1]);
    not(in[2], &out[2]);
    not(in[3], &out[3]);
    not(in[4], &out[4]);
    not(in[5], &out[5]);
    not(in[6], &out[6]);
    not(in[7], &out[7]);
    not(in[8], &out[8]);
    not(in[9], &out[9]);
    not(in[10], &out[10]);
    not(in[11], &out[11]);
    not(in[12], &out[12]);
    not(in[13], &out[13]);
    not(in[14], &out[14]);
    not(in[15], &out[15]);
}

void and16(BIT a[16], BIT b[16], BIT out[16]) {
    and(a[0],  b[0],  &out[0]);
    and(a[1],  b[1],  &out[1]);
    and(a[2],  b[2],  &out[2]);
    and(a[3],  b[3],  &out[3]);
    and(a[4],  b[4],  &out[4]);
    and(a[5],  b[5],  &out[5]);
    and(a[6],  b[6],  &out[6]);
    and(a[7],  b[7],  &out[7]);
    and(a[8],  b[8],  &out[8]);
    and(a[9],  b[9],  &out[9]);
    and(a[10], b[10], &out[10]);
    and(a[11], b[11], &out[11]);
    and(a[12], b[12], &out[12]);
    and(a[13], b[13], &out[13]);
    and(a[14], b[14], &out[14]);
    and(a[15], b[15], &out[15]);
}

void or16(BIT a[16], BIT b[16], BIT out[16]) {
    or(a[0],  b[0],  &out[0]);
    or(a[1],  b[1],  &out[1]);
    or(a[2],  b[2],  &out[2]);
    or(a[3],  b[3],  &out[3]);
    or(a[4],  b[4],  &out[4]);
    or(a[5],  b[5],  &out[5]);
    or(a[6],  b[6],  &out[6]);
    or(a[7],  b[7],  &out[7]);
    or(a[8],  b[8],  &out[8]);
    or(a[9],  b[9],  &out[9]);
    or(a[10], b[10], &out[10]);
    or(a[11], b[11], &out[11]);
    or(a[12], b[12], &out[12]);
    or(a[13], b[13], &out[13]);
    or(a[14], b[14], &out[14]);
    or(a[15], b[15], &out[15]);
}

void mux16(BIT a[16], BIT b[16], BIT sel, BIT out[16]) {
    mux(a[0],  b[0],  sel, &out[0]);
    mux(a[1],  b[1],  sel, &out[1]);
    mux(a[2],  b[2],  sel, &out[2]);
    mux(a[3],  b[3],  sel, &out[3]);
    mux(a[4],  b[4],  sel, &out[4]);
    mux(a[5],  b[5],  sel, &out[5]);
    mux(a[6],  b[6],  sel, &out[6]);
    mux(a[7],  b[7],  sel, &out[7]);
    mux(a[8],  b[8],  sel, &out[8]);
    mux(a[9],  b[9],  sel, &out[9]);
    mux(a[10], b[10], sel, &out[10]);
    mux(a[11], b[11], sel, &out[11]);
    mux(a[12], b[12], sel, &out[12]);
    mux(a[13], b[13], sel, &out[13]);
    mux(a[14], b[14], sel, &out[14]);
    mux(a[15], b[15], sel, &out[15]);
}

void mux4way16(BIT a[16], BIT b[16], BIT c[16], BIT d[16], BIT sel[2], BIT out[16]) {
    BIT outab[16], outcd[16];
    mux16(a, b, sel[0], outab);
    mux16(c, d, sel[0], outcd);
    mux16(outab, outcd, sel[1], out);
}

void mux8way16(BIT a[16], BIT b[16], BIT c[16], BIT d[16], 
               BIT e[16], BIT f[16], BIT g[16], BIT h[16], 
               BIT sel[3], BIT out[16]) {
    BIT outad[16], outeh[16];
    mux4way16(a, b, c, d, &sel[0], outad);
    mux4way16(e, f, g, h, &sel[0], outeh);
    mux16(outad, outeh, sel[2], out);
}


void dmux4way(BIT in, BIT sel[2], BIT *a, BIT *b, BIT *c, BIT *d) {
    BIT iab, icd;
    dmux(in, sel[1], &iab, &icd);
    dmux(iab, sel[0], a, b);
    dmux(icd, sel[0], c, d);
}

void dmux8way(BIT in, BIT sel[3], 
              BIT *a, BIT *b, BIT *c, BIT *d,
              BIT *e, BIT *f, BIT *g, BIT *h) {
    BIT iad, ieh;
    dmux(in, sel[2], &iad, &ieh);
    dmux4way(iad, &sel[0], a, b, c, d);
    dmux4way(ieh, &sel[0], e, f, g, h);
}

void or8way(BIT in[8], BIT *out) {
    BIT or01, or23, or45, or67, or03, or47;
    or(in[0], in[1], &or01);
    or(in[2], in[3], &or23);
    or(in[4], in[5], &or45);
    or(in[6], in[7], &or67);
    or(or01,  or23,  &or03);
    or(or45,  or67,  &or47);
    or(or03,  or47,  out);
}

void or16way(BIT in[16], BIT *out) {
    BIT orLo, orHi;
    or8way(&in[0], &orLo);
    or8way(&in[8], &orHi);
    or(orLo, orHi, out);
}

