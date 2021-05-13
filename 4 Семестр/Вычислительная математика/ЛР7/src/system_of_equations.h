#pragma once
#include<vector>
#include<iomanip>
#include "Colors.h"
using namespace std;

//Класс системы линейных уравнений
class system_of_equations{
public:
	//Коэффициенты перед х
	vector<vector<double>> coefficients;
	//Столбец свободных членов
	vector<double> free;
	//Количество уравнений/переменных
	int n;

	//Конструктор с параметрами
	system_of_equations(vector<vector<double>> a, vector<double> b) {
		this->n = b.size();

		vector<double> tmp(this->n,0);
		for (int i = 0; i < this->n; i++) {
			this->coefficients.push_back(tmp);
			this->free.push_back(0);
		}

		for (int i = 0; i < this->n; i++){
			for (int j = 0; j < this->n; j++){
				this->coefficients[i][j] = a[i][j];
			}
			this->free[i] = b[i];
		}

	}

	/*Метод Гаусса
	Принцип работы:
		1)Поиск масимального коэффициента
		2)Перестановка первой строки и строки с максимальным коэффициентом в матрице A
		3)Перестановка первой строки и строки с максимальным коэффициентом в векторе b
		4)Перестановка первого столбца и столбца с максимальным коэффициентом в матрице A
		6)Приведение матрицы к треугольному виду
		6)Обратный ход метода Гаусса для поиска корней системы
	*/
	vector<double> Gauss() {
		cout<<Green<<"\nСоставленная система уравнений:\n"<<setprecision(4)<<Yellow
			<< setw(6) << coefficients[0][0] << " * p1 + " << setw(6) << coefficients[0][1] << " * p2 + " << setw(6)
			<< coefficients[0][2] << " * p3 + " << setw(6) << coefficients[0][3] << " * p4 =" << free[0] << "\n"
			<< setw(6) << coefficients[1][0] << " * p1 + " << setw(6) << coefficients[1][1] << " * p2 + " << setw(6)
			<< coefficients[1][2] << " * p3 + " << setw(6) << coefficients[1][3] << " * p4 =" << free[1] << "\n"
			<< setw(6) << coefficients[2][0] << " * p1 + " << setw(6) << coefficients[2][1] << " * p2 + " << setw(6)
			<< coefficients[2][2] << " * p3 + " << setw(6) << coefficients[2][3] << " * p4 =" << free[2] << "\n"
			<< setw(6) << coefficients[3][0] << " * p1 + " << setw(6) << coefficients[3][1] << " * p2 + " << setw(6)
			<< coefficients[3][2] << " * p3 + " << setw(6) << coefficients[3][3] << " * p4 =" << free[3] << "\n";

		vector<double>x(4);
		double a_max = 0;
		int i_max = 0, j_max = 0;

		//Поиск максимального коэффициента в матрице A
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				if (coefficients[i][j] > a_max) {
					a_max = coefficients[i][j];
					i_max = i;
					j_max = j;
				}
			}
		}


		//Перестановка первой строки и строки с максимальным коэффициентом в матрице a
		double tmp = 0;
		for (int j = 0; j < 4; j++) {
			tmp = coefficients[0][j];
			coefficients[0][j] = coefficients[i_max][j];
			coefficients[i_max][j] = tmp;
		}


		//Перестановка первой строки и строки с максимальным коэффициентом в векторе b
		tmp = free[0];
		free[0] = free[i_max];
		free[i_max] = tmp;


		//Перестановка первого столбца и столбца с максимальным коэффициентом в матрице a
		for (int i = 0; i < 4; i++) {
			double tmp = 0;
			tmp = coefficients[i][0];
			coefficients[i][0] = coefficients[i][j_max];
			coefficients[i][j_max] = tmp;
		}

		//Приведение матрицы к треугольному виду
		tmp = coefficients[0][0];
		coefficients[0][0] = 1;
		coefficients[0][1] = coefficients[0][1] / tmp;
		coefficients[0][2] = coefficients[0][2] / tmp;
		coefficients[0][3] = coefficients[0][3] / tmp;
		free[0] = free[0] / tmp;

		tmp = coefficients[1][0];
		coefficients[1][0] = coefficients[1][0] - coefficients[0][0] * tmp;
		coefficients[1][1] = coefficients[1][1] - coefficients[0][1] * tmp;
		coefficients[1][2] = coefficients[1][2] - coefficients[0][2] * tmp;
		coefficients[1][3] = coefficients[1][3] - coefficients[0][3] * tmp;
		free[1] = free[1] - free[0] * tmp;


		tmp = coefficients[2][0];
		coefficients[2][0] = coefficients[2][0] - coefficients[0][0] * tmp;
		coefficients[2][1] = coefficients[2][1] - coefficients[0][1] * tmp;
		coefficients[2][2] = coefficients[2][2] - coefficients[0][2] * tmp;
		coefficients[2][3] = coefficients[2][3] - coefficients[0][3] * tmp;
		free[2] = free[2] - free[0] * tmp;

		tmp = coefficients[3][0];
		coefficients[3][0] = coefficients[3][0] - coefficients[0][0] * tmp;
		coefficients[3][1] = coefficients[3][1] - coefficients[0][1] * tmp;
		coefficients[3][2] = coefficients[3][2] - coefficients[0][2] * tmp;
		coefficients[3][3] = coefficients[3][3] - coefficients[0][3] * tmp;
		free[3] = free[3] - free[0] * tmp;

		tmp = coefficients[1][1];
		coefficients[1][1] = 1;
		coefficients[1][2] = coefficients[1][2] / tmp;
		coefficients[1][3] = coefficients[1][3] / tmp;
		free[1] = free[1] / tmp;

		tmp = coefficients[2][1];
		coefficients[2][0] = coefficients[2][0] - coefficients[1][0] * tmp;
		coefficients[2][1] = coefficients[2][1] - coefficients[1][1] * tmp;
		coefficients[2][2] = coefficients[2][2] - coefficients[1][2] * tmp;
		coefficients[2][3] = coefficients[2][3] - coefficients[1][3] * tmp;
		free[2] = free[2] - free[1] * tmp;

		tmp = coefficients[3][1];
		coefficients[3][0] = coefficients[3][0] - coefficients[1][0] * tmp;
		coefficients[3][1] = coefficients[3][1] - coefficients[1][1] * tmp;
		coefficients[3][2] = coefficients[3][2] - coefficients[1][2] * tmp;
		coefficients[3][3] = coefficients[3][3] - coefficients[1][3] * tmp;
		free[3] = free[3] - free[1] * tmp;

		tmp = coefficients[2][2];
		coefficients[2][2] = 1;
		coefficients[2][3] = coefficients[2][3] / tmp;
		free[2] = free[2] / tmp;

		tmp = coefficients[3][2];
		coefficients[3][0] = coefficients[3][0] - coefficients[2][0] * tmp;
		coefficients[3][1] = coefficients[3][1] - coefficients[2][1] * tmp;
		coefficients[3][2] = coefficients[3][2] - coefficients[2][2] * tmp;
		coefficients[3][3] = coefficients[3][3] - coefficients[2][3] * tmp;
		free[3] = free[3] - free[2] * tmp;

		//Обратный ход метода Гаусса для поиска корней системы
		x[3] = free[3] / coefficients[3][3];
		x[2] = (free[2] - coefficients[2][3] * x[3]) / coefficients[2][2];
		x[1] = (free[1] - coefficients[1][2] * x[2] - coefficients[1][3] * x[3]) / coefficients[1][1];
		x[0] = (free[0] - coefficients[0][1] * x[1] - coefficients[0][2] * x[2] - coefficients[0][3] * x[3]) / coefficients[0][0];


		return x;
	}
};

