#include <iostream>
using namespace std;
int main()
{
	int u,u1;
	setlocale(LC_ALL, "Russian");
	cout << "������� ������ �������� � ��/�  ";
	cin >> u;
	cout << "������� ������ �������� � �/�  ";
	cin >> u1;
	if (u*1000/36000>u1)
	{
		cout << "������ �������� ������ ";
	}
	else {
		cout << "������ �������� ������ ";
	}

	return 0;
}