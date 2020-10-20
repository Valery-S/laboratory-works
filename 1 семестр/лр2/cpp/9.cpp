#define Pi 3.14159265358979323846
#include <iostream>
using namespace std;
int main()
{
	int r, a;
	setlocale(LC_ALL, "Russian");
	cout << "¬ведите радиус круга  ";
	cin >> r;
	cout << "¬ведите сторону квадрата ";
	cin >>a;
	if (Pi*r*r / a*a)
	{
		cout << "ѕлощадь круга больше ";
	}
	else {
		cout << "ѕлощадь квадрата больше ";
	}

	return 0;
}