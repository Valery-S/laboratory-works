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

//Зашифровать
String^ Encode(String^ input_string, String^ key, string language) {
	String^ characters(L"");
	//Выбор языка алфавита
	if (language == "en") { characters = " ABCDEFGHIJKLMNOPQRSTUVWXYZ"; }
	if (language == "rus") { characters = " АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; }
	size_t N = characters->Length;

	String^ res="";
	size_t key_index = 0,c=0,c1=0,c2=0;
	
	//Приведение букв открытого текста и ключа к верхнему регистру 
	key = key->ToUpper();
	input_string = input_string->ToUpper();

	for (size_t i = 0; i < input_string->Length; i++) {
		//Поиск в алфавите текущей буквы открытого текста
		//И запоминание её номера
		c = characters->IndexOf(input_string[i]);
		// Поиск в алфавите текущей буквы ключа
		//И запоминание её номера
		c1= characters->IndexOf(key[key_index]);
		//Расчет номера буквы закрытого текста
		c2 = (c1 + c) % N;
		//Добавление буквы в зашифрованный текст
		res = res + characters[c2];
		key_index++;
		//Если индекс буквы ключа равен длине ключа,
		//То повторяем ключ
		if (key_index  == key->Length) { key_index = 0; }
	}
	return res;
}

//Расшифровать
String^ Decode(String^ input_string, String^ key,string language) {
	String^ characters(L"");
	//Выбор языка алфавита
	if (language == "en") {characters = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";}
	if (language == "rus") { characters = " АБВГДЕЁЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ"; }
	size_t N = characters->Length;
	
	String^ res = "";
	size_t key_index = 0, c = 0, c1 = 0, c2 = 0;
	
	//Приведение букв закрытого текста и ключа к верхнему регистру 
	key = key->ToUpper();
	input_string = input_string->ToUpper();

	for (size_t i = 0; i < input_string->Length; i++) {
		//Поиск в алфавите текущей буквы закрытого текста
		//И запоминание её номера
		c = characters->IndexOf(input_string[i]);
		//Поиск в алфавите текущей буквы ключа
		//И запоминание её номера
		c1 = characters->IndexOf(key[key_index]);
		//Расчет номера буквы открытого текста
		c2 = (c - c1 + N) % N;
		//Добавление буквы в расшифрованный текст
		res = res + characters[c2];
		key_index++;
		//Если индекс буквы ключа равен длине ключа,
		//То повторяем ключ
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
