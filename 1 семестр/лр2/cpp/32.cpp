#include <iostream>
using namespace std;
int main()
{
	float x, y;
	setlocale(LC_ALL, "Russian");
	cout << "������� ���������� ����� ";
	cin >> x >> y;
	if (x>0&&y>0)
	{
		cout << "����� � � 1 ��������� ";
	}
	if (x == 0 )
	{
		cout << "����� � �� ��� � ";
	}
	if (y == 0)
	{
		cout << "����� � �� ��� y ";
	}
	if (x < 0 && y > 0)
	{
		cout << "����� � �o 2 ��������� ";
	}
	if (x < 0 && y < 0)
	{
		cout << "����� � � 3 ��������� ";
	}
	if (x > 0 && y < 0)
	{
		cout << "����� � � 4 ��������� ";
	}
	return 0;
}