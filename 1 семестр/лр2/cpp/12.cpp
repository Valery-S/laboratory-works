#include <iostream>
using namespace std;
int main()
{
	int a;
	setlocale(LC_ALL, "Russian");
	cout << "¬ведите число  ";
	cin >> a;
	if (a % 10 == a / 10)
	{
		cout << "цифры одинаковы ";
	}
	else {
		cout << "цифры не одинаковы ";
	}

	return 0;
}