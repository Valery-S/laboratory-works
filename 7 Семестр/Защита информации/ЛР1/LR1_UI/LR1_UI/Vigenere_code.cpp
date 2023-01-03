#include "Vigenere_code.h"
#include<Windows.h>
#include<stdio.h>
#include <string>


using namespace std;
using namespace System;
using namespace System::Windows::Forms;

void main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	LR1UI::Vigenere_code form;
	Application::Run(% form);
}


System::Void LR1UI::Vigenere_code::Vigenere_code_Load(System::Object^ sender, System::EventArgs^ e){
	textBox3->ReadOnly = true;
	radioButton2->Checked = true;
	return System::Void();
}

//�����������
String^ Encode(String^ input_string, String^ key, string language) {
	String^ characters(L"");
	//����� ����� ��������
	if (language == "en") { characters = " ABCDEFGHIJKLMNOPQRSTUVWXYZ"; }
	if (language == "rus") { characters = " �����Ũ��������������������������"; }
	size_t N = characters->Length;

	String^ res="";
	size_t key_index = 0,c=0,c1=0,c2=0;
	
	//���������� ���� ��������� ������ � ����� � �������� �������� 
	key = key->ToUpper();
	input_string = input_string->ToUpper();

	for (size_t i = 0; i < input_string->Length; i++) {
		//����� � �������� ������� ����� ��������� ������
		//� ����������� � ������
		c = characters->IndexOf(input_string[i]);
		// ����� � �������� ������� ����� �����
		//� ����������� � ������
		c1= characters->IndexOf(key[key_index]);
		//������ ������ ����� ��������� ������
		c2 = (c1 + c) % N;
		//���������� ����� � ������������� �����
		res = res + characters[c2];
		key_index++;
		//���� ������ ����� ����� ����� ����� �����,
		//�� ��������� ����
		if (key_index  == key->Length) { key_index = 0; }
	}
	return res;
}

//������������
String^ Decode(String^ input_string, String^ key,string language) {
	String^ characters(L"");
	//����� ����� ��������
	if (language == "en") {characters = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";}
	if (language == "rus") { characters = " �����Ũ��������������������������"; }
	size_t N = characters->Length;
	
	String^ res = "";
	size_t key_index = 0, c = 0, c1 = 0, c2 = 0;
	
	//���������� ���� ��������� ������ � ����� � �������� �������� 
	key = key->ToUpper();
	input_string = input_string->ToUpper();

	for (size_t i = 0; i < input_string->Length; i++) {
		//����� � �������� ������� ����� ��������� ������
		//� ����������� � ������
		c = characters->IndexOf(input_string[i]);
		//����� � �������� ������� ����� �����
		//� ����������� � ������
		c1 = characters->IndexOf(key[key_index]);
		//������ ������ ����� ��������� ������
		c2 = (c - c1 + N) % N;
		//���������� ����� � �������������� �����
		res = res + characters[c2];
		key_index++;
		//���� ������ ����� ����� ����� ����� �����,
		//�� ��������� ����
		if (key_index == key->Length) { key_index = 0; }
	}
	return res;
}

System::Void LR1UI::Vigenere_code::button1_Click(System::Object^ sender, System::EventArgs^ e){
	string language;
	if (radioButton1->Checked) { language = "en"; }
	if (radioButton2->Checked) { language = "rus"; }
	textBox3->Text=Encode(textBox1->Text, textBox2->Text,language);
	return System::Void();
}

System::Void LR1UI::Vigenere_code::button2_Click(System::Object^ sender, System::EventArgs^ e){
	string language;
	if (radioButton1->Checked) { language = "en"; }
	if (radioButton2->Checked) { language = "rus"; }
	textBox3->Text = Decode(textBox1->Text, textBox2->Text,language);
	return System::Void();
}
