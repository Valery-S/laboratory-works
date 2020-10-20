#include <iostream>
using namespace std;
int main()
{
	float a;
	setlocale(LC_ALL, "Russian");
	cout << "Введите число  ";
	cin >> a;
	int b = (int)a;
	if (b % 3 == 0)
	{
		cout << "целая часть числа кратна 3 ";
	}
	else {
		cout << "целая часть числа не кратна 3 ";
	}

	return 0;
}