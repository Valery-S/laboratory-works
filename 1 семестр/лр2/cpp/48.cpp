#include <iostream>
using namespace std;
int main()
{
	float  a, b, c;
	setlocale(LC_ALL, "Russian");
	cout << "������� 3 �����   ";
	cin >> a >> b >> c;
	
	if (c-b==b-a)
	{
		cout << "����� �������� �������������� �������������������  ";
	}
	else {
		if (c / b == b / a)
		{
			cout << "����� �������� �������������� �������������������  ";
		}else{
			cout << "����� �� ��������  �������������������  ";
		}
	}

	return 0;
}