#include <iostream>
using namespace std;
int main()
{
	int a;
	setlocale(LC_ALL, "Russian");
	cout << "������� �����  ";
	cin >> a;
	if (a % 2 == 0)
	{
		cout << "����� ������������� ������ ������ ";
	}
	else {
		cout << "����� ������������� �������� ������ ";
	}

	return 0;
}