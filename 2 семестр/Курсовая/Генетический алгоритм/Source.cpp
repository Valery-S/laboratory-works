#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <ctime>
using namespace std;
struct Graph {
	int quantity = 0;//колличество городов
	int length = 0;//длина пути
	vector<vector<double>>distance;//таблица расстояний 
	vector<int>individual_f;//особь 1
	vector<int>individual_s;//особь 2
	vector<int>individual_t;//особь 3
};
Graph read(string file_name) {//Функция чтения данных из файла
	cout  << "Режим чтения" << endl;
	Graph gr;
	vector<vector<double>> input_data;
	ifstream in;
	in.open(file_name);//открываем файл на чтение
	if (!in)//проверка на корректность файла
	{
		if (in.eof()) {
			cout << "Файл пуст" << endl;
			exit(-1);
		}
		else {
			cout << "Неверное имя файла" << endl;
			exit(-1);
		}
	}
	if (in.is_open()) {
		int num;
		in >> num;
		vector<double>string(num);
		vector<double>a(num);
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				in >> string[j];//cчитывем данные i-той строки
				a[i] = 0;
			}
			input_data.push_back(string);//записываем данные в таблицу расстояний
		}
		gr.quantity = num;//записываем количество городов
		gr.distance = input_data;//переписываем даные расстояний
		cout << "Данные считаны" << endl;
	}
	in.close();
	return gr;
}
Graph choose_f(Graph gr) {//выбор особи 1
	srand((unsigned)time(NULL));//изменение начального значения ГПСЧ 
	gr.individual_f.resize(gr.quantity + 1);//устанавливаем размер "особи"
	for (int i = 0; i < gr.quantity; i++) { gr.individual_f[i] = -1; }
	bool flag = false;
	int k = 0;//число городов в "особи"
	int j = 0;//переменная, в которую будет записываться псевдослучайное число
	while (k < gr.quantity) {
		j = rand() % gr.quantity;
		if (k == 0) {//если в особи еще нет ни одного города
			gr.individual_f[k] = j;
			k++;}
		else {//если в особи есть хотя бы 1 город
			if (gr.distance[gr.individual_f[k - 1]][j] != -1) {//если расстояние между последним и сгенерированным городом не равно -1 
				for (int i = 0; i < gr.quantity; i++)
				{
					if (gr.individual_f[i] == j) {//проверяем есть ли в особи город j
						flag = true;
						break;
					}
					else { flag = false; }
				}
				if (flag == false) { gr.individual_f[k] = j; k++; }//если город j в особи не обнаружен, то добавляем его
			}
		}
	}
	return gr;
}
Graph choose_s(Graph gr) {//выбор особи 2
	srand((unsigned)time(NULL) * 2);//изменение начального значения ГПСЧ для того, чтобы особи были разные
	gr.individual_s.resize(gr.quantity + 1);
	for (int i = 0; i < gr.quantity; i++) { gr.individual_s[i] = -1; }
	int k = 0, j;
	bool flag = false;
	while (k < gr.quantity) {
		j = rand() % gr.quantity;
		if (k == 0) {//если в особи еще нет ни одного города
			gr.individual_s[k] = j;
			k++;}
		else {//если в особи есть хотя бы 1 город
			if (gr.distance[gr.individual_s[k - 1]][j] != -1) {//если расстояние между последним и сгенерированным городом не равно -1 
				for (int i = 0; i < gr.quantity; i++)
				{
					if (gr.individual_s[i] == j) {//проверяем есть ли в особи город j
						flag = true;
						break;
					}
					else { flag = false; }
				}
				if (flag == false) { gr.individual_s[k] = j; k++; }//если город j в особи не обнаружен, то добавляем его
			}
		}
	}
	return gr;
}
Graph choose_t(Graph gr) {//выбор особи 3
	srand((unsigned)time(NULL)*3);//изменение начального значения ГПСЧ для того, чтобы особи были разные
	gr.individual_t.resize(gr.quantity + 1);
	for (int i = 0; i < gr.quantity; i++) { gr.individual_t[i] = -1; }
	int k = 0, j;
	bool flag = false;
	while (k < gr.quantity) {
		j = rand() % gr.quantity;
		if (k == 0) {//если в особи еще нет ни одного города
			gr.individual_t[k] = j;
			k++;}
		else  {//если в особи есть хотя бы 1 город
			if (gr.distance[gr.individual_t[k - 1]][j] != -1) {//если расстояние между последним и сгенерированным городом не равно -1 
				for (int i = 0; i < gr.quantity; i++)
				{
					if (gr.individual_t[i] == j) {//проверяем есть ли в особи город j
						flag = true;
						break;
					}
					else { flag = false; }
				}
				if (flag == false) { gr.individual_t[k] = j; k++; }//если город j в особи не обнаружен, то добавляем его
			}
		}
	}
	return gr;
}
Graph choose(Graph gr) {//выбор трех особей
	gr = choose_f(gr);// выбор особи
	gr.individual_f[gr.quantity] = gr.individual_f[0];//запись в последнюю ячейку первого города
	// если расстояние между последним и предпоследним городом равно -1, то нужно перевыбрать особь 
	while (gr.distance[gr.individual_f[gr.quantity]][gr.individual_f[gr.quantity - 1]] == -1) {
		gr = choose_f(gr);
		gr.individual_f[gr.quantity] = gr.individual_f[0];}
	gr = choose_s(gr);
	gr.individual_s[gr.quantity] = gr.individual_s[0];
	while (gr.distance[gr.individual_s[gr.quantity]][gr.individual_s[gr.quantity - 1]] == -1) {
		gr = choose_s(gr);
		gr.individual_s[gr.quantity] = gr.individual_s[0];}
	gr = choose_t(gr);
	gr.individual_t[gr.quantity] = gr.individual_t[0];
	while (gr.distance[gr.individual_t[gr.quantity]][gr.individual_t[gr.quantity - 1]] == -1) {
		gr = choose_t(gr);
		gr.individual_t[gr.quantity] = gr.individual_t[0];}
	return gr;
}
Graph mutation(Graph gr,int& flag) {//мутация наилучшей особи
	double sum_s = 0, sum_f = 0, sum_t = 0,Sum=0,sum_n=0,sum_max=0,max1 = 0, max2 = 0;
	int k=1,n=1,max1_s=0,max2_s=0;
	vector<int>new_individual(gr.quantity+1);//новая особь
	for (int i = 0; i < gr.quantity; i++){
		sum_f = sum_f + gr.distance[gr.individual_f[i]][gr.individual_f[i + 1]];//подсчет длины пути 1 
		sum_s = sum_s + gr.distance[gr.individual_s[i]][gr.individual_s[i + 1]];//подсчет длины пути 2 
		sum_t = sum_t + gr.distance[gr.individual_t[i]][gr.individual_t[i + 1]];//подсчет длины пути 3
	}
	//выбор наилучшего пути
	Sum = sum_f;
	if (sum_s < Sum) { Sum = sum_s; k = 2; }
	if (sum_t < Sum) { Sum = sum_t; k = 3; }
	//выбор наихудшего пути
	sum_max = sum_f;
	if (sum_s > sum_max) { sum_max = sum_s; n = 2; }
	if (sum_t >sum_max) { sum_max = sum_t; n = 3; }
	//расстановка особей в порядке возрастания длины пути
	if (k == 1 && n == 2) {
		double buf_i;
		vector<int>buf(gr.quantity + 1);
		buf_i = sum_s;
		buf = gr.individual_s;
		sum_s = sum_t;
		gr.individual_s = gr.individual_t;
		gr.individual_t = buf;
		sum_t = buf_i;}
	if (k == 2 && n == 3) {
		double buf_i;
		vector<int>buf(gr.quantity + 1);
		buf = gr.individual_s;
		buf_i = sum_s;
		gr.individual_s = gr.individual_f;
		sum_s = sum_f;
		gr.individual_f = buf;
		sum_f = buf_i;}
	if (k == 2 && n == 1) {
		double buf_i;
		vector<int>buf(gr.quantity + 1);
		buf_i = sum_f;
		buf = gr.individual_f;
		gr.individual_f = gr.individual_t;
		sum_f = sum_t;
		gr.individual_t = buf;
		sum_t = buf_i;
		buf = gr.individual_f;
		buf_i = sum_f;
		gr.individual_f = gr.individual_s;
		sum_f = sum_s;
		gr.individual_s = buf;
		sum_s = buf_i;}
	if (k == 3 && n == 1){
		double buf_i;
		vector<int>buf(gr.quantity + 1);
		buf = gr.individual_f;
		buf_i = sum_f;
		gr.individual_f = gr.individual_t;
		sum_f = sum_t;
		gr.individual_t = buf;
		sum_t = buf_i;}
	if (k == 3 && n == 2){
		double buf_i;
		vector<int>buf(gr.quantity + 1);
		buf = gr.individual_s;
		buf_i = sum_s;
		gr.individual_s = gr.individual_t;
		sum_s = sum_t;
		gr.individual_t = buf;
		sum_t = buf_i;
		buf = gr.individual_f;
		buf_i = sum_f;
		gr.individual_f = gr.individual_s;
		sum_f = sum_s;
		gr.individual_s = buf;
		sum_s = buf_i;}
	gr.length = sum_f;//лучшая длина пути- длина пути первой особи
	//Мутация проиходит у той особи, длина пути которой меньше(первой), что бы достичь ещё меньшей длины. 
	//Она осуществляется по двум генам  с максимальным расстоянием между городами.
	//Если расстояние уменьшилось, то новая заменяет ту, у которой проводилась мутация.
	for (int i = 1; i < gr.quantity; i++){
		if (gr.distance[gr.individual_f[i]][gr.individual_f[i+1]]>max1){
			max1 = gr.distance[gr.individual_f[i]][gr.individual_f[i + 1]];
			max1_s = i;
		}
	}
	for (int i = 1; i < gr.quantity; i++) {
		if (gr.distance[gr.individual_f[i]][gr.individual_f[i + 1]] > max2 && gr.distance[gr.individual_f[i]][gr.individual_f[i + 1]] < max1) {
			max2 = gr.distance[gr.individual_f[i]][gr.individual_f[i + 1]];
			max2_s = i;
		}
	}
	new_individual = gr.individual_f;
	new_individual[max1_s] = new_individual[max2_s];
	new_individual[max2_s] = gr.individual_f[max1_s];
	for (int i = 0; i < gr.quantity; i++){sum_n = sum_n + gr.distance[new_individual[i]][new_individual[i + 1]];}//подсчет длины пути новой особи 
	//Если мутация прошла успешно т.е длина уменьшилась, то заменяем особь.
	//Иначе присваимаем переменной flag,преданной как параметр значение равное 0 - показатель неуспешной мутации
	if (sum_n < sum_f) { 
		gr.individual_f = new_individual;
		gr.length = sum_n;
		cout << "Мутация прошла успешно"<<endl;
		cout << "Лучший путь на данный момент" << endl;
		for (int i = 0; i < gr.quantity + 1; i++) { cout << gr.individual_f[i] + 1 << " "; }
		cout << endl << "лучшая длина пути на данный момент " << gr.length << endl << endl;
	}
	else {
		flag = 0;
		cout << "Мутация прошла неуспешно" << endl << endl;}
	return gr;
}

int main() {
	double start = clock();
	int flag=1;
	setlocale(LC_ALL, "RUS");
	cout << "Введите имя файла для чтения данных"<<endl;
	string file_name;
	cin >> file_name;
	Graph gr;
	gr = read(file_name);
	gr=choose(gr);
	cout << "сформированные особи:"<<endl;
	for (int i = 0; i < gr.quantity + 1; i++) { cout << gr.individual_f[i] + 1 << " "; }
	cout << endl;
	for (int i = 0; i < gr.quantity + 1; i++) { cout << gr.individual_s[i] + 1 << " "; }
	cout << endl;
	for (int i = 0; i < gr.quantity + 1; i++) { cout << gr.individual_t[i] + 1 << " "; }
	cout << endl<<endl;
	while (flag == 1) {
		gr = mutation(gr, flag);
	}
	cout << "Лучшая длина пути "<<gr.length << endl;
	cout << "Лучший путь " << endl;
	for (int i = 0; i < gr.quantity+1; i++){cout << gr.individual_f[i] + 1 << " " ;}
	cout << endl<<"time="<< (clock() - start) / CLOCKS_PER_SEC;
	return 0;
}