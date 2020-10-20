#include <iostream>
using namespace std;
int main()
{
	int a, b, c, d;
	setlocale(LC_ALL, "Russian");
	cout << "Введите число  ";
	cin >> a;
	b = a % 10;
	c = (a / 10) % 10;
	d = a / 100;
	if ((a*b*c)>=100)
	{
		cout << "произведение цифр является трехзначным числом числом ";
	}
	else {
		cout << "произведение цифр не является трехзначным числом числом";
	}

	return 0;
}