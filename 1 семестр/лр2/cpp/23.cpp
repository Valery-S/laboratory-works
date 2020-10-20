#include <iostream>
using namespace std;
int main()
{
	int a, b, c, d,e;
	setlocale(LC_ALL, "Russian");
	cout << "¬ведите число  ";
	cin >> a;
	b = a % 10;
	c = (a / 10) % 10;
	d = (a / 100)%10;
	e = a / 1000;
	if (e+d==c+b)
	{
		cout << "cумма двух первых  цифр равна сумме двух  последних цифр ";
	}
	else {
		cout << "cумма двух первых  цифр не равна сумме двух  последних цифр ";
	}

	return 0;
}