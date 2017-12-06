// �ѦҤ��m�Ghttp://ccckmit.wikidot.com/ocs:cpu0
// �w�q�G�e�קκA�`��
`define INT32 2'b11     // �e�� 32 �줸
`define INT24 2'b10     // �e�� 24 �줸
`define INT16 2'b01     // �e�� 16 �줸
`define BYTE  2'b00     // �e��  8 �줸
// itype ���ﶵ�GRESET:���m���_�AABORT:�������_�AIRQ:�w�餤�_�AERROR:���~���_
`define EXE 3'b000
`define RESET 3'b001
`define ABORT 3'b010
`define IRQ 3'b011
`define ERROR 3'b100

module cpu0(input clock, reset, input [2:0] itype, output reg [2:0] tick, 
             output reg [31:0] ir, pc, mar, mdr, inout [31:0] dbus, 
             output reg m_en, m_rw, output reg [1:0] m_w1);
    reg signed [31:0] R [0:15];
    reg [7:0] op;
    reg [3:0] a, b, c;
    reg signed [11:0] cx12;
    reg signed [15:0] cx16;
    reg signed [23:0] cx24;
    reg [4:0] c5;
    reg signed [31:0] c12, c16, c24, Ra, Rb, Rc, ipc; // ipc:instruction PC

    // �Ȧs��²��
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
    // ���O�s�X��
    parameter [7:0] LD=8'h00,ST=8'h01,LDB=8'h02,STB=8'h03,LDR=8'h04,STR=8'h05,
    LBR=8'h06,SBR=8'h07,LDI=8'h08,CMP=8'h10,MOV=8'h12,ADD=8'h13,SUB=8'h14,
    MUL=8'h15,DIV=8'h16,AND=8'h18,OR=8'h19,XOR=8'h1A,ROL=8'h1C,ROR=8'h1D,
    SHL=8'h1E,SHR=8'h1F,JEQ=8'h20,JNE=8'h21,JLT=8'h22,JGT=8'h23,JLE=8'h24,
    JGE=8'h25,JMP=8'h26,SWI=8'h2A,CALL=8'h2B,RET=8'h2C,IRET=8'h2D,
    PUSH=8'h30,POP=8'h31,PUSHB=8'h32,POPB=8'h33;

    reg inInt = 0;

    task memReadStart(input [31:0] addr, input [1:0] w1); begin // Ū���O���� Word
       mar = addr;     // read(m[addr])
       m_rw = 1;     // Ū���Ҧ��Gread 
       m_en = 1;     // �Ұ�Ū��
       m_w1 = w1;
    end    endtask

    task memReadEnd(output [31:0] data); begin // Ū���O���駹���A���o���
       mdr = dbus; // ���o�O����Ǧ^�� dbus = m[addr]
       data = mdr; // �Ǧ^���
       m_en = 0; // Ū������
    end    endtask

    // �g�J�O���� -- addr:�g�J��}, data:�g�J���
    task memWriteStart(input [31:0] addr, input [31:0] data, input [1:0] w1); begin 
       mar = addr;    // write(m[addr], data)
       mdr = data;
       m_rw = 0;    // �g�J�Ҧ��Gwrite
       m_en = 1;     // �Ұʼg�J
       m_w1  = w1;
    end    endtask

    task memWriteEnd; begin // �g�J�O���駹��
       m_en = 0; // �g�J����
    end endtask

    task regSet(input [3:0] i, input [31:0] data); begin
        if (i!=0) R[i] = data;
    end endtask

    task taskInterrupt(input [2:0] iMode); begin
    if (inInt==0) begin
        case (iMode)
            `RESET: begin `PC = 0; tick = 0; R[0] = 0; `SW = 0; `LR = -1; end
            `ABORT: begin `LR = `PC; `PC = 4; end
            `IRQ:   begin `LR = `PC; `PC = 8; end
            `ERROR: begin `LR = `PC; `PC = 12; end
        endcase
        $display("taskInterrupt(%3b)", iMode);
        inInt = 1;
    end
    end endtask

    task taskExecute; begin
            tick = tick+1;
            m_en = 0;
            case (tick)    
                1: begin  // Tick 1 : ���O�^���A�N PC ����}�׬y�ƤW�Amemory.read(m[PC])
                    memReadStart(`PC, `INT32);
                    ipc  = `PC;
                    `PC = `PC+4;
                end
                2: begin  // Tick 2 : ���O�ѽX�Air = m[PC]
                    memReadEnd(ir); // IR = dbus = m[PC]
                    {op,a,b,c,cx12} = ir;
                    cx24 = ir[23:0];
                    cx16 = ir[15:0];
                    c5  = ir[4:0];
                    c12 = cx12; // ���X cx12 ���ର 32 �줸������ c12
                    c16 = cx16; // ���X cx16 ���ର 32 �줸������ c16
                    c24 = cx24; // ���X cx24 ���ର 32 �줸������ c24
                    Ra = R[a];
                    Rb = R[b];
                    Rc = R[c];
                end
                3: begin // Tick 3 : ���O����
                    case (op)
                        // ���J�x�s���O
                        LD:  memReadStart(Rb+c16, `INT32);         // ���Jword;    LD Ra, [Rb+Cx];     Ra<=[Rb+ Cx]
                        ST:  memWriteStart(Rb+c16, Ra, `INT32); // �x�sword;    ST Ra, [Rb+ Cx];     Ra=>[Rb+ Cx]
                        LDB: memReadStart(Rb+c16, `BYTE);        // ���Jbyte;    LDB Ra, [Rb+ Cx];     Ra<=(byte)[Rb+ Cx]
                        STB: memWriteStart(Rb+c16, Ra, `BYTE);     // �x�sbyte;    STB Ra, [Rb+ Cx];    Ra=>(byte)[Rb+ Cx]
                        LDR: memReadStart(Rb+Rc, `INT32);        // LD��Rc��;     LDR Ra, [Rb+Rc];    Ra<=[Rb+ Rc]
                        STR: memWriteStart(Rb+Rc, Ra, `INT32);    // ST��Rc��;    STR Ra, [Rb+Rc];    Ra=>[Rb+ Rc]
                        LBR: memReadStart(Rb+Rc, `BYTE);        // LDB��Rc��;    LBR Ra, [Rb+Rc];    Ra<=(byte)[Rb+ Rc]
                        SBR: memWriteStart(Rb+Rc, Ra, `BYTE);    // STB��Rc��;    SBR Ra, [Rb+Rc];    Ra=>(byte)[Rb+ Rc]
                        LDI: R[a] = Rb+c16;                     // �ߧY���J;    LDI Ra, Rb+Cx;        Ra<=Rb + Cx
                        // �B����O
                        CMP: begin `N=(Ra-Rb<0);`Z=(Ra-Rb==0); end // ���;        CMP Ra, Rb;         SW=(Ra >=< Rb)
                        MOV: regSet(a, Rb);                 // ����;            MOV Ra, Rb;         Ra<=Rb
                        ADD: regSet(a, Rb+Rc);                // �[�k;            ADD Ra, Rb, Rc;     Ra<=Rb+Rc
                        SUB: regSet(a, Rb-Rc);                // ��k;            SUB Ra, Rb, Rc;     Ra<=Rb-Rc
                        MUL: regSet(a, Rb*Rc);                // ���k;             MUL Ra, Rb, Rc;     Ra<=Rb*Rc
                        DIV: regSet(a, Rb/Rc);                // ���k;             DIV Ra, Rb, Rc;     Ra<=Rb/Rc
                        AND: regSet(a, Rb&Rc);                // �줸 AND;        AND Ra, Rb, Rc;     Ra<=Rb and Rc
                        OR:  regSet(a, Rb|Rc);                // �줸 OR;            OR Ra, Rb, Rc;         Ra<=Rb or Rc
                        XOR: regSet(a, Rb^Rc);                // �줸 XOR;        XOR Ra, Rb, Rc;     Ra<=Rb xor Rc
                        SHL: regSet(a, Rb<<c5);                // �V������;        SHL Ra, Rb, Cx;     Ra<=Rb << Cx
                        SHR: regSet(a, Rb>>c5);                // �V�k����;        SHR Ra, Rb, Cx;     Ra<=Rb >> Cx
                        // ���D���O
                        JEQ: if (`Z) `PC=`PC+c24;            // ���D (�۵�);        JEQ Cx;        if SW(=) PC  PC+Cx
                        JNE: if (!`Z) `PC=`PC+c24;            // ���D (���۵�);    JNE Cx;     if SW(!=) PC  PC+Cx
                        JLT: if (`N)`PC=`PC+c24;        // ���D ( < );        JLT Cx;     if SW(<) PC  PC+Cx
                        JGT: if (!`N&&!`Z) `PC=`PC+c24;        // ���D ( > );        JGT Cx;     if SW(>) PC  PC+Cx
                        JLE: if (`N || `Z) `PC=`PC+c24;        // ���D ( <= );        JLE Cx;     if SW(<=) PC  PC+Cx    
                        JGE: if (!`N || `Z) `PC=`PC+c24;    // ���D ( >= );        JGE Cx;     if SW(>=) PC  PC+Cx
                        JMP: `PC = `PC+c24;                     // ���D (�L����);    JMP Cx;     PC <= PC+Cx
                        SWI: begin `LR=`PC;`PC= c24; `I = 1'b1; end // �n���_;    SWI Cx;         LR <= PC; PC <= Cx; INT<=1
                        CALL:begin `LR=`PC;`PC=`PC + c24; end // ����Ƶ{��;    CALL Cx;     LR<=PC; PC<=PC+Cx
                        RET: begin `PC=`LR; end                // ��^;            RET;         PC <= LR
                        IRET:begin `PC=`LR;`I = 1'b0; end    // ���_��^;        IRET;         PC <= LR; INT<=0
                        // ���|���O    
                        PUSH:begin `SP = `SP-4; memWriteStart(`SP, Ra, `INT32); end // ���J word;    PUSH Ra;    SP-=4;[SP]<=Ra;
                        POP: begin memReadStart(`SP, `INT32); `SP = `SP + 4; end    // �u�X word;    POP Ra;     Ra=[SP];SP+=4;
                        PUSHB:begin `SP = `SP-1; memWriteStart(`SP, Ra, `BYTE); end    // ���J byte;    PUSHB Ra;     SP--;[SP]<=Ra;(byte)
                        POPB:begin memReadStart(`SP, `BYTE); `SP = `SP+1; end        // �u�X byte;    POPB Ra;     Ra<=[SP];SP++;(byte)
                    endcase
                end
                4: begin // Ū���g�J���O�����A�����O����
                    case (op)
                        LD, LDB, LDR, LBR, POP, POPB  : memReadEnd(R[a]); // Ū���O���駹��
                        ST, STB, STR, SBR, PUSH, PUSHB: memWriteEnd(); // �g�J�O���駹��
                    endcase
                    $display("%4dns %8x : %8x R[%02d]=%-8x=%-d SW=%8x", $stime, ipc, ir, a, R[a], R[a], `SW);
                    if (op==RET && `PC < 0) begin
                        $display("RET to PC < 0, finished!");
                        $finish;
                    end
                    tick = 0;
                end                
            endcase
    end endtask

    always @(posedge clock) begin
        if (reset) begin
            taskInterrupt(`RESET);
        end else if (tick == 0 && itype != `EXE) begin
            taskInterrupt(itype);
        end else begin
            inInt = 0;
            taskExecute();
        end
        pc = `PC;
    end
endmodule

module memory0(input clock, reset, en, rw, input [1:0] m_w1, 
                input [31:0] abus, dbus_in, output [31:0] dbus_out);
reg [7:0] m [0:258];
reg [31:0] data;

integer i;
initial begin
    $readmemh("cpu0i.hex", m);
    for (i=0; i < 255; i=i+4) begin
       $display("%8x: %8x", i, {m[i], m[i+1], m[i+2], m[i+3]});
    end
end

    always @(clock or abus or en or rw or dbus_in) 
    begin
        if (abus >=0 && abus <= 255) begin
            if (en == 1 && rw == 0) begin // r_w==0:write
                data = dbus_in;
                case (m_w1)
                    `BYTE:  {m[abus]} = dbus_in[7:0];
                    `INT16: {m[abus], m[abus+1] } = dbus_in[15:0];
                    `INT24: {m[abus], m[abus+1], m[abus+2]} = dbus_in[24:0];
                    `INT32: {m[abus], m[abus+1], m[abus+2], m[abus+3]} = dbus_in;
                endcase
            end else if (en == 1 && rw == 1) begin// r_w==1:read
                case (m_w1)
                    `BYTE:  data = {8'h00  , 8'h00,   8'h00,   m[abus]      };
                    `INT16: data = {8'h00  , 8'h00,   m[abus], m[abus+1]    };
                    `INT24: data = {8'h00  , m[abus], m[abus+1], m[abus+2]  };
                    `INT32: data = {m[abus], m[abus+1], m[abus+2], m[abus+3]};
                endcase
            end else
                data = 32'hZZZZZZZZ;
        end else
            data = 32'hZZZZZZZZ;
    end
    assign dbus_out = data;
endmodule

module main;
reg clock, reset;
reg [2:0] itype;
wire [2:0] tick;
wire [31:0] pc, ir, mar, mdr, dbus;
wire m_en, m_rw;
wire [1:0] m_w1;

cpu0 cpu(.clock(clock), .reset(reset), .itype(itype), .pc(pc), .tick(tick), .ir(ir),
.mar(mar), .mdr(mdr), .dbus(dbus), .m_en(m_en), .m_rw(m_rw), .m_w1(m_w1));

memory0 mem(.clock(clock), .reset(reset), .en(m_en), .rw(m_rw), .m_w1(m_w1), 
.abus(mar), .dbus_in(mdr), .dbus_out(dbus));

initial begin
  clock = 0;
  reset = 1;
  #200 reset = 0; itype=`EXE;
  #100000 $finish;
end

always #1000 begin
  itype = `IRQ; #200 itype = `EXE;
end

always #10 clock=clock+1;

endmodule
