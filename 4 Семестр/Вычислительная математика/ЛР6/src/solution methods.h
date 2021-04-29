#pragma once
#include<cmath>
#include<vector>
#include<iostream>
#include<iomanip>
#include"Value_function_table.h"

/*Библиотека для решения  дифференциального уравнения методом Эйлера и Рунге-Кутта*/


/*Нахождение значения функции при заданных x и y
 *Параметр equation отвечает за выбор функции
 *Если equation=1, то находится значение функции f(x,y)=x+sin(y/3^(1/2))
 *Если equation=2, то находится значение функции f(x,y)=(0.8-y^2)*cos(x)+0.3y */
double f_x_y(double x, double y,int equation) {
	double res=0;
	if (equation == 1) {
		res = x + sin(y / pow(3, 0.5));
	}
	if (equation == 2) {
		res = (0.8 - y * y) * cos(x) + 0.3 * y;
	}
	return res;
}



/*Решение уравнения методом Эйлера*/
void Euler(Value_function_table table, int equation) {

	for (size_t i = 1; i < table.n; i++){
		table.y[i]=table.y[i - 1] + table.h * f_x_y(table.x[i - 1], table.y[i - 1],equation);
	}

	cout<<Blue<<"Решение методом Эйлера\n"
		   <<Green << "\t\tf(xi)\n"
		   << "\txi\t|\tyi\n"
		   <<"-------------------------------------\n";
	for (size_t i = 0; i < table.n; i++){
		cout << "\t" << table.x[i] << "\t|\t" << setprecision(5)<< table.y[i] << "\n";
	}
}



/*Решение уравнения методом Эйлера с пересчётом*/
void Euler_recount(Value_function_table table, int equation) {
	double y;

	for (size_t i = 1; i < table.n; i++){
		y = table.y[i-1]+table.h*f_x_y(table.x[i - 1], table.y[i - 1],equation);

		table.y[i]=table.y[i - 1] + table.h / 2 *
			(f_x_y(table.x[i - 1], table.y[i - 1],equation) + f_x_y(table.x[i - 1], y,equation));
	}

	cout << Blue << "Решение методом Эйлера с пересчётом\n"
		<< Green << "\t\tf(xi)\n"
		<< "\txi\t|\tyi\n"
		<< "-------------------------------------\n";
	for (size_t i = 0; i < table.n; i++) {
		cout << "\t" << table.x[i] << "\t|\t" << setprecision(5) << table.y[i] << "\n";
	}
}


/*Решение методом Рунге-Кутта*/
void Runge_Kutt(Value_function_table table, int equation) {
	double k1, k2, k3, k4;

	for (size_t i = 1; i < table.n; i++){
		k1 = f_x_y(table.x[i - 1], table.y[i - 1],equation);
		k2 = f_x_y(table.x[i - 1] + table.h / 4, table.y[i - 1] + k1 * table.h / 4, equation);
		k3 = f_x_y(table.x[i - 1] + table.h / 2, table.y[i - 1] + k2 * table.h / 2, equation);
		k4 = f_x_y(table.x[i - 1] + table.h, table.y[i - 1] + table.h * k1 - 2 * table.h * k2 + 2 * table.h * k3, equation);

		table.y[i]=table.y[i - 1] + (k1 + 4*k3 + k4) * table.h / 6;
	}

	cout << Blue << "Решение методом Рунге-Кутта\n"
		<< Green << "\t\tf(xi)\n"
		<< "\txi\t|\tyi\n"
		<< "-------------------------------------\n";
	for (size_t i = 0; i < table.n; i++) {
		cout << "\t" << table.x[i] << "\t|\t" << setprecision(5) << table.y[i] << "\n";
	}
	
}

/*Решение методом Адамса*/
void Adams(Value_function_table table, int equation) {
	//Нахождение первых 3 значений методом Рунге-Кутта
	double k1, k2, k3, k4;
	for (size_t i = 1; i < 4; i++) {
		k1 = f_x_y(table.x[i - 1], table.y[i - 1], equation);
		k2 = f_x_y(table.x[i - 1] + table.h / 4, table.y[i - 1] + k1 * table.h / 4, equation);
		k3 = f_x_y(table.x[i - 1] + table.h / 2, table.y[i - 1] + k2 * table.h / 2, equation);
		k4 = f_x_y(table.x[i - 1] + table.h, table.y[i - 1] + table.h * k1 - 2 * table.h * k2 + 2 * table.h * k3, equation);

		table.y[i] = table.y[i - 1] + (k1 + 4 * k3 + k4) * table.h / 6;
	}

	//Нахождение остальных значений методом Адамса
	double d_f = 0, d_2_f = 0, d_3_f = 0;
	for (size_t i = 4; i < table.n; i++){
		d_f = f_x_y(table.x[i - 1], table.y[i - 1], equation) -
			    f_x_y(table.x[i - 2], table.y[i - 2], equation);

		d_2_f= f_x_y(table.x[i - 1], table.y[i - 1], equation) -
			     2*f_x_y(table.x[i - 2], table.y[i - 2], equation) + 
			     f_x_y(table.x[i - 3], table.y[i - 3], equation);

		d_3_f = f_x_y(table.x[i - 1], table.y[i - 1], equation) -
			      3 * f_x_y(table.x[i - 2], table.y[i - 2], equation) +
			      3 * f_x_y(table.x[i - 3], table.y[i - 3], equation) -
			      f_x_y(table.x[i - 4], table.y[i - 4], equation);

		table.y[i] = table.y[i - 1] +
			           table.h * f_x_y(table.x[i - 1], table.y[i - 1], equation) +
			           pow(table.h, 2) * d_f / 2 +
			           5 * pow(table.h, 3) * d_2_f / 12 +
			           3 * pow(table.h, 4) * d_3_f / 8;
	}


	cout << Blue << "Решение методом Адамса\n"
		<< Green << "\t\tf(xi)\n"
		<< "\txi\t|\tyi\n"
		<< "-------------------------------------\n";
	for (size_t i = 0; i < table.n; i++) {
		cout << "\t" << table.x[i] << "\t|\t" << setprecision(5) << table.y[i] << "\n";
	}
}