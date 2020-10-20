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
	if ((b*b*b+c*c*c+d*d*d) == a*a)
	{
		cout << "квадрат этого числа равен сумме кубов его цифр. ";
	}
	else {
		cout << "квадрат этого числа не равен сумме кубов его цифр.  ";
	}

	return 0;
}