#define Pi 3.14159265358979323846
#include <iostream>
using namespace std;
int main()
{
	int s, s1,a,r;
	setlocale(LC_ALL, "Russian");
	cout << "������� ������� �����  ";
	cin >> s;
	a = sqrt(s);
	cout << "������� ������� �������� ";
	cin >> s1;
	r = sqrt(s1 / Pi);
	if (a>=2*r)
	{
		cout << "���� ���������� � �������� ";
	}
	else {
		cout << "���� �� ���������� � �������� ";
	}

	return 0;
}