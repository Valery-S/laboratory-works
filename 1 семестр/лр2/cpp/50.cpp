#include <iostream>
using namespace std;
int main()
{
	float  x1,x2,x3,y1,y2,y3,p,s,a,b,c,alpha;
	setlocale(LC_ALL, "Russian");
	cout << "������� ���������� 3 �����   ";
	cin >> x1 >> y1 >> x2 >> y2>>x3>>y3;
	a = sqrt((x1 - x2) * (x1 - x2) + (y1 - y2)* (y1 - y2));/*c������ a*/
	b = sqrt((x2 - x3) * (x2 - x3) + (y2 - y3)* (y2 - y3));/*c������ c*/
	c = sqrt((x1 - x3) * (x1 - x3) + (y1 - y3)* (y1 - y3));/*c������ b*/
	p = (a + b + c) / 2;/*������������ ������������ abc*/
	s = sqrt(p * (p - a) * (p - b) * (p - c));/*������� ������������ �� ������� ������*/
	if (s==0)
	{
		cout<< "����� ����� �� ����� ������   ";
	}
	else {
		
		alpha = acos((b * b + a * a - c * c) / (2 * b * c));
		cout << "���� b =  "<<alpha;
	}
	return 0;
}