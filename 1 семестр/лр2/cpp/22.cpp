#include <iostream>
using namespace std;
int main()
{
	int a, b, c, d;
	setlocale(LC_ALL, "Russian");
	cout << "¬ведите число  ";
	cin >> a;
	b = a % 10;
	c = (a / 10) % 10;
	d = a / 100;
	if (b == c ||b==d||d==c)
	{
		cout << "есть одинаковые цифры ";
	}
	else {
		cout << "нет одинковых цифр";
	}

	return 0;
}