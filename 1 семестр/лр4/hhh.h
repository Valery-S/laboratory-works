#ifndef _hhh_H_
#define _hhh_H_
#include<iostream>
#include<cstdlib>
#include<iomanip>
using namespace std;
int **filling(int d, int c) {/*функция заполнения массива*/
	char b;
	int  **a = new int*[d];
	cout << "choose how to fill the matrix : manually (enter m) or randomly (enter r) ";
	cin >> b;
	if (b == 'm')
	{
		cout << "enter the elements of the matrix  ";
		for (int i = 0; i < d; i++)
		{
			a[i] = new int[c];
			if (a[i] == 0)
			{
				exit(-1);
			}
			for (int j = 0; j < c; j++)
			{
				cin >> a[i][j];
			}
		}
	}
	if (b == 'r')
	{
		for (int i = 0; i < d; i++)
		{
			a[i] = new int[c];
			if (a[i] == 0)
			{
				exit(-1);
			}
			for (int j = 0; j < c; j++)
			{
				a[i][j] = rand() % 200;
			}
		}
	}
	return a;
}
int proverka() {/*функция проверки правильности ввода разрера массива*/
	int n = 0;
	char b = 1;
	while (cin.good()) {
		if (n == 0) {
			while (b != 0)
			{
				b = cin.get();
				if (b >= '0' && b <= '9')
				{
					n = n * 10 + (b - 48);

				}
				else {
					if (b != '\n')
					{
						cout << "error, write again " << endl;
						n = 0;
					}
					else
					{
						break;
					}
				}

			}
		}
		else {
			break;
		}
	}
	return n;
}
int trace(int **a, int q, int b) {/*функция  вычисления следа матрицы */
	int t = 0;
	for (int i = 0; i < q; i++)
	{
		for (int j = 0; j < b; j++)
		{
			if (i == j)
			{
				t = t + a[i][j];
			}
		}
	}
	return t;
}
int **composition(int trace, int row, int column, int** a ) {/*функция вычисления матрицы R (матрица А * след матрицы С)*/
	int** r = new int* [row];
	for (int i = 0; i < row; i++)
	{
		r[i] = new int[column];
		for (int j = 0; j < column; j++)
		{
			r[i][j] = a[i][j] * trace;
		}
	}
	return r;
}
#endif
