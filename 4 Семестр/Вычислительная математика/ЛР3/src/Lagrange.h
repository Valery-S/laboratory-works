#ifndef _Lagrange_
#define _Lagrange_
#include <vector>
#include <iostream>
#include <iomanip>
#include "Colors.h"
#include "Value_function_table.h"
/*Метод для приближенного вычисления значений
	при помощи многочлена Лагранжа для равноостоящих узлов
	Параметры:
		1)t - таблица значений функции
		2)values - значения х, в которых нужно найти значение функции
*/
vector<double> Lagrange(Value_function_table table, vector<double> values) {
  //Вектор для хранения ответов
  vector<double>res;
  for (size_t k = 0; k < values.size(); k++) {
    //Перемнная для хранения промежуточного результата
    double r = 0;
    for (size_t i = 0; i < table.n; i++) {
      //Временная переменная для хранения результатов вычислений
      double temp = 1;
      for (size_t j = 0; j < table.n; j++) {
        //если i = j, то шаг пропускатеся
        if (i != j) {
          //Вычисление членов произведения вида (Х-Xj)/(Xi-Xj))
          temp *= (values[k] - table.x[j]) / (table.x[i] - table.x[j]);
        }
      }
      //Полученное произвдевение умножаем на Yi и добавляем к ответу
      r += temp * table.y[i];
    }
    //Заносим ответ в вектор ответов
    res.push_back(r);
  }
  //Вывод результатов в консоль
  cout << Green << "\n    X    |    Y\n"
    << " ------------------\n";
  for (int i = 0; i < res.size(); i++) {
    cout << Blue << setprecision(4) << "  " << values[i] << "  " << Green
      << " |" << Blue << setw(9) << setprecision(6) << res[i] << "\n";
  }
  return res;
}
#endif