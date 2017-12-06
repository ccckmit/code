// ��J a, b ��|���� op �ҫ��w���B��A�M��N���G��b�Ȧs�� y ��
module falu(input [63:0] ia, input [63:0] ib, input [1:0] op, output reg [63:0] oy);
real a, b, y;

always @(a or b or op) begin
  a = $bitstoreal(ia);
  b = $bitstoreal(ib); 
  case (op)
    2'b00: y = a + b;
    2'b01: y = a - b;
    2'b10: y = a * b;
    2'b11: y = a / b;
  endcase
  $display("falu32:op=%d a=%f b=%f y=%f", op, a, b, y);
  oy = $realtobits(y);
end
endmodule

module main;                // ���յ{���}�l
  reg  [63:0] a64, b64;
  wire [63:0] y64;
  reg  [1:0] op;
  real a, b;

  falu falu1(a64, b64, op, y64);     // �إߤ@�� alu �椸�A�W�٬� alu1

  initial begin              // ���յ{������l�ưʧ@
    a = 3.14159;  a64 = $realtobits(a);
    b = 2.71818;  b64 = $realtobits(b);
	op = 0;
  end

  always #50 begin           // �C�� 50 �`��N�@�U�C�ʧ@
    op = op + 1;             // �� op ���ȥ[ 1
  end

  initial #1000 $finish;      // �ɶ��� 1000 �`��N����

endmodule
