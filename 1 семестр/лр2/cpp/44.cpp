#include <iostream>
using namespace std;
int main()
{
	int c, m,s;
	setlocale(LC_ALL, "Russian");
	cout << "�������  ����, ������ � �������  ";
	cin >> c >> m>>s;
	cout << (c - 1) * 60 + m << " ����� ��� " << ((c - 1) * 60 + m) * 60 + s << " c������ ������ � ������ ����� "<<endl;
	if (m>15)
	{
		cout << m - 15 << " ����� ������ � ������ �������� ���� ";
	}
	else {
		cout << m + 45 << " ����� ������ � ������ �������� ���� ";
	}
	return 0;
}