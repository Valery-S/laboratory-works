#include <iostream>
using namespace std;
int main()
{
	int a;
	setlocale(LC_ALL, "Russian");
	cout << "Введите число  ";
	cin >> a;
	if (a%10>a/10)
	{
		cout << "Вторая цифра больше ";
	}
	else {
		cout << "Первая цифра больше ";
	}

	return 0;
}