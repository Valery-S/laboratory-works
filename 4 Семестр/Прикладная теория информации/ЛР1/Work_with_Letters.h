#ifndef _Work_with_Letters_
#define _Work_with_Letters_
#include<string>
#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include <algorithm>
#include"binary_tree.h"
#include "colors.h"
using namespace std;

/*Фунция чтения из файла
* Параметры функции:
*		1)in - Ссылка на поток ввода
* Принцип работы:
*		1)Пока не дошли до конца файла:
			1.1)Получаем из него символ
			1.2)Записываем символ в вектор res
*/
vector<char> read_from_file(ifstream& in) {
	char tmp;
	vector<char>res;
	while (in.get(tmp)) {
		res.push_back(tmp);
	}
	return res;
}

/*Функция поиска уникальных символов в тексте
* Параметры функции:
*		1)data - Вектор всех символов
* Принцип работы:
*		1)Пока не дошли до конца вектора data
*			1.1)Проверяем есть ли в векторе res текущий символ
*			1.2)Если символ не встретился, то добавляем его в вектор res
*/
vector<char> find_unique_letters(vector<char> data) {
	vector<char> res;
	for (int i = 0; i < data.size(); i++) {
		bool flag = false;
		for (int k = 0; k < res.size(); k++) {
			if (res[k] == data[i]) { flag = true; }
		}
		if (flag == false) { res.push_back(data[i]); }
	}
	return res;
}

/*Функция подсчёта количества каждого уникального символа
* Параметры функции:
*		1)data - Вектор всех символов
*		2)letters - Вектор уникальных символов
*	Принцип работы:
*		1)Пока не дошли до конца вектора data 
*			1.1)Пока не дошли до конца вектора letters
*				1.1.1)Если текущий символ  в векторе letters совпадает с символом,рассматриваемым
*							в векторе data,то прибавляем 1 к количеству данного символа.
*/
vector<int> counting_letters(vector<char>data, vector<char>letters) {
	vector<int> res(letters.size());
	for (int i = 0; i < letters.size(); i++) {
		for (int j = 0; j < data.size(); j++) {
			if (data[j] == letters[i]) { res[i] = res[i] + 1; }
		}
	}
	return res;
}
/*Функция создания вектора узлов
* Параметры функции:
*		1)count- вектор количества символов
*		2)letters- вектор уникальных символов
* Принцип работы:
*		1)Для каждого символа создаётся узел с полями "символ" и "количество"
*/
vector<Node*> create_vector(vector<int>count, vector<char>letters) {
	vector<Node*>res;
	for (int i = 0; i < letters.size(); i++){
		Node* n = new Node;
		n->count = count[i];
		n->letter = letters[i];
		res.push_back(n);
	}
	return res;
}

/*Функция создания дерева из списка узлов
* Параметры функции:
*		1)*v- Указатель на вектор
* Принцип работы:
*		1)Пока в векторе находятся больше одного узла
*			1.1)Сортируем список в порядке увеличения числа, находящегося в узле
*			1.2)Создаём левого потомка из первого узла в векторе
*			1.3)Удаляем первый узел
*			1.4)Создаём правого потомка из первого узла в векторе
*			1.5)Удаляем первый узел
*			1.6)Создаём узел родителя и добавляем его в вектор
*/
void create_tree(vector<Node*>* v) {
	while ((*v).size() != 1) {

		sort((*v).begin(),(*v).end(),compare);
		Node* left = (*v).front();
		(*v).erase((*v).begin());
		Node* right = (*v).front();
		(*v).erase((*v).begin());
		Node* parent = new Node(left, right);
		parent->left->parent = parent;
		parent->right->parent = parent;
		(*v).push_back(parent);
	}
}

/*Функция создания таблицы кодов символов
* Параметры функции:
*		1)*root -указатель на корень дерева
* Принцип работы:
*		1)Если у узла есть левый сын,то в вектор code добавляется ноль
*			и вызывается функция с параметром, равным левому сыну
*		2)Если у узла есть праый сын,то в вектор code добавляется единица
*			и вызывается функция с параметром, равным правому сыну
*		3)Если у узла нет сыновей, то в таблицу table добавляется новая строка с текущим кодом и символом
*		4)Если У узла есть родитель, то удаляем посленее число из вектора code(поднимаемся на уровень выше)
*/
vector<bool> code;
map<char, vector<bool>> table;
map<char, vector<bool>> create_table(Node* root) {
	if (root->left != NULL) {
		code.push_back(0);
		create_table(root->left);
	}
	if (root->right != NULL) {
			code.push_back(1);
			create_table(root->right);
	}
	if (root->left == NULL && root->right == NULL) {
		table[root->letter] = code;
		
	}
	if (root->parent != NULL) {
		code.pop_back();
	}
	return table;
}

/*Функция вывода таблицы кодов в консоль
* Параметры функции:
*		1)table- таблица кодов символов
*/
void print_map_to_console(map<char, vector<bool>>table) {
	cout<<Yellow << "\n\nСимволы закодированы. Их коды: \n";
	for (auto it = table.begin(); it != table.end(); ++it) {
		cout<<Green << it->first << " : ";
		for (int i = 0; i < it->second.size(); i++) {
			cout << it->second[i];
		}
		cout << "\n";
	}
}

/*Функция записи сжатого файла
* Параметры функции:
*		1)out- Ссылка на поток вывода
*		2)data- вектор символов(исходный текст)
*		3)table- таблица кодов символов
* Принцип работы:
*		1)Формируем блоки из 0 и 1 длиной по 8 символов и выписываем их в файл
*/
void write_to_compressed_file(ofstream &out,vector<char>data,map<char,vector<bool>>table) {
	cout << "Результат сжатия записан в файл output.bin\n";
	int count = 0;
	char buf = 0; 
	for (int i = 0; i < data.size(); i++){
		for (int j = 0; j < table[data[i]].size(); j++){
			buf = buf | (table[data[i]][j]) << (7 - count);
			count++;
			if (count == 8) {
				count = 0;
				out << buf;
				buf = 0;
			}
		}
	}
}
#endif