#include <iostream>
using namespace std;
int main()
{
	int a,b,c;
	setlocale(LC_ALL, "Russian");
	cout << "Введите число  ";
	cin >> a;
	b = a % 10;
	c = a / 10;
	if (a *a==4*(b*b*b+c*c*c))
	{
		cout << " квадрат этого числа равен учетверенной сумме кубов его цифр. ";
	}
	else {
		cout << " квадрат этого числа не равен учетверенной сумме кубов его цифр. ";
	}

	return 0;
}