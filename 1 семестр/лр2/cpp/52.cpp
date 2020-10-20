#include <iostream>
#include <string>
#include <sstream> 
using namespace std;
int main()
{
	setlocale(LC_ALL, "Russian");
	double y;
	y = 3 * sqrt(0.05) + 4 / pow(0.05, 5) + pow(0.05, 1.5) - 7 / 0.05;
	double yMax = y, yMin = y;
	cout << "y                             x"<<endl;
	for (double i =0.05 ; i < 1.6; i=i+0.05)
	{
		y = 3 * sqrt(i) + 4 / pow(i, 5) + pow(i, 1.5) - 7 / i;
		if (y > yMax) { yMax = y; }
		if (y < yMin) { yMin = y; }
		ostringstream ostr;   /* преобразование числа в строку,*/
		ostr << y;	          /* что бы в последующем вывести*/ 
		string s = ostr.str();/*нужное колличество пробелов дл€ получени€ красивой таблицы*/
		cout << y;
		for (int i = 0; i < 30 - (s.size()); i++)/*цикл выводит пробелы*/
		{
			cout << " ";
		}
		cout << i << endl;
	}
	cout << "Ќаибольшее значение функции у = "<<yMax<< "      Ќаименьшее значение функции у = "<<yMin;
	return 0;
}
