#include <iostream>
using namespace std;
int main()
{
	int a, b, c, k = 0, a1, b1, c1;
	setlocale(LC_ALL, "Russian");
	cout << "������� 3 ����� ";
	cin >> a >> b >> c;
	a1 = abs(a % 2);
	b1 = abs(b % 2);
	c1 = abs(c % 2);
	k = a1+b1+c1;
	cout << "�������� ����� " << k;
	return 0;
}