#pragma once
#include<vector>
#include <algorithm> 
#include<iostream>
using namespace std;

double const E = 0.001;

//Класс уравнений четвертой степени.
struct equation {
	vector<double>coefficients;

	//Метод для задания коэфициентов
	void setCoefficients(vector<double> coeff){
		for (int i = 0; i < coeff.size(); i++){
			this->coefficients.push_back(coeff[i]);
		}
	}


	//Метод для получение значения функции в заданной точке
	double getValueAtX(double x){
		double res;
		res=pow(x, 4) + coefficients[0] * pow(x, 3) + coefficients[1] * pow(x, 2) +coefficients[2] * x + coefficients[3];
		return res;
	}


	//Метод для получения интервалов смены знаков функции.
  vector<vector<double>> getIntervals(){
		vector<double> x_vector;
		vector<double> y_vector;

		//Задаем интервал иксов от -100 до 100
		for (double i = -100.0; i <= 100; i++){
			x_vector.push_back(i);
		}

		//Получаем значения функии в каждой точке интервала
		//от -100 до 100
		for (int i=0; i < x_vector.size(); i++){
			y_vector.push_back(getValueAtX(x_vector[i]));
		}

		//В векторзначения при которых функция меняет знак
		vector<double> new_vector;
		for (int i = 0; i < y_vector.size() - 1; i++){
			if (y_vector[i] * y_vector[i + 1] < 0){
					new_vector.push_back(x_vector[i]);
					new_vector.push_back(x_vector[i+1]);
			}
		}

		//Сортировка по возрастанию
		sort(new_vector.begin(), new_vector.end());

		//Записываем по парам полученные значения
		vector<vector<double>> cord_vector;
		for (int i = 0; i < new_vector.size(); i = i + 2) {
			vector<double> temp;
			temp.push_back(new_vector[i]);
			temp.push_back(new_vector[i + 1]);
			cord_vector.push_back(temp);
		}

		return cord_vector;
  }



	//Метод для получения решений методом бисекций.
	vector<double> Bisection() {
		vector<double> res;

		//Значение, для хранения X(i-1) - ответ полученный на пред. итерации
		double prev_value ;

		//Переменная для хранения значения Xi
		double xI;

		//Получение списка интервалов монотонности, которые содержат решения
		vector<vector<double>> intervals = this->getIntervals();

		//Проход по каждому интервалу [a;b]
		double a, b;
		for (int i = 0; i < intervals.size(); i++){
			prev_value = -DBL_MAX;
			xI = DBL_MAX;			
			a = intervals[i][0];
			b = intervals[i][1];
			//Пока разница текущего и предыдущего значений больше
			//установленной погрешность E=0.001, вычисляем новое значение
			while (abs(prev_value - xI) > E) {
				prev_value = xI;
				xI = (a + b) / 2.0;
				//Если значение функии при Xi и при X = a имеет разные знаки,
				//то меняем b из промежутка [a;b] на Xi
				//иначе меняем a на Xi
				if (this->getValueAtX(xI) * this->getValueAtX(a) < 0){
					b = xI;
				}
				else{
					a = xI;
				}
			}
			//Записываем полученный ответ в результирующий вектор
			res.push_back(xI);
		}
		return res;
	}
};