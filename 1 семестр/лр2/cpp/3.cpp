#include <iostream>
using namespace std;
int main()
{
	int A;
	setlocale(LC_ALL, "Russian");
	cout << "������� �����  ";
	cin >> A;
	if (A%2 == 0) {
		cout << "����� ������"<<endl ;
	}
	else {
		cout << "����� �� ������" << endl;
	}
	if (A % 10 == 4) {
		cout << "����� ������������ ������ 4" << endl;
	}
	else {
		cout << "����� �� ������������ ������ 4" << endl;
	}
	return 0;
}