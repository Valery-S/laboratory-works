#include <iostream>
using namespace std;
int main()
{
	int a;
	setlocale(LC_ALL, "Russian");
	cout << "Введите число  ";
	cin >> a;
	if (a % 2 == 0)
	{
		cout << "Число заканчивается четной цифрой ";
	}
	else {
		cout << "Число заканчивается нечетной цифрой ";
	}

	return 0;
}