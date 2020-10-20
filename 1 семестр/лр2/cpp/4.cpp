#include <iostream>
using namespace std;
int main()
{
	int A;
	setlocale(LC_ALL, "Russian");
	cout << "Введите число  ";
	cin >> A;
	if (A % 2 == 0) {
		cout << "цисло четное" << endl;
	}
	else {
		cout << "цисло не четное" << endl;
	}
	if (A % 10 == 7) {
		cout << "цисло оканчивается цифрой 7" << endl;
	}
	else {
		cout << "цисло не оканчивается цифрой 7" << endl;
	}
	return 0;
}