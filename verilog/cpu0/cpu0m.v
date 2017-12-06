`define PC R[15] // �{���p�ƾ� PC ���O R[15] ���O�W

module cpu0m(input clock); // CPU0-Mini ���֨����Gcpu0mc �Ҳ�
  parameter [7:0] LD = 8'h00, ST=8'h01, ADD=8'h13, JMP=8'h26; // �䴩 4 �ӫ��O
  reg signed [31:0] R [0:15];   // �ŧi�Ȧs�� R[0..15] �� 16 �� 32 �줸�Ȧs��
  reg signed [31:0] IR;         // ���O�Ȧs�� IR
  reg [7:0] m [0:128];          // �������֨��O����
  reg [7:0] op;                 // �ܼơG�B��N�X op
  reg [3:0] ra, rb, rc;         // �ܼơG�Ȧs���N�� ra, rb, rc
  reg signed [11:0] cx12;       // �ܼơG12 �줸�`�� cx12
  reg signed [15:0] cx16;       // �ܼơG16 �줸�`�� cx16
  reg signed [23:0] cx24;       // �ܼơG24 �줸�`�� cx24
  reg signed [31:0] addr;       // �ܼơG�Ȧs�O�����}

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
      {op,ra,rb,rc,cx12} = IR;                      // �ѽX���q�G�N IR �Ѭ� {op, ra, rb, rc, cx12}
      cx24 = IR[23:0];                              //           �ѥX IR[23:0] ��J cx24
      cx16 = IR[15:0];                              //           �ѥX IR[15:0] ��J cx16
      addr = R[rb]+cx16;                              // �O����s����} = PC+cx16
      case (op) // �ھ� OP ����������ʧ@
        LD: begin   // ���J���O�G R[ra] = m[addr]
          R[ra] = {m[addr], m[addr+1], m[addr+2], m[addr+3]};
          $write("%4dns %8x : LD  %x,%x,%-4x", $stime, `PC, ra, rb, cx16);
          end
        ST: begin   // �x�s���O�G m[addr] = R[ra]
          {m[addr], m[addr+1], m[addr+2], m[addr+3]} = R[ra];
          $write("%4dns %8x : ST  %x,%x,%-4x", $stime, `PC, ra, rb, cx16);
          end
        ADD: begin  // �[�k���O�G R[ra] = R[rb]+R[rc]
          R[ra] = R[rb]+R[rc];
          $write("%4dns %8x : ADD %x,%x,%-4x", $stime, `PC, ra, rb, rc);
          end
        JMP:begin   // ���D���O�G PC = PC + cx24
          addr = cx24; // ���X cx ���ର 32 �줸������
          `PC = `PC + addr; // ���D�ؼЦ�}=PC+cx
          $write("%4dns %8x : JMP %-8x", $stime, `PC, cx24);
          end
      endcase
      $display(" R[%2d]=%4d", ra, R[ra]); // ��ܥؼмȦs������
  end
endmodule

module main;                // ���յ{���}�l
reg clock;                  // �ɯ� clock �ܼ�

cpu0m cpu(clock);          // �ŧi cpu0mc �B�z��

initial clock = 0;          // �@�}�l clock �]�w�� 0
always #10 clock=~clock;    // �C�j 10 �`��N clock �ϬۡA���Ͷg���� 20 �`���ɯ�
initial #640 $finish;       // �b 640 �`���ɭ԰�����աC(�]���o�ɪ� R[1] ��n�O 1+2+...+10=55 �����G)
endmodule
