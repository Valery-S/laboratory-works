#include <iostream>
using namespace std;
int main()
{
	int A;
	setlocale(LC_ALL, "Russian");
	cout << "Введите число  ";
	cin >> A;
	if (A % 2 == 0) {
		cout << "цисло оканчивается четной цифрой" << endl;
	}
	else {
		cout << "цисло не оканчивается четной цифрой" << endl;
	}

	return 0;
}