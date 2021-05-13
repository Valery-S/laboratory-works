#include<vector>
#include <iostream>
#include "Matrix.h"
#include "equation.h"
using namespace std;

//Метод для вывода вектора.
void print_vector(vector<double> vec){
  for (double v : vec){
   cout<<Yellow << setprecision(7) <<v<<"\n";
  }
  cout <<"\n";
}

//Метод для вывода матрицы
void print_matrix(matrix m) {
  for (int i = 0; i < m.n; i++){
    for (int j = 0; j < m.n; j++){
      cout << Yellow << m.a[i][j] << "\t";
    }
    cout << "\n";
  }
}

//Метод для вывода числа с учётом знака
void print_with_sign(double a) {
  if (a<0){
    cout << Yellow << a;
  }
  else {
    cout << Yellow << "+" << a;
  }
}

//Метод для вывода уравнения в консоль.
void print_equation(equation eq) {
  cout << Yellow << "z^4 ";
  print_with_sign(eq.coefficients[0]);
  cout << " * z^3 ";
  print_with_sign(eq.coefficients[1]);
  cout << " * z^2 ";
  print_with_sign(eq.coefficients[2]);
  cout << " * z ";
  print_with_sign(eq.coefficients[3]);
  cout << " = 0\n";
}