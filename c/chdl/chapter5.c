// ============= Chapter 5 ==================

void screen(WORD r[8*K], BIT in[16], BIT load, BIT address[13], BIT out) {
    // ram8K(r, in, load, address, out);
}

void keyboard(WORD r[1], BIT out[16]) {
    BIT in[16];
    if (_kbhit()) *r = _getch();
    reg(r, in, 0, out);
}

void memory(WORD r[24*K+1], BIT in[16], BIT load, BIT address[15], BIT out[16]) {
    BIT N14, Mload, Sload, outM[16], outS[16], outK[16], outSK[16];
    not(address[14], &N14);
    and(N14, load, &Mload);
    and(address[14], load, &Sload);
//    printf("  memory:address=%04hx N14=%d Mload=%d Sload=%d\n", bits2int(address, 15), N14, Mload, Sload);
    ram16K(r, in, Mload, address, outM); // 16K
//    printf("  ram16K:in=%04hx outM=%04hx", bits2int(in, 16), bits2int(outM, 16));
    screen(&r[16*K], in, Sload, address, outS); // 8K
//    printf("  screen:address=%04hx N14=%d Mload=%d Sload=%d\n", bits2int(address, 15), N14, Mload, Sload);
    keyboard(&r[24*K], outK); // size=1
//    printf("  keyboard:address=%04hx N14=%d Mload=%d Sload=%d\n", bits2int(address, 15), N14, Mload, Sload);
    mux16(outS, outK, address[13], outSK);
    mux16(outM, outSK, address[14], out);
}


BIT Aout[16], AorM[16], Dout[16], ALUout[16], Ain[16];
BIT Ainstruction, AluToA, Aload, PCload, Dload;
BIT ng, zr, g, ngzr, passLT, passEQ, passGT, passLE, pass;

void cpu(BIT inM[16], BIT instruction[16], BIT reset,
         BIT outM[16], BIT *writeM, BIT addressM[15], BIT outPc[15]) { // BIT addressM[15], BIT outPc[15]
    printf("  instruction=%04hx\n", bits2int(instruction, 16));
    // JUMP condition
    or(ng, zr, &ngzr);
    not(ngzr, &g);
    and(ng, instruction[2], &passLT);
    and(zr, instruction[1], &passEQ);
    and(g,  instruction[0], &passGT);
    or(passLT, passEQ, &passLE);
    or(passLE, passGT, &pass);
    and(instruction[15], pass, &PCload);
    printf("  ng=%x zr=%x g=%x pass=%x PCload=%x ALUout=%04hx\n", ng, zr, g, pass, PCload, bits2int(ALUout, 16));

    mux16(Aout, inM, instruction[12], AorM);

    // ALU
    alu(Dout, AorM, instruction[11], instruction[10], instruction[9],
        instruction[8], instruction[7], instruction[6], ALUout, &zr, &ng);
//    printf("  ALUout=%04hx zr=%x ng=%x\n", bits2int(ALUout, 16), zr, ng);

    // PC
    pc(PC, Aout, PCload, 1, reset, outPc); // 這裡有問題 outPC 慢一拍，而且被存起來，與真正 PC 脫離了 ??
    printf("  PC=%04hx Aout=%04hx PCload=%d reset=%d outPc=%04hx\n", *PC, bits2int(Aout, 16), PCload, reset, bits2int(outPc, 15));
/*
85:PC=0006 A=0010 D=0004 reset=0
  instruction=0001
  ng=0 zr=0 g=1 pass=1 PCload=0 ALUout=0004
  PC=0007 Aout=000a (真正的 PC) PCload=0 reset=0 outPc=0006 ???
  computer:PC=0007 outPC=0006 A=0001 D=0004 instruction=0001 loadM=0 addressM=000a outM=0000
90:PC=0007 A=0001 D=0004 reset=0
*/    
    
    // A register
    not(instruction[15], &Ainstruction);
    and(instruction[15], instruction[5], &AluToA); // AluToA = I[15]&d1
    or(Ainstruction, AluToA, &Aload);
    mux16(instruction, ALUout, AluToA, Ain);
    reg(A, Ain, Aload, Aout);

    and16(Aout, Aout, addressM);
//    printf("  A=%04hx Ain=%04hx Aload=%x Aout=%04hx addressM=%04hx\n", *A, bits2int(Ain, 16), Aload, bits2int(Aout, 16), bits2int(addressM, 15));

    // D register
    and(instruction[15], instruction[4], &Dload);
    
    reg(D, ALUout, Dload, Dout);

    // Output
    and(instruction[15], instruction[3], writeM);
    and16(ALUout, ALUout, outM);
}

// 這裡必須用全域變數，因為有迴路！ rom32K => instructiion => cpu => outPc => rom32K
// BIT inM[16], loadM, addressM[15], outM[16], outPc[15], instruction[16];
BIT inM[16], loadM, addressM[16], outM[16], outPc[16], instruction[16];

void computer(BIT reset) {
    int2bits(*PC, outPc, 15); // 因為 outPC 慢一拍，所以補上這行！
    rom32K(ROM, outPc, instruction);
//    printf("  rom32k:outPc=%04hx instruction=%04hx\n", bits2int(outPc, 15), bits2int(instruction, 16));
    cpu(outM, instruction, reset, inM, &loadM, addressM, outPc);
    //    printf("cpu:outM=%04hx instructon=%04hx reset=%x inM=%04hx loadM=%x addressM=%04hx outPc=%04hx\n", 
    //      bits2int(outM,16), bits2int(instruction, 16), reset, bits2int(inM,16), loadM, bits2int(addressM,15), bits2int(outPc,16));
    memory(MEMORY, inM, loadM, addressM, outM);
//    printf("  memory: addressM=%04hx, inM=%04hx, loadM=%x outM=%04hx\n", bits2int(addressM, 15), bits2int(inM, 16), loadM, bits2int(outM, 16));
    printf("  computer:PC=%04hx outPC=%04hx A=%04hx D=%04hx instruction=%04hx loadM=%x addressM=%04hx outM=%04hx\n", 
           *PC, bits2int(outPc, 15), *A, *D, bits2int(instruction, 16), loadM, bits2int(addressM, 15), bits2int(outM, 16));
}
