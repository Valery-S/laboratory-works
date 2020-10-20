#include <iostream>
using namespace std;
int main()
{
	int a;
	setlocale(LC_ALL, "Russian");
	cout << "Введите число  ";
	cin >> a;
	if (a % 2 == 1)
	{
		cout << "Число заканчивается нечетной цифрой ";
	}
	else {
		cout << "Число заканчивается четной цифрой ";
	}

	return 0;
}
