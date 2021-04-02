#ifndef _given_points_
#define _given_points_
#include<vector>
#include<iostream>
#include<fstream>
#include"colors.h"
using namespace std;

class points {
public:
	vector<double> x;
	size_t n;
	void set_points() {
		bool is_readed = false;
		while (is_readed == false) {
			cout << Green << "Выберите способ ввода данных\n"
				<< "\t{1} - ручной ввод в консоль\n"
				<< "\t{2} - чтение из файла\n";
			int metod;
			cin >> metod;
			if (metod == 1) {
				cout << Green << "Введите количество точек  ";
				int k;
				double x_val;
				cin >> k;
				this->n = k;
				for (size_t i = 1; i <= n; i++) {
					cout << Yellow << "\n\tВведите координату x " << i << " точки ";
					cin >> x_val;
					this->x.push_back(x_val);
					cout << Reset << "\n";
				}
				is_readed = true;
			}
			else {
				if (metod == 2) {
					cout << Green << "Введите имя файла ";
					string file_name;
					cin >> file_name;
					ifstream in(file_name);
					int k;
					double x_val;
					in >> k;
					this->n = k;
					for (size_t i = 1; i <= this->n; i++) {
						in >> x_val;
						this->x.push_back(x_val);
					}
					is_readed = true;
				}
			}
		}
		cout << Green << "Cчитанные точки\n";
		for (size_t i = 0; i < this->n; i++){
			cout << Blue<<setprecision(3) << x[i] << "\n";
		}
	}
};
#endif