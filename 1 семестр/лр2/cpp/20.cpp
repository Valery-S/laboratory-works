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
	if ((d+b+c)%5==0)
	{
		cout << "сумма цифр кратна 5";
	}
	else {
		cout << "сумма цифр не кратна 5";
	}

	return 0;
}