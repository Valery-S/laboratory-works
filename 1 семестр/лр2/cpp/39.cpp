#include <iostream>
using namespace std;
int main()
{
	int a, b, c, k = 0;
	setlocale(LC_ALL, "Russian");
	cout << "¬ведите 3 числа ";
	cin >> a >> b >> c;
	if (a % 2 != 0)
	{
		k++;
	}
	if (b % 2 != 0)
	{
		k++;
	}
	if (c % 2 != 0)
	{
		k++;
	}
	if (k == 2)
	{
		cout << "Cреди чисел есть ровно 2 нечетных числа";
	}
	else {
		cout << "Cреди чисел нет ровно 2-х нечетных чисел";
	}
	return 0;
}