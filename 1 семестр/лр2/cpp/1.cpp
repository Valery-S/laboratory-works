#include <iostream>
using namespace std;
int main()
{	int M,N;
setlocale(LC_ALL, "Russian");
cout << "������� ����� � � N ";
cin >> M >> N;
if (M % N == 0) {
	cout << M / N;
}
else {
	cout << "M �� ������� �� N ��� �������";
}
	return 0;
}