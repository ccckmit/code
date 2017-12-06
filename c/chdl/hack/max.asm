0  = 0000    @R0
1  = fc10    D=M              // D = first number
2  = 0001    @R1
3  = f4d0    D=D-M            // D = first number - second number
4  = 000a    @OUTPUT_FIRST
5  = e301    D;JGT            // if D>0 (first is greater) goto output_first
6  = 0001    @R1
7  = fc10    D=M              // D = second number
8  = 000c    @OUTPUT_D
9  = ea87    0;JMP            // goto output_d
10 = 0000 (OUTPUT_FIRST)  @R0             
11 = fc10   D=M              // D = first number
12 = 0002 (OUTPUT_D)   @R2
13 = e308   M=D              // M[2] = D (greatest number)
14 = 000e (INFINITE_LOOP)   @INFINITE_LOOP
15 = ea87   0;JMP            // infinite loop