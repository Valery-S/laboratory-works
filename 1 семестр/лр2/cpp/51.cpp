#include <iostream>
using namespace std;
int main()
{
	int n;
	long s = 0;
	setlocale(LC_ALL, "Russian");
	cout << "¬ведите n   ";
	cin >> n;
	for (int i = n; i <= (2*n); i++)
	{
		s = s + i*i;
	}
	cout << "—умма равна  "<<s;
	return 0;
}