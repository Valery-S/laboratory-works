#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<iomanip>
using namespace std;
struct Graph {
	int quantity=0;//колличество городов
	double length = 0;//длина пути
	vector<vector<double>>distance;//таблица расстояний 
	vector<int>way;//путь 
	vector<vector<double>>assessment;//оценка нулевых клеток
	void print_matrix() {
		for (int j = 0; j < quantity; j++){
			for (int i = 0; i < quantity; i++){
				cout << setw(5)<<distance[j][i];
			}
			cout << endl;
		}
	}
	
};
Graph read(string file_name) {//Функция чтения данных из файла
	cout << endl  << "Режим чтения" << endl;
	Graph gr;
	ifstream in;
	in.open(file_name);//открываем файл на чтение
	if (!in)//проверка на корректность файла
	{
		if (in.eof()){
			cout << "Файл пуст" << endl;
			exit(-1);
		}
		else{
			cout << "Неверное имя файла" << endl;
			exit(-1);
		}
	}
	if (in.is_open()) {
		int num;
		in >> num;
		vector<vector<double>> input_data;
		vector<double>string(num);
		//vector<double>a(num);
		for (int i = 0; i < num; i++) {
			for (int j = 0; j < num; j++) {
				in >> string[j];//cчитывем данные i-той строки
				//a[i] = 0;
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
Graph step(Graph gr,int p) {
	vector<vector<double>>buf;
	buf = gr.distance;
	cout << "Выполняется шаг " << p << endl << endl << "Матрица на данном этапе " << endl;
	gr.print_matrix();
	cout << endl;
	//вычисление минимума в строке
	vector<double>min_str(gr.quantity);
	for (int i = 0; i < gr.quantity; i++)
	{
			int k = 0;
			while (gr.distance[i][k] == -1  && k<gr.quantity-1) { k++; }
			if (k == 0) { min_str[i] = gr.distance[i][0]; }
			if (k != 0) { min_str[i] = gr.distance[i][k]; }
			//проверка на то, что строка не вычерктнута
			double res = 0;
			for (int j = 0; j < gr.quantity; j++){res = res+gr.distance[i][j];}
			if (res==gr.quantity*(-1.0)){min_str[i] = 0;}
			
			for (int j = k; j < gr.quantity; j++){
				if (gr.distance[i][j] < min_str[i] && gr.distance[i][j] != -1) { min_str[i] = gr.distance[i][j]; }
			}
			
	}
	cout << "Мининумы в строках "<<endl;
	for (int i = 0; i < gr.quantity; i++){cout << min_str[i]<<" ";}
	cout << endl<<endl;
	//редукция матрицы по строкам
	for (int i = 0; i < gr.quantity; i++){
		for (int j = 0; j < gr.quantity; j++){
			if (gr.distance[i][j]!=-1){gr.distance[i][j] = gr.distance[i][j] - min_str[i];}
		}
	}
	cout << "Редукция матрицы по строкам." << endl << "Матрица на данном этапе " << endl;
	gr.print_matrix();
	cout << endl ;
	//вычисление минимума по столбцам
	vector<double>min_column(gr.quantity);
	for (int i = 0; i < gr.quantity; i++){
		int k = 0;
		while (gr.distance[k][i] == -1 && k < gr.quantity - 1) { k++; }
		if (k == 0) { min_column[i] = gr.distance[0][i]; }
		if (k != 0) { min_column[i] = gr.distance[k][i]; }
		//проверка на то, что столбец не вычеркнут
		double res = 0;
		for (int j = 0; j < gr.quantity; j++) {res = res + gr.distance[j][i];}
		if (res == gr.quantity * (-1.0)) { min_column[i] = 0; }

		for (int j = k; j < gr.quantity; j++){
			if (gr.distance[j][i] < min_column[i] && gr.distance[j][i] != -1) { min_column[i] = gr.distance[j][i]; }
		}
	}
	cout << "Мининумы с столбцах"<<endl;
	for (int i = 0; i < gr.quantity; i++){
		cout << min_column[i] << " ";
	}
	cout << endl << endl;
	//редукция матрицы по столбцам
	for (int i = 0; i < gr.quantity; i++){
		for (int j = 0; j < gr.quantity; j++){
			if (gr.distance[i][j] != -1) { gr.distance[i][j] = gr.distance[i][j] - min_column[j]; }
		}
	}
	cout << "Редукция матрицы по столбцам." << endl<< "Матрица на данном этапе " << endl;
	gr.print_matrix();
	cout << endl ;
	//Нахождение нулевых клеток
	vector<int> zero_x;
	vector<int> zero_y;
	for (int i = 0; i < gr.quantity; i++){
		for (int j = 0; j < gr.quantity; j++){
			if (gr.distance[i][j] == 0) { zero_x.push_back(i); zero_y.push_back(j); }
		}
	}
	//Поиск минимума в столбцах и строках с нулевыми клетками
	vector<double>min_str_zero(size(zero_x));
	vector<double>min_col_zero(size(zero_x));
	for (int i = 0; i < size(zero_x); i++) {
		min_str_zero[i] = DBL_MAX;
		int r = zero_x[i];
		for (int j = 0; j < zero_y[i]; j++){
			if (gr.distance[r][j] < min_str_zero[i] && gr.distance[r][j] != -1) { min_str_zero[i] = gr.distance[r][j]; }
		}
		for (int j = zero_y[i]+1; j < gr.quantity; j++) {
			if (gr.distance[r][j] < min_str_zero[i] && gr.distance[r][j] != -1) { min_str_zero[i] = gr.distance[r][j]; }
		}
		min_col_zero[i] = DBL_MAX;
		r = zero_y[i];
		for (int j = 0; j < zero_x[i]; j++)	{
			if (gr.distance[j][r] < min_col_zero[i] && gr.distance[j][r] != -1) { min_col_zero[i] = gr.distance[j][r]; }
		}
		for (int j = zero_x[i]+1; j < gr.quantity; j++) {
			if (gr.distance[j][r] < min_col_zero[i] && gr.distance[j][r] != -1) { min_col_zero[i] = gr.distance[j][r]; }
		}
	}
	//Поиск максимальной оценки нулевых клеток
	int c = 0, s = 0;
	double max_ass = 0;
	for (int i = 0; i < size(zero_x); i++){
		if (min_str_zero[i] == DBL_MAX) { min_str_zero[i] = 0; }
		if (min_col_zero[i] == DBL_MAX) { min_col_zero[i] = 0; }
		if (size(gr.way) > 0) {//если в пути есть города, то нужно проверить, что город из которого идем равен последнему записанному городу
			if (min_str_zero[i] + min_col_zero[i] >= max_ass && zero_x[i] == gr.way[size(gr.way) - 1] && zero_y[i] != gr.way[0]) {
				max_ass = min_str_zero[i] + min_col_zero[i];
				c = zero_y[i];
				s = zero_x[i];}
		}
		else {
			if (min_str_zero[i] + min_col_zero[i] > max_ass ) {
				max_ass = min_str_zero[i] + min_col_zero[i];
				c = zero_y[i];
				s = zero_x[i];}
		}
	}
	if (size(gr.way) == 0) {
		gr.way.push_back(s);//добавляем в путь город s, из которого идем 
		gr.way.push_back(c);//добавляем в путь город с, в который идем 
		gr.distance[s][c] = -1;//вычеркиваем клетку, что бы ей больше не пользоваться
		gr.distance[c][s] = -1;//вычеркиваем противоположную клетку
	}else {
		gr.way.push_back(c);//добавляем в путь город с, в который идем 
		gr.distance[s][c] = -1;//вычеркиваем клетку, что бы ей больше не пользоваться
		gr.distance[c][s] = -1;//вычеркиваем противоположную клетку
	}
	if (size(gr.way) == gr.quantity) { gr.way.push_back(gr.way[0]);}
	cout<<"Путь на данный момент"<<endl;
	for (int i = 0; i < size(gr.way); i++){cout << gr.way[i]+1<<" ";}
	cout << endl;
	//уничтожение из таблицы расстояний городов s и с 
	for (int i = 0; i < gr.quantity; i++) {
		gr.distance[s][i] = -1;
		gr.distance[i][c] = -1;}
	//возвращение невычеркнутым клеткам изначального значения
	for (int i = 0; i < gr.quantity; i++){
		for (int j = 0; j < gr.quantity; j++){
			if (gr.distance[i][j] != -1) { gr.distance[i][j] = buf[i][j]; }
		}
	}
	cout << endl;
	cout << "Выполнен шаг "<<p<<endl;
	return gr;
}
int main() {
	double start = clock();
	setlocale(LC_ALL, "RUS");
	cout << "Введите имя файла для чтения данных" << endl;
	string file_name;
	cin >> file_name;
	Graph gr;
	gr = read(file_name);
	vector<vector<double>>distance;
	distance = gr.distance;
	int i = 1;
	while (size(gr.way) != gr.quantity+1 ){
		gr = step(gr, i);
		i++;}
	cout << "Лучший путь "<<endl;
	for (int i = 0; i < gr.quantity; i++) {
		gr.length = gr.length + distance[gr.way[i]][gr.way[i + 1]];
		cout << gr.way[i]+1 << " ";}
	cout << gr.way[gr.quantity]+1;
	cout << endl<<"Лучшая длина пути = "<<gr.length<<endl << "time=" << (clock() - start) / CLOCKS_PER_SEC;
	return 0;
}