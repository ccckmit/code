module regbank(input [3:0] ra1, output [31:0] rd1, 
               input [3:0] ra2, output [31:0] rd2,
               input clk, input w_en, 
               input [3:0] wa, input [31:0] wd);
 reg [31:0] r[15:0]; // �ŧi 16 �� 32 �줸���Ȧs��
 assign rd1 = r[ra1]; // Ū�����ޭȬ� ra1 ���Ȧs��
 assign rd2 = r[ra2]; // Ū�����ޭȬ� ra2 ���Ȧs��
 always @(posedge clk)
 begin
  if (w_en) // w_en=1 �ɼg�J��Ȧs��
    r[wa] <= wd; // �N wd �g�J����ޭȬ� wa ���Ȧs��
 end
endmodule

module main;
reg [3:0] ra1, ra2, wa;
reg clk, w_en;
wire [31:0] rd1, rd2;
reg [31:0] wd;

regbank rb0(ra1, rd1, ra2, rd2, clk, w_en, wa, wd);

initial
begin
  wa = 0;
  ra1 = 0;
  ra2 = 0;
  wd = 0;
  clk = 0;
  w_en = 1;
end

initial #200 ra1 = 0;

always #50 begin
  clk = clk + 1;
  $monitor("%4dns monitor: ra1=%d rd1=%d ra2=%d rd2=%d wa=%d wd=%d", 
           $stime, ra1, rd1, ra2, rd2, wa, wd);
end

always #100 begin
  wa = wa + 1;
  wd = wd + 2;
  ra1 = ra1 + 1;
  ra2 = ra2 - 1;
end

initial #1000 $finish;

endmodule
