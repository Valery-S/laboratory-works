#include "MyList.h"
#include<iostream>
using namespace std;
int main() {
	setlocale(LC_ALL, "ru");		//Включение русского языка
	int col=0,str=0;			//Количество строк и стобцов в матрице
	List<int> AD, AU, AL, LJ, LI;	//Списки, отвечающие за хранение данных 
//об элементах матрицы
	List <int>LJ_2;			//Список для проверки того, что матрица 
//является структурно симметричной
	int element;				//Элемент матрицы
	List<int> different;		//Список для хранения Различных 
//элементов матрицы
	cout << "Введите количество строк"<<endl;
	cin >> str;
	cout << "Введите количество столбцов" << endl;
	cin >> col;
							//Обработка введённых данных
	if (str == 0 || col == 0) {
		cout<<"Неверно заданы размеры матрицы."<<endl;
		exit(-1);
	}
	if (str!=col){
cout << "Количетство строк не совпадает с количеством столбцов" 
    "Матрица не явлется структурно-симметричной" << endl;
		exit(-1);
	}

							//Ввод элементов матрицы - заполнение 
//списков
	cout << "Введите элементы матрицы." << endl;
	for (int i = 0; i < str; i++){
int flag = 0;		//Показывает встречался ли ненулевой
//элемент в этой строке верхней части //матрицы, используется для заполнения //списка LI
		for (int j = 0; j <col; j++){
			cin >> element;
			if (element != 0 && i < j) { flag++; }
			if (i == j) { AD.push_back(element);}
			if (element != 0 && i < j) {
				AU.push_back(element);
				LJ.push_back(j+1);
			}
			if (element != 0 && i > j) {
				AL.push_back(element); 
				LJ_2.push_back(i + 1);
			}
			if (flag == 1 ) {
				LI.push_back(AU.get_size());
				flag = 2;
			}
							//Если мы находимся в верхней части 
//матрицы, дошли до конца строки и не 
//встретили ненулевого элемента, то //"пропускаем" клетку в списке LI
			if (flag == 0 && i < j && j==col-1) {
LI.push_back(0); 
}
		}
	}
							//Обработка "Пропущенных" клеток в 
//списке LI. Если "Пропущена" последняя //клетка, записываем в неё количество //ненулевых элементов+1
	if (LI[LI.get_size() - 1] == 0) { 
LI[LI.get_size() - 1] = AU.get_size() + 1; 
}
	for (int i = 0; i < LI.get_size() -1; i++){
		if (LI[i] == 0) {
			int p = 0;
							//Находим первую не нулевую клетку
//после серии нулей и переносим это //значение на нулевые клетки
			for (int j = i; j < LI.get_size() - 2; j++) {
				if (LI[j + 1] != 0) {
p = LI[j + 1];
}
			}
			LI[i] = p;
		}
	}
	//Проверка на то, что матрицы ялвяется структурно-симметричной
	if (LJ_2.get_size() == LJ.get_size()) {
		int flag = 0;
		for (int i = 0; i <LJ.get_size(); i++){
			if (LJ_2[i] != LJ[i]) { flag = 1; }
		}
		if (flag == 0) {
			cout << endl << "Матрица структурно-симметричная"<<endl;
			cout << "Сформированный список AD: " << endl;
			for (int i = 0; i < AD.get_size(); i++) { 
cout << AD[i] << "     "; 
}
			cout << endl << "Сформированный список AU: " << endl;
			for (int i = 0; i < AU.get_size(); i++) { 
cout << AU[i] << "     "; 
}
			cout << endl << "Сформированный список AL: " << endl;
			for (int i = 0; i < AL.get_size(); i++) { 
cout << AL[i] << "     "; 
}
			cout << endl << "Сформированный список LJ: " << endl;
			for (int i = 0; i < LJ.get_size(); i++) { 
cout << LJ[i] << "     "; 
}
			cout << endl << "Сформированный список LI: " << endl;
			for (int i = 0; i < LI.get_size(); i++) {
 cout << LI[i] << "     "; 
}
		}
		else{ 
cout << endl << "Матрица не является структурно-
			  симметричной" << endl;
exit(-1);
}
	}
	else {
cout << endl << "Матрица не является структурно-
  симметричной"<<endl;
		exit(-1);
}
							//Поиск различных элементов в массиве
	different.push_back(AD[0]);
	for (int i = 1; i < AD.get_size() -1; i++) {
		int flag = 0;
		for (int j = 0; j < different.get_size() - 1; j++) {
			if (different[j] == AD[i]) { 
flag = 1; 
}
		}
		if (flag == 0) { 
different.push_back(AD[i]); 
}
	}
	for (int i = 0; i < AU.get_size() -1; i++) {
		int flag = 0;
		for (int j = 0; j < different.get_size() -1; j++) {
			if (different[j] == AU[i]) { 
flag = 1; 
}
		}
		if (flag == 0) { 
different.push_back(AU[i]); 
}
	}
	for (int i = 0; i < AL.get_size() -1; i++) {
		int flag = 0;
		for (int j = 0; j < different.get_size() -1; j++) {
			if (different[j] == AL[i]) { 
flag = 1; 
}
		}
		if (flag == 0) { 
different.push_back(AL[i]); 
}
	}
	//Вывод различных элементов
	cout <<"Количетство разлиных элементов: "<<different.get_size()
 <<endl<< "Различные элементы массива:" << endl;
	for (int j = 0; j < different.get_size() -1; j++) {
cout << different[j]<<"   ";
}
	cout << endl;
	return 0;
}
