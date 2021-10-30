// ���� � �������, �������������� ��� �������� � ������ �����������
#ifndef CUEMU_STORAGE_H
#define CUEMU_STORAGE_H

// ��������� ���� �����
typedef unsigned __int32 dword;  // ������� �����
typedef unsigned __int64 qword;  // ������������ �����
typedef unsigned __int8 uint8;   // ����

// ������� ������������ ������������ ������ �����������
struct microcommand {
 dword addr;            // �����
 qword cmd;             // ������� ���� �������������
 microcommand *next;    // ��������� �� ��������� �������
};

// ������� ���������� ��������� ���������� �� �������� ���� �������������

// ��������� ���������� ������� ���� �������������
#define GET_CMD(cmd) ((cmd) & 0x1FFFFFFFFF)
// ��������� ���� ��������� ������������ �������
#define GET_CONDITION(cmd) (dword(((cmd) >> 37) & 0x7))
// ��������� ����� �������� �1 (������� 41-45)
#define GET_ADDR1(cmd) (dword(((cmd) >> 40) & 0x1F))
// ��������� ����� �������� �2 (������� 46-50)
#define GET_ADDR2(cmd) (dword(((cmd) >> 45) & 0x1F))
// ��������� ���� ��������� ����������� ������
#define GET_GROUP(cmd) (dword(((cmd) >> 43) & 0x3))

// ��������� ����� � ����� ������������� �����, ��������������� �������������
// cmd_index
#define MK_OP(cmd_index) (qword(1) << (cmd_index-1))
// ��������� ������ �� ���� ��������: �������� low � �������� high
#define MK_GROUP(low,high) ((dword(high)<<1) | dword(low))

// ���������, ������������ �� ������������� mc � ������� ���� �������� cmd
#define IS_PRESENT(cmd,mc) ((cmd) & MK_OP(mc))

// ��������� �������
microcommand *add(microcommand *list);
microcommand *find_prev(microcommand *list);
microcommand *remove(microcommand *list);
void clear(microcommand *list);
microcommand *search_addr(microcommand *list, dword addr);
microcommand *parse_line(microcommand *list, const char *line);
void deparse_line(microcommand *list, char *buf);

#define CHARTOOEM_BUF_SIZE 1024
char *chartooem(const char *str);

#endif