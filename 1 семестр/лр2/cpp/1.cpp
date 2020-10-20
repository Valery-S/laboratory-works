#include <iostream>
using namespace std;
int main()
{	int M,N;
setlocale(LC_ALL, "Russian");
cout << "Введите числа М и N ";
cin >> M >> N;
if (M % N == 0) {
	cout << M / N;
}
else {
	cout << "M не делится на N без остатка";
}
	return 0;
}