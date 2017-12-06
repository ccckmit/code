module multiplier(output reg [63:0] z, input [31:0] x, y); 
reg [31:0] a;
integer i; 

always @(x , y)
begin 
  a=x;
  z=0; // ��l�Ƭ� 0
  for(i=0;i<31;i=i+1) begin
    if (y[i])
      z = z + a; // �Ъ`�N�A�o�O block assignment =�A�ҥH�|�y������A���׶V������V�[�C
    a=a << 1;
  end
end
endmodule

module main; 
reg [31:0] a, b; 
wire [63:0] c; 

multiplier m(c, a, b); 

initial begin 
  a = 17;
  b = 7; 
  #10;
  $display("a=%d b=%d c=%d", a, b, c); 
end 

endmodule 