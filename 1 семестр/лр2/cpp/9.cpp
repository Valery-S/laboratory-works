#define Pi 3.14159265358979323846
#include <iostream>
using namespace std;
int main()
{
	int r, a;
	setlocale(LC_ALL, "Russian");
	cout << "������� ������ �����  ";
	cin >> r;
	cout << "������� ������� �������� ";
	cin >>a;
	if (Pi*r*r / a*a)
	{
		cout << "������� ����� ������ ";
	}
	else {
		cout << "������� �������� ������ ";
	}

	return 0;
}