#include <iostream>
using namespace std;
int main()
{
	float a;
	setlocale(LC_ALL, "Russian");
	cout << "������� �����  ";
	cin >> a;
	int b = (int)a;
	if (b % 3 == 0)
	{
		cout << "����� ����� ����� ������ 3 ";
	}
	else {
		cout << "����� ����� ����� �� ������ 3 ";
	}

	return 0;
}