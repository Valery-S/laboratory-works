#include <iostream>
using namespace std;
int main()
{
	float a;
	setlocale(LC_ALL, "Russian");
	cout << "Введите число  ";
	cin >> a;
	int b = (int)a;
	if (b % 2 == 0)
	{
		cout << "целая часть числа заканчивается четной цифрой ";
	}
	else {
		cout << "целая часть числа заканчивается нечетной цифрой";
	}

	return 0;
}