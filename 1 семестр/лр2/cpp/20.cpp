#include <iostream>
using namespace std;
int main()
{
	int a, b, c, d;
	setlocale(LC_ALL, "Russian");
	cout << "������� �����  ";
	cin >> a;
	b = a % 10;
	c = (a / 10) % 10;
	d = a / 100;
	if ((d+b+c)%5==0)
	{
		cout << "����� ���� ������ 5";
	}
	else {
		cout << "����� ���� �� ������ 5";
	}

	return 0;
}