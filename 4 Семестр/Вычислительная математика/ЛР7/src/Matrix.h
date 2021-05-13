#pragma once
#include<vector>
using namespace std;

//Класс квадратной матрицы
struct matrix{
	int n;                     //Размерность матрицы
	vector<vector<double>> a;  //Коэффициенты матрицы

	//Конструктор с параметрами
	matrix(vector<vector<double>> A, int N) {
		vector<double> tmp(N,0);
		for (int i = 0; i < N; i++){
			this->a.push_back(tmp);
		}

		for (int i = 0; i < N; i++){
			for (int j = 0; j < N; j++){
				this->a[i][j] = A[i][j];
			}
		}

		this->n = N;
	}

	//Метод умножения матрицы на вектор
	vector<double>multiplyByVector(vector<double> vec) {
		vector<double>res(vec.size());

		for (int i = 0; i < this->n; i++){
			for (int j = 0; j < this->n; j++){
				res[i] += this->a[i][j] * vec[j];
			}
		}

		return res;
	}

};

