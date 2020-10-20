/*Заданы матрицы A и C с размерами M×N и L×L соответственно.
Написать функции умножения матрицы на скаляр и вычисления следа
квадратной матрицы.Вычислить и напечатать Slc - след матрицы C и
матрицу R = A×Slc.*/
#include "hhh.h"
char logo[] = "*********************************************************\n"

"* Nizhniy Novgorod Technical University *\n"

"* Study work number 4. Task number 1. *\n"

"* Performed student 19-IVT-3 Sukhorukov V.A. *\n"

"*********************************************************\n";
int main() {
	int m=1, n=2,l,tr;
	cout << logo;
	cout << "enter the number of rows in the matrix A" << endl;
	m = proverka();
	cout << "enter the number of columns in the matrix A" << endl;
	n = proverka();
	cout << "enter the number of rows and columns in the matrix C" << endl;
	l = proverka();
	cout << "Filling matrix A: ";
	int** a = filling(m, n);
	cout << "Filling matrix C: ";
	int** c = filling(l, l);
	tr = trace(c,l,l);
	int** r  = composition(tr,m,n,a);
	cout <<"trace matrix's C = "<< tr << endl << "matrix A is : "<< endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout << setw(3) << a[i][j] << "  ";
			if (j == n - 1)
			{
				cout << endl;
			}
		}
	}
	cout <<  "matrix C is : " << endl;
	for (int i = 0; i < l; i++)
	{
		for (int j = 0; j < l; j++)
		{
			cout << setw(3) << c[i][j] << "  ";
			if (j == l - 1)
			{
				cout << endl;
			}
		}
	}
	cout << "matrix R is : " << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			cout <<setw(5) <<r[i][j]<<"  ";
			if (j==n-1)
			{
				cout << endl;
			}
		}
	}
	for (int i = 0; i < m; i++)
	{
		delete[]a[i];
	}
	for (int i = 0; i < l; i++)
	{
		delete[]c[i];
	}
	for (int i = 0; i < m; i++)
	{
		delete[]r[i];
	}
	return 0;
}