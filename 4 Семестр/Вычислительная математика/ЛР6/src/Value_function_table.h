#pragma once
#include<vector>
#include<iostream>
#include"Colors.h"
using namespace std;

/*����� ��� �������� ������� �������� �������*/
class Value_function_table{
public:
	vector<double>x;                    //���������� x �����
	vector<double>y;                    //���������� y �����
	size_t n;                           //���������� ����� 

	double a;                           //����� ������� ��� �
	double b;                           //������ ������� ��� �
	double h;														//���

	Value_function_table() {
		n = 0;
		a = 0;
		b = 0;
		h = 0;
	}

	//������� ���������� �������
	void set_value() {
		setlocale(LC_ALL, "Russian");    //��������� �������� ����� � �������

		cout<<Yellow << "X:[a,b]\n������� � ";
		cin >> this->a;
		cout << "\n������� b ";
		cin >> this->b;
		cout << "\n������� ��� h ";
		cin >> this->h;
		cout << "\n������� y0 ";
		double y0; cin >> y0;
		this->y.push_back(y0);
		

		for (double i = a; i <=b; i=i+h){
			this->x.push_back(i);
			this->y.push_back(0);
		}
		this->n = this->x.size();
	}

};

