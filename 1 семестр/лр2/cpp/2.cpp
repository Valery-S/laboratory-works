#include <iostream>
using namespace std;
int main()
{
	int A, B;
	setlocale(LC_ALL, "Russian");
	cout << "Введите числа B и A ";
	cin >> B >> A;
	if (B % A == 0) {
		cout << "B  делится на A без остатка"; ;
	}
	else {
		cout << "B не делится на A без остатка";
	}
	return 0;
}