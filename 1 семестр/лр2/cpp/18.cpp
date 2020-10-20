#include <iostream>
using namespace std;
int main()
{
	int a, b, c, d;
	setlocale(LC_ALL, "Russian");
	cout << "Введите число  ";
	cin >> a;
	b = a % 10;
	c = (a / 10) / 10;
	d = a / 100;
	if ((b+c+d)>=10)
	{
		cout << "cумма цифр является двузначным числом ";
	}
	else {
		cout << "cумма цифр не является двузначным числом ";
	}

	return 0;
}