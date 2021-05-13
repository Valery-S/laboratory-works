#pragma once
#include<vector>
#include <algorithm> 
#include<iostream>
using namespace std;

double const E = 0.001;

//����� ��������� ��������� �������.
struct equation {
	vector<double>coefficients;

	//����� ��� ������� ������������
	void setCoefficients(vector<double> coeff){
		for (int i = 0; i < coeff.size(); i++){
			this->coefficients.push_back(coeff[i]);
		}
	}


	//����� ��� ��������� �������� ������� � �������� �����
	double getValueAtX(double x){
		double res;
		res=pow(x, 4) + coefficients[0] * pow(x, 3) + coefficients[1] * pow(x, 2) +coefficients[2] * x + coefficients[3];
		return res;
	}


	//����� ��� ��������� ���������� ����� ������ �������.
  vector<vector<double>> getIntervals(){
		vector<double> x_vector;
		vector<double> y_vector;

		//������ �������� ����� �� -100 �� 100
		for (double i = -100.0; i <= 100; i++){
			x_vector.push_back(i);
		}

		//�������� �������� ������ � ������ ����� ���������
		//�� -100 �� 100
		for (int i=0; i < x_vector.size(); i++){
			y_vector.push_back(getValueAtX(x_vector[i]));
		}

		//� �������������� ��� ������� ������� ������ ����
		vector<double> new_vector;
		for (int i = 0; i < y_vector.size() - 1; i++){
			if (y_vector[i] * y_vector[i + 1] < 0){
					new_vector.push_back(x_vector[i]);
					new_vector.push_back(x_vector[i+1]);
			}
		}

		//���������� �� �����������
		sort(new_vector.begin(), new_vector.end());

		//���������� �� ����� ���������� ��������
		vector<vector<double>> cord_vector;
		for (int i = 0; i < new_vector.size(); i = i + 2) {
			vector<double> temp;
			temp.push_back(new_vector[i]);
			temp.push_back(new_vector[i + 1]);
			cord_vector.push_back(temp);
		}

		return cord_vector;
  }



	//����� ��� ��������� ������� ������� ��������.
	vector<double> Bisection() {
		vector<double> res;

		//��������, ��� �������� X(i-1) - ����� ���������� �� ����. ��������
		double prev_value ;

		//���������� ��� �������� �������� Xi
		double xI;

		//��������� ������ ���������� ������������, ������� �������� �������
		vector<vector<double>> intervals = this->getIntervals();

		//������ �� ������� ��������� [a;b]
		double a, b;
		for (int i = 0; i < intervals.size(); i++){
			prev_value = -DBL_MAX;
			xI = DBL_MAX;			
			a = intervals[i][0];
			b = intervals[i][1];
			//���� ������� �������� � ����������� �������� ������
			//������������� ����������� E=0.001, ��������� ����� ��������
			while (abs(prev_value - xI) > E) {
				prev_value = xI;
				xI = (a + b) / 2.0;
				//���� �������� ������ ��� Xi � ��� X = a ����� ������ �����,
				//�� ������ b �� ���������� [a;b] �� Xi
				//����� ������ a �� Xi
				if (this->getValueAtX(xI) * this->getValueAtX(a) < 0){
					b = xI;
				}
				else{
					a = xI;
				}
			}
			//���������� ���������� ����� � �������������� ������
			res.push_back(xI);
		}
		return res;
	}
};