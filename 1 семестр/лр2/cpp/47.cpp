#include <iostream>
using namespace std;
int main()
{
	int e, d, a, b, c;
	setlocale(LC_ALL, "Russian");
	cout << "������� ����� �������   ";
	cin >> a >> b >> c;
	cout << "�������  ����� �������  ";
	cin >> d >> e;
	if ((a <= d && b <= e) || (a <= e && b <= d) || (a <= d && c <= e) || (a <= e && c <= d) || (b <= d && c <= e) || (b <= e && c <= d))
	{
		cout << "������ � �������  " << a << " " << b << "  " << c << " ����� ����������� ����� ��������� �������� " << d << " " << e;
	}
	else {
		cout << "������ � �������  " << a << " " << b << "  " << c << " ������ ����������� ����� ��������� �������� " << d << " " << e;
	}

	return 0;
}