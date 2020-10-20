#include "MyList.h"
#include<iostream>
using namespace std;
//--Функция для подсчёта массы кучи
template <typename T>
int List_sum(List<T> list) {
	int sum = 0;
	for (int i = 0; i < list.get_size(); i++){
		sum = sum + list[i];
	}
	return sum;
}
//---Перегрузка оператора << для вывода списка
template <typename T>
ostream& operator<<(ostream& os, List<T> list) {
	for (int i = 0; i < list.get_size(); i++) {
		os << list[i] << "   ";
	}
	os << endl;
	return os;
}
int main(){
	setlocale(LC_ALL, "ru");//Включение русского языка
	int N = 0;				//Количество камней
	int max_mass=0;			//Масса максимального камня
	int mass = 0;			//Масса текущего в цикле камня
	int max_mass_index = 0;	//Номер камня с максимальной массой
	List<float> L_mass;		//Массы камней
	List<int> first_index;	//Номера камней первой кучи
	List<int> second_index;	//Номера камней второй кучи
	List<float>first_mass;	//Массы камней в первой куче
	List<float>second_mass;	//Массы камней во второй куче
	//---Получение и обработка исходных данных
	cout << "Введите количество камней" << endl;
	cin >> N;
	if (N<=0){
		cout << "Некорректное количество камней" << endl;
		exit(-1);
	}
	for (int i = 0; i < N; i++){
		cout<<endl << "Введите массу "<<i<<"   камня " << endl;
		cin >> mass;
		if (mass < 0) {
			cout << "Некорректная масса камня" << endl;
			exit(-1);
		}
		if (mass>max_mass){
			max_mass = mass;
			max_mass_index = i;
		}
		L_mass.push_back(mass);
	}
	//---Добавление камня с максимальной массой в первую кучу
	first_mass.push_back(max_mass);
	first_index.push_back(max_mass_index);
	//---Обработка оставшихся камней
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
	//-----Обработка полученных масс
	int sum1 = List_sum(first_mass);
	int sum2 = List_sum(second_mass);
	int max_sum = sum1;
	int min_sum = sum2;
	if (sum2 > max_mass) {
		max_mass = sum2;
		min_sum = sum1;
	}
	//--Вывод результата
	if (min_sum*2<=max_sum){
		cout << "Камни можно разделить на кучи, соглачно условию." << endl
			<< "Номера камней в первой куче: " << first_index
			<< "Массы камней в первой куче: " << first_mass
			<< "Масса первой кучи: " << List_sum(first_mass)<<endl
			<< "Номера камней во второй куче: " << second_index
			<< "Массы камней во второй куче: " << second_mass
			<< "Масса второй кучи: " << List_sum(second_mass)<<endl;
	}
	else {
		cout << "Камни нельзя разделить на кучи, соглачно условию." << endl;
	}
	return 0;
}