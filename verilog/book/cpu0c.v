`define PC   R[15]   // �{���p�ƾ�
`define LR   R[14]   // �s���Ȧs��
`define SP   R[13]   // ���|�Ȧs��
`define SW   R[12]   // ���A�Ȧs��
// ���A�Ȧs���X�Ц줸
`define N    `SW[31] // �t���X��
`define Z    `SW[30] // �s�X��
`define C    `SW[29] // �i��X��
`define V    `SW[28] // ����X��
`define I    `SW[7]  // �w�餤�_�\�i
`define T    `SW[6]  // �n�餤�_�\�i
`define M    `SW[0]  // �Ҧ��줸

module cpu0c(input clock); // CPU0-Mini ���֨����Gcpu0mc �Ҳ�
  parameter [7:0] LD=8'h00,ST=8'h01,LDB=8'h02,STB=8'h03,LDR=8'h04,STR=8'h05,
    LBR=8'h06,SBR=8'h07,ADDI=8'h08,CMP=8'h10,MOV=8'h12,ADD=8'h13,SUB=8'h14,
    MUL=8'h15,DIV=8'h16,AND=8'h18,OR=8'h19,XOR=8'h1A,ROL=8'h1C,ROR=8'h1D,
    SHL=8'h1E,SHR=8'h1F,JEQ=8'h20,JNE=8'h21,JLT=8'h22,JGT=8'h23,JLE=8'h24,
    JGE=8'h25,JMP=8'h26,SWI=8'h2A,CALL=8'h2B,RET=8'h2C,IRET=8'h2D,
    PUSH=8'h30,POP=8'h31,PUSHB=8'h32,POPB=8'h33;
  reg signed [31:0] R [0:15];   // �ŧi�Ȧs�� R[0..15] �� 16 �� 32 �줸�Ȧs��
  reg signed [31:0] IR;         // ���O�Ȧs�� IR
  reg [7:0] m [0:128];          // �������֨��O����
  reg [7:0] op;                 // �ܼơG�B��N�X op
  reg [3:0] ra, rb, rc;         // �ܼơG�Ȧs���N�� ra, rb, rc
  reg [4:0] c5;                 // �ܼơG5 �줸�`�� c5
  reg signed [11:0] c12;        // �ܼơG12 �줸�`�� c12
  reg signed [15:0] c16;        // �ܼơG16 �줸�`�� c16
  reg signed [23:0] c24;        // �ܼơG24 �줸�`�� c24
  reg signed [31:0] sp, jaddr, laddr, raddr;
  reg signed [31:0] temp;

  initial  // ��l��
  begin
    `PC = 0;                    // �N PC �]���_�ʦ�} 0
    R[0] = 0;                   // �N R[0] �Ȧs���j��]�w�� 0
    {m[0],m[1],m[2],m[3]}    = 32'h001F0018; // 0000       LD   R1, K1
    {m[4],m[5],m[6],m[7]}    = 32'h002F0010; // 0004       LD   R2, K0
    {m[8],m[9],m[10],m[11]}  = 32'h003F0014; // 0008       LD   R3, SUM
    {m[12],m[13],m[14],m[15]}= 32'h13221000; // 000C LOOP: ADD  R2, R2, R1
    {m[16],m[17],m[18],m[19]}= 32'h13332000; // 0010       ADD  R3, R3, R2
    {m[20],m[21],m[22],m[23]}= 32'h26FFFFF4; // 0014       JMP  LOOP
    {m[24],m[25],m[26],m[27]}= 32'h00000000; // 0018 K0:   WORD 0
    {m[28],m[29],m[30],m[31]}= 32'h00000001; // 001C K1:   WORD 1
    {m[32],m[33],m[34],m[35]}= 32'h00000000; // 0020 SUM:  WORD 0
  end
  
  always @(posedge clock) begin // �b clock �ɯߪ�����t��Ĳ�o
      IR = {m[`PC], m[`PC+1], m[`PC+2], m[`PC+3]};  // ���O�^�����q�GIR=m[PC], 4 �� Byte ���O����
      `PC = `PC+4;                                  // �^�������APC �e�i��U�@�ӫ��O��}
      {op,ra,rb,rc,c12} = IR;                      // �ѽX���q�G�N IR �Ѭ� {op, ra, rb, rc, c12}
      c5  = IR[4:0];
      c24 = IR[23:0];
      c16 = IR[15:0];
      jaddr = `PC+c16;
	  laddr = R[rb]+c16;
	  raddr = R[rb]+R[rc];
//	  $display(" ra=%d, rb=%d, rc=%d, jaddr=%x, laddr=%x, raddr=%x", ra, rb, rc, jaddr, laddr, raddr);
      case (op) // �ھ� OP ����������ʧ@
        LD: begin   // ���J���O�G R[ra] = m[addr]
          R[ra] = {m[laddr], m[laddr+1], m[laddr+2], m[laddr+3]};
          $write("%4dns %8x : LD  %x,%x,%-4x", $stime, `PC, ra, rb, c16);
          end
        ST: begin   // �x�s���O�G m[addr] = R[ra]
          {m[laddr], m[laddr+1], m[laddr+2], m[laddr+3]} = R[ra];
          $write("%4dns %8x : ST  %x,%x,%-4x", $stime, `PC, ra, rb, c16);
          end
        LDB:begin   // ���Jbyte;     LDB Ra, [Rb+ Cx];   Ra<=(byte)[Rb+ Cx]
          R[ra] = { 24'b0, m[laddr] };
          $write("%4dns %8x : LDB %x,%x,%-4x", $stime, `PC, ra, rb, c16);
          end
        STB:begin   // �x�sbyte;     STB Ra, [Rb+ Cx];   Ra=>(byte)[Rb+ Cx]
          m[laddr] = R[ra][7:0];
          $write("%4dns %8x : STB %x,%x,%-4x", $stime, `PC, ra, rb, c16);
          end
        LDR:begin   // LD �� Rc ��;  LDR Ra, [Rb+Rc];    Ra<=[Rb+ Rc]
          R[ra] = {m[raddr], m[raddr+1], m[raddr+2], m[raddr+3]};
          $write("%4dns %8x : LDR %x,%x,%-4x", $stime, `PC, ra, rb, c16);
          end
        STR:begin   // ST �� Rc ��;  STR Ra, [Rb+Rc];    Ra=>[Rb+ Rc]
          {m[raddr], m[raddr+1], m[raddr+2], m[raddr+3]} = R[ra];
          $write("%4dns %8x : STR %x,%x,%-4x", $stime, `PC, ra, rb, c16);
          end
        LBR:begin   // LDB �� Rc ��; LBR Ra, [Rb+Rc];    Ra<=(byte)[Rb+ Rc]
          R[ra] = { 24'b0, m[raddr] };
          $write("%4dns %8x : LBR %x,%x,%-4x", $stime, `PC, ra, rb, c16);
          end
        SBR:begin   // STB �� Rc ��; SBR Ra, [Rb+Rc];    Ra=>(byte)[Rb+ Rc]
          m[raddr] = R[ra][7:0];
          $write("%4dns %8x : SBR %x,%x,%-4x", $stime, `PC, ra, rb, c16);
          end
        MOV:begin   // ����;        MOV Ra, Rb;         Ra<=Rb
		  R[ra] = R[rb];
          $write("%4dns %8x : MOV %x,%x", $stime, `PC, ra, rb);
          end
        CMP:begin   // ���;        CMP Ra, Rb;         SW=(Ra >=< Rb)
		  temp = R[ra]-R[rb];
		  `N=(temp<0);`Z=(temp==0);
          $write("%4dns %8x : CMP %x,%x; SW=%x", $stime, `PC, ra, rb, `SW);
          end
        ADDI:begin  // R[a] = Rb+c16;  // �ߧY�ȥ[�k;   LDI Ra, Rb+Cx; Ra<=Rb + Cx
		  R[ra] = R[rb]+c16;
          $write("%4dns %8x : ADDI %x,%x,%-4x", $stime, `PC, ra, rb, c16);
          end
        ADD: begin  // �[�k���O�G R[ra] = R[rb]+R[rc]
          R[ra] = R[rb]+R[rc];
          $write("%4dns %8x : ADD %x,%x,%-4x", $stime, `PC, ra, rb, rc);
          end
        SUB:begin   // ��k;        SUB Ra, Rb, Rc;     Ra<=Rb-Rc
          R[ra] = R[rb]-R[rc];
          $write("%4dns %8x : SUB %x,%x,%-4x", $stime, `PC, ra, rb, rc);
          end
        MUL:begin   // ���k;        MUL Ra, Rb, Rc;     Ra<=Rb*Rc
          R[ra] = R[rb]*R[rc];
          $write("%4dns %8x : MUL %x,%x,%-4x", $stime, `PC, ra, rb, rc);
          end
        DIV:begin   // ���k;        DIV Ra, Rb, Rc;     Ra<=Rb/Rc
          R[ra] = R[rb]/R[rc];
          $write("%4dns %8x : DIV %x,%x,%-4x", $stime, `PC, ra, rb, rc);
          end
        AND:begin   // �줸 AND;    AND Ra, Rb, Rc;     Ra<=Rb and Rc
          R[ra] = R[rb]&R[rc];
          $write("%4dns %8x : AND %x,%x,%-4x", $stime, `PC, ra, rb, rc);
          end
        OR:begin    // �줸 OR;     OR Ra, Rb, Rc;         Ra<=Rb or Rc
          R[ra] = R[rb]|R[rc];
          $write("%4dns %8x : OR  %x,%x,%-4x", $stime, `PC, ra, rb, rc);
          end
        XOR:begin   // �줸 XOR;    XOR Ra, Rb, Rc;     Ra<=Rb xor Rc
          R[ra] = R[rb]^R[rc];
          $write("%4dns %8x : XOR %x,%x,%-4x", $stime, `PC, ra, rb, rc);
          end
        SHL:begin   // �V������;    SHL Ra, Rb, Cx;     Ra<=Rb << Cx
          R[ra] = R[rb]<<c5;
          $write("%4dns %8x : SHL %x,%x,%-4x", $stime, `PC, ra, rb, c5);
          end
        SHR:begin   // �V�k����;        SHR Ra, Rb, Cx;     Ra<=Rb >> Cx
          R[ra] = R[rb]+R[rc];
          $write("%4dns %8x : SHR %x,%x,%-4x", $stime, `PC, ra, rb, c5);
          end		  
        JMP:begin   // ���D���O�G PC = PC + cx24
          `PC = `PC + c24;
          $write("%4dns %8x : JMP %-8x", $stime, `PC, c24);
          end
        JEQ:begin   // ���D (�۵�);        JEQ Cx;        if SW(=) PC  PC+Cx
		  if (`Z) `PC=`PC+c24;
          $write("%4dns %8x : JEQ %-8x", $stime, `PC, c24);
          end
        JNE:begin   // ���D (���۵�);    JNE Cx;     if SW(!=) PC  PC+Cx
		  if (!`Z) `PC=`PC+c24;
          $write("%4dns %8x : JNE %-8x", $stime, `PC, c24);
          end
        JLT:begin   // ���D ( < );        JLT Cx;     if SW(<) PC  PC+Cx
          if (`N) `PC=`PC+c24;
          $write("%4dns %8x : JLT %-8x", $stime, `PC, c24);
          end
        JGT:begin   // ���D ( > );        JGT Cx;     if SW(>) PC  PC+Cx
          if (!`N&&!`Z) `PC=`PC+c24;
          $write("%4dns %8x : JGT %-8x", $stime, `PC, c24);
          end
        JLE:begin   // ���D ( <= );        JLE Cx;     if SW(<=) PC  PC+Cx  
          if (`N || `Z) `PC=`PC+c24;
          $write("%4dns %8x : JLE %-8x", $stime, `PC, c24);
          end
        JGE:begin   // ���D ( >= );        JGE Cx;     if SW(>=) PC  PC+Cx
          if (!`N || `Z) `PC=`PC+c24;
          $write("%4dns %8x : JGE %-8x", $stime, `PC, c24);
          end
        SWI:begin   // �n���_;    SWI Cx;         LR <= PC; PC <= Cx; INT<=1
          `LR=`PC;`PC= c24; `I = 1'b1;
          $write("%4dns %8x : SWI %-8x", $stime, `PC, c24);
          end
        CALL:begin  // ����Ƶ{��;    CALL Cx;     LR<=PC; PC<=PC+Cx
          `LR=`PC;`PC=`PC + c24;
          $write("%4dns %8x : CALL %-8x", $stime, `PC, c24);
          end
        RET:begin   // ��^;            RET;         PC <= LR
          `PC=`LR;
          $write("%4dns %8x : RET, PC=%x", $stime, `PC);
          end
        IRET:begin  // ���_��^;        IRET;         PC <= LR; INT<=0
          `PC=`LR;`I = 1'b0;
          $write("%4dns %8x : RET, PC=%x", $stime, `PC);
          end
        PUSH:begin  // ���J word;    PUSH Ra;    SP-=4;[SP]<=Ra;
          sp = `SP-4; `SP = sp; {m[sp], m[sp+1], m[sp+2], m[sp+3]} = R[ra];
          $write("%4dns %8x : PUSH %-x", $stime, `PC, R[ra]);
		  end
        POP:begin   // �u�X word;    POP Ra;     Ra=[SP];SP+=4;
          sp = `SP+4; `SP = sp; R[ra]={m[sp], m[sp+1], m[sp+2], m[sp+3]};
          $write("%4dns %8x : POP %-x", $stime, `PC, R[ra]);
          end
        PUSHB:begin // ���J byte;    PUSHB Ra;   SP--;[SP]<=Ra;(byte)
          sp = `SP-1; `SP = sp; m[sp] = R[ra];
          $write("%4dns %8x : PUSHB %-x", $stime, `PC, R[ra]);
          end
        POPB:begin  // �u�X byte;    POPB Ra;  Ra<=[SP];SP++;(byte)
          sp = `SP+1; `SP = sp; R[ra]=m[sp];
          $write("%4dns %8x : POPB %-x", $stime, `PC, R[ra]);
          end
      endcase
      $display(" R[%2d]=%4d", ra, R[ra]); // ��ܥؼмȦs������
  end
endmodule

module main;                // ���յ{���}�l
reg clock;                  // �ɯ� clock �ܼ�

cpu0c cpu(clock);          // �ŧi cpu0mc �B�z��

initial clock = 0;          // �@�}�l clock �]�w�� 0
always #10 clock=~clock;    // �C�j 10 �`��N clock �ϬۡA���Ͷg���� 20 �`���ɯ�
initial #640 $finish;       // �b 640 �`���ɭ԰�����աC(�]���o�ɪ� R[1] ��n�O 1+2+...+10=55 �����G)
endmodule
