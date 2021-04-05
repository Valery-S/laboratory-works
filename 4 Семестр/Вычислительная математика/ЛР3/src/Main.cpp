#include<iostream>
#include "Value_function_table.h"
#include "Newton_Interpolation.h"
#include "given_points.h"
#include "Lagrange_ranv.h"
#include "Lagrange.h"
using namespace std;
int main() {
	setlocale(LC_ALL, "Russian");    //Включение русского языка в консоли
	while (true) {
		cout << Green << "Для интерполяции функции введите i, для завершения программы введите q \n";
		char c,m;
		cin >> c;
		if (c != 'q') {
			cout<<Yellow << "Ввод данных таблицы\n";
			Value_function_table table;
			table.set_value();
			points p;
			vector<double> r;
			cout << Yellow << "Ввод точек, в которых нужно найти значение\n";
			p.set_points();
			cout<<Green<<"\nВыберите способ интерполяции\n"
				  << "\t{1} - формула Ньютона\n"
				  << "\t{2} - интерполяционный многочлен Лагранжа для равноотстоящих узлов\n"
					<< "\t{3} - интерполяционный многочлен Лагранжа для неравноотстоящих узлов\n";
			cin >> m;
			switch (m){
				case'1':
					r = Newton(table, p.x);
					break;
				case'2':
					r= Lagrange_ranv(table, p.x);
					break;
				case'3':
					r = Lagrange(table, p.x);
					break;
			}
		}
		else {
			break;
		}
	}
	return 0;
}
