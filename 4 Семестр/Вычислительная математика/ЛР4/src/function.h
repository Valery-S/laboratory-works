#pragma once
#include<iostream>
#include<vector>
#include<cmath>
#include"colors.h"

using namespace std;
/*Библиотека для работы с исходной функцией и её производными */


/*Функция считывания пределов интегрирования*/
void get_limits(double* lower_limit, double* upper_limit) {
	cout << Green << "Введите пределы интегрирования \n"
		<< Yellow << "\tНижний предел ";
	cin >> *lower_limit;
	cout << "\tВерхний предел ";
	cin >> *upper_limit;
}

/*Функция считывания n*/
int get_n() {
	int n;
	cout << Green << "Введите n - число отрезков разбиения ";
	cin >> n;
	return n;
}

/*Функция вывода меню*/
char menu_item_selection() {
	char c;
	cout << Green << "\nВыберите, что нужно сделать :\n" << Yellow
		<< "\t{1} - Найти интеграл методом центральных прямоугольников\n"
		<< "\t{2} - Найти интеграл методом трапеций\n"
		<< "\t{3} - Найти интеграл по формуле Симпсона\n"
		<< "\t{n} - Сменить n\n"
		<< "\t{q} - Завершить программу\n";
	cin >> c;
	return c;
}

/*Функция нахождения значений х на каждом отрезке
 *Параметры:
 *	1)lower_limit-нижний предел
 *	2)upper_limit-верхний предел
 *	3)n-число отрезков
 */
vector <double> get_x(double lower_limit, double upper_limit, int n) {
	vector <double> x(n + 1);

	double h = (upper_limit - lower_limit) / n;  //Шаг
	x[0] = lower_limit;

	for (int i = 1; i < (n + 1); i++) {
		x[i] = x[i - 1] + h;
	}

	return x;
}

/*Функция нахождения значения функции в заданной точке*/
double f_x(double x) {
	double y = (log10(x * x + 0.8)) / (x - 1);
	return y;
}

/*Функция нахождения у на каждом отрезке
 *Параметры:
 *	1)x - вектор значений х
 */
vector <double> get_y(vector<double>x) {
	vector <double> y(x.size());

	for (int i = 0; i < (x.size()); i++) {
		y[i] = f_x(x[i]);
	}

	return y;
}

/*Функция нахождения значения второй производной в заданной точке
*                     2*x        (2x^2/(x^2+0.8)-1)      lg(x^2+0.8)
*           -  --------------  - -------------------   + ------------
*              (x-1)*(x^2+0.8)        x^2+0.8              (x-1)^2
*f''(x)=2 * ----------------------------------------------------------
*		                     (x-1)
*/
double second_derivative(double x) {
	double temp1, temp2, temp3, res;
	
	temp1 = -2*x / (x - 1) * (x * x + 0.8);
	temp2 = -((2 * x * x) / (x * x + 0.8) - 1) / (x * x + 0.8);
	temp3 = log10(x * x + 0.8) / ((x - 1) * (x - 1));

	res = 2 * (temp1 + temp2 + temp3) / (x - 1);

	return res;
}

/*Функция нахождения значения третьей производной в заданной точке
* 
* 
*               3(2*x^2/(x^2+0.8)-1)         6x               2x(4x/(x^2+0.8)-3)         3lg(x^2+0.8)
*	         ------------------ +  ------------------  +	--------------------   -  ----------------   
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



