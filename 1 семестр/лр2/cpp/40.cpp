#include <iostream>
using namespace std;
int main()
{
	int a, b, c;
	setlocale(LC_ALL, "Russian");
	cout << "������� 2 ����� ";
	cin >> a >> b ;
	if (a<b)
	{
		c = a;
		a = b;
		b = c;
	} 
	cout << "������� �����  "<<a<< "  �������� ����� "<<b;
	return 0;
}