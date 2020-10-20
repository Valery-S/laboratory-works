#include <iostream>
using namespace std;
int main()
{
	float x, y;
	setlocale(LC_ALL, "Russian");
	cout << "Введите координаты точки ";
	cin >> x >> y;
	if (x>0&&y>0)
	{
		cout << "Точка А в 1 квадранте ";
	}
	if (x == 0 )
	{
		cout << "Точка А на оси х ";
	}
	if (y == 0)
	{
		cout << "Точка А на оси y ";
	}
	if (x < 0 && y > 0)
	{
		cout << "Точка А вo 2 квадранте ";
	}
	if (x < 0 && y < 0)
	{
		cout << "Точка А в 3 квадранте ";
	}
	if (x > 0 && y < 0)
	{
		cout << "Точка А в 4 квадранте ";
	}
	return 0;
}