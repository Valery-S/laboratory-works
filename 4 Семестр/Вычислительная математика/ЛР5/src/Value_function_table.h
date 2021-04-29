#pragma once
#include<vector>
#include<iostream>
#include<fstream>
#include<string>
#include"Colors.h"
#include <iomanip>
using namespace std;

/*����� ��� �������� ������� �������� �������*/
class Value_function_table{
public:
	vector<double>x;                    //���������� x �����
	vector<double>y;										//���������� y �����
	size_t n;                           //���������� ����� 

	Value_function_table() {
		n = 0;
	}

	//������� ���������� �������
	void set_value() {
		setlocale(LC_ALL, "Russian");    //��������� �������� ����� � �������
	
		bool is_readed = false;
		while (is_readed == false) {
			cout<<Green << "�������� ������ ����� ������\n"
				<< "\t{1} - ������ ���� � �������\n"
				<< "\t{2} - ������ �� �����\n";
			int metod;
			cin >> metod;
			if (metod == 1) {
				cout << Green << "������� ���������� ����� � ������� ";
				int k;
				double x_val, y_val;
				cin >> k;
				this->n = k;
				for (size_t i = 1; i <= n; i++) {
					cout << Yellow << "\n\t������� ���������� x " << i << " ����� ";
					cin >> x_val;
					cout << "\t������� ���������� y " << i << " ����� ";
					cin >> y_val;

					this->x.push_back(x_val);
					this->y.push_back(y_val);
					cout << Reset << "\n";
				}
				is_readed = true;
			}
			else {
				if (metod == 2) {
					cout << Green << "������� ��� ����� ";
					string file_name;
					cin >> file_name;
					ifstream in(file_name);
					int k;
					double x_val, y_val;
					in >> k;
					this->n = k;
					for (size_t i = 1; i <= n; i++) {
						in >> x_val >> y_val;

						this->x.push_back(x_val);
						this->y.push_back(y_val);
					}
					is_readed = true;
				}
			}
		}

		//����� �������������� ������� � �������
		cout << Yellow << "�������������� �������:\n"
			<< Green << "\n    X    |    Y\n"
			<< " ------------------\n";
		for (int i = 0; i < this->x.size(); i++) {
			cout << Blue<< "  " <<fixed<< setprecision(3) << this->x[i] << "  " << Green
				<< " |" << Blue << setw(9) << setprecision(4) << this->y[i] << "\n";
		}

	}

};

