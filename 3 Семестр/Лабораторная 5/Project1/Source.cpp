#include "MyList.h"
#include<iostream>
using namespace std;
//--������� ��� �������� ����� ����
template <typename T>
int List_sum(List<T> list) {
	int sum = 0;
	for (int i = 0; i < list.get_size(); i++){
		sum = sum + list[i];
	}
	return sum;
}
//---���������� ��������� << ��� ������ ������
template <typename T>
ostream& operator<<(ostream& os, List<T> list) {
	for (int i = 0; i < list.get_size(); i++) {
		os << list[i] << "   ";
	}
	os << endl;
	return os;
}
int main(){
	setlocale(LC_ALL, "ru");//��������� �������� �����
	int N = 0;				//���������� ������
	int max_mass=0;			//����� ������������� �����
	int mass = 0;			//����� �������� � ����� �����
	int max_mass_index = 0;	//����� ����� � ������������ ������
	List<float> L_mass;		//����� ������
	List<int> first_index;	//������ ������ ������ ����
	List<int> second_index;	//������ ������ ������ ����
	List<float>first_mass;	//����� ������ � ������ ����
	List<float>second_mass;	//����� ������ �� ������ ����
	//---��������� � ��������� �������� ������
	cout << "������� ���������� ������" << endl;
	cin >> N;
	if (N<=0){
		cout << "������������ ���������� ������" << endl;
		exit(-1);
	}
	for (int i = 0; i < N; i++){
		cout<<endl << "������� ����� "<<i<<"   ����� " << endl;
		cin >> mass;
		if (mass < 0) {
			cout << "������������ ����� �����" << endl;
			exit(-1);
		}
		if (mass>max_mass){
			max_mass = mass;
			max_mass_index = i;
		}
		L_mass.push_back(mass);
	}
	//---���������� ����� � ������������ ������ � ������ ����
	first_mass.push_back(max_mass);
	first_index.push_back(max_mass_index);
	//---��������� ���������� ������
	for (int i = 1; i < L_mass.get_size(); i++){
		int sum1 = List_sum(first_mass);
		int sum2 = List_sum(second_mass);
		if (sum2 >= sum1) {
			first_mass.push_back(L_mass[i]);
			first_index.push_back(i);
		}
		else {
			second_mass.push_back(L_mass[i]);
			second_index.push_back(i);
		}
	}
	//-----��������� ���������� ����
	int sum1 = List_sum(first_mass);
	int sum2 = List_sum(second_mass);
	int max_sum = sum1;
	int min_sum = sum2;
	if (sum2 > max_mass) {
		max_mass = sum2;
		min_sum = sum1;
	}
	//--����� ����������
	if (min_sum*2<=max_sum){
		cout << "����� ����� ��������� �� ����, �������� �������." << endl
			<< "������ ������ � ������ ����: " << first_index
			<< "����� ������ � ������ ����: " << first_mass
			<< "����� ������ ����: " << List_sum(first_mass)<<endl
			<< "������ ������ �� ������ ����: " << second_index
			<< "����� ������ �� ������ ����: " << second_mass
			<< "����� ������ ����: " << List_sum(second_mass)<<endl;
	}
	else {
		cout << "����� ������ ��������� �� ����, �������� �������." << endl;
	}
	return 0;
}