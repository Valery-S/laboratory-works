#include <iostream>
using namespace std;
int main()
{
	int a,b,c;
	setlocale(LC_ALL, "Russian");
	cout << "������� �����  ";
	cin >> a;
	b = a % 10;
	c = a / 10;
	if (a *a==4*(b*b*b+c*c*c))
	{
		cout << " ������� ����� ����� ����� ������������ ����� ����� ��� ����. ";
	}
	else {
		cout << " ������� ����� ����� �� ����� ������������ ����� ����� ��� ����. ";
	}

	return 0;
}