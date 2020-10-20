#include <iostream>
using namespace std;
int main()
{
	int a, b, c;
	setlocale(LC_ALL, "Russian");
	cout << "Введите число  ";
	cin >> a;
	b = a % 10;
	c = a / 10;
	if (b+c>=10)
	{
		cout << "сумма цифр является двузначным числом ";
	}
	else {
		cout << "сумма цифр не является двузначным числом ";
	}

	return 0;
}