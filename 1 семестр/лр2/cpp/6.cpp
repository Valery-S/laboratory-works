#include <iostream>
using namespace std;
int main()
{
	int g,m,g1,m1;
	setlocale(LC_ALL, "Russian");
	cout << "������� ��� � ����� �������� ��������  ";
	cin >> g>>m;
	cout << "������� ����������� ��� � �����  ";
	cin >> g1 >> m1;
	cout<< "������� �������� : "<<(g1*12+m1-g*12-m)/12;

	return 0;
}