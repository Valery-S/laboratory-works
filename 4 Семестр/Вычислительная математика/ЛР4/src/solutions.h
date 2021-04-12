#pragma once
#include<iostream>
#include<vector>
#include"colors.h"

using namespace std;

/*Библиотека, содержащая методы нахождения интеграла и погрешности этих методов*/

/*Функция поиска интеграла методом центральных прямоугольников
 *Параметры
 *	1)x - вектор значений х
 */
double central_rectangles(vector<double>x) {
	double res=0;

	for (int i = 1; i < x.size(); i++){
		res = res + f_x((x[i - 1] + x[i]) / 2);
	}
	res = res * (x[1] - x[0]);
	
	cout<<Blue << "Значение интеграла, вычисленное методом центральных прямоугольников при n="
		  << x.size() - 1 << " равно " << res << "\n";

	return res;
}

/*Функция поиска интеграла методом трапеций
 *Параметры
 *	1)h - длина отрезка (шаг)
 *	2)у - вектор значений у
 */
double trapeze(double h, vector <double> y) {
	double res = (y[0]+y[y.size()-1])/2.0;

	for (int i = 1; i < y.size()-1; i++){
		res = res + y[i];
	}
	res = res * h;

	cout << Blue << "Значение интеграла, вычисленное методом трапеций при n="
		<< y.size() - 1 << " равно " << res << "\n";

	return res;
}

/*Функция поиска интеграла методом Симпосна
 *Параметры
 *	1)h - длина отрезка (шаг)
 *	2)у - вектор значений у
 */
double Simpson(double h, vector <double> y) {
	double res=y[0]+y[y.size()-1];

	for (int i = 1; i < y.size()-1; i++){
		if (i % 2 == 1) {res = res + 4 * y[i];}
		else { res = res + 2 * y[i];}
	}
	res = res * h / 3;

	cout << Blue << "Значение интеграла, вычисленное методом Cимпсона при n="
		<< y.size() - 1 << " равно " << res << "\n";

	return res;
}

/*Функция поиска погрешности метода центральных прямоугольников
 *Параметры
 *	1)lower_limit - нижний предел
 *  2)upper_limit - верхний предел
 *	3)x - вектор значений х
 */
double central_rectangles_errror(double lower_limit, double upper_limit, vector<double>x) {
	double res=1,temp, max_d;

	max_d=abs(second_derivative(x[0]));
	for (int i = 1; i < x.size(); i++){
		temp = abs(second_derivative(x[i]));
		if (temp > max_d) { max_d = temp; }
	}

	res = (upper_limit - lower_limit) * (x[1]-x[0]) * (x[1] - x[0]) * max_d / 24;

	cout << Blue << "Значение погрешности при вычислении методом центральных прямоугольников при n="
		<< x.size() - 1 << " равно " << res << "\n";

	return res;
}

/*Функция поиска погрешности метода трапеций
 *Параметры
 *	1)lower_limit - нижний предел
 *  2)upper_limit - верхний предел
 *	3)x - вектор значений х
 */
double trapeze_errror(double lower_limit, double upper_limit, vector<double>x) {
	double res = 1, temp, max_d;

	max_d = abs(second_derivative(x[0]));
	for (int i = 1; i < x.size(); i++) {
		temp = abs(second_derivative(x[i]));
		if (temp > max_d) { max_d = temp; }
	}

	res = (upper_limit - lower_limit) * (x[1] - x[0]) * (x[1] - x[0]) * max_d / 12;

	cout << Blue << "Значение погрешности при вычислении методом трапеций при n="
		<< x.size() - 1 << " равно " << res << "\n";

	return res;
}

/*Функция поиска погрешности метода Симсона
 *Параметры
 *	1)lower_limit - нижний предел
 *  2)upper_limit - верхний предел
 *	3)x - вектор значений х
 */
double Simpson_errror(double lower_limit, double upper_limit, vector<double>x) {
	double res = 1, temp, max_d;

	max_d = abs(third_derivative(x[0]));
	for (int i = 1; i < x.size(); i++) {
		temp = abs(third_derivative(x[i]));
		if (temp > max_d) { max_d = temp; }
	}

	res = (upper_limit - lower_limit) * (x[1] - x[0]) * (x[1] - x[0]) * (x[1] - x[0]) * max_d / 288;

	cout << Blue << "Значение погрешности при вычислении методом Симсона при n="
		<< x.size() - 1 << " равно " <<fixed<< res << "\n";

	return res;
}
