#include<iostream>
#include<vector>
#include"colors.h"
#include"function.h"
#include"solutions.h" 
using namespace std;
int main() {
	setlocale(LC_ALL, "rus");

	double lower_limit, upper_limit;     //������� ��������������
	int n;                               //����� ��������, �� ������� ���������� ��������
	vector<double>x, y;                  //�������� x � y �� ������ �������
	char c;                              //����� ������ ����

	cout << Green << "��������� ��� ���������� ��������� ������� lg(x^2+0.8)/(x-1)\n";
	get_limits(&lower_limit, &upper_limit);
	n = get_n();
	x=get_x(lower_limit,upper_limit,n);
	y = get_y(x);

	bool end = false;
	while (end == false) {
		c = menu_item_selection();
		switch (c) {
			case '1':
				central_rectangles(x);
				central_rectangles_errror(lower_limit, upper_limit, x);
				break;
			case '2':
				trapeze(x[1]-x[0], y);
				trapeze_errror(lower_limit, upper_limit, x);
				break;
			case '3':
				Simpson(x[1] - x[0], y);
				Simpson_errror(lower_limit, upper_limit, x);
				break;
			case'n':
				n = get_n();
				x = get_x(lower_limit, upper_limit, n);
				y = get_y(x);
				break;
			case 'q':
				end = true;
				break;
			default:
				cout << Red << "�������� ����, ��������� �������!\n";
		}
	}

	return 0;
}