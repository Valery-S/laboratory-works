#include <iostream>
using namespace std;
int main()
{
	int A;
	setlocale(LC_ALL, "Russian");
	cout << "������� �����  ";
	cin >> A;
	if (A % 2 == 0) {
		cout << "����� ������" << endl;
	}
	else {
		cout << "����� �� ������" << endl;
	}
	if (A % 10 == 7) {
		cout << "����� ������������ ������ 7" << endl;
	}
	else {
		cout << "����� �� ������������ ������ 7" << endl;
	}
	return 0;
}