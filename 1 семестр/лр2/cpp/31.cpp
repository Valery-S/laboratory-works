#include <iostream>
using namespace std;
int main()
{
	float x, y;
	setlocale(LC_ALL, "Russian");
	cout << "������� 2 ����� ";
	cin >> x >> y ;
	if (x > y)
	{
		float a;
		a = y;
		y = (y + x) / 2;
		x = 2 * x * a;
	}
	else {
		float a;
		a = x;
		x = (y + x) / 2;
		y = 2 * y * a;
	}
	cout << x << "  " << y;
	return 0;
}