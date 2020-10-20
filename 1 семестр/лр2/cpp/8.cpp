#include <iostream>
using namespace std;
int main()
{
	int u,u1;
	setlocale(LC_ALL, "Russian");
	cout << "¬ведите первую скорость в км/ч  ";
	cin >> u;
	cout << "¬ведите вторую скорость в м/с  ";
	cin >> u1;
	if (u*1000/36000>u1)
	{
		cout << "ѕерва€ скорость больше ";
	}
	else {
		cout << "¬тора€ скорость больше ";
	}

	return 0;
}