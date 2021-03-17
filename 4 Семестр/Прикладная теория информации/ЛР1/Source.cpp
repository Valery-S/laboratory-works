#include "Work_with_Letters.h"
#include "binary_tree.h"
using namespace std;

int main() {
	string file_name;								//��� ��������� �����
	vector<char>data;								//������ ��� �������� ���������� ��������� �����
	vector<char>letters;						//������ ���������� �������� � �����
	vector<int>count;								//������, �������� ���������� ���������� �������� � �����
	vector<Node*>node_vector;				//������ ����� ������
	map<char, vector<bool>> table;	//�������, �������� ��� ��������������� �������
	Node* root;											//��������� �� ������ ������
	ifstream input;									//��������� �� �������� ����
	ofstream out;										//��������� �� �������� ����
	setlocale(LC_ALL, "Russian");		//��������� �������� ����� � �������

	//������ ����� ��������� �����
	cout<<Yellow << "������ ��������� ������������� ��� ������ ������ ������� ��������.\n"
			<< "������� ��� �����, ������� ����� �����.\n"<<Blue;
	cin >> file_name;
	input.open(file_name);
	
	//������ ������ �� �����
	data = read_from_file(input);
	//����� ���������� �������� 
	letters = find_unique_letters(data);
	//������� ���������� ������� ������� 
	count = counting_letters(data,letters);
	//�������� ������� �����
	node_vector = create_vector(count,letters);
	//�������� ������ ��������
	create_tree(&node_vector);
	//��������� ������ �� ������ ������
	root = node_vector.front();
	//�������� ������� ����� ��������
	table = create_table(root);

	//����� ���������� � �������
	cout<<Yellow << "���������� ���������� �������� � ������ " << letters.size() << "\n";
	for (int i = 0; i < letters.size(); i++){
		cout<<Green << letters[i] << " ����������� " << count[i] << " ���\n";
	}
	print_map_to_console(table);
	
	//����� ���������� � ������ ����
	out.open("output.bin");
	write_to_compressed_file(out, data, table);
	
	input.close();
	out.close();
	cout << Reset;
	return 0;
}