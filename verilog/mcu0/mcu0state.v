module mcu(input reset, clock, mready, output reg mw, men, output reg [11:0] maddr, inout [15:0] mdata);
  parameter [3:0] LD=4'h0,ADD=4'h1,JMP=4'h2,ST=4'h3,CMP=4'h4,JEQ=4'h5;
  parameter [2:0] start=0, fetch=1, decode=2, execute=3;
  reg [2:0] pstate, nstate;
  
  always @(pstate or mready) begin :combinatorial // �b clock �ɯߪ�����t��Ĳ�o
    case (pstate)
      start: begin
	    nstate = fetch;
	  end
      fetch: begin
	    nstate = decode;
      end
      decode: begin
		nstate = execute;
      end
      execute: begin 
	    nstate = fetch;
      end
    endcase
  end
  always @(posedge clock or reset) begin : sequential // �b clock �ɯߪ�����t��Ĳ�o
    if (reset) 
	  pstate <= start;
	else 
      pstate <= nstate;
  end
  assign mdata = mw?mdr:16'hz;
endmodule

module main;                // ���յ{���}�l
reg clock, reset;           // �ɯ� clock �ܼ�
wire w, men, mready;
wire [11:0] addr;
wire [15:0] data;

mcu mcu0(reset, clock, mready, w, men, addr, data); // �ŧi�B�z��

initial begin
  clock = 0;
  reset = 1;          // �@�}�l�����m
  $monitor("%5dns: reset=%x, pstate=%x ", $stime, reset, mcu0.pstate);
  #50 reset = 0;
  #1000 $finish;
end
always #5 clock=~clock;    // �C�j 10ns �ϬۡA�ɯ߶g���� 20ns
endmodule
