#include <iostream>
using namespace std;
int main()
{
	int m,n,a,b,c;
	setlocale(LC_ALL, "Russian");
	cout << "�������   ������������ a,b,c ��������� ax^2+bx+c=y  ";
	cin >> a>>b>>c;
	cout << "�������  ���������� �����  ";
	cin >> m >> n;
	if (a*m*m+b*m+c==n)
	{
		cout << "������ "<<a<<"x^2"<<"+" <<b<<"x"<<"+"<<c<<" �������� ����� ����� "<<"("<<m<<";"<<n<<")";
	}
	
	return 0;
}