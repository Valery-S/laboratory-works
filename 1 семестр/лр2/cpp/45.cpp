#include <iostream>
using namespace std;
int main()
{
	int v;
	setlocale(LC_ALL, "Russian");
	cout << "�������  ������� ��������  ";
	cin >> v;
	if (v<7)
	{
		cout << "�������  ����������";
	}
	if (v <= 18 && v>=7)
	{
		cout << "�������  ��������";
	}
	if (v >18 && v <65)
	{
		cout << "������� ��������";
	}
	if (v >= 65)
	{
		cout << "������� ���������";
	}
	return 0;
}