#include <iostream>
using namespace std;
int main()
{
	float a;
	setlocale(LC_ALL, "Russian");
	cout << "������� �����  ";
	cin >> a;
	int b = (int)a;
	if (b % 2 == 0)
	{
		cout << "����� ����� ����� ������������� ������ ������ ";
	}
	else {
		cout << "����� ����� ����� ������������� �������� ������";
	}

	return 0;
}