#ifndef _Lagrange_ranv_
#define _Lagrange_ranv_
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
vector<double> Lagrange_ranv(Value_function_table table, vector<double> values) {
	//������ ��� �������� �������
	vector<double>res;
	//���������� ���� ����� �������
	double h = table.x[1] - table.x[0];
  for (size_t k = 0; k < values.size(); k++) {
    //��������� ��� �������� �������������� ����������
    double r = 0;
    for (int i = 0; i < table.n; i++) {
      //��������� ���������� ��� �������� ����������� ����������
      double temp = 1;
      for (int j = 0; j < table.n; j++) {
        //���� i = j, �� ��� ������������
        if (i != j) {
          //���������� ������ ������������ ���� (�-X0-j*h)/(h*(i-j)))
          temp *= (values[k] - table.x[0]-j*h) / (double(h * (i - j)));
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
    cout << Blue << setprecision(5) << "  " << values[i] << "  " << Green
      << " |" << Blue << setw(9) << setprecision(6) << res[i] << "\n";
  }

  return res;
}
#endif