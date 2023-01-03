#include "Gamma_Encryption.h"
#include<Windows.h>
#include<stdio.h>

using namespace std;
using namespace System;
using namespace System::Windows::Forms;


void main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	LR2UI::Gamma_Encryption form;
	Application::Run(% form);
}
System::Void LR2UI::Gamma_Encryption::Gamma_Encryption_Load(System::Object^ sender, System::EventArgs^ e){
	textBox3->ReadOnly = true;
	return System::Void();
}

//çàøèôðîâàòü
String^ Encode(String^ input_string, String^ key) {
	String^ characters(L"");
	characters = " ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞß0123456789!@#$%^&*()";
	size_t N = characters->Length;

	String^ res = "";
	size_t key_index = 0, c = 0, c1 = 0, c2 = 0;

	key = key->ToUpper();
	input_string = input_string->ToUpper();

	for (size_t i = 0; i < input_string->Length; i++) {
		c = characters->IndexOf(input_string[i]);
		c1 = characters->IndexOf(key[key_index]);
		c2 = (c1 + c) % N;
		res = res + characters[c2];
		key_index++;
		if (key_index == key->Length) { key_index = 0; }
	}
	return res;
}
//Ðàñøèôðîâàòü
String^ Decode(String^ input_string, String^ key) {
	String^ characters(L"");
	characters = " ÀÁÂÃÄÅ¨ÆÇÈÉÊËÌÍÎÏÐÑÒÓÔÕÖ×ØÙÚÛÜÝÞß0123456789!@#$%^&*()";
	size_t N = characters->Length;

	String^ res = "";
	size_t key_index = 0, c = 0, c1 = 0, c2 = 0;

	key = key->ToUpper();
	input_string = input_string->ToUpper();

	for (size_t i = 0; i < input_string->Length; i++) {
		c = characters->IndexOf(input_string[i]);
		c1 = characters->IndexOf(key[key_index]);
		c2 = (c - c1 + N) % N;
		res = res + characters[c2];
		key_index++;
		if (key_index == key->Length) { key_index = 0; }
	}
	return res;
}

System::Void LR2UI::Gamma_Encryption::button1_Click(System::Object^ sender, System::EventArgs^ e) {
	textBox3->Text = Encode(textBox1->Text, textBox2->Text);
	return System::Void();
}

System::Void LR2UI::Gamma_Encryption::button2_Click(System::Object^ sender, System::EventArgs^ e) {
	textBox3->Text = Decode(textBox1->Text, textBox2->Text);
	return System::Void();
}


