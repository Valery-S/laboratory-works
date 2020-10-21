#include "MyList.h"
#include<iostream>
/*������� �������� ������������  ����� */
int proverka() {
	int n = 0;
	int i = 0, count = 0;
	bool f = false;
	char b[50];
	while (n == 0) {
		f = false;
		i = 0;
		while (cin.peek() != '\n') {
			b[i] = cin.get();
			i++;
		}
		cin.ignore();
		count = i;
		for (int j = 0; j < count; j++) {
			if (b[j]<'0' || b[j]>'9') {
				f = true;
			}
		}
		if (f == true) {
			cout << "������, ������� ��� ���\n";
		}
		else {
			for (int j = 0; j < count; j++) {
				n = n * 10 + b[j] - 48;
			}
		}
	}
	return n;
}
using namespace std;
int main() {
	setlocale(LC_ALL, "ru");		//��������� �������� �����
	int col=0,str=0;				//���������� ����� � ������� � �������
	List<int> AD, AU, AL, LJ, LI;	//������, ���������� �� �������� ������ �� ��������� �������
	List <int>LJ_2;					//������ ��� �������� ����, ��� ������� �������� ���������� ������������
	int element;					//������� �������
	List<int> different;			//��������� �������� �������
	cout << "������� ���������� �����"<<endl;
	str=proverka();
	cout << "������� ���������� ��������" << endl;
	col = proverka();
	//��������� �������� ������
	if (str == 0 || col == 0) {
		cout << "������� ������ ������� �������." << endl;
		exit(-1);
	}
	if (str!=col){
		cout << "����������� ����� �� ��������� � ����������� ��������. "
				"������� �� ������� ����������-������������" << endl;
		exit(-1);
	}
	//���� ��������� ������� - ���������� �������
	cout << "������� �������� �������." << endl;
	for (int i = 0; i < str; i++){
		int flag = 0;				//���������� ���������� �� ��������� ������� � ���� ������ ������� ����� �������
									//������������ ��� ���������� ������ LI
		for (int j = 0; j <col; j++){
			element = proverka();
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
			//���� �� ��������� � ������� ����� �������, ����� �� ����� ������ 
			//� �� ��������� ���������� ��������, �� "����������" ������ � ������ LI
			if (flag == 0 && i < j && j==col-1) {LI.push_back(0); }
		}
	}
	//��������� "�����������" ������ � ������ LI
	//���� "���������" ��������� ������, ���������� � �� ���������� ��������� ���������+1
	if (LI[LI.get_size() - 1] == 0) { LI[LI.get_size() - 1] = AU.get_size() + 1; }
	for (int i = 0; i < LI.get_size() -1; i++){
		if (LI[i] == 0) {
			int p = 0;
			//������� ������ �� ������� ������ ����� ����� �����
			//� ��������� ��� �������� �� ������� ������
			for (int j = i; j < LI.get_size() - 2; j++) {
				if (LI[j + 1] != 0) {p = LI[j + 1];}
			}
			LI[i] = p;
		}
	}
	//�������� �� ��, ��� ������� �������� ����������-������������
	if (LJ_2.get_size() == LJ.get_size()) {
		int flag = 0;
		for (int i = 0; i <LJ.get_size(); i++){
			if (LJ_2[i] != LJ[i]) { flag = 1; }
		}
		if (flag == 0) {
			cout << endl << "������� ����������-������������"<<endl << endl;
			cout << "�������������� ������ AD: " << endl;
			for (int i = 0; i < AD.get_size(); i++) { cout << AD[i] << "     "; }
			cout << endl << endl << "�������������� ������ AU: " << endl;
			for (int i = 0; i < AU.get_size(); i++) { cout << AU[i] << "     "; }
			cout << endl << endl << "�������������� ������ AL: " << endl;
			for (int i = 0; i < AL.get_size(); i++) { cout << AL[i] << "     "; }
			cout << endl << endl << "�������������� ������ LJ: " << endl;
			for (int i = 0; i < LJ.get_size(); i++) { cout << LJ[i] << "     "; }
			cout << endl << endl << "�������������� ������ LI: " << endl;
			for (int i = 0; i < LI.get_size(); i++) { cout << LI[i] << "     "; }
			cout << endl << endl;
		}
		else{ 
			cout << endl << "������� �� �������� ����������-������������" << endl << endl;
			exit(-1);
		}
	}
	else {
		cout << endl << "������� �� �������� ����������-������������"<<endl << endl;
		exit(-1);
	}
	//����� ��������� ��������� � �������
	different.push_back(AD[0]);
	for (int i = 1; i < AD.get_size() -1; i++) {
		int flag = 0;
		for (int j = 0; j < different.get_size() - 1; j++) {
			if (different[j] == AD[i]) { flag = 1; }
		}
		if (flag == 0) { different.push_back(AD[i]); }
	}
	for (int i = 0; i < AU.get_size() -1; i++) {
		int flag = 0;
		for (int j = 0; j < different.get_size() -1; j++) {
			if (different[j] == AU[i]) { flag = 1; }
		}
		if (flag == 0) { different.push_back(AU[i]); }
	}
	for (int i = 0; i < AL.get_size() -1; i++) {
		int flag = 0;
		for (int j = 0; j < different.get_size() -1; j++) {
			if (different[j] == AL[i]) { flag = 1; }
		}
		if (flag == 0) { different.push_back(AL[i]); }
	}
	//����� ��������� ���������
	cout <<"����������� �������� ���������: "<<different.get_size() <<endl<< "��������� �������� �������:" << endl;
	for (int j = 0; j < different.get_size() -1; j++) {cout << different[j]<<"   ";}
	cout << endl;
	return 0;
}
