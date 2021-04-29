#pragma once
#include<vector>
#include<iostream>
#include"Colors.h"
using namespace std;

/*Класс для описания таблицы значений функции*/
class Value_function_table{
public:
	vector<double>x;                    //Координаты x точек
	vector<double>y;                    //Координаты y точек
	size_t n;                           //Количество точек 

	double a;                           //Левая граница для х
	double b;                           //Правая граница для х
	double h;														//Шаг

	Value_function_table() {
		n = 0;
		a = 0;
		b = 0;
		h = 0;
	}

	//Функция заполнения таблицы
	void set_value() {
		setlocale(LC_ALL, "Russian");    //Включение русского языка в консоли

		cout<<Yellow << "X:[a,b]\nВведите а ";
		cin >> this->a;
		cout << "\nВведите b ";
		cin >> this->b;
		cout << "\nВведите шаг h ";
		cin >> this->h;
		cout << "\nВведите y0 ";
		double y0; cin >> y0;
		this->y.push_back(y0);
		

		for (double i = a; i <=b; i=i+h){
			this->x.push_back(i);
			this->y.push_back(0);
		}
		this->n = this->x.size();
	}

};

