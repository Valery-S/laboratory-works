#include <iostream>
using namespace std;
int main()
{
	float  x1,x2,x3,y1,y2,y3,p,s,a,b,c,alpha;
	setlocale(LC_ALL, "Russian");
	cout << "Введите координаты 3 точек   ";
	cin >> x1 >> y1 >> x2 >> y2>>x3>>y3;
	a = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2)* (y1 - y2));/*cторона a*/
	b = sqrt((x2 - x3) * (x2 - x3) + (y2 - y3)* (y2 - y3));/*cторона c*/
	c = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3)* (y1 - y3));/*cторона b*/
	p = (a + b + c) / 2;/*полупериметр треугольника abc*/
	s = sqrt(p * (p - a) * (p - b) * (p - c));/*площадь треугольника по формуле Герона*/
	if (s==0)
	{
		cout<< "точки лежат на одной прямой   ";
	}
	else {
		
		alpha = acos((b * b + a * a - c * c) / (2 * b * c));
		cout << "угол b =  "<<alpha;
	}
	return 0;
}