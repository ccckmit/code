// ir2as0 �����X�ഫ���զX�y���A�Ϊk�d�ҡG node ir2as0 test.ir0 > test.as0
var fs = require("fs");
var util = require("util");
var format = util.format;  // �r��榡��
var log = console.log;     // �N console.log �W���Y�u�@�I

// Ū�J�����ɡA�ä��Φ��@��@�檺�r��
var lines = fs.readFileSync(process.argv[2], "utf8").split("\n"); 

// ��X�զX�y��
var asm=function(label, op, p, p1, p2) {
  var asCode = format("%s\t%s\t%s\t%s\t%s", label, op, p, p1, p2);
  log(asCode);
}

var cmpCount = 0; // ����B�⪺�аO���i���ơA�G�[�W�@�� counter �H�Y�Ϥ�

// �N�@�椤���X line �ഫ���զX�y��
function ir2as(line) {
  var tokens = line.split("\t"); // �N�����X���Φ��@�Ӥ@�Ӫ����
  var label = tokens[0];         // ���X�аO label
  var iop = tokens[1], aop="";   // ���X�B�� iop
  var p = tokens.slice(2);       // ���X�ѼƳ���
  if (label !== "")              // �Y���аO�A������X�@��u�t�аO���զX�y��
    asm(label, "", "", "", "");
  switch (iop) {                 // �ھڹB�� iop �����e�A�M�w�n�ন�ƻ�զX�y��
    case "=":                    // �d�ҡG= X Y �אּ LD R1, Y; ST R1, X
	asm("", "LD", "R1", p[1], "");
	asm("", "ST", "R1", p[0], "");
	break;
    // �d�ҡG + X A B �אּ LD R1, A;  LD R2, B; ADD R3, R1, R2; ST R3, X;
    case "+": case "-": case "*": case "/": case "<<":
	asm("", "LD", "R1", p[1], "");
	asm("", "LD", "R2", p[2], "");
	aop = {"+":"ADD", "-":"SUB", "*":"MUL", "/":"DIV"}[iop];
	asm("", aop, "R3", "R1", "R2");
	asm("", "ST", "R3", p[0], "");
	break;
    // �d�ҡG ++ X �אּ LDI R1, 1; LD R2, X; ADD R2, R1, R2; ST R2, X; 
    case "++": case "--":
	asm("", "LDI", "R1", "1", "");
	asm("", "LD",  "R2", p[0], "");
	aop = {"++":"ADD", "--":"SUB" }[iop];
	asm("", aop, "R2", "R1", "R2");
	asm("", "ST",  "R2", p[0]);
	break;
    // �d�ҡG < X, A, B �אּ LD R1, A; LD R2, B; CMP R1, R2; JLT CSET0; LDI R1, 1; JMP EXIT0; CSET0: LDI R1, 0; CEXIT0: ST R1, X
    case "<": case "<=": case ">": case ">=": case "==": case "!=": 
	asm("", "LD", "R1", p[1], "");
	asm("", "LD", "R2", p[2], "");
	asm("", "CMP", "R1", "R2", "");
	aop = {"<":"JLT", "<=":"JLE", ">":"JGT", ">=":"JGE", "==":"JEQ", "!=":"JNE"}[iop];
	asm("", aop, "CSET"+cmpCount, "", "");
	asm("", "LDI", "R1", "1", "");
	asm("",  "JMP", "CEXIT"+cmpCount, "", "");
	asm("CSET"+cmpCount, "LDI", "R1", "0", "");
	asm("CEXIT"+cmpCount, "ST", "R1", p[0], "");
	break;
    // �d�ҡG call X, F �אּ CALL F; ST R1, X;
    case "call":
	asm("",  "CALL", p[1], "",   "");
	asm("",  "ST",   "R1", p[0], "");
	break;
    // �d�ҡG arg X �אּ LD R1, X; PUSH R1;
    case "arg":
	asm("",  "LD",  "R1", p[0], "");
	asm("",  "PUSH","R1", "", "");
	break;
    case "function": // �d�ҡG sum function �u�ͦ��аO sum�A�S���ͦ��զX�y�����O
	break;
    case "endf": // ��Ƶ����A�S���ͦ��զX�y�����O
	break;
    case "param": // �d�ҡG param X �אּ POP R1; ST R1, X; 
	asm("",  "POP", "R1", "", "");
	asm("",  "ST",  "R1", p[0], "");
	break;
    case "return":  // �d�ҡG return X �אּ LD R1, X; RET;
	asm("",  "LD","R1", p[0], "");
	asm("",  "RET","", "", "");
	break;
    case "if0":  // �d�ҡG if0 X Label �אּ CMP R0, X; JEQ Label;
	asm("",  "CMP","R0", p[0], "");
	asm("",  "JEQ",p[1], "", "");
	break;
    case "goto":  // �d�ҡG goto Label �אּ JMP label
	asm("",  "JMP", p[0], "", "");
	break;
    case "array":  // �d�ҡG X array �אּ LD R1, X; CALL ARRAY; (���G X=new array())
	asm("",  "LD", "R1", p[0], "");
	asm("",  "CALL", "ARRAY", "", "");
	break;
    case "[]":  // �d�ҡG [] X A i  �אּ LD R1, A; LD R2, i; CALL AGET; ST R1, X (���G X=A[i])
	asm("",  "LD", "R1", p[1], "");
	asm("",  "LD", "R2", p[2], "");
	asm("",  "CALL", "AGET", "", "");
	asm("",  "ST", "R1", p[0], "");
	break;
    case "length": // �d�ҡG length len, A �אּ LD R1, A; CALL ALEN; ST R1, len;
	asm("",  "LD", "R1", p[1], "");
	asm("",  "CALL", "ALEN", "", "");
	asm("",  "ST", "R1", p[0], "");
	break;
    case "apush": // �d�ҡG apush A, X �אּ LD R1,A; LD R2, X; CALL APUSH
	asm("",  "LD", "R1", p[0], "");
	asm("",  "LD", "R2", p[1], "");
	asm("",  "CALL", "APUSH", "", "");
	break;
    case "table": // �d�ҡG table T �אּ LD R1,T; CALL TABLE
	asm("",  "LD", "R1", p[0], "");
	asm("",  "CALL", "TABLE", "", "");
	break;
    case "map": // �d�ҡG map table field value �אּ LD R1, table; LD R2, field; LD R3, value; CALL TMAP
	asm("",  "LD", "R1", p[0], "");
	asm("",  "LD", "R2", p[1], "");
	asm("",  "LD", "R3", p[2], "");
	asm("",  "CALL", "TMAP", "", "");
	break;
    case "":
	break;
    default: 
      log("Error : %s not found!", iop);
  }
}

// �N�Ҧ������X���ഫ���զX�y��
for (var i in lines) {
  if (lines[i].trim().length > 0) {
    log("// %s", lines[i]);
    ir2as(lines[i]);
  }
}
