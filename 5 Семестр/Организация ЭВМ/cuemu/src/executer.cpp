#include <cstdlib>
#include <cstdio>
#include <cstring>
#include "executer.h"

// ��� ������� �������� ������������� �������������
// ��������, noncompat_1 �������� ������ �������������, ������������� �
// �������������� 1
uint8 noncompat_1[] = {2, 3, 4, 5, 9, 10, 0};
uint8 noncompat_2[] = {1, 3, 4, 9, 10, 0};
uint8 noncompat_3[] = {1, 2, 9, 10, 0};
uint8 noncompat_4[] = {1, 2, 3, 9, 0};
uint8 noncompat_5[] = {1, 2, 3, 6, 7, 8, 9, 10, 0};
uint8 noncompat_6[] = {7, 8, 5, 9, 10, 0};
uint8 noncompat_7[] = {6, 5, 9, 10, 0};
uint8 noncompat_8[] = {6, 7, 9, 5, 10, 0};
uint8 noncompat_9[] = {1, 2, 3, 4, 5, 6, 7, 8, 10, 0};
uint8 noncompat_10[] = {1, 2, 3, 5, 6, 7, 8, 9, 0};
uint8 noncompat_11[] = {12, 13, 14, 15, 16, 17, 0};
uint8 noncompat_12[] = {11, 13, 14, 15, 16, 17, 0};
uint8 noncompat_13[] = {11, 12, 14, 15, 16, 17, 0};
uint8 noncompat_14[] = {11, 12, 13, 15, 0};
uint8 noncompat_15[] = {11, 12, 13, 14, 16, 17, 18, 19, 20, 21, 22, 0};
uint8 noncompat_16[] = {11, 12, 13, 14, 15, 17, 18, 19, 20, 21, 22, 0};
uint8 noncompat_17[] = {11, 12, 13, 14, 15, 16, 18, 19, 20, 21, 22, 0};
uint8 noncompat_18[] = {16, 17, 19, 20, 21, 22, 0};
uint8 noncompat_19[] = {16, 17, 18, 20, 21, 22, 0};
uint8 noncompat_20[] = {15, 16, 17, 18, 19, 22, 0};
// uint8 noncompat_21[] = {15, 16, 17, 18, 19, 22, 36, 0};
uint8 noncompat_22[] = {15, 16, 17, 18, 19, 20, 21};
uint8 noncompat_23[] = {0};
// uint8 noncompat_24[] = {36, 0};
uint8 noncompat_25[] = {26, 27, 28, 29, 33, 34, 0};
uint8 noncompat_26[] = {25, 27, 28, 29, 33, 34, 0};
uint8 noncompat_27[] = {25, 26, 28, 29, 33, 34, 0};
uint8 noncompat_28[] = {25, 26, 27, 33, 0};
uint8 noncompat_29[] = {25, 26, 27, 30, 31, 32, 0};
uint8 noncompat_30[] = {29, 31, 32, 33, 34, 0};
uint8 noncompat_31[] = {30, 32, 33, 34, 0};
uint8 noncompat_32[] = {29, 30, 31, 33, 34, 0};
uint8 noncompat_33[] = {25, 26, 27, 28, 29, 30, 31, 32, 34, 0};
uint8 noncompat_34[] = {25, 26, 27, 28, 29, 30, 31, 32, 33, 0};

