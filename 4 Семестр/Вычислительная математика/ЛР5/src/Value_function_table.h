#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include"Colors.h"
#include <iomanip>
using namespace std;

/*Класс для описания таблицы значений функции*/
class Value_function_table{
public:
	vector<double>x;                    //Координаты x точек
	vector<double>y;										//Координаты y точек
	size_t n;                           //Количество точек 

	Value_function_table() {
		n = 0;
	}

	//Функция заполнения таблицы
	void set_value() {
		setlocale(LC_ALL, "Russian");    //Включение русского языка в консоли
	
		bool is_readed = false;
		while (is_readed == false) {
			cout<<Green << "Выберите способ ввода данных\n"
				<< "\t{1} - ручной ввод в консоль\n"
				<< "\t{2} - чтение из файла\n";
			int metod;
			cin >> metod;
			if (metod == 1) {
				cout << Green << "Введите количество точек в таблице ";
				int k;
				double x_val, y_val;
				cin >> k;
				this->n = k;
				for (size_t i = 1; i <= n; i++) {
					cout << Yellow << "\n\tВведите координату x " << i << " точки ";
					cin >> x_val;
					cout << "\tВведите координату y " << i << " точки ";
					cin >> y_val;

					this->x.push_back(x_val);
					this->y.push_back(y_val);
					cout << Reset << "\n";
				}
				is_readed = true;
			}
			else {
				if (metod == 2) {
					cout << Green << "Введите имя файла ";
					string file_name;
					cin >> file_name;
					ifstream in(file_name);
					int k;
					double x_val, y_val;
					in >> k;
					this->n = k;
					for (size_t i = 1; i <= n; i++) {
						in >> x_val >> y_val;

						this->x.push_back(x_val);
						this->y.push_back(y_val);
					}
					is_readed = true;
				}
			}
		}

		//Вывод сформированной таблицы в консоль
		cout << Yellow << "Сформированная таблица:\n"
			<< Green << "\n    X    |    Y\n"
			<< " ------------------\n";
		for (int i = 0; i < this->x.size(); i++) {
			cout << Blue<< "  " <<fixed<< setprecision(3) << this->x[i] << "  " << Green
				<< " |" << Blue << setw(9) << setprecision(4) << this->y[i] << "\n";
		}

	}

};

