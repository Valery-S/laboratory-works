#include <iostream>
using namespace std;
int main()
{
	float a,b,c;
	setlocale(LC_ALL, "Russian");
	cout << "������� ����a  ";
	cin >> a>>b>>c;
	if (a>=0)
	{
		a = a * a ;
	}
	else {
		a = a * a * a * a;
	}
	if (b>=0)
	{
		b = b * b ;
	}
	else {
		b = b * b * b * b;
	}
	if (c >= 0)
	{
		c = c * c;
	}
	else {
		c = c * c * c * c;
	}
	cout << a<<" " << b << " " << c;
	return 0;
}