#include<iostream>
#include "Value_function_table.h"
#include "Newton_Interpolation.h"
#include "given_points.h"
#include "Lagrange_ranv.h"
#include "Lagrange.h"
using namespace std;
int main() {
	setlocale(LC_ALL, "Russian");    //¬ключение русского €зыка в консоли
	while (true) {
		cout << Green << "ƒл€ интерпол€ции функции введите i, дл€ завершени€ программы введите q \n";
		char c,m;
		cin >> c;
		if (c != 'q') {
			cout<<Yellow << "¬вод данных таблицы\n";
			Value_function_table table;
			table.set_value();
			points p;
			vector<double> r;
			cout << Yellow << "¬вод точек, в которых нужно найти значение\n";
			p.set_points();
			cout<<Green<<"\n¬ыберите способ интерпол€ции\n"
				  << "\t{1} - формула Ќьютона\n"
				  << "\t{2} - интерпол€ционный многочлен Ћагранжа дл€ равноотсто€щих узлов\n"
					<< "\t{3} - интерпол€ционный многочлен Ћагранжа дл€ неравноотсто€щих узлов\n";
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