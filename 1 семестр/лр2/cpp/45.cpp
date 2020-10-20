#include <iostream>
using namespace std;
int main()
{
	int v;
	setlocale(LC_ALL, "Russian");
	cout << "Введите  возраст человека  ";
	cin >> v;
	if (v<7)
	{
		cout << "человек  дошкольник";
	}
	if (v <= 18 && v>=7)
	{
		cout << "человек  школьник";
	}
	if (v >18 && v <65)
	{
		cout << "человек работник";
	}
	if (v >= 65)
	{
		cout << "человек пенсеонер";
	}
	return 0;
}