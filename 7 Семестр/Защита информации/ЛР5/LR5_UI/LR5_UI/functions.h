#include <math.h>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

//�������
const char ALPHABET[34]{ ' ', '�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�',
                        '�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�','�' };
//--------------------------------------------------------------------------------------
//������� �������� �� ������� �����
bool prime(int n) {
  bool k = true;
  if (n != 2) {
    for (int i = 2; i < (int)sqrt(n) + 1; i++) {
      //����� ����� �� ��� ����� �� ���� 
      if (n % i == 0) {
        // ���� ������� 0, ����� �� �������
        k = false;
        break;
      }
    }
  }
  return k;
}
//--------------------------------------------------------------------------------------
//������� ��������� �������� �����
int genPrime() {
  int t = rand() % INT_MAX/10;
  do {
    t++;
  } 
  while (!prime(t));
  return t;
}
//--------------------------------------------------------------------------------------
//������� ���������� ��� ������� �������
int evklid(int num1, int num2) {
  vector<int> r;
  int i = 1;
  r.push_back(max(num1, num2));
  r.push_back(min(num1, num2));
  while (r[i] != 0){
    i++;
    r.push_back(r[i - 2] % r[i - 1]);
  }
  return r[i - 1];
}
//--------------------------------------------------------------------------------------
//������� ��������� ������� �������� �����
int genCoprime(int x){
  int i = 1 + rand() % 99;
  do{
    i++;
  } 
  while (evklid(x, i) != 1);
  return i;
}
//--------------------------------------------------------------------------------------
//������� ���������� ��������� ����������
int gend(int f, int e) {
  for (int i = 1; i < 100; i++){
    if (((f * (i)+1) % e) == 0){
      return (int)((f * (i)+1) / e);
    }
  }
}
//--------------------------------------------------------------------------------------
//������� ���������� � ������� ��� ������� �����
long long int mul(int& x, int& k, int& n){
  long long int res = 1;
  for (int i = 0; i < k; i++){
    res = res * x % n;
  }
  return res;
}
//--------------------------------------------------------------------------------------
//������� ����������
void encrypt(string& out, const string& input, int& e, int& n){
  for (int i = 0; i < input.size(); i++){
    for (int j = 0; j < sizeof(ALPHABET); j++){
      if (ALPHABET[j] == input[i]){
        //������� ����������
        int res = mul(j, e, n);
        out += to_string(res);
        out += " ";
      }
    }
  }
}
//--------------------------------------------------------------------------------------
//������� �����������
void decrypt(string& out1, const string& input, int& d, int& n){
  stringstream text(input);
  string letter;
  while (text >> letter){
    int code = stoi(letter);
    //������� �����������
    int r = mul(code, d, n); 
    out1 += ALPHABET[r];
  }
}
