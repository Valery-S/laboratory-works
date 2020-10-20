#include <iostream>
using namespace std;
int main()
{
	int a, b, c, d, e;
	setlocale(LC_ALL, "Russian");
	cout << "Введите число  ";
	cin >> a;
	b = a % 10;
	c = (a / 10) % 10;
	d = (a / 100) % 10;
	e = a / 1000;
	if ((e&d*c*b)%4==0)
	{
		cout << "Произведение цифр кратно 4 ";
	}
	else {
		cout << "Произведение цифр не кратно 4 ";
	}

	return 0;
}