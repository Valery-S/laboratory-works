#include<iostream>
#include<vector>
#include"colors.h"
#include"function.h"
#include"solutions.h" 
using namespace std;
int main() {
	setlocale(LC_ALL, "rus");

	double lower_limit, upper_limit;     //Пределы интегрирования
	int n;                               //Число отрезков, на которые разделится исходный
	vector<double>x, y;                  //Значения x и y на каждом отрезке
	char c;                              //Выбор пункта меню

	cout << Green << "Программа для вычисления интеграла функции lg(x^2+0.8)/(x-1)\n";
	get_limits(&lower_limit, &upper_limit);
	n = get_n();
	x=get_x(lower_limit,upper_limit,n);
	y = get_y(x);

	bool end = false;
	while (end == false) {
		c = menu_item_selection();
		switch (c) {
			case '1':
				central_rectangles(x);
				central_rectangles_errror(lower_limit, upper_limit, x);
				break;
			case '2':
				trapeze(x[1]-x[0], y);
				trapeze_errror(lower_limit, upper_limit, x);
				break;
			case '3':
				Simpson(x[1] - x[0], y);
				Simpson_errror(lower_limit, upper_limit, x);
				break;
			case'n':
				n = get_n();
				x = get_x(lower_limit, upper_limit, n);
				y = get_y(x);
				break;
			case 'q':
				end = true;
				break;
			default:
				cout << Red << "Неверный ввод, повторите попытку!\n";
		}
	}

	return 0;
}
