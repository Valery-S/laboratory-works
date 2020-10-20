#include <iostream>
using namespace std;
int main()
{
	int c, m,s;
	setlocale(LC_ALL, "Russian");
	cout << "Введите  часы, минуты и секунды  ";
	cin >> c >> m>>s;
	cout << (c - 1) * 60 + m << " минут или " << ((c - 1) * 60 + m) * 60 + s << " cсекунд прошло с начала суток "<<endl;
	if (m>15)
	{
		cout << m - 15 << " минут прошло с начала четверти часа ";
	}
	else {
		cout << m + 45 << " минут прошло с начала четверти часа ";
	}
	return 0;
}