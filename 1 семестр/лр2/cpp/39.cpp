#include <iostream>
using namespace std;
int main()
{
	int a, b, c, k = 0;
	setlocale(LC_ALL, "Russian");
	cout << "������� 3 ����� ";
	cin >> a >> b >> c;
	if (a % 2 != 0)
	{
		k++;
	}
	if (b % 2 != 0)
	{
		k++;
	}
	if (c % 2 != 0)
	{
		k++;
	}
	if (k == 2)
	{
		cout << "C���� ����� ���� ����� 2 �������� �����";
	}
	else {
		cout << "C���� ����� ��� ����� 2-� �������� �����";
	}
	return 0;
}