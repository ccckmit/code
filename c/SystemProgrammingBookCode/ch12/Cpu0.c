#include "Cpu0.h"

void runObjFile(char *objFile) {
  printf("===VM0:run %s on CPU0===\n", objFile);
  Cpu0 *cpu0 = Cpu0New(objFile);
  Cpu0Run(cpu0, 0);
  Cpu0Dump(cpu0);
  Cpu0Free(cpu0);
}

Cpu0* Cpu0New(char *objFile) {
  Cpu0 *cpu0=ObjNew(Cpu0, 1);
  cpu0->m = newFileBytes(objFile, &cpu0->mSize);
  return cpu0;
}

void Cpu0Free(Cpu0 *cpu0) {
  freeMemory(cpu0->m);
  ObjFree(cpu0);
}

#define bits(i, from, to) \
  ((UINT32) i << (31-to) >> (31-to+from))
#define ROR(i, k) \
  (((UINT32)i>>k)|(bits(i,32-k, 31)<<(32-k)))
#define ROL(i, k) \
  (((UINT32)i<<k)|(bits(i,0,k-1)<<(32-k)))
#define SHR(i, k) ((UINT32)i>>k)
#define SHL(i, k) ((UINT32)i<<k)
#define bytesToInt32(p) \
  (INT32)(p[0]<<24|p[1]<<16|p[2]<<8|p[3])
#define bytesToInt16(p) (INT16)(p[0]<<8|p[1])
#define int32ToBytes(i, bp) \
  { bp[0]=i>>24; bp[1]=i>>16; bp[2]=i>>8; bp[3]=i;}
#define StoreInt32(i, m, addr) \
  { BYTE *p=&m[addr]; int32ToBytes(i, p); }
#define LoadInt32(i, m, addr) \
  { BYTE *p=&m[addr]; i=bytesToInt32(p); }
#define StoreByte(b, m, addr) \
  { m[addr] = (BYTE) b; }
#define LoadByte(b, m, addr) { b = m[addr]; }

#define PC R[15]
#define LR R[14]
#define SP R[13]
#define FP R[12]
#define SW R[11]
#define CC cpu0->cc

void Cpu0Run(Cpu0 *cpu0, int start) {
  int IR, op, ra, rb, rc, cc;
  int c5, c12, c16, c24, caddr, raddr;
  BYTE *m=cpu0->m;
  int  *R=cpu0->R;
  PC = start;
  LR = -1;
  BOOL stop = FALSE;
  while (!stop) {
    R[0] = 0;
    LoadInt32(IR, m, PC);
    cpu0->IR = IR;
    PC += 4;
    op = bits(IR, 24, 31);
    ra = bits(IR, 20, 23);
    rb = bits(IR, 16, 19);
    rc = bits(IR, 12, 15);
    c5 = bits(IR,  0, 4);
    c12= bits(IR, 0, 11);
    c16= bits(IR, 0, 15);
    c24= bits(IR, 0, 23);
    if (bits(IR, 11, 11)!=0) c12 |= 0xFFFFF000;
    if (bits(IR, 15, 15)!=0) c16 |= 0xFFFF0000;
    if (bits(IR, 23, 23)!=0) c24 |= 0xFF000000;
    caddr = R[rb]+c16;
    raddr = R[rb]+R[rc];
    switch (op) {
      case OP_LD : LoadInt32(R[ra], m, caddr); break;
      case OP_ST : StoreInt32(R[ra], m, caddr); break;
      case OP_LB : LoadByte(R[ra], m, caddr); break;
      case OP_SB : StoreByte(R[ra], m, caddr); break;
      case OP_LDR: LoadInt32(R[ra], m, raddr); break;
      case OP_STR: StoreInt32(R[ra], m, raddr); break;
      case OP_LBR: LoadByte(R[ra], m, raddr); break;
      case OP_SBR: StoreByte(R[ra], m, raddr); break;
      case OP_LDI: R[ra] = c16; break;
      case OP_CMP: {
        if (R[ra] > R[rb])
          CC = '>';
        else if (R[ra] < R[rb])
          CC = '<';
        else
          CC = '=';
        break;
      } case OP_MOV: R[ra] = R[rb]; break;
      case OP_ADD: R[ra] = R[rb] + R[rc]; break;
      case OP_SUB: R[ra] = R[rb] - R[rc]; break;
      case OP_MUL: R[ra] = R[rb] * R[rc]; break;
      case OP_DIV: R[ra] = R[rb] / R[rc]; break;
      case OP_AND: R[ra] = R[rb] & R[rc]; break;
      case OP_OR:  R[ra] = R[rb] | R[rc]; break;
      case OP_XOR: R[ra] = R[rb] ^ R[rc]; break;
      case OP_ROL: R[ra] = ROL(R[rb],c5); break;
      case OP_ROR: R[ra] = ROR(R[rb],c5); break;
      case OP_SHL: R[ra] = SHL(R[rb],c5); break;
      case OP_SHR: R[ra] = SHR(R[rb],c5); break;
      case OP_JEQ: if (CC=='=') PC += c24; break;
      case OP_JNE: if (CC!='=') PC += c24; break;
      case OP_JLT: if (CC=='<') PC += c24; break;
      case OP_JGT: if (CC=='>') PC += c24; break;
      case OP_JLE: if (strMember(CC, "<=")) PC+=c24; break;
      case OP_JGE: if (strMember(CC, ">=")) PC+=c24; break;
      case OP_JMP: PC+=c24; break;
      case OP_SWI: LR = PC; PC=c24; break;
      case OP_JSUB:LR = PC; PC+=c24; break;
      case OP_RET: if (LR<0) stop=TRUE; else PC=LR; break;
      case OP_PUSH:SP-=4; StoreInt32(R[ra], m, SP); break;
      case OP_POP: LoadInt32(R[ra], m, SP); SP+=4; break;
      case OP_PUSHB:SP--; StoreByte(R[ra], m, SP); break;
      case OP_POPB:LoadByte(R[ra], m, SP); SP++; break;
      default: printf("Error:invalid op (%02x) ", op);
    }
    printf("PC=%08x IR=%08x R[%02d]=0x%08x=%d\n", 
            PC, IR, ra, R[ra], R[ra]);
  }
}

void Cpu0Dump(Cpu0 *cpu0) {
  printf("\n===CPU0 dump registers===\n");
  printf("IR =0x%08x=%d\n", cpu0->IR, cpu0->IR);
  int i;
  for (i=0; i<16; i++)
    printf("R[%02d]=0x%08x=%d\n",i,cpu0->R[i],cpu0->R[i]);
}
