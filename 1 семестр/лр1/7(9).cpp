/* figure: task7 */
/*****************************************************************/
/* Filename: task7.cpp */
/* Abstract: ��� ������� �++ ��������� */
/* Description: ������� ������� �����  */
/* Create Date: 2019 / 09 / 22 */
/* Author:��������� ������� ���������� */
/*****************************************************************/
char logo[] = "*********************************************************\n"

"* Nizhniy Novgorod Technical University *\n"

"* Study work number 1. Task number 7. *\n"

"* Performed student 19-IVT-3 Sukhorukov V.A. *\n"

"*********************************************************\n";
#include <iostream>/* ����������� ���������� �����/������*/
#define Pi 3.14159265358979323846/* ������������ �������� ����� ��*/
using namespace std;/* ������������� ������������ ���� std*/
int main()/*������ ��������� ���������� � ������ ������� main() */
{	/* BEGIN: ������ ���� ������� ������� ������ */
	cout << logo;
	cout << "write the value of the circle radius ";/*����� ��������� �� ����� */
	float s, r;/*���������� ���������� ���� � ��������� ������ */
	cin >> r;/*���������� ������� */
	s = r * r * Pi;/*������� ������� */
	cout << "area =  " << s; /*������� ��������� �� ����� */
	return 0;/* ������� ���������� �� � ������ �������� ������ */
}/* END: ����� ���� ������� ������� ������ */