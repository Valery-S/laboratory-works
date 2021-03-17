#include "Work_with_Letters.h"
#include "binary_tree.h"
using namespace std;

int main() {
	string file_name;		//Имя исходного файла
	vector<char>data;		//Вектор для хранения информации исходного файла
	vector<char>letters;		//Вектор уникальных символов в файле
	vector<int>count;		//Вектор, хранящий количество уникальных символов в файле
	vector<Node*>node_vector;	//Вектор узлов дерева
	map<char, vector<bool>> table;	//Таблица, хранящая код закодированного символа
	Node* root;			//Указатель на корень дерева
	ifstream input;			//Указатель на исходный файл
	ofstream out;			//Указатель на конечный файл
	setlocale(LC_ALL, "Russian");	//Включение русского языка в консоли

	//Запрос имени исходного файла
	cout<<Yellow << "Данная программа предназначена для сжатия файлов методом Хаффмана.\n"
			<< "Введите имя файла, который нужно сжать.\n"<<Blue;
	cin >> file_name;
	input.open(file_name);
	
	//Чтение данных из файла
	data = read_from_file(input);
	//Поиск уникальных символов 
	letters = find_unique_letters(data);
	//Подсчёт количества каждого символа 
	count = counting_letters(data,letters);
	//Создание вектора узлов
	node_vector = create_vector(count,letters);
	//Создание дерева символов
	create_tree(&node_vector);
	//Получение ссылки на корень дерева
	root = node_vector.front();
	//Создание таблицы кодов символов
	table = create_table(root);

	//Вывод информации в консоль
	cout<<Yellow << "Количество уникальных символов в тексте " << letters.size() << "\n";
	for (int i = 0; i < letters.size(); i++){
		cout<<Green << letters[i] << " встречается " << count[i] << " раз\n";
	}
	print_map_to_console(table);
	
	//Вывод информации в сжатый файл
	out.open("output.bin");
	write_to_compressed_file(out, data, table);
	
	input.close();
	out.close();
	cout << Reset;
	return 0;
}
