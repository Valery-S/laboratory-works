#include <iostream>
using namespace std;
int main()
{
	int A;
	setlocale(LC_ALL, "Russian");
	cout << "������� �����  ";
	cin >> A;
	if (A % 2 == 0) {
		cout << "����� ������������ ������ ������" << endl;
	}
	else {
		cout << "����� �� ������������ ������ ������" << endl;
	}

	return 0;
}