#include <iostream>
using namespace std;
int main()
{
	int a, b, c, d,e;
	setlocale(LC_ALL, "Russian");
	cout << "������� �����  ";
	cin >> a;
	b = a % 10;
	c = (a / 10) % 10;
	d = (a / 100)%10;
	e = a / 1000;
	if (e+d==c+b)
	{
		cout << "c���� ���� ������  ���� ����� ����� ����  ��������� ���� ";
	}
	else {
		cout << "c���� ���� ������  ���� �� ����� ����� ����  ��������� ���� ";
	}

	return 0;
}