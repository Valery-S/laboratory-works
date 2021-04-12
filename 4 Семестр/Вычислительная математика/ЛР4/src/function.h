#pragma once
#include<iostream>
#include<vector>
#include<cmath>
#include"colors.h"

using namespace std;
/*���������� ��� ������ � �������� �������� � � ������������ */


/*������� ���������� �������� ��������������*/
void get_limits(double* lower_limit, double* upper_limit) {
	cout << Green << "������� ������� �������������� \n"
		<< Yellow << "\t������ ������ ";
	cin >> *lower_limit;
	cout << "\t������� ������ ";
	cin >> *upper_limit;
}

/*������� ���������� n*/
int get_n() {
	int n;
	cout << Green << "������� n - ����� �������� ��������� ";
	cin >> n;
	return n;
}

/*������� ������ ����*/
char menu_item_selection() {
	char c;
	cout << Green << "\n��������, ��� ����� ������� :\n" << Yellow
		<< "\t{1} - ����� �������� ������� ����������� ���������������\n"
		<< "\t{2} - ����� �������� ������� ��������\n"
		<< "\t{3} - ����� �������� �� ������� ��������\n"
		<< "\t{n} - ������� n\n"
		<< "\t{q} - ��������� ���������\n";
	cin >> c;
	return c;
}

/*������� ���������� �������� � �� ������ �������
 *���������:
 *	1)lower_limit-������ ������
 *	2)upper_limit-������� ������
 *	3)n-����� ��������
 */
vector <double> get_x(double lower_limit, double upper_limit, int n) {
	vector <double> x(n + 1);

	double h = (upper_limit - lower_limit) / n;  //���
	x[0] = lower_limit;

	for (int i = 1; i < (n + 1); i++) {
		x[i] = x[i - 1] + h;
	}

	return x;
}

/*������� ���������� �������� ������� � �������� �����*/
double f_x(double x) {
	double y = (log10(x * x + 0.8)) / (x - 1);
	return y;
}

/*������� ���������� � �� ������ �������
 *���������:
 *	1)x - ������ �������� �
 */
vector <double> get_y(vector<double>x) {
	vector <double> y(x.size());

	for (int i = 0; i < (x.size()); i++) {
		y[i] = f_x(x[i]);
	}

	return y;
}

/*������� ���������� �������� ������ ����������� � �������� �����
*                     2*x        (2x^2/(x^2+0.8)-1)      lg(x^2+0.8)
*           -  --------------  - -------------------   + ------------
*              (x-1)*(x^2+0.8)        x^2+0.8              (x-1)^2
*f''(x)=2 * ----------------------------------------------------------
*																		(x-1)
*/
double second_derivative(double x) {
	double temp1, temp2, temp3, res;
	
	temp1 = -2*x / (x - 1) * (x * x + 0.8);
	temp2 = -((2 * x * x) / (x * x + 0.8) - 1) / (x * x + 0.8);
	temp3 = log10(x * x + 0.8) / ((x - 1) * (x - 1));

	res = 2 * (temp1 + temp2 + temp3) / (x - 1);

	return res;
}

/*������� ���������� �������� ������� ����������� � �������� �����
* 
* 
*               3(2*x^2/(x^2+0.8)-1)         6x               2x(4x/(x^2+0.8)-3)         3lg(x^2+0.8)
*			     		 ------------------ +  ------------------  +	--------------------   -  ----------------   
*                (x-1)*(x^2+0.8)     (x-1)^2*(x^2+0.8)         (x^2+0.8)^2                (x-1)^3 
* f'''(x)=2 * ------------------------------------------------------------------------------------
*                                            (x-1)
* 
* 
*/
double third_derivative(double x) {
	double temp1, temp2, temp3,temp4, res;

	temp1 = 3 * (2 * x * x / (x * x + 0.8) - 1) / ((x - 1) * (x * x + 0.8));
	temp2 = 6 * x / ((x - 1) * (x - 1) * (x * x + 0.8));
	temp3 = 2 * x * (4 * x / (x * x + 0.8) - 3) / ((x * x + 0.8) * (x * x + 0.8));
	temp4 = -3 * log10(x * x + 0.8) / ((x - 1) * (x - 1) * (x - 1));

	res = 2 * (temp1 + temp2 + temp3+temp4) / (x - 1);

	return res;
}



