#include<iostream>
#include<fstream>
#include<vector>
#include"Colors.h"
#include"Value_function_table.h"
#include"Newton.h"
#include"Lagrange.h"

using namespace std;
int main() {
	setlocale(LC_ALL, "Russian");    //¬ключение русского €зыка в консоли
	cout << Yellow << "¬вод данных таблицы\n";
	Value_function_table table;
	table.set_value();
	Newton_first_derivative(table);
	Newton_second_derivative(table);
	Lagrange_first_derivative(table);
	Lagrange_second_derivative(table);
	return 0;
}