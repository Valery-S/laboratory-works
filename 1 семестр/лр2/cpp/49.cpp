#include <iostream>
using namespace std;
int main()
{
	float  a, b, c,d;
	bool f1,f2,f3,f4;
	setlocale(LC_ALL, "Russian");
	cout << "Введите длины 4 отрезков   ";
	cin >> a >> b >> c>>d;
	f1 = a < b + c && b < a + c && c < a + b;
	f2 = a < b + d && b < a + d && d < a + b;
	f3 = a < d + c && d < a + c && c < a + d;
	f4 = d < b + c && b < d + c && c < b + d;
	if (f1==true)
	{
		cout << "Можно посторить треугольник со сторонами  " << a << "   " << b << "   " << c;
	}
	if (f2 == true)
	{
		cout << "Можно посторить треугольник со сторонами  " << a << "   " << b << "   " << d;
	}
	if (f3 == true)
	{
		cout << "Можно посторить треугольник со сторонами  " << a << "   " << d << "   " << c;
	}
	if (f4 == true)
	{
		cout << "Можно посторить треугольник со сторонами  " << b << "   " << d << "   " << c;
	}
	if ((f1||f2||f3||f4)==false)
	{
		cout << " треугольник построить нельзя " ;
	}
	return 0;
}