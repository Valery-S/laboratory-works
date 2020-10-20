#include <iostream>
using namespace std;
int main()
{
	int g,m,g1,m1;
	setlocale(LC_ALL, "Russian");
	cout << "¬ведите год и мес€ц рождени€ человека  ";
	cin >> g>>m;
	cout << "¬ведите сегодн€шний год и мес€ц  ";
	cin >> g1 >> m1;
	cout<< "¬озраст человека : "<<(g1*12+m1-g*12-m)/12;

	return 0;
}