// ������ ���������� �������������
cmdinfo commands[] = {
 {OP_CL_RGA_SIGN,  "����� ��� RGA", noncompat_1},
 {OP_RD_RGA_SIGN,  "����� ��� RGA", noncompat_2},
 {OP_INV_RGA_SIGN, "�������� ��� RGA", noncompat_3},
 {OP_GET_RGA_SIGN, "������ ��� RGA", noncompat_4},
 {OP_CL_RGA_DIG,   "����� �������� �������� RGA", noncompat_6},
 {OP_RD_RGA_DIG,   "����� �������� �������� RGA", noncompat_7},
 {OP_SET_RGA_MSB,  "������� �������� ������� RGA � 1", noncompat_8},
 {OP_SHR_RGA,      "����� ������ RGA", noncompat_9},
 {OP_GET_RGA_INV,  "������ RGA � �������� ����", noncompat_5},
 {OP_GET_RGA,      "������ RGA", noncompat_10},
 {OP_CL_RGB_SIGN,  "����� ��� RGB", noncompat_25},
 {OP_RD_RGB_SIGN,  "����� ��� RGB", noncompat_26},
 {OP_INV_RGB_SIGN, "�������� ��� RGB", noncompat_27},
 {OP_GET_RGB_SIGN, "������ ��� RGB", noncompat_28},
 {OP_CL_RGB_DIG,   "����� �������� �������� RGB", noncompat_30},
 {OP_RD_RGB_DIG,   "����� �������� �������� RGB", noncompat_31},
 {OP_SET_RGB_LSB,  "������� �������� ������� RGB � 1", noncompat_32},
 {OP_SHL_RGB,      "����� RGB �����", noncompat_33},
 {OP_GET_RGB_INV,  "������ RGB � �������� ����", noncompat_29},
 {OP_GET_RGB,      "������ RGB", noncompat_34},
 {OP_CL_SUM_SIGN,  "����� ��� � ��� ���������", noncompat_11},
 {OP_RD_SUM_SIGN,  "����� ��� � ��� ���������", noncompat_12},
 {OP_INV_SUM_SIGN, "�������� ��� � ��� ���������", noncompat_13},
 {OP_GET_SUM_SIGN, "������ ��� ���������", noncompat_14},
 {OP_MK_SUM_INV,   "������������ ��������� ���� � ���������", noncompat_15},
 {OP_GET_SUM,      "������ ���������", noncompat_16},
 {OP_GET_SUM_INV,  "������ ��������� � �������� ����", noncompat_17},
 {OP_CL_SUM_DIG,   "������� �������� �������� ���������", noncompat_18},
 {OP_RD_SUM_DIG,   "����� �������� �������� ���������", noncompat_19},
 {OP_SET_SUM_LSB,  "������� �������� ������� ��������� � 1", noncompat_20},
 {OP_SET_SUM_MSB,  "������� �������� ������� ��������� � 1", noncompat_20},		// noncompat_21==noncompat_20
 {OP_INV_SUM_DIG,  "�������� �������� �������� ���������", noncompat_22},
 {OP_CARRY_LEFT,   "��������� �������/����� �����", noncompat_23},
 {OP_CARRY_RIGHT,  "��������� �������/����� ������", noncompat_23},
 {OP_GET_MEM,      "��������� ������ �� \"������\"", NULL},
 {OP_STOP,         "������� ���������", NULL},
 {OP_DEC_COUNTER,  "��������� ������� �� 1", NULL},
 {0,               NULL}
};

dword rga, rgb, sum, mem, counter, addr;

dword temp_area;

addressing amode = natural;
stepping smode = trace;

int max_sum_iters = 1024;

// ������������� ���� � �������� dw � ������������ �� ��������� [MIN_ADDR, MAX_ADDR]
void set_addr(dword dw)
{
 addr = dw;
#if 0   // MIN_ADDR=0 ��� cuemu-gui
 if (addr<MIN_ADDR) addr = MIN_ADDR;
#endif 
 if (addr>MAX_ADDR) addr = MAX_ADDR;
}

// ����� ��������� ������������� �� ���� cmd
// ���������� ��������� �� ��������� ��������� ���� NULL, ���� ������ �� �������
cmdinfo *find_command(uint8 cmd)
{
 cmdinfo *p = commands;
 while(p->name) {
  if (p->opcode == cmd) return p;
  p++;
 }
 return NULL;
}

// ���������, ���������� �� ������������� code1 � code2
bool is_compatible(uint8 code1, uint8 code2)
{
 cmdinfo *p = find_command(code1);
 if (!p) return false;
 uint8 *ptr = p->noncompat;
 if (!ptr) return true;
 while(*ptr) {
  if (*ptr==code2) return false;
  ptr++;
 }
 return true;
}

// ��������� ������� ���� ������������� cmd �� ������������� �������������.
// ���� ������� ���, ������� ������ ���������� ���������� ���������� ����
// ���� �� ����, ������������ ���������� compat_exception
void check_command(qword cmd)
{
 uint8 i=1;
 cmdinfo *ptr;
 while(i<=37) {
  if (IS_PRESENT(cmd, i)) {
   ptr = find_command(i);
   if (!ptr) break;
   uint8 *p = ptr->noncompat;
   if (!p) break;
   while(*p) {
    if (IS_PRESENT(cmd, *p)) {
     compat_exception ex;
     ex.code1 = i;
     ex.code2 = *p;
     throw ex;
    }
    p++;
   }
  }
  i++;
 }
}

// ������������� �������� � ��������� ��������
void init_registers()
{
 rga = rgb = sum = mem = counter = 0;
 addr = 1;        // ������ ���������� � �������!
}

#pragma startup init_registers

// �������� ���� ����� � ��������� ������
// (��, x86 ����� �� �����... :)
dword sum_with_right_carry(dword dw1, dword dw2, int numbits, dword &carry)
{
 dword res = 0;
 for (int i=numbits-1; i>=0; i--) {
  dword tmp = ((dw1>>i) & 1) + ((dw2>>i) & 1) + carry;
  carry = tmp>>1;
  res |= (tmp & 1)<<i;
 }
 return res;
}

// ��������� ������� cmd � ������ ������������ ������ ���������� c
// ��� ������� ��������� false ������ � ����� ������: ����� ����������
// ������������� 36 (�������)
bool do_execute(qword cmd, cable *c)
{
 bool g5_processed = false;
 bool g6_processed = false;
 bool g8_processed = false;
 temp_area = 0;
 if (IS_PRESENT(cmd, OP_GET_RGA_SIGN)) {
  temp_area |= rga & SIGNUM_MASK;
 }
 if (IS_PRESENT(cmd, OP_GET_RGB_SIGN)) {
  temp_area |= rgb & SIGNUM_MASK;
 }
 if (IS_PRESENT(cmd, OP_GET_SUM_SIGN)) {
  temp_area |= sum & SIGNUM_MASK;
 }
 if (IS_PRESENT(cmd, OP_GET_RGA)) {
  temp_area |= rga & REG_MASK;
 }
 if (IS_PRESENT(cmd, OP_GET_RGB)) {
  temp_area |= rgb & REG_MASK;
 }
 if (IS_PRESENT(cmd, OP_GET_SUM)) {
  temp_area |= sum & REG_MASK;
 }
 if (IS_PRESENT(cmd, OP_GET_MEM)) {
  temp_area |= mem & REG_MASK;
 }
 if (IS_PRESENT(cmd, OP_GET_RGA_INV)) {
  dword tmp = rga & REG_MASK;
  if (tmp & SIGNUM_MASK) tmp ^= DIGITS_MASK;
  temp_area |= tmp;
 }
 if (IS_PRESENT(cmd, OP_GET_RGB_INV)) {
  dword tmp = rgb & REG_MASK;
  if (tmp & SIGNUM_MASK) tmp ^= DIGITS_MASK;
  temp_area |= tmp;
 }
 if (IS_PRESENT(cmd, OP_GET_SUM_INV)) {
  dword tmp = sum & REG_MASK;
  if (tmp & SIGNUM_MASK) tmp ^= DIGITS_MASK;
  temp_area |= tmp;
 }
 if (IS_PRESENT(cmd, OP_CL_RGA_SIGN)) {
  rga &= ~SIGNUM_MASK;
 }
 if (IS_PRESENT(cmd, OP_RD_RGA_SIGN)) {
  rga |= temp_area & SIGNUM_MASK;
 }
 if (IS_PRESENT(cmd, OP_INV_RGA_SIGN)) {
  rga ^= SIGNUM_MASK;
 }
 if (IS_PRESENT(cmd, OP_CL_RGA_DIG)) {
  rga &= ~DIGITS_MASK;
 }
 if (IS_PRESENT(cmd, OP_RD_RGA_DIG)) {
  rga |= temp_area & DIGITS_MASK;
 }
 if (IS_PRESENT(cmd, OP_SET_RGA_MSB)) {
  rga |= MSB_MASK;
 }
 if (IS_PRESENT(cmd, OP_SHR_RGA)) {
  rga = ((rga & DIGITS_MASK) >> 1) | (rga & SIGNUM_MASK);
  if (GET_C(C_G1)) rga |= MSB_MASK;
 }
 out_connector(c, C_G2, rga & LSB_MASK);
 if (IS_PRESENT(cmd, OP_CL_RGB_SIGN)) {
  rgb &= ~SIGNUM_MASK;
 }
 if (IS_PRESENT(cmd, OP_RD_RGB_SIGN)) {
  rgb |= temp_area & SIGNUM_MASK;
 }
 if (IS_PRESENT(cmd, OP_INV_RGB_SIGN)) {
  rgb ^= SIGNUM_MASK;
 }
 if (IS_PRESENT(cmd, OP_CL_RGB_DIG)) {
  rgb &= ~DIGITS_MASK;
 }
 if (IS_PRESENT(cmd, OP_RD_RGB_DIG)) {
  rgb |= temp_area & DIGITS_MASK;
 }
 if (IS_PRESENT(cmd, OP_SET_RGB_LSB)) {
  rgb |= LSB_MASK;
 }
 if (IS_PRESENT(cmd, OP_SHL_RGB)) {
  rgb = ((rgb << 1) & DIGITS_MASK) | (rgb & SIGNUM_MASK);
  if (GET_C(C_G10)) rgb |= LSB_MASK;
 }
 out_connector(c, C_G9, rgb & MSB_MASK);
 if (IS_PRESENT(cmd, OP_CL_SUM_SIGN)) {
  sum &= ~(SIGNUM_MASK | OVERFLOW_MASK);
 }
 if (IS_PRESENT(cmd, OP_RD_SUM_SIGN)) {
  sum ^= temp_area & SIGNUM_MASK;
  sum ^= (temp_area & SIGNUM_MASK) << 1;
 }
 if (IS_PRESENT(cmd, OP_INV_SUM_SIGN)) {
  sum ^= (SIGNUM_MASK | OVERFLOW_MASK);
 }
 if (IS_PRESENT(cmd, OP_MK_SUM_INV)) {
  if (sum & SIGNUM_MASK) sum ^= DIGITS_MASK;
 }
 if (IS_PRESENT(cmd, OP_CL_SUM_DIG)) {
  g8_processed = true;
  g5_processed = true;
  g6_processed = true;
  if (IS_PRESENT(cmd, OP_CARRY_LEFT)) {
   if (find_connection(c, C_G5, C_G6)) {
    sum = ((sum << 1) & DIGITS_MASK) | (sum & (SIGNUM_MASK | OVERFLOW_MASK))
          | GET_C(C_G8);
   } else {
    out_connector(c, C_G3, sum>>10);
    flush_connectors();
    sum = ((sum<<1) & SUM_MASK) | GET_C(C_G8);
   }
  } else if (IS_PRESENT(cmd, OP_CARRY_RIGHT)) {
   if (find_connection(c, C_G5, C_G6)) {
    sum = ((sum & DIGITS_MASK) >> 1) | (sum & (SIGNUM_MASK | OVERFLOW_MASK));
    sum |= GET_C(C_G5)<<10;
   } else sum >>= 1;
  } else sum &= ~DIGITS_MASK;
 }
 if (IS_PRESENT(cmd, OP_RD_SUM_DIG)) {
  if (IS_PRESENT(cmd, OP_CARRY_LEFT)) {
   int i;
   sum += temp_area & DIGITS_MASK + GET_C(C_G8);
   out_connector(c, C_G3, sum >> 11);
   sum &= SUM_MASK;
   for (i=0; i<max_sum_iters; i++) {
    flush_connectors();
    if (!GET_C(C_G8)) break;
    sum++;
    out_connector(c, C_G3, sum >> 11);
    sum &= SUM_MASK;
   }
  } else if (IS_PRESENT(cmd, OP_CARRY_RIGHT)) {
   dword carry = GET_C(C_G5);
   sum = sum_with_right_carry(sum, temp_area & DIGITS_MASK, 10, carry);
   out_connector(c, C_G4, carry);
   for (int i=0; i<max_sum_iters; i++) {
    flush_connectors();
    if (!GET_C(C_G5)) break;
    carry = GET_C(C_G5);
    sum = sum_with_right_carry(sum, 0, 10, carry);
    out_connector(c, C_G4, carry);
    sum &= SUM_MASK;
   }
  } else sum ^= ((temp_area & DIGITS_MASK) | GET_C(C_G8) | (GET_C(C_G5)<<10)
                                           | (GET_C(C_G6)<<9));
  g8_processed = true;
  g5_processed = true;
  g6_processed = true;
 } else out_connector(c, C_G3, 0);
 if (!g8_processed) {
  sum ^= GET_C(C_G8);
 }
 if (!g5_processed) {
  sum ^= GET_C(C_G5)<<10;
 }
 if (!g6_processed) {
  sum ^= GET_C(C_G6)<<9;
 }
// out_connector(c, C_G6, sum & OVERFLOW_MASK);
 if (IS_PRESENT(cmd, OP_SET_SUM_LSB)) {
  sum |= LSB_MASK;
 }
 if (IS_PRESENT(cmd, OP_SET_SUM_MSB)) {
  sum |= MSB_MASK;
 }
 if (IS_PRESENT(cmd, OP_INV_SUM_DIG)) {
  sum ^= DIGITS_MASK;
 }
 if (IS_PRESENT(cmd, OP_DEC_COUNTER)) {
  counter--;
  counter &= COUNTER_MASK;
 }
 if (IS_PRESENT(cmd, OP_STOP)) {addr = 1; return false;}
 out_connector(c, C_ONE, true);
 out_connector(c, C_COUNT, counter!=0);
 flush_connectors();
 return true;
}

// ��������� ��������������, ������������ � ������ list � ������
// ���������� connect
void execute(microcommand *list, cable *connect)
{
 if (!list) return;
repeat:              // ���� ����� �������, ���� smode==eauto
 microcommand *ptr;
 while(true) {
// ������ ������� � ������� addr (����)
  ptr = search_addr(list, addr);
  if (ptr) break;       // ���� �������, �� ��������� ��
// ���� ���, �� ��������� � ���������� ������
  addr++;
  if (addr>MAX_ADDR) {addr = MIN_ADDR; return;}
 }
// ��������� ������� �� ������ ���������
 switch(amode) {
  case natural:         // ������������ ���������
  {
   int c = GET_CONDITION(ptr->cmd);
   if (c) {
    bool val = GET_C(C_C1 + c - 1);
//  ���� �������� � �� ������� �������, �� ��������� �� ��������� � ��� �� ������
    if (val) addr = GET_ADDR1(ptr->cmd);
    else addr++;     // � ��������� ������ ������ ����������� ����
   } else addr++;
  }
  break;
  case forced1:
  {
// �������������� ��������� � ����� �������� �����
// ����� �������� ������: ���� ������� �����, �� ���� ������������� �� 1,
// ���� ������� - �� ���� ����������� �� ��������� ���� �� � �� �� �����������
   int c = GET_CONDITION(ptr->cmd);
   if (c) {
    bool val = GET_C(C_C1 + c - 1);
    if (val) {addr++; goto complete;}
    else addr = GET_ADDR1(ptr->cmd);
   } else {    // ���� ������ ������������ ������� ����� ���� - ����������� �������
    addr = GET_ADDR1(ptr->cmd);
   }
  }
  break;
  case forced2:
  {
// �������������� ��������� � ����� ��������� ������
// ���� ������� �������, �� ������������ ������ �������� ����
// ���� �����, �� ������ (� �.�. ����� ������ ������� ����� ����)
   int c = GET_CONDITION(ptr->cmd);
   if (c) {
    bool val = GET_C(C_C1 + c - 1);
    if (val) addr = GET_ADDR2(ptr->cmd);
    else addr = GET_ADDR1(ptr->cmd);
   } else {
    addr = GET_ADDR1(ptr->cmd);
   }
  }
  break;
  case forcedma:
  {
// �������������� ��������� � ������������� ����������
   int c = GET_CONDITION(ptr->cmd);
   dword grp;
   switch(GET_GROUP(ptr->cmd)) {
    case 0: addr++; break;
    case 1: grp = MK_GROUP(GET_C(C_C1), GET_C(C_C2)); break;
    case 2: grp = MK_GROUP(GET_C(C_C3), GET_C(C_C4)); break;
    case 3: grp = MK_GROUP(GET_C(C_C5), GET_C(C_C6)); break;
   }
   if (c) {
    bool val = GET_C(C_C1 + c - 1);
    if (val) {
     addr++;
     goto complete;
    } else {
     addr = (GET_ADDR1(ptr->cmd) & 0x7) | (grp<<3);
    }
   } else {
    addr = (GET_ADDR1(ptr->cmd) & 0x7) | (grp<<3);
   }
  }
  break;
 }
 if (!do_execute(ptr->cmd, connect)) return;

 complete:
 if (smode==eauto) goto repeat;
}