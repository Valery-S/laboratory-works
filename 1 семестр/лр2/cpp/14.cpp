#include <iostream>
using namespace std;
int main()
{
	int a, b, c;
	setlocale(LC_ALL, "Russian");
	cout << "������� �����  ";
	cin >> a;
	b = a % 10;
	c = a / 10;
	if (b+c>=10)
	{
		cout << "����� ���� �������� ���������� ������ ";
	}
	else {
		cout << "����� ���� �� �������� ���������� ������ ";
	}

	return 0;
}