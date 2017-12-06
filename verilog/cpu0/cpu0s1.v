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
// IR ���
`define OP   IR[31:24]
`define Ra   IR[23:20]
`define Rb   IR[19:16]
`define Rc   IR[15:12]
`define C5   IR[4:0]

module cpu0(input clock); // CPU0 �B�z��
  parameter [7:0] LD=8'h00,ST=8'h01,LDB=8'h02,STB=8'h03,LDR=8'h04,STR=8'h05,
    LBR=8'h06,SBR=8'h07,ADDI=8'h08,CMP=8'h10,MOV=8'h12,ADD=8'h13,SUB=8'h14,
    MUL=8'h15,DIV=8'h16,AND=8'h18,OR=8'h19,XOR=8'h1A,ROL=8'h1C,ROR=8'h1D,
    SHL=8'h1E,SHR=8'h1F,JEQ=8'h20,JNE=8'h21,JLT=8'h22,JGT=8'h23,JLE=8'h24,
    JGE=8'h25,JMP=8'h26,SWI=8'h2A,CALL=8'h2B,RET=8'h2C,IRET=8'h2D,
    PUSH=8'h30,POP=8'h31,PUSHB=8'h32,POPB=8'h33;
  reg signed [31:0] R [0:15];   // �ŧi�Ȧs�� R[0..15] �� 16 �� 32 �줸�Ȧs��
  reg signed [31:0] IR;         // ���O�Ȧs�� IR
  reg [7:0] m [0:256];          // �������֨��O����
//  reg [4:0] c5;                 // �ܼơG5 �줸�`�� c5
  reg signed [15:0] c16;        // �ܼơG16 �줸�`�� c16
  reg signed [23:0] c24;        // �ܼơG24 �줸�`�� c24
  reg signed [31:0] sp, laddr, raddr;
  reg signed [31:0] temp;
  reg signed [31:0] pc;
  
  integer i;  
  initial begin // ��l��
    `PC = 0;                    // �N PC �]���_�ʦ�} 0
    `SW = 0;
    R[0] = 0;                   // �N R[0] �Ȧs���j��]�w�� 0
    $readmemh("cpu0s.hex", m);
    for (i=0; i < 255; i=i+4) begin
       $display("%8x: %8x", i, {m[i], m[i+1], m[i+2], m[i+3]});
    end
  end
  
  always @(posedge clock) begin // �b clock �ɯߪ�����t��Ĳ�o
      pc = `PC;
      IR = {m[`PC], m[`PC+1], m[`PC+2], m[`PC+3]};  // ���O�^�����q�GIR=m[PC], 4 �� Byte ���O����
      `PC = `PC+4;                                  // �^�������APC �e�i��U�@�ӫ��O��}
      c24 = IR[23:0];
      c16 = IR[15:0];
      laddr = R[`Rb]+c16;
      raddr = R[`Rb]+R[`Rc];
      case (`OP) // �ھ� OP ����������ʧ@
        LD: begin   // ���J���O�G R[`Ra] = m[addr]
          R[`Ra] = {m[laddr], m[laddr+1], m[laddr+2], m[laddr+3]};
          $display("%4dns %8x : LD    R%-d R%-d 0x%x ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, c16, `Ra, R[`Ra], R[`Ra]);
          end
        ST: begin   // �x�s���O�G m[addr] = R[`Ra]
          {m[laddr], m[laddr+1], m[laddr+2], m[laddr+3]} = R[`Ra];
          $display("%4dns %8x : ST    R%-d R%-d 0x%x ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, c16, `Ra, R[`Ra], R[`Ra]);
          end
        LDB:begin   // ���Jbyte;     LDB Ra, [Rb+ Cx];   Ra<=(byte)[Rb+ Cx]
          R[`Ra] = { 24'b0, m[laddr] };
          $display("%4dns %8x : LDB   R%-d R%-d 0x%x ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, c16, `Ra, R[`Ra], R[`Ra]);
          end
        STB:begin   // �x�sbyte;     STB Ra, [Rb+ Cx];   Ra=>(byte)[Rb+ Cx]
          m[laddr] = R[`Ra][7:0];
          $display("%4dns %8x : STB   R%-d R%-d 0x%x ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, c16, `Ra, R[`Ra], R[`Ra]);
          end
        LDR:begin   // LD �� Rc ��;  LDR Ra, [Rb+Rc];    Ra<=[Rb+ Rc]
          R[`Ra] = {m[raddr], m[raddr+1], m[raddr+2], m[raddr+3]};
          $display("%4dns %8x : LDR   R%-d R%-d R%-d    ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, `Rc, `Ra, R[`Ra], R[`Ra]);
          end
        STR:begin   // ST �� Rc ��;  STR Ra, [Rb+Rc];    Ra=>[Rb+ Rc]
          {m[raddr], m[raddr+1], m[raddr+2], m[raddr+3]} = R[`Ra];
          $display("%4dns %8x : STR   R%-d R%-d R%-d    ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, `Rc, `Ra, R[`Ra], R[`Ra]);
          end
        LBR:begin   // LDB �� Rc ��; LBR Ra, [Rb+Rc];    Ra<=(byte)[Rb+ Rc]
          R[`Ra] = { 24'b0, m[raddr] };
          $display("%4dns %8x : LBR   R%-d R%-d R%-d    ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, `Rc, `Ra, R[`Ra], R[`Ra]);
          end
        SBR:begin   // STB �� Rc ��; SBR Ra, [Rb+Rc];    Ra=>(byte)[Rb+ Rc]
          m[raddr] = R[`Ra][7:0];
          $display("%4dns %8x : SBR   R%-d R%-d R%-d    ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, `Rc, `Ra, R[`Ra], R[`Ra]);
          end
        MOV:begin   // ����;        MOV Ra, Rb;         Ra<=Rb
          R[`Ra] = R[`Rb];
          $display("%4dns %8x : MOV   R%-d R%-d        ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, `Ra, R[`Ra], R[`Ra]);
          end
        CMP:begin   // ���;        CMP Ra, Rb;         SW=(Ra >=< Rb)
          temp = R[`Ra]-R[`Rb];
          `N=(temp<0);`Z=(temp==0);
          $display("%4dns %8x : CMP   R%-d R%-d        ; SW=0x%x", $stime, pc, `Ra, `Rb, `SW);
          end
        ADDI:begin  // R[a] = Rb+c16;  // �ߧY�ȥ[�k;   LDI Ra, Rb+Cx; Ra<=Rb + Cx
          R[`Ra] = R[`Rb]+c16;
          $display("%4dns %8x : ADDI  R%-d R%-d %-d ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, c16, `Ra, R[`Ra], R[`Ra]);
          end
        ADD: begin  // �[�k���O�G R[`Ra] = R[`Rb]+R[`Rc]
          R[`Ra] = R[`Rb]+R[`Rc];
          $display("%4dns %8x : ADD   R%-d R%-d R%-d    ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, `Rc, `Ra, R[`Ra], R[`Ra]);
          end
        SUB:begin   // ��k;        SUB Ra, Rb, Rc;     Ra<=Rb-Rc
          R[`Ra] = R[`Rb]-R[`Rc];
          $display("%4dns %8x : SUB   R%-d R%-d R%-d    ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, `Rc, `Ra, R[`Ra], R[`Ra]);
          end
        MUL:begin   // ���k;        MUL Ra, Rb, Rc;     Ra<=Rb*Rc
          R[`Ra] = R[`Rb]*R[`Rc];
          $display("%4dns %8x : MUL   R%-d R%-d R%-d    ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, `Rc, `Ra, R[`Ra], R[`Ra]);
          end
        DIV:begin   // ���k;        DIV Ra, Rb, Rc;     Ra<=Rb/Rc
          R[`Ra] = R[`Rb]/R[`Rc];
          $display("%4dns %8x : DIV   R%-d R%-d R%-d    ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, `Rc, `Ra, R[`Ra], R[`Ra]);
          end
        AND:begin   // �줸 AND;    AND Ra, Rb, Rc;     Ra<=Rb and Rc
          R[`Ra] = R[`Rb]&R[`Rc];
          $display("%4dns %8x : AND   R%-d R%-d R%-d    ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, `Rc, `Ra, R[`Ra], R[`Ra]);
          end
        OR:begin    // �줸 OR;     OR Ra, Rb, Rc;         Ra<=Rb or Rc
          R[`Ra] = R[`Rb]|R[`Rc];
          $display("%4dns %8x : OR    R%-d R%-d R%-d    ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, `Rc, `Ra, R[`Ra], R[`Ra]);
          end
        XOR:begin   // �줸 XOR;    XOR Ra, Rb, Rc;     Ra<=Rb xor Rc
          R[`Ra] = R[`Rb]^R[`Rc];
          $display("%4dns %8x : XOR   R%-d R%-d R%-d    ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, `Rc, `Ra, R[`Ra], R[`Ra]);
          end
        SHL:begin   // �V������;    SHL Ra, Rb, Cx;     Ra<=Rb << Cx
          R[`Ra] = R[`Rb]<<`C5;
          $display("%4dns %8x : SHL   R%-d R%-d %-d     ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, `C5, `Ra, R[`Ra], R[`Ra]);
          end
        SHR:begin   // �V�k����;        SHR Ra, Rb, Cx;     Ra<=Rb >> Cx
          R[`Ra] = R[`Rb]>>`C5;
          $display("%4dns %8x : SHR   R%-d R%-d %-d     ; R%-2d=0x%8x=%-d", $stime, pc, `Ra, `Rb, `C5, `Ra, R[`Ra], R[`Ra]);
          end          
        JMP:begin   // ���D���O�G PC = PC + cx24
          `PC = `PC + c24;
          $display("%4dns %8x : JMP   0x%x       ; PC=0x%x", $stime, pc, c24, `PC);
          end
        JEQ:begin   // ���D (�۵�);        JEQ Cx;        if SW(=) PC  PC+Cx
          if (`Z) `PC=`PC+c24;
          $display("%4dns %8x : JEQ   0x%08x     ; PC=0x%x", $stime, pc, c24, `PC);
          end
        JNE:begin   // ���D (���۵�);    JNE Cx;     if SW(!=) PC  PC+Cx
          if (!`Z) `PC=`PC+c24;
          $display("%4dns %8x : JNE   0x%08x     ; PC=0x%x", $stime, pc, c24, `PC);
          end
        JLT:begin   // ���D ( < );        JLT Cx;     if SW(<) PC  PC+Cx
          if (`N) `PC=`PC+c24;
          $display("%4dns %8x : JLT   0x%08x     ; PC=0x%x", $stime, pc, c24, `PC);
          end
        JGT:begin   // ���D ( > );        JGT Cx;     if SW(>) PC  PC+Cx
          if (!`N&&!`Z) `PC=`PC+c24;
          $display("%4dns %8x : JGT   0x%08x     ; PC=0x%x", $stime, pc, c24, `PC);
          end
        JLE:begin   // ���D ( <= );        JLE Cx;     if SW(<=) PC  PC+Cx  
          if (`N || `Z) `PC=`PC+c24;
          $display("%4dns %8x : JLE   0x%08x     ; PC=0x%x", $stime, pc, c24, `PC);
          end
        JGE:begin   // ���D ( >= );        JGE Cx;     if SW(>=) PC  PC+Cx
          if (!`N || `Z) `PC=`PC+c24;
          $display("%4dns %8x : JGE   0x%08x     ; PC=0x%x", $stime, pc, c24, `PC);
          end
        SWI:begin   // �n���_;    SWI Cx;         LR <= PC; PC <= Cx; INT<=1
          `LR=`PC;`PC= c24; `I = 1'b1;
          $display("%4dns %8x : SWI   0x%08x     ; PC=0x%x", $stime, pc, c24, `PC);
          end
        CALL:begin  // ����Ƶ{��;    CALL Cx;     LR<=PC; PC<=PC+Cx
          `LR=`PC;`PC=`PC + c24;
          $display("%4dns %8x : CALL  0x%08x     ; PC=0x%x", $stime, pc, c24, `PC);
          end
        RET:begin   // ��^;            RET;         PC <= LR
          `PC=`LR;
          $display("%4dns %8x : RET                  ; PC=0x%x", $stime, pc, `PC);
          if (`PC<0) $finish;
          end
        IRET:begin  // ���_��^;        IRET;         PC <= LR; INT<=0
          `PC=`LR;`I = 1'b0;
          $display("%4dns %8x : IRET             ; PC=0x%x", $stime, pc, `PC);
          end
        PUSH:begin  // ���J word;    PUSH Ra;    SP-=4;[SP]<=Ra;
          sp = `SP-4; `SP = sp; {m[sp], m[sp+1], m[sp+2], m[sp+3]} = R[`Ra];
          $display("%4dns %8x : PUSH  R%-d            ; R%-2d=0x%8x, SP=0x%x", $stime, pc, `Ra, `Ra, R[`Ra], `SP);
          end
        POP:begin   // �u�X word;    POP Ra;     Ra=[SP];SP+=4;
          sp = `SP; R[`Ra]={m[sp], m[sp+1], m[sp+2], m[sp+3]}; `SP = sp+4; 
          $display("%4dns %8x : POP   R%-d            ; R%-2d=0x%8x, SP=0x%x", $stime, pc, `Ra, `Ra, R[`Ra], `SP);
          end
        PUSHB:begin // ���J byte;    PUSHB Ra;   SP--;[SP]<=Ra;(byte)
          sp = `SP-1; `SP = sp; m[sp] = R[`Ra];
          $display("%4dns %8x : PUSHB R%-d            ; R[%-d]=0x%8x, SP=0x%x", $stime, pc, `Ra, `Ra, R[`Ra], `SP);
          end
        POPB:begin  // �u�X byte;    POPB Ra;  Ra<=[SP];SP++;(byte)
          sp = `SP+1; `SP = sp; R[`Ra]=m[sp];
          $display("%4dns %8x : POPB  R%-d            ; R[%-d]=0x%8x, SP=0x%x", $stime, pc, `Ra, `Ra, R[`Ra], `SP);
          end
      endcase
  end
endmodule

module main;                // ���յ{���}�l
reg clock;                  // �ɯ� clock �ܼ�

cpu0 cpu(clock);            // �ŧi CPU

initial clock = 0;          // �@�}�l clock �]�w�� 0
always #10 clock=~clock;    // �C�j 10 �`��N clock �ϬۡA���Ͷg���� 20 �`���ɯ�
initial #2000 $finish;      // ������աC(�]���o�ɪ� R[1] ��n�O 1+2+...+10=55 �����G)
endmodule
