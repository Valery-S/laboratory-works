#include <iostream>
using namespace std;
int main()
{
	int a, b;
	setlocale(LC_ALL, "Russian");
	cout << "�������  ���� � �����  ";
	cin >> a >> b;
	cout << "������  " << (b/3) + 1<< " �������"<< " �� ��� ������ ������ "<< ((b-1)*30+a)-(b/3)*3*30<<" ����";
	return 0;
}