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
	if (b==c==d)
	{
		cout << "����� ����������";
	}
	else {
		cout << "����� �� ����������";
	}

	return 0;
}