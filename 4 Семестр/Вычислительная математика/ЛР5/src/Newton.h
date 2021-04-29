#ifndef _Newton_
#define _Newton_
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
				cout<<Blue << setw(7)<<fixed << setprecision(4) << finiteDifferences[i][j] << " ";
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

/*Метод для приближенного вычисления значений первой производной
  при помощи интерполяционной формулы Ньютона
	Параметры:
		1)table - таблица значений функции
*/
vector<double> Newton_first_derivative(Value_function_table table) {
	vector<double> res;

	//Нахождение конечных разностей 
	vector<vector<double>> finiteDifferences;
	finiteDifferences = get_finite_differences(table);
	print_finite_differences(finiteDifferences);

	//Вычисление шага h
	double h = table.x[1] - table.x[0];

	//Перемнная для хранения параметра t
	double t;

	//Вычисление середины отрезка переданных X
	double mid = (table.x[0] + table.x[(table.n) - 1]) / 2;

	//Нахождение значения функции в каждой переданной точке
	for (size_t k = 0; k < table.x.size(); k++){

		//Переменная для хранения результата
		double r = 0;

		//Если Xi лежит в промежутке левее середины
    //То значение функции вычисляется методом интерполяции вперед
		if (table.x[k] < mid) {
			//t вычисляется как (x - x0)/h
			t = (table.x[k] - table.x[0]) / h;

			//t вычисляется как (x - x0)/h
			t = (table.x[k] - table.x[0]) / h;

			//К результату прибавляются ΔY0
			r += finiteDifferences[0][0];
			//прибавляем к результату последующие слагаемые до Δ^5y0
			r += ((2.0 * t - 1.0) * finiteDifferences[1][0] / getFact(2));
			r += ((3.0 * t * t - 6.0 * t + 2.0) * finiteDifferences[2][0] / getFact(3));
			r += ((4.0 * t * t * t - 18.0 * t * t + 22.0 * t - 6.0) * finiteDifferences[3][0] / getFact(4));
			r += ((5.0 * t * t * t * t - 40.0 * t * t * t + 105.0 * t * t - 100.0 * t + 24.0) * finiteDifferences[4][0] / getFact(5));

			//Делим полученный результат на h
			r = r / h;

			//В вектор ответов заносим полученное значение
			res.push_back(r);
		}
		//Иначе Xi лежит в промежутке правее середины
		//значение функции вычисляется методом интерполяции назад
		else {
			//t вычисляется как (x - xn)/h
			t = (table.x[k] - table.x[table.n - 1]) / h;

			//К результату прибавляются ΔY(n-1)
			r += finiteDifferences[0][finiteDifferences[0].size() - 2];
			//прибавляем к результату последующие слагаемые до ΔY(n-6)
			r += ((2.0 * t + 1.0) * finiteDifferences[1][finiteDifferences[1].size() - 1] / getFact(2));
			r += ((3.0 * t * t + 6.0 * t + 2.0) * finiteDifferences[2][finiteDifferences[2].size() - 1] / getFact(3));
			r += ((4.0 * t * t * t + 18.0 * t * t + 22.0 * t + 6.0) * finiteDifferences[3][finiteDifferences[3].size() - 1] / getFact(4));
		  r += ((5.0 * t * t * t * t + 40.0 * t * t * t + 105.0 * t * t + 100.0 * t + 24.0) * finiteDifferences[4][finiteDifferences[4].size() - 1] / getFact(5));
			
			//Делим полученный результат на h
			r = r / h;

			//В вектор ответов заносим полученное значение
			res.push_back(r);
			}
	}

	//Вывод результатов в консоль
	cout << Blue << "\nНьютон первая производная\n"
		<< Green << "\txi\t|\ty'i\n"
		<< "-------------------------------------\n";
	for (size_t i = 0; i < res.size(); i++) {
		cout << "\t" << setprecision(3) << table.x[i] << "\t|\t" << setprecision(5) << res[i] << "\n";
	}
	return res;
}


/*Метод для приближенного вычисления значений второй производной
	при помощи интерполяционной формулы Ньютона
	Параметры:
		1)table - таблица значений функции
*/
vector<double> Newton_second_derivative(Value_function_table table) {
	vector<double> res;

	//Нахождение конечных разностей 
	vector<vector<double>> finiteDifferences;
	finiteDifferences = get_finite_differences(table);

	//Вычисление шага h
	double h = table.x[1] - table.x[0];

	//Перемнная для хранения параметра t
	double t;

	//Вычисление середины отрезка переданных X
	double mid = (table.x[0] + table.x[(table.n) - 1]) / 2;

	//Нахождение значения функции в каждой переданной точке
	for (size_t k = 0; k < table.x.size(); k++) {
		//Переменная для хранения результата
		double r = 0;

		//Если Xi лежит в промежутке левее середины
		//То значение функции вычисляется методом интерполяции вперед
		if (table.x[k] < mid) {
			//t вычисляется как (x - x0)/h
			t = (table.x[k] - table.x[0]) / h;

			//К результату прибавляются Δ2Y0
			r += finiteDifferences[1][0];

			//прибавляем к результату последующие слагаемые до Δ^5y0
			r += ((6.0 * t - 6.0) * finiteDifferences[2][0]) / getFact(3);
			r += ((12.0 * t * t - 36.0 * t + 22.0) * finiteDifferences[3][0]) / getFact(4);
			r += ((20.0 * t * t * t - 120.0 * t * t + 210.0 * t - 100.0) * finiteDifferences[4][0] / getFact(5));

			//Делим полученный результат на h^2
			r /= (h * h);

			//В вектор ответов заносим полученное значение
			res.push_back(r);
		}
		//Иначе Xi лежит в промежутке правее середины
		//значение функции вычисляется методом интерполяции назад
		else {
			//t вычисляется как (x - xn)/h
			t = (table.x[k] - table.x[table.n - 1]) / h;

			//К результату прибавляются Δ2Y(n-2)
			r += finiteDifferences[1][finiteDifferences[0].size() - 2];

			//прибавляем к результату последующие слагаемые до ΔY(n-5)
			r += ((6.0 * t + 6.0) * finiteDifferences[2][finiteDifferences[2].size() - 1]) / getFact(3);
			r += ((12.0 * t * t + 36.0 * t + 22.0) * finiteDifferences[3][finiteDifferences[3].size() - 1]) / getFact(4);
			r += ((20.0 * t * t * t + 120.0 * t * t + 210.0 * t + 100.0) * finiteDifferences[4][finiteDifferences[4].size() - 1] / getFact(5));;

			//Делим полученный результат на h^2
			r /= (h * h);

			//В вектор ответов заносим полученное значение
			res.push_back(r);
		}
	}

	//Вывод результатов в консоль
	cout << Blue << "\nНьютон вторая производная\n"
		<< Green << "\txi\t|\ty''i\n"
		<< "-------------------------------------\n";
	for (size_t i = 0; i < res.size(); i++) {
		cout << "\t"<< setprecision(3) << table.x[i] << "\t|\t" << setprecision(5) << res[i] << "\n";
	}
	return res;
}
#endif