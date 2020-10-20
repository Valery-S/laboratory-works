#include <iostream>
using namespace std;
int main()
{
	int m, n;
	setlocale(LC_ALL, "Russian");
	cout << "¬ведите 2 числа ";
	cin >> m >> n;
	if ( m==n)
	{
		m = 0;
		n = 0;
		
	}
	else {
		m = m + n;
		n = m;
	}
	cout << m<<" " << n;
	return 0;
}