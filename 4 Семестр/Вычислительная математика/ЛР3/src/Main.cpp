#include<iostream>
#include "Value_function_table.h"
#include "Newton_Interpolation.h"
#include "given_points.h"
#include "Lagrange_ranv.h"
#include "Lagrange.h"
using namespace std;
int main() {
	setlocale(LC_ALL, "Russian");    //��������� �������� ����� � �������
	while (true) {
		cout << Green << "��� ������������ ������� ������� i, ��� ���������� ��������� ������� q \n";
		char c,m;
		cin >> c;
		if (c != 'q') {
			cout<<Yellow << "���� ������ �������\n";
			Value_function_table table;
			table.set_value();
			points p;
			vector<double> r;
			cout << Yellow << "���� �����, � ������� ����� ����� ��������\n";
			p.set_points();
			cout<<Green<<"\n�������� ������ ������������\n"
				  << "\t{1} - ������� �������\n"
				  << "\t{2} - ���������������� ��������� �������� ��� �������������� �����\n"
					<< "\t{3} - ���������������� ��������� �������� ��� ���������������� �����\n";
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