#include <iostream>
#include <vector>
#include "Matrix.h"
#include "system_of_equations.h"
#include "Colors.h"
#include "Print.h"
#include "equation.h"
using namespace std;
int main() {
	vector<vector<double>>c;
	vector<double>y0(4),y1(4), y2(4), y3(4), y4(4);

	setlocale(LC_ALL, "Russian");    //Включение русского языка в консоли
	cout<<Green << "Определение собственных чисел и собственных векторов матрицы методом Крылова\n\n" << Reset;

	//создаем объект матрица, передаем туда исходные данные
	vector<double> tmp(4, 0);
	for (int i = 0; i < 4; i++){c.push_back(tmp);}
	c[0][0] = 1;		c[0][1] = 1.5;		c[0][2] = 0.4;		c[0][3] = 2;
	c[1][0] = 1.5;	c[1][1] = -1.2;		c[1][2] = 1;      c[1][3] = -0.5;
	c[2][0] = 0.4;	c[2][1] = 1;			c[2][2] = 2;			c[2][3] = 1.2;
	c[3][0] = 2;		c[3][1] = -0.5;		c[3][2] = 1.2;		c[3][3] = 2.5;

	matrix mat(c, 4);
	cout<<Green << "Исходная матрица:\n";
	print_matrix(mat);

	//задаем вектор y0
	y0[0] = 0;	y0[1] = 1;
	y0[2] = 0;	y0[3] = 0;
	cout << Green << "\nВектор y0:\n";
	print_vector(y0);

	//вычсиление вектора y1 и его вывод
	y1 = mat.multiplyByVector(y0);
	cout << Green << "Вектор y1:\n";
	print_vector(y1);

	//вычсиление вектора y2 и его вывод
	y2 = mat.multiplyByVector(y1);
	cout << Green << "Вектор y2:\n";
	print_vector(y2);

	//вычсиление вектора y3 и его вывод
	y3 = mat.multiplyByVector(y2);
	cout << Green << "Вектор y3:\n";
	print_vector(y3);

	//вычсиление вектора y4 и его вывод
	y4 = mat.multiplyByVector(y3);
	cout << Green << "Вектор y4:\n";
	print_vector(y4);

	//Создание объекта - система уравнений, на основе полученных векторов
	vector<vector<double>> temporary(4);
	temporary[0].push_back(y3[0]);	temporary[0].push_back(y2[0]);
	temporary[0].push_back(y1[0]);	temporary[0].push_back(y0[0]);

	temporary[1].push_back(y3[1]);	temporary[1].push_back(y2[1]);
	temporary[1].push_back(y1[1]);	temporary[1].push_back(y0[1]);

	temporary[2].push_back(y3[2]);	temporary[2].push_back(y2[2]);
	temporary[2].push_back(y1[2]);	temporary[2].push_back(y0[2]);

	temporary[3].push_back(y3[3]);	temporary[3].push_back(y2[3]);
	temporary[3].push_back(y1[3]);	temporary[3].push_back(y0[3]);

	vector<double> y4_invert(4);
	y4_invert[0] = y4[0] * (-1);	y4_invert[1] = y4[1] * (-1);
	y4_invert[2] = y4[2] * (-1);	y4_invert[3] = y4[3] * (-1);

	system_of_equations system(temporary, y4_invert);

	//Решение системы методом Гаусса
	vector<double>p = system.Gauss();
	cout << Green << "\nРешение системы уравнений методом Гаусса\n";
	print_vector(p);

	//Создаем объект уравнение на основе полученных решений системы
	equation polinom;
	polinom.setCoefficients(p);
	cout << Green << "Полученное уравнение P(z):\n";
	print_equation(polinom);

	//Получение собственных чисел - решений полученного уравнения
	vector<double> res;
	res=polinom.Bisection();
	cout << Green << "\nРешения уравнения - собственные числа матрицы:\n";
	print_vector(res);
	
	//На основе полученных собственных чисел
	//векторов p и векторов y0-y4 через схему Горнера
	//находим собственные вектора
	cout<<Green<<"\nНахождение собсвтенных векторов:\n";
	vector < vector <double> > ownVectors(4, vector <double>(4));
	for (int k = 0; k < 4; k++){
		vector<double>q(5);
		q[0] = 1.0;
		vector<double>y0_tmp, y1_tmp, y2_tmp, y3_tmp;
		for (int i = 0; i < y0.size(); i++){
			y0_tmp.push_back(y0[i]);
			y1_tmp.push_back(y1[i]);
			y2_tmp.push_back(y2[i]);
			y3_tmp.push_back(y3[i]);
		}
		

		//вычисление значения qi
		for (int j = 1, i = 0; i < p.size(); i++, j++){
			q[j] = res[k] * q[j - 1] + p[i];
		}

		//умножаем вектор Y3 на q0
		for (int j = 0; j < y3.size(); j++){
			y3_tmp[j] *= q[0];
		}

		//умножаем вектор Y2 на q1
		for (int j = 0; j < y2.size(); j++) {
			y2_tmp[j] *= q[1];
		}

		//умножаем вектор Y1 на q2
		for (int j = 0; j < y1.size(); j++) {
			y1_tmp[j] *= q[2];
		}

		//умножаем вектор Y0 на q3
		for (int j = 0; j < y0.size(); j++) {
			y0_tmp[j] *= q[3];
		}

		//Получаем собтсвенный вектор путем сложения
		//произвдеений qi на вектор Yj
		ownVectors[k][0] = y0_tmp[0] + y1_tmp[0] + y2_tmp[0] + y3_tmp[0];
		ownVectors[k][1] = y0_tmp[1] + y1_tmp[1] + y2_tmp[1] + y3_tmp[1];
		ownVectors[k][2] = y0_tmp[2] + y1_tmp[2] + y2_tmp[2] + y3_tmp[2];
		ownVectors[k][3] = y0_tmp[3] + y1_tmp[3] + y2_tmp[3] + y3_tmp[3];

		cout<<Green<<"Собственный вектор V " << (k + 1) << ":\n";
		print_vector(ownVectors[k]);
	}

	cout << Reset;
	return 0;
}