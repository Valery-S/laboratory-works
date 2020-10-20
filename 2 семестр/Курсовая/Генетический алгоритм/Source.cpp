#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include <ctime>
using namespace std;
struct Graph {
	int quantity = 0;//����������� �������
	int length = 0;//����� ����
	vector<vector<double>>distance;//������� ���������� 
	vector<int>individual_f;//����� 1
	vector<int>individual_s;//����� 2
	vector<int>individual_t;//����� 3
};
Graph read(string file_name) {//������� ������ ������ �� �����
	cout  << "����� ������" << endl;
	Graph gr;
	vector<vector<double>> input_data;
	ifstream in;
	in.open(file_name);//��������� ���� �� ������
	if (!in)//�������� �� ������������ �����
	{
		if (in.eof()) {
			cout << "���� ����" << endl;
			exit(-1);
		}
		else {
			cout << "�������� ��� �����" << endl;
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
				in >> string[j];//c������� ������ i-��� ������
				a[i] = 0;
			}
			input_data.push_back(string);//���������� ������ � ������� ����������
		}
		gr.quantity = num;//���������� ���������� �������
		gr.distance = input_data;//������������ ����� ����������
		cout << "������ �������" << endl;
	}
	in.close();
	return gr;
}
Graph choose_f(Graph gr) {//����� ����� 1
	srand((unsigned)time(NULL));//��������� ���������� �������� ���� 
	gr.individual_f.resize(gr.quantity + 1);//������������� ������ "�����"
	for (int i = 0; i < gr.quantity; i++) { gr.individual_f[i] = -1; }
	bool flag = false;
	int k = 0;//����� ������� � "�����"
	int j = 0;//����������, � ������� ����� ������������ ��������������� �����
	while (k < gr.quantity) {
		j = rand() % gr.quantity;
		if (k == 0) {//���� � ����� ��� ��� �� ������ ������
			gr.individual_f[k] = j;
			k++;}
		else {//���� � ����� ���� ���� �� 1 �����
			if (gr.distance[gr.individual_f[k - 1]][j] != -1) {//���� ���������� ����� ��������� � ��������������� ������� �� ����� -1 
				for (int i = 0; i < gr.quantity; i++)
				{
					if (gr.individual_f[i] == j) {//��������� ���� �� � ����� ����� j
						flag = true;
						break;
					}
					else { flag = false; }
				}
				if (flag == false) { gr.individual_f[k] = j; k++; }//���� ����� j � ����� �� ���������, �� ��������� ���
			}
		}
	}
	return gr;
}
Graph choose_s(Graph gr) {//����� ����� 2
	srand((unsigned)time(NULL) * 2);//��������� ���������� �������� ���� ��� ����, ����� ����� ���� ������
	gr.individual_s.resize(gr.quantity + 1);
	for (int i = 0; i < gr.quantity; i++) { gr.individual_s[i] = -1; }
	int k = 0, j;
	bool flag = false;
	while (k < gr.quantity) {
		j = rand() % gr.quantity;
		if (k == 0) {//���� � ����� ��� ��� �� ������ ������
			gr.individual_s[k] = j;
			k++;}
		else {//���� � ����� ���� ���� �� 1 �����
			if (gr.distance[gr.individual_s[k - 1]][j] != -1) {//���� ���������� ����� ��������� � ��������������� ������� �� ����� -1 
				for (int i = 0; i < gr.quantity; i++)
				{
					if (gr.individual_s[i] == j) {//��������� ���� �� � ����� ����� j
						flag = true;
						break;
					}
					else { flag = false; }
				}
				if (flag == false) { gr.individual_s[k] = j; k++; }//���� ����� j � ����� �� ���������, �� ��������� ���
			}
		}
	}
	return gr;
}
Graph choose_t(Graph gr) {//����� ����� 3
	srand((unsigned)time(NULL)*3);//��������� ���������� �������� ���� ��� ����, ����� ����� ���� ������
	gr.individual_t.resize(gr.quantity + 1);
	for (int i = 0; i < gr.quantity; i++) { gr.individual_t[i] = -1; }
	int k = 0, j;
	bool flag = false;
	while (k < gr.quantity) {
		j = rand() % gr.quantity;
		if (k == 0) {//���� � ����� ��� ��� �� ������ ������
			gr.individual_t[k] = j;
			k++;}
		else  {//���� � ����� ���� ���� �� 1 �����
			if (gr.distance[gr.individual_t[k - 1]][j] != -1) {//���� ���������� ����� ��������� � ��������������� ������� �� ����� -1 
				for (int i = 0; i < gr.quantity; i++)
				{
					if (gr.individual_t[i] == j) {//��������� ���� �� � ����� ����� j
						flag = true;
						break;
					}
					else { flag = false; }
				}
				if (flag == false) { gr.individual_t[k] = j; k++; }//���� ����� j � ����� �� ���������, �� ��������� ���
			}
		}
	}
	return gr;
}
Graph choose(Graph gr) {//����� ���� ������
	gr = choose_f(gr);// ����� �����
	gr.individual_f[gr.quantity] = gr.individual_f[0];//������ � ��������� ������ ������� ������
	// ���� ���������� ����� ��������� � ������������� ������� ����� -1, �� ����� ����������� ����� 
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
Graph mutation(Graph gr,int& flag) {//������� ��������� �����
	double sum_s = 0, sum_f = 0, sum_t = 0,Sum=0,sum_n=0,sum_max=0,max1 = 0, max2 = 0;
	int k=1,n=1,max1_s=0,max2_s=0;
	vector<int>new_individual(gr.quantity+1);//����� �����
	for (int i = 0; i < gr.quantity; i++){
		sum_f = sum_f + gr.distance[gr.individual_f[i]][gr.individual_f[i + 1]];//������� ����� ���� 1 
		sum_s = sum_s + gr.distance[gr.individual_s[i]][gr.individual_s[i + 1]];//������� ����� ���� 2 
		sum_t = sum_t + gr.distance[gr.individual_t[i]][gr.individual_t[i + 1]];//������� ����� ���� 3
	}
	//����� ���������� ����
	Sum = sum_f;
	if (sum_s < Sum) { Sum = sum_s; k = 2; }
	if (sum_t < Sum) { Sum = sum_t; k = 3; }
	//����� ���������� ����
	sum_max = sum_f;
	if (sum_s > sum_max) { sum_max = sum_s; n = 2; }
	if (sum_t >sum_max) { sum_max = sum_t; n = 3; }
	//����������� ������ � ������� ����������� ����� ����
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
	gr.length = sum_f;//������ ����� ����- ����� ���� ������ �����
	//������� ��������� � ��� �����, ����� ���� ������� ������(������), ��� �� ������� ��� ������� �����. 
	//��� �������������� �� ���� �����  � ������������ ����������� ����� ��������.
	//���� ���������� �����������, �� ����� �������� ��, � ������� ����������� �������.
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
	for (int i = 0; i < gr.quantity; i++){sum_n = sum_n + gr.distance[new_individual[i]][new_individual[i + 1]];}//������� ����� ���� ����� ����� 
	//���� ������� ������ ������� �.� ����� �����������, �� �������� �����.
	//����� ����������� ���������� flag,��������� ��� �������� �������� ������ 0 - ���������� ���������� �������
	if (sum_n < sum_f) { 
		gr.individual_f = new_individual;
		gr.length = sum_n;
		cout << "������� ������ �������"<<endl;
		cout << "������ ���� �� ������ ������" << endl;
		for (int i = 0; i < gr.quantity + 1; i++) { cout << gr.individual_f[i] + 1 << " "; }
		cout << endl << "������ ����� ���� �� ������ ������ " << gr.length << endl << endl;
	}
	else {
		flag = 0;
		cout << "������� ������ ���������" << endl << endl;}
	return gr;
}

int main() {
	double start = clock();
	int flag=1;
	setlocale(LC_ALL, "RUS");
	cout << "������� ��� ����� ��� ������ ������"<<endl;
	string file_name;
	cin >> file_name;
	Graph gr;
	gr = read(file_name);
	gr=choose(gr);
	cout << "�������������� �����:"<<endl;
	for (int i = 0; i < gr.quantity + 1; i++) { cout << gr.individual_f[i] + 1 << " "; }
	cout << endl;
	for (int i = 0; i < gr.quantity + 1; i++) { cout << gr.individual_s[i] + 1 << " "; }
	cout << endl;
	for (int i = 0; i < gr.quantity + 1; i++) { cout << gr.individual_t[i] + 1 << " "; }
	cout << endl<<endl;
	while (flag == 1) {
		gr = mutation(gr, flag);
	}
	cout << "������ ����� ���� "<<gr.length << endl;
	cout << "������ ���� " << endl;
	for (int i = 0; i < gr.quantity+1; i++){cout << gr.individual_f[i] + 1 << " " ;}
	cout << endl<<"time="<< (clock() - start) / CLOCKS_PER_SEC;
	return 0;
}