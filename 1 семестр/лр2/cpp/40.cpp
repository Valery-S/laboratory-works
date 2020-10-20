#include <iostream>
using namespace std;
int main()
{
	int a, b, c;
	setlocale(LC_ALL, "Russian");
	cout << "Введите 2 числа ";
	cin >> a >> b ;
	if (a<b)
	{
		c = a;
		a = b;
		b = c;
	} 
	cout << "Большее число  "<<a<< "  меньшеее число "<<b;
	return 0;
}