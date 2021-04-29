#include "solution methods.h"
#include "Value_function_table.h"
#include "Colors.h"
#include<iomanip>
using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");    //Включение русского языка в консол
	cout<<Blue << "Решение уравнения y'=f(x,y)=x+sin(y/3^(1/2))\n";
	Value_function_table table_f,table_s;
	table_f.set_value();
	Euler(table_f,1);
	Euler_recount(table_f,1);
	Runge_Kutt(table_f,1);
	cout << Blue << "Решение уравнения y'=f(x,y)=(0.8-y^2)*cos(x)+0.3y\n";
	table_s.set_value();
	Adams(table_s, 2);
	Euler_recount(table_s, 2);

	return 0;
}