// ��J a, b ��|���� op �ҫ��w���B��A�M��N���G��b�Ȧs�� y ��
module alu(input [31:0] a, input [31:0] b, input [1:0] op, output reg [31:0] y);

    task f32to64(input [31:0] x32, output [63:0] x64); 
    reg [10:0] e;
    begin
        e = {3'b0, x32[30:23]};
        e = e + (1023 - 127);
        x64 = {x32[31], e, x32[22:0], 29'b0};
    end endtask

    task f64to32(input [63:0] x64, output [31:0] x32); 
    reg [10:0] e;
    begin
        e = {x64[62:52]};
        e = e + (127-1023);
        x32 = {x64[63], e[7:0], x64[51-:23]};
    end endtask
	
    task falu32(input [31:0] a32, input [31:0] b32, input [1:0] op, output [31:0] y32);
    reg [63:0] a64, b64, y64;
    real a, b, y;
    begin
        f32to64(a32, a64); a = $bitstoreal(a64);
        f32to64(b32, b64); b = $bitstoreal(b64); 
        case (op)
            2'b00: y = a + b;
            2'b01: y = a - b;
            2'b10: y = a * b;
            2'b11: y = a / b;
        endcase
         $display("falu32:op=%d a=%f b=%f y=%f", op, a, b, y);
        y64 = $realtobits(y);
        f64to32(y64, y32);
    end
    endtask
	
	always @(a or b or op) begin
	  flu32(a, b, op, y);
	end
endmodule

module main;                // ���յ{���}�l
 reg  [7:0] a, b;           // �ŧi a, b �� 8 �줸�Ȧs��
 wire  [7:0] y;             // �ŧi y �� 8 �줸�u��
 reg  [2:0] op;             // �ŧi op �� 3 �줸�Ȧs��

 alu alu1(a, b, op, y);     // �إߤ@�� alu �椸�A�W�٬� alu1

 initial begin              // ���յ{������l�ưʧ@
  a = 8'h07;                // �]�w a ���ƭ� 7
  b = 8'h03;                // �]�w b ���ƭ� 3
  op = 3'b000;              // �]�w op ����l�Ȭ� 000
 end

 always #50 begin           // �C�� 50 �`��N�@�U�C�ʧ@
   op = op + 1;             // �� op ���ȥ[ 1
 end

initial #1000 $finish;      // �ɶ��� 1000 �`��N����

endmodule
