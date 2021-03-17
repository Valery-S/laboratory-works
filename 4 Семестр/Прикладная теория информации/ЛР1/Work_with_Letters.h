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

/*������ ������ �� �����
* ��������� �������:
*		1)in - ������ �� ����� �����
* ������� ������:
*		1)���� �� ����� �� ����� �����:
			1.1)�������� �� ���� ������
			1.2)���������� ������ � ������ res
*/
vector<char> read_from_file(ifstream& in) {
	char tmp;
	vector<char>res;
	while (in.get(tmp)) {
		res.push_back(tmp);
	}
	return res;
}

/*������� ������ ���������� �������� � ������
* ��������� �������:
*		1)data - ������ ���� ��������
* ������� ������:
*		1)���� �� ����� �� ����� ������� data
*			1.1)��������� ���� �� � ������� res ������� ������
*			1.2)���� ������ �� ����������, �� ��������� ��� � ������ res
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

/*������� �������� ���������� ������� ����������� �������
* ��������� �������:
*		1)data - ������ ���� ��������
*		2)letters - ������ ���������� ��������
*	������� ������:
*		1)���� �� ����� �� ����� ������� data 
*			1.1)���� �� ����� �� ����� ������� letters
*				1.1.1)���� ������� ������  � ������� letters ��������� � ��������,���������������
*							� ������� data,�� ���������� 1 � ���������� ������� �������.
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
/*������� �������� ������� �����
* ��������� �������:
*		1)count- ������ ���������� ��������
*		2)letters- ������ ���������� ��������
* ������� ������:
*		1)��� ������� ������� �������� ���� � ������ "������" � "����������"
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

/*������� �������� ������ �� ������ �����
* ��������� �������:
*		1)*v- ��������� �� ������
* ������� ������:
*		1)���� � ������� ��������� ������ ������ ����
*			1.1)��������� ������ � ������� ���������� �����, ������������ � ����
*			1.2)������ ������ ������� �� ������� ���� � �������
*			1.3)������� ������ ����
*			1.4)������ ������� ������� �� ������� ���� � �������
*			1.5)������� ������ ����
*			1.6)������ ���� �������� � ��������� ��� � ������
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

/*������� �������� ������� ����� ��������
* ��������� �������:
*		1)*root -��������� �� ������ ������
* ������� ������:
*		1)���� � ���� ���� ����� ���,�� � ������ code ����������� ����
*			� ���������� ������� � ����������, ������ ������ ����
*		2)���� � ���� ���� ����� ���,�� � ������ code ����������� �������
*			� ���������� ������� � ����������, ������ ������� ����
*		3)���� � ���� ��� �������, �� � ������� table ����������� ����� ������ � ������� ����� � ��������
*		4)���� � ���� ���� ��������, �� ������� �������� ����� �� ������� code(����������� �� ������� ����)
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

/*������� ������ ������� ����� � �������
* ��������� �������:
*		1)table- ������� ����� ��������
*/
void print_map_to_console(map<char, vector<bool>>table) {
	cout<<Yellow << "\n\n������� ������������. �� ����: \n";
	for (auto it = table.begin(); it != table.end(); ++it) {
		cout<<Green << it->first << " : ";
		for (int i = 0; i < it->second.size(); i++) {
			cout << it->second[i];
		}
		cout << "\n";
	}
}

/*������� ������ ������� �����
* ��������� �������:
*		1)out- ������ �� ����� ������
*		2)data- ������ ��������(�������� �����)
*		3)table- ������� ����� ��������
* ������� ������:
*		1)��������� ����� �� 0 � 1 ������ �� 8 �������� � ���������� �� � ����
*/
void write_to_compressed_file(ofstream &out,vector<char>data,map<char,vector<bool>>table) {
	cout << "��������� ������ ������� � ���� output.bin\n";
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