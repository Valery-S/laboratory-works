#ifndef _Newton_Interpolation_
#define _Newton_Interpolation_
#include <vector>
#include <iostream>
#include <iomanip>
#include "Colors.h"
#include "Value_function_table.h"
using namespace std;


//Метод для нахождения конечных разнстей
vector<vector<double>> get_finite_differences(Value_function_table t) {
	vector<vector<double>> res;

	//Вычисления конечные разностей первого порядка
	vector<double> temp;
	for (size_t  i = 1; i < t.n; i++) {
		temp.push_back(t.y[i] - t.y[i - 1]);
	}
	res.push_back(temp);

	//На каждом i-ом шаге вычисляем значения конченых разностей нового порядка
	//и заносим в промежуточный список.
	//Полученный промежуточный список заносим в список списков промежуточных разностей 
	for (size_t i = 0; i < t.n - 2; i++) {
		//Создание нового вектора конечных разностей
		vector<double>tmp;
		for (size_t j = 0; j < res[i].size() - 1; j++) {
			//Вычисление конечных разностей
			tmp.push_back(res[i][j + 1] - res[i][j]);
		}
		res.push_back(tmp);
	}
	return res;
}


/*Метод для вывода конечных разностей i - ого 
  порядка в "лестничном виде"
*/
void print_finite_differences(vector<vector<double>> finiteDifferences) {
  for (size_t  i = 0; i < finiteDifferences.size(); i++){
     cout<<Green << "Конечные разности  "<<setw(3)<<(i + 1)<< " порядка: ";
 
    for (size_t  j = 0; j < finiteDifferences[i].size(); j++){
				cout<<Blue << setw(10)<<fixed << setprecision(6) << finiteDifferences[i][j] << " ";
    }
    cout<<Reset << "\n";
  }
	return;
}

//Метод для получения факториала
int getFact(int n){
	int res = 1;
	while (n > 1){
		res *= n;
		n--;
	}
	return res;
}

/*Метод для приближенного вычисления значений
  при помощи интерполяционной формулы Ньютона
	Параметры:
		1)t - таблица значений функции
		2)values - значения х, в которых нужно найти значение функции
*/
vector<double> Newton(Value_function_table table, vector<double> values) {
	vector<double> res;

	//Нахождение конечных разностей 
	vector<vector<double>> finiteDifferences;
	finiteDifferences = get_finite_differences(table);
	print_finite_differences(finiteDifferences);

	//Вычисление середины отрезка переданных X
	double mid = (table .x[0] + table.x[(table.n) - 1]) / 2;

	//Вычисление шага h
	double h = table.x[1] - table.x[0];

	//Перемнная для хранения параметра t
	double t;

	//Нахождение значения функции в каждой переданной точке
	for (size_t k = 0; k < values.size(); k++){
		//Переменная для хранения результата
		double r = 0;

		//Если Xi лежит в промежутке левее середины
		//То значение функции вычисляется методом интерполяции вперед
		if (values[k] < mid){
			//t вычисляется как (x - x0)/h
			t = (values[k] - table.x[0]) / h;

			//К результату прибавляются Y0 + t*ΔY0
			r += table.y[0];
			r += t * finiteDifferences[0][0];

			//Вычисление членов (t(t-1)..(t-n+1) * ΔnY0)/n!
			for (int i = 1; i < finiteDifferences.size(); i++){
				double temp = 1;
				//Промежуточные вычисления числителя (t - 1)..(t - n+1)
				for (int j = 1; j <= i; j++){
					temp *= (t - j);
				}
				//К текущему результату добавляем член вида: (t(t-1)..(t-n+1) * ΔnY0)/n!
				r += temp * t * finiteDifferences[i][0] / getFact(i+1);
			}
			//В вектор ответов заносим значение полученное при интерполяции вперед
			res.push_back(r);
		}
		//Иначе Xi лежит в промежутке правее середины
		//значение функции вычисляется методом интерполяции назад
		else{
			//t вычисляется как (x - xn)/h
			t = (values[k] - table.x[table.n-1]) / h;

			//К результату прибавляются Yn + t*ΔY(n-1)
			r+= table.y[table.n-1];
			r += t * finiteDifferences[0][finiteDifferences[0].size() -2];

			//Вычисление членов (t(t+1)..(t+n-1) * ΔnY(n-1))/n!
			for (int i = 1; i < finiteDifferences.size(); i++){
				double temp = 1;
				//Промежуточные вычисления числителя (t + 1)..(t + n-1)
				for (int j = 1; j <=i; j++){
					temp *= (t + j);
				}
				//К текущему результату добавляем член вида: (t(t+1)..(t+n-1) * ΔnY(n-1))/n!
				r += t * temp * finiteDifferences[i][finiteDifferences[i].size()-1] / getFact(i+1);
			}
			//В вектор ответов заносим значение полученное при интерполяции назад
			res.push_back(r);
		}
	}
	//Вывод результатов в консоль
	cout << Green << "\n    X    |    Y\n"
		<<" ------------------\n";
	for (int i = 0; i < res.size(); i++){
		cout << Blue << setprecision(2)<<"  "<< values[i] <<"  "<< Green
				 << " |" << Blue << setw(9) << setprecision(6) << res[i] << "\n";
	}
	return res;
}
#endif