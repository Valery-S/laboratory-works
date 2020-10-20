#include <iostream>
using namespace std;
int main()
{
	int r,r1;
	setlocale(LC_ALL, "Russian");
	cout << "Введите первое расстояние в км  "<<endl;
	cin >> r;
	cout << "Введите второе расстояние в фт  " << endl;
	cin >> r1;
	if (r > r1 * 0.00045) {
		cout << "Первое расстояние больше " << endl;
	}
	else {
		cout << "Второе  расстояние больше " << endl;
	}

	return 0;
}