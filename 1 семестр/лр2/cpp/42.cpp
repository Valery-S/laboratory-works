#include <iostream>
using namespace std;
int main()
{
	int a, b, c;
	setlocale(LC_ALL, "Russian");
	cout << "�������  ���� � �����  � ��� ";
	cin >> a >> b >> c;
	cout << "C 1 ������ 1970 ���� ������ " << ((c - 1) * 365 + (b - 1) * 30 + a) - (1969 * 365) << " ����";
	return 0;
}