#include <iostream>
using namespace std;
int main()
{
	int r,r1;
	setlocale(LC_ALL, "Russian");
	cout << "������� ������ ���������� � ��  "<<endl;
	cin >> r;
	cout << "������� ������ ���������� � ��  " << endl;
	cin >> r1;
	if (r > r1 * 0.00045) {
		cout << "������ ���������� ������ " << endl;
	}
	else {
		cout << "������  ���������� ������ " << endl;
	}

	return 0;
}