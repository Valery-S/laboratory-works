#include <iostream>
using namespace std;
int main()
{
	int A, B;
	setlocale(LC_ALL, "Russian");
	cout << "������� ����� B � A ";
	cin >> B >> A;
	if (B % A == 0) {
		cout << "B  ������� �� A ��� �������"; ;
	}
	else {
		cout << "B �� ������� �� A ��� �������";
	}
	return 0;
}