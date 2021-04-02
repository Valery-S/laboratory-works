#ifndef _Lagrange_
#define _Lagrange_
#include <vector>
#include <iostream>
#include <iomanip>
#include "Colors.h"
#include "Value_function_table.h"
/*����� ��� ������������� ���������� ��������
	��� ������ ���������� �������� ��� ������������� �����
	���������:
		1)t - ������� �������� �������
		2)values - �������� �, � ������� ����� ����� �������� �������
*/
vector<double> Lagrange(Value_function_table table, vector<double> values) {
  //������ ��� �������� �������
  vector<double>res;
  for (size_t k = 0; k < values.size(); k++) {
    //��������� ��� �������� �������������� ����������
    double r = 0;
    for (size_t i = 0; i < table.n; i++) {
      //��������� ���������� ��� �������� ����������� ����������
      double temp = 1;
      for (size_t j = 0; j < table.n; j++) {
        //���� i = j, �� ��� ������������
        if (i != j) {
          //���������� ������ ������������ ���� (�-Xj)/(Xi-Xj))
          temp *= (values[k] - table.x[j]) / (table.x[i] - table.x[j]);
        }
      }
      //���������� ������������� �������� �� Yi � ��������� � ������
      r += temp * table.y[i];
    }
    //������� ����� � ������ �������
    res.push_back(r);
  }
  //����� ����������� � �������
  cout << Green << "\n    X    |    Y\n"
    << " ------------------\n";
  for (int i = 0; i < res.size(); i++) {
    cout << Blue << setprecision(4) << "  " << values[i] << "  " << Green
      << " |" << Blue << setw(9) << setprecision(6) << res[i] << "\n";
  }
  return res;
}
#endif