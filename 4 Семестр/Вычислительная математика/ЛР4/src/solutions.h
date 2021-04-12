#pragma once
#include<iostream>
#include<vector>
#include"colors.h"

using namespace std;

/*����������, ���������� ������ ���������� ��������� � ����������� ���� �������*/

/*������� ������ ��������� ������� ����������� ���������������
 *���������
 *	1)x - ������ �������� �
 */
double central_rectangles(vector<double>x) {
	double res=0;

	for (int i = 1; i < x.size(); i++){
		res = res + f_x((x[i - 1] + x[i]) / 2);
	}
	res = res * (x[1] - x[0]);
	
	cout<<Blue << "�������� ���������, ����������� ������� ����������� ��������������� ��� n="
		  << x.size() - 1 << " ����� " << res << "\n";

	return res;
}

/*������� ������ ��������� ������� ��������
 *���������
 *	1)h - ����� ������� (���)
 *	2)� - ������ �������� �
 */
double trapeze(double h, vector <double> y) {
	double res = (y[0]+y[y.size()-1])/2.0;

	for (int i = 1; i < y.size()-1; i++){
		res = res + y[i];
	}
	res = res * h;

	cout << Blue << "�������� ���������, ����������� ������� �������� ��� n="
		<< y.size() - 1 << " ����� " << res << "\n";

	return res;
}

/*������� ������ ��������� ������� ��������
 *���������
 *	1)h - ����� ������� (���)
 *	2)� - ������ �������� �
 */
double Simpson(double h, vector <double> y) {
	double res=y[0]+y[y.size()-1];

	for (int i = 1; i < y.size()-1; i++){
		if (i % 2 == 1) {res = res + 4 * y[i];}
		else { res = res + 2 * y[i];}
	}
	res = res * h / 3;

	cout << Blue << "�������� ���������, ����������� ������� C������� ��� n="
		<< y.size() - 1 << " ����� " << res << "\n";

	return res;
}

/*������� ������ ����������� ������ ����������� ���������������
 *���������
 *	1)lower_limit - ������ ������
 *  2)upper_limit - ������� ������
 *	3)x - ������ �������� �
 */
double central_rectangles_errror(double lower_limit, double upper_limit, vector<double>x) {
	double res=1,temp, max_d;

	max_d=abs(second_derivative(x[0]));
	for (int i = 1; i < x.size(); i++){
		temp = abs(second_derivative(x[i]));
		if (temp > max_d) { max_d = temp; }
	}

	res = (upper_limit - lower_limit) * (x[1]-x[0]) * (x[1] - x[0]) * max_d / 24;

	cout << Blue << "�������� ����������� ��� ���������� ������� ����������� ��������������� ��� n="
		<< x.size() - 1 << " ����� " << res << "\n";

	return res;
}

/*������� ������ ����������� ������ ��������
 *���������
 *	1)lower_limit - ������ ������
 *  2)upper_limit - ������� ������
 *	3)x - ������ �������� �
 */
double trapeze_errror(double lower_limit, double upper_limit, vector<double>x) {
	double res = 1, temp, max_d;

	max_d = abs(second_derivative(x[0]));
	for (int i = 1; i < x.size(); i++) {
		temp = abs(second_derivative(x[i]));
		if (temp > max_d) { max_d = temp; }
	}

	res = (upper_limit - lower_limit) * (x[1] - x[0]) * (x[1] - x[0]) * max_d / 12;

	cout << Blue << "�������� ����������� ��� ���������� ������� �������� ��� n="
		<< x.size() - 1 << " ����� " << res << "\n";

	return res;
}

/*������� ������ ����������� ������ �������
 *���������
 *	1)lower_limit - ������ ������
 *  2)upper_limit - ������� ������
 *	3)x - ������ �������� �
 */
double Simpson_errror(double lower_limit, double upper_limit, vector<double>x) {
	double res = 1, temp, max_d;

	max_d = abs(third_derivative(x[0]));
	for (int i = 1; i < x.size(); i++) {
		temp = abs(third_derivative(x[i]));
		if (temp > max_d) { max_d = temp; }
	}

	res = (upper_limit - lower_limit) * (x[1] - x[0]) * (x[1] - x[0]) * (x[1] - x[0]) * max_d / 288;

	cout << Blue << "�������� ����������� ��� ���������� ������� ������� ��� n="
		<< x.size() - 1 << " ����� " <<fixed<< res << "\n";

	return res;
}
