#include <iostream>
using namespace std;
int main()
{
	float a, b, c;
	int k = 0;
	setlocale(LC_ALL, "Russian");
	cout << "������� 3 ����� ";
	cin >> a >> b >> c;
	if (a > 0)
	{
		k++;

	}
	if (b > 0)
	{
		k++;

	}
	if (c > 0)
	{
		k++;

	}

	cout << "����� ��������� ������������� �����: " << k;
	return 0;
}