#include "DES_feedback_by_cipher.h"
#include"permutation_tables.h"
#include <string>
#include <vector>
#include<bitset>
#include <msclr\marshal_cppstd.h>
using namespace std;
using namespace System;
using namespace System::Windows::Forms;
using namespace msclr::interop;

//--------------------------------------------------------------------------------------------------------------------
//������������ ����� � ������ ����� ������
System::Void sortLR(bitset<32>& L, bitset<32>& R, bitset<64>& resIP) {
  for (int i = 0; i < 64; i++) {
    if (i <= 31) { L[i] = resIP[i]; }
    else { R[i - 32] = resIP[i]; }
  }
  return System::Void();
}
//--------------------------------------------------------------------------------------------------------------------
//����������� ����� ������ 56 ���
//  57   49    41   33    25    17    9
//   1   58    50   42    34    26   18
//  10    2    59   51    43    35   27
//  19   11     3   60    52    44   36
//  63   55    47   39    31    23   15
//   7   62    54   46    38    30   22
//  14    6    61   53    45    37   29
//  21   13     5   28    20    12    4
//������������ ���� ������� 56 ������� �����
System::Void sortCD(bitset<28>& C, bitset<28>& D, bitset<64>& resKey) {
  //����������, �������� ����� ������� ����
  int spot = 0;
  int k = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 7; j++, k++) {
      spot = G[i][j];
      //����������� �������� �� ��������� ������
      if (i < 4) { C[k] = resKey[spot - 1]; }
      //����������� ��������� ��������
      else { D[k - 28] = resKey[spot - 1]; }
    }
  }
  return System::Void();
}
//--------------------------------------------------------------------------------------------------------------------
//��������� 48 ������� ����� i-���� ������
System::Void getKi(bitset<28>& C, bitset<28>& D, int i, bitset<48>& Ki) {
  //������ �����
  if (i == 0 || i == 1 || i == 8 || i == 15) {
    C <<= 1;
    D <<= 1;
  }
  else {
    C <<= 2;
    D <<= 2;
  }
  //���������� CD
  bitset<56> CD(0);
  for (int i = 0; i < 56; i++) {
    if (i <= 27) { CD[i] = C[i]; }
    else { CD[i] = D[i - 28]; }
  }
  //������������ 48 ������� ����� �� ������� H
  int spot = 0;
  int k = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 6; j++, k++) {
      spot = H[i][j];
      Ki[k] = CD[spot - 1];
    }
  }
  return System::Void();
}
//--------------------------------------------------------------------------------------------------------------------
//��������� 48 ������� ����� i-���� ������ ��� �������������
System::Void getDecoderKi(bitset<28> C, bitset<28> D, int iterator, bitset<48>& Ki) {
  for (int i = 0; i < iterator; i++) {
    if (i == 0 || i == 1 || i == 8 || i == 15) {
      C <<= 1;
      D <<= 1;
    }
    else {
      C <<= 2;
      D <<= 2;
    }
  }
  //���������� CD
  bitset<56> CD(0);
  for (int i = 0; i < 56; i++) {
    if (i <= 27) { CD[i] = C[i]; }
    else { CD[i] = D[i - 28]; }
  }
  //������������ 48 ������� ����� �� ������� H
  int spot = 0;
  int k = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 6; j++, k++) {
      spot = H[i][j];
      Ki[k] = CD[spot - 1];
    }
  }
  return System::Void();
}
//--------------------------------------------------------------------------------------
//������� F ��������� ���������� DES
System::Void F(bitset<32>& R, bitset<48>& Ki, bitset<32>& resB) {
  //���������� ����� ������ �� ������� �
  bitset<48> ER(0);
  int spot = 0;
  int k = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 6; j++, k++) {
      spot = E[i][j];
      ER[k] = R[spot - 1];
    }
  }
  //�������� ����������� ������ ����� � ������ �� ������ 2
  ER ^= Ki;
  //����� ���������� �������� �� 8 ������ �� 6 ��� 
  bitset<6> ER1(0); bitset<6> ER2(0);
  bitset<6> ER3(0); bitset<6> ER4(0);
  bitset<6> ER5(0); bitset<6> ER6(0);
  bitset<6> ER7(0); bitset<6> ER8(0);
  //������� �������� � ������ ����� �� �������
  for (int i = 0; i < 6; i++) {
    ER1[i] = ER[i]; ER2[i] = ER[i + 6];
    ER3[i] = ER[i + 12]; ER4[i] = ER[i + 18];
    ER5[i] = ER[i + 24]; ER6[i] = ER[i + 30];
    ER7[i] = ER[i + 36]; ER8[i] = ER[i + 42];
  }
  //����������, �������� ����� ������
  bitset<2> row(0);
  //����������, �������� ����� �������
  bitset<4> column(0);
  bitset<32> value_from_S(0);
  //����� �������� � �������� S
  for (int i = 0; i < 8; i++) {
    bitset<6> tmp_ER;
    if (i == 0) { tmp_ER = ER1; } if (i == 1) { tmp_ER = ER2; }
    if (i == 2) { tmp_ER = ER3; } if (i == 3) { tmp_ER = ER4; }
    if (i == 4) { tmp_ER = ER5; } if (i == 5) { tmp_ER = ER6; }
    if (i == 6) { tmp_ER = ER7; } if (i == 7) { tmp_ER = ER8; }
    //����� ��������� �������� � ������� S
    row[0] = tmp_ER[0]; row[1] = tmp_ER[5];
    column[0] = tmp_ER[1]; column[1] = tmp_ER[2];
    column[2] = tmp_ER[3]; column[3] = tmp_ER[4];
    //����������, �������� �������� ������  ������
    int number;
    //����� �������� � �������� S
    if (i == 0) { number = S1[row.to_ulong()][column.to_ulong()] - 1; }
    if (i == 1) { number = S2[row.to_ulong()][column.to_ulong()] - 1; }
    if (i == 2) { number = S3[row.to_ulong()][column.to_ulong()] - 1; }
    if (i == 3) { number = S4[row.to_ulong()][column.to_ulong()] - 1; }
    if (i == 4) { number = S5[row.to_ulong()][column.to_ulong()] - 1; }
    if (i == 5) { number = S6[row.to_ulong()][column.to_ulong()] - 1; }
    if (i == 6) { number = S7[row.to_ulong()][column.to_ulong()] - 1; }
    if (i == 7) { number = S8[row.to_ulong()][column.to_ulong()] - 1; }
    //�������� ������������������ �� 4 ���
    bitset<4> B(number);
    //���������� ������������������ �� 32 ���
    for (int j = 0; j < 4; j++) {
      value_from_S[i * 4 + j] = B[j];
    }
  }
  //������������ ��� � ������������ � �������� P
  spot = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 4; j++) {
      spot = P[i][j];
      resB[i * 4 + j] = value_from_S[spot - 1];
    }
  }
  return System::Void();
}
//--------------------------------------------------------------------------------------
//����������� � ������
string convertToString(vector<bool> resultLR,int lenght) {
  string str = "";
  for (int i = 0; i < (lenght/8); i++) {
    bitset<8> value(0);
    for (int j = 0; j < 8; j++) {
      value[j] = resultLR[i * 8 + j];
    }
    int num = value.to_ulong();
    str += char(num);
  }
  return str;
}
//----------------------------------------------------------------------------------
//������� ���������� ������� DES � ������ "�������� ����� �� �����"
vector<bool> coder(bitset<64> res, bitset<64> resKey,int input_blok_lenght) {
  //���������� ��������� �� �����
  bitset<64> resIP(0);
  int spot = 0;
  //��������� ������������ ��� �� ������� IP
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      spot = IP[i][j];
      resIP[i * 8 + j] = res[spot - 1];
    }
  }
  //������ � ����� ���� ���������
  bitset<32> L(0); bitset<32> R(0);
  //���������� �����
  sortLR(L, R, resIP);
  //��� �������� �����
  bitset<28> C(0); bitset<28> D(0);
  //��������� 56 ������� �����
  sortCD(C, D, resKey);
  //���� i-���� ������
  bitset<48> Ki(0);
  //16 ������� ����������
  for (int c = 0; c < 16; c++) {
    getKi(C, D, c, Ki);
    bitset<32> resB(0);
    F(R, Ki, resB);
    bitset<32> tmp1 = L;
    bitset<32> tmp2 = R;
    L = tmp2;
    R = tmp1 ^ resB;
  }
  //���������� �� ���� ������� ����� ������ 64 ���
  bitset<64> resultLR(0);
  for (int i = 0; i < 64; i++) {
    if (i < 32) { resultLR[i] = L[i]; }
    else { resultLR[i] = R[i - 32]; }
  }
  //�������� ������������
  bitset<64> FP(0);
  spot = 0;
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      spot = finalIP[i][j];
      FP[i * 8 + j] = resultLR[spot - 1];
    }
  }
  //��������� ������� � ���
  vector<bool> k_bit(input_blok_lenght);
  for (int i = 0; i < input_blok_lenght; i++){
    k_bit[i] = FP[i];
  }
  return k_bit;
}
//--------------------------------------------------------------------------------------
//������� ������������� ������� DES � ������ "�������� ����� �� �����"
vector<bool> deCoder(bitset<64> res, bitset<64> resKey, int input_blok_lenght) {
  bitset<64> resIP(0);
  int spot = 0;
  //�������� ������������
  //����������� ��������������� ������ �������� ���� �� ������� IP ��������
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      spot = finalIP[i][j];
      resIP[spot - 1] = res[i * 8 + j];
    }
  }
  bitset<32> L(0);
  bitset<32> R(0);
  //���������� ����� �� ����� � ������
  sortLR(L, R, resIP);
  bitset<28> C(0);
  bitset<28> D(0);
  sortCD(C, D, resKey);
  bitset<48> Ki(0);
  //�������� 16 ������� � �������� ������� 
  for (int c = 16; c > 0; c--) {
    getDecoderKi(C, D, c, Ki);
    bitset<32> resB(0);
    F(L, Ki, resB);
    bitset<32> tmp1 = L;
    bitset<32> tmp2 = R;
    R = tmp1;
    L = tmp2 ^ resB;
  }
  //���������� �� ���� ������� ����� ������ 64 ���
  bitset<64> resultLR(0);
  for (int i = 0; i < 64; i++) {
    if (i < 32) { resultLR[i] = L[i]; }
    else { resultLR[i] = R[i - 32]; }
  }
  bitset<64> FP(0);
  spot = 0;
  //��������� ������������ � �������� �������
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 8; j++) {
      spot = IP[i][j];
      FP[spot - 1] = resultLR[i * 8 + j];
    }
  }
  //��������� ������� � ���
  vector<bool> k_bit(input_blok_lenght);
  for (int i = 0; i < input_blok_lenght; i++) {
    k_bit[i] = FP[i];
  }
  return k_bit;
}

//--------------------------------------------------------------------------------------
//������� ������� ��������� �����
System::Void main() {
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);
  LR4UI::DES_feedback_by_cipher form;
  Application::Run(% form);
  return System::Void();
}
//--------------------------------------------------------------------------------------
//�������, ���������� ��� �������� �����.
//������������� ������������ ����� ������ � ���� ��� ����� ����� - 8 ��������.
System::Void LR4UI::DES_feedback_by_cipher::DES_feedback_by_cipher_Load(System::Object^ sender, System::EventArgs^ e) {
  textBox2->MaxLength = 8;
  textBox3->ReadOnly = true;
  textBox4->ReadOnly = true;
  numericUpDown1->Minimum = 1;
  numericUpDown1->Maximum = 6;
  return System::Void();
}
//�������, ���������� ��� ������� �� ������ "�����������" � �����.
//������������� � ��������� ���� 3 ��������� ������� ����������.
System::Void LR4UI::DES_feedback_by_cipher::button1_Click(System::Object^ sender, System::EventArgs^ e) {
  string text = "";
  string key = "";
  string result = "";
  string f_result = "";
  bitset<64> resKey(0);
  int offset = 0;
  int input_blok_lenght = (int)numericUpDown1->Value * 8;
  text = marshal_as<string>(textBox1->Text);
  key = marshal_as<string>(textBox2->Text);

  //����������� ����� � ������������������ ���
  //������ �� ������� �������
  for (int itKey = 0; itKey < key.length(); itKey++) {
    //������������ ������ � ����
    bitset<8> val(key[itKey]);
    //���������� �������� 8 ��� �������� �������
    for (int i = 0; i < 8; i++) {
      //��������� ������������� ������
      resKey[offset + i] = val[i];
    }
    //���������� �� 8 ���
    offset += 8;
  }
  //���� ����� ����� ������ 8 ��������, 
  //��������� ���������� ����� ������
  for (int itKey = offset; itKey < 64; itKey++) {
    resKey[itKey] = 0;
  }
  //����������� ������ ��������� ������ � ������������������ ���
  int lenght_text_in_bit = 8 * text.length();
  vector<bool> all_text_bit(lenght_text_in_bit);
  for (int i = 0; i < text.length(); i++) {
    bitset<8> tmp(text[i]);
    for (int j = 0; j < 8; j++) {
      all_text_bit[i * 8 + j] = tmp[j];
    }
  }
  //���������� ������� �������������
  bitset<64> vector_inital(12346789);
  //��� ���� �����������
  vector<bool>cipher_text(lenght_text_in_bit);
  //� ��� �����������
  vector<bool>k_bit_cipher_text(input_blok_lenght);
  //� ��� ���������� ���������� DES
  vector<bool>k_bit(input_blok_lenght);
  //���������� ������ �� k ���
  int n = lenght_text_in_bit / input_blok_lenght;
  int finish, finish1;
  for (int j = 0; j < n; j++) {
    //DES ����������
    k_bit = coder(vector_inital, resKey, input_blok_lenght);
    //�������� �� ������ 2 � �������� ������� - ��������� �����������
    for (size_t i = 0; i < input_blok_lenght; i++) {
      k_bit_cipher_text[i] = k_bit[i] ^ all_text_bit[i + j * input_blok_lenght];
      finish = i + j * input_blok_lenght;
    }
    //����� ������� ������������� �� K ���
    vector_inital <<= input_blok_lenght;
    //������ � ����� ������� ������������� K ��� �����������
    //���������� ����� ����������� K ������
    for (size_t i = 0; i < input_blok_lenght; i++) {
      //������ � ����� ������� ������������� �����������
      vector_inital[63 - input_blok_lenght + i] = k_bit_cipher_text[i];
      cipher_text[i + j * input_blok_lenght] = k_bit_cipher_text[i];
      finish1 = i + j * input_blok_lenght;
    }
  }
  //��������� ��������� ���
  n = lenght_text_in_bit % input_blok_lenght;
  k_bit = coder(vector_inital, resKey, input_blok_lenght);
  for (size_t i = 0; i < n; i++) {
    k_bit_cipher_text[i] = k_bit[i] ^ all_text_bit[finish + 1 + i];
  }
  for (size_t i = 0; i < input_blok_lenght - n; i++) {
    k_bit_cipher_text[n + i] = k_bit[i] ^ 0;
  }
  int tmp = 0;
  for (size_t i = finish1 + 1; i < lenght_text_in_bit; i++) {
    cipher_text[i] = k_bit_cipher_text[tmp];
    tmp++;
  }
  //�������������� ��� � �����
  result = convertToString(cipher_text, lenght_text_in_bit);
  //���������� ����� ��� ������ � �����
  String^ myString = marshal_as<System::String^>(result);
  textBox3->Text = myString;
  return System::Void();
}


//--------------------------------------------------------------------------------------
//�������, ���������� ��� ������� �� ������ "������������" � �����.
//������������� � ��������� ���� 3 ��������� ������� �������������.
System::Void LR4UI::DES_feedback_by_cipher::button2_Click(System::Object^ sender, System::EventArgs^ e) {
  string result = "";
  string key = "";
  string decoderResult = "";
  int input_blok_lenght = (int)numericUpDown1->Value * 8;
  bitset<64> resKey(0);
  int offset = 0;
  result = marshal_as<string>(textBox1->Text);
  key = marshal_as<string>(textBox2->Text);
  //����������� ����� � ������������������ ���
  //������ �� ������� �������
  for (int itKey = 0; itKey < key.length(); itKey++) {
    //������������ ������ � ����
    bitset<8> val(key[itKey]);
    //���������� �������� 8 ��� �������� �������
    for (int i = 0; i < 8; i++) {
      //��������� ������������� ������
      resKey[offset + i] = val[i];
    }
    //���������� �� 8 ���
    offset += 8;
  }
  //���� ����� ����� ������ 8 ��������, ��������� ���������� ����� ������
  for (int itKey = offset; itKey < 64; itKey++) {
    resKey[itKey] = 0;
  }
  //����������� ������ ��������� ������ � ������������������ ���
  int lenght_text_in_bit = 8 * result.length();
  vector<bool> all_text_bit(lenght_text_in_bit);
  for (int i = 0; i < result.length(); i++) {
    bitset<8> tmp(result[i]);
    for (int j = 0; j < 8; j++) {
      all_text_bit[i * 8 + j] = tmp[j];
    }
  }
  //���������� ������� �������������
  bitset<64> vector_inital(12346789);
  //��� ���� ��������� ������
  vector<bool>open_text(lenght_text_in_bit);
  //� ��� ��������� ������
  vector<bool>k_bit_open_text(input_blok_lenght);
  //� ��� ���������� ���������� DES
  vector<bool>k_bit(input_blok_lenght);
  //���������� ������ �� k ���
  int n = lenght_text_in_bit / input_blok_lenght;
  int finish, finish1;
  for (int j = 0; j < n; j++) {
    //DES ����������
    k_bit = coder(vector_inital, resKey, input_blok_lenght);
    //�������� �� ������ 2 � �������� ������� - ��������� ��������� ������
    for (size_t i = 0; i < input_blok_lenght; i++) {
      k_bit_open_text[i] = k_bit[i] ^ all_text_bit[i + j * input_blok_lenght];
      finish = i + j * input_blok_lenght;
    }
    //����� ������� ������������� �� K ���
    vector_inital <<= input_blok_lenght;
    //������ � ����� ������� ������������� K ��� �����������
    //���������� ����� ��������� ������ K ������
    for (size_t i = 0; i < input_blok_lenght; i++) {
      //������ � ����� ������� ������������� �����������
      vector_inital[63 - input_blok_lenght + i] = all_text_bit[i + j * input_blok_lenght];
      open_text[i + j * input_blok_lenght] = k_bit_open_text[i];
      finish1 = i + j * input_blok_lenght;
    }
  }
  //��������� ��������� ���
  n = lenght_text_in_bit % input_blok_lenght;
  k_bit = coder(vector_inital, resKey, input_blok_lenght);
  for (size_t i = 0; i < n; i++) {
    k_bit_open_text[i] = k_bit[i] ^ all_text_bit[finish + 1 + i];
  }
  for (size_t i = 0; i < input_blok_lenght - n; i++) {
    k_bit_open_text[n + i] = k_bit[i] ^ 0;
  }
  int tmp = 0;
  for (size_t i = finish1 + 1; i < lenght_text_in_bit; i++) {
    open_text[i] = k_bit_open_text[tmp];
    tmp++;
  }
  //�������������� ��� � �����
  decoderResult = convertToString(open_text, lenght_text_in_bit);
  //���������� ���� ��� ������ ������ � ��������� ����
  String^ myString = marshal_as<System::String^>(decoderResult);
  textBox3->Text = myString;
  return System::Void();
}

System::Void LR4UI::DES_feedback_by_cipher::numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e){
  textBox4->Text =""+ numericUpDown1->Value * 8;
  return System::Void();
}