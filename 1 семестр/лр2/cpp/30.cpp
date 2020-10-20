#include <iostream>
using namespace std;
int main()
{
	float x1, y1, x2, y2,r2,r1;
	setlocale(LC_ALL, "Russian");
	cout << "Введите координаты первой и второй  точек ";
	cin>> x1>> y1 >> x2 >> y2;
	r1 =sqrt( x1 * x1 + y1 * y1);
	r2 = sqrt(x2 * x2 + y2 * y2);
	if (r2>r1)
	{
		cout << "первая точка расположена ближе к началу координат";
	}
	else {
		cout << "вторая точка расположена ближе к началу координат";
	}
	return 0;
}