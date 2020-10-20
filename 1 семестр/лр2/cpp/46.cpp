#include <iostream>
using namespace std;
int main()
{
	int m,n,a,b,c;
	setlocale(LC_ALL, "Russian");
	cout << "¬ведите   коэффициенты a,b,c уравнени€ ax^2+bx+c=y  ";
	cin >> a>>b>>c;
	cout << "¬ведите  координаты точки  ";
	cin >> m >> n;
	if (a*m*m+b*m+c==n)
	{
		cout << "график "<<a<<"x^2"<<"+" <<b<<"x"<<"+"<<c<<" проходит через точку "<<"("<<m<<";"<<n<<")";
	}
	
	return 0;
}