module FSM(input reset, clock);
  parameter [3:0] LD=4'h0,ADD=4'h1,JMP=4'h2,ST=4'h3,CMP=4'h4,JEQ=4'h5;
  parameter [2:0] start=0, fetch=1, decode=2, execute=3;
  reg [2:0] pstate, nstate;
  
  always @(pstate) begin :combinatorial // �b clock �ɯߪ�����t��Ĳ�o
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
endmodule

module main;           // ���յ{���}�l
reg clock, reset;      // �ɯ� clock �ܼ�

FSM fsm(reset, clock); // �ŧi�B�z��

initial begin
  clock = 0;
  reset = 1;          // �@�}�l�����m
  $monitor("%5dns: reset=%x, pstate=%x ", $stime, reset, mcu0.pstate);
  #50 reset = 0;
  #1000 $finish;
end
always #5 clock=~clock;    // �C�j 10ns �ϬۡA�ɯ߶g���� 20ns
endmodule
