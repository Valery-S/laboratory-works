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
	if ((b + c )%3==0)
	{
		cout << "сумма цифр кратна 3 ";
	}
	else {
		cout << "сумма цифр не кратна 3  ";
	}

	return 0;
}