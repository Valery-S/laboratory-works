#include <iostream>
using namespace std;
int main()
{
	int a, b, c, d;
	setlocale(LC_ALL, "Russian");
	cout << "¬ведите число  ";
	cin >> a;
	b = a % 10;
	c = (a / 10) % 10;
	d = a / 100;
	if (b==c==d)
	{
		cout << "цифры одинаковые";
	}
	else {
		cout << "цифры не одинаковые";
	}

	return 0;
}