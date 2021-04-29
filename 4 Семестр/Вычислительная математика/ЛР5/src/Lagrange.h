#ifndef _Lagrange_
#define _Lagrange_
#include <vector>
#include <iostream>
#include <iomanip>
#include "Colors.h"
#include "Value_function_table.h"
using namespace std;


/*Метод для приближенного вычисления значений первой производной
	при помощи интерполяционной формулы Ньютона
	Параметры:
		1)table - таблица значений функции
*/
vector<double> Lagrange_first_derivative(Value_function_table table) {
	vector<double> res;
	double h = table.x[1] - table.x[0];
	double  r;

	// вычисление производной в начальных точках
	r = (-25 * table.y[0] + 48 * table.y[1] - 36 * table.y[2] + 16 * table.y[3] - 3 * table.y[4]) / (12 * h);
	res.push_back(r);

	r = (-3 * table.y[0] - 10 * table.y[1] + 18 * table.y[2] - 6 *  table.y[3] +  table.y[4]) / (12 * h);
	res.push_back(r);

	// вычисление производной в средних точках
	for (int i = 2; i < 10; i++){
		r = ( table.y[i - 2] - 8 *  table.y[i - 1] + 8 *  table.y[i + 1] -  table.y[i + 2]) / (12 * h);
		res.push_back(r);
	}

	// вычисление производной в последних точках
	r = (- table.y[7] + 6 *  table.y[8] - 18 *  table.y[9] + 10 *  table.y[10] + 3 *  table.y[11]) / (12 * h);
	res.push_back(r);

	r = (3 *  table.y[7] - 16 *  table.y[8] + 36 *  table.y[9] - 48 *  table.y[10] + 25 *  table.y[11]) / (12 * h);
	res.push_back(r);


	//Вывод результатов в консоль
	cout << Blue << "\nЛагранж первая производная\n"
		<<Green<< "\txi\t|\ty'i\n"
		<< "-------------------------------------\n";
	for (size_t i = 0; i < res.size(); i++) {
		cout << "\t" << setprecision(3) << table.x[i] << "\t|\t" << setprecision(5) << res[i] << "\n";
	}
	return res;
}


/*Метод для приближенного вычисления значений первой производной
	при помощи интерполяционной формулы Ньютона
	Параметры:
		1)table - таблица значений функции
*/
vector<double> Lagrange_second_derivative(Value_function_table table) {
	double h, res ;
	vector<double> r;
	h =  table.x[1] -  table.x[0];
	
	// вычисление производной в начальной точке
	res = (2.0 *  table.y[0] - 5.0 *  table.y[1] + 4.0 *  table.y[2] -  table.y[3]) / (h * h);
	r.push_back(res);

	// вычисление производной в средних точках
	for (int i = 1; i < 11; i++){
		res = ( table.y[i - 1] - 2 *  table.y[i] +  table.y[i + 1]) / (h * h);
		r.push_back(res);
	}

	// вычисление производной в конечной точке
	res = (- table.y[8] + 4 *  table.y[9] - 5 *  table.y[10] + 2 *  table.y[11]) / (h * h);
	r.push_back(res);

	cout << Blue <<"\nЛагранж вторая производная\n"
		<< Green << "\txi\t|\ty''i\n"
		<< "-------------------------------------\n";
	for (size_t i = 0; i < r.size(); i++) {
		cout << "\t" << setprecision(3)<< table.x[i] << "\t|\t" << setprecision(5) << r[i] << "\n";
	}
	return r;
}

#endif