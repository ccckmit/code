module main;
reg clock;

initial begin
  $monitor("%4dns clock=%x", $stime, clock);
  clock = 0;
  #300; $finish;
end

always #5 clock=~clock; // �C�j 5ns �ϬۡA�ɯ߶g���� 10ns
endmodule
