#include "RSA_form.h"
#include "functions.h"
#include <msclr\marshal_cppstd.h>
using namespace std;
using namespace System;
using namespace System::Windows::Forms;
using namespace msclr::interop;

//--------------------------------------------------------------------------------------
//Главная функция запускает форму
System::Void main() {
  Application::EnableVisualStyles();
  Application::SetCompatibleTextRenderingDefault(false);
  LR5UI::RSA_form form;
  Application::Run(% form);
  return System::Void();
}
//--------------------------------------------------------------------------------------
//Функция вызываемая при загрузке формы
System::Void LR5UI::RSA_form::RSA_form_Load(System::Object^ sender, System::EventArgs^ e){
  textBox3->ReadOnly = true;
  textBox4->ReadOnly = true;
  textBox5->ReadOnly = true;
  textBox6->ReadOnly = true;
  textBox7->ReadOnly = true;
  textBox8->ReadOnly = true;
  textBox9->ReadOnly = true;
  textBox12->ReadOnly = true;
  return System::Void();
}
//--------------------------------------------------------------------------------------
//Функция, вызываемая при нажатии на кнопку "Зашифровать" в форме.
//Устанавливает в текстовое поле 3 результат функции шифрования.
System::Void LR5UI::RSA_form::button1_Click(System::Object^ sender, System::EventArgs^ e){
  int e1, d, n, f, p, q;
  string text = "";
  string out = "";
  srand(time(0));

  text = marshal_as<string>(textBox1->Text);

  p = genPrime();
  q = genPrime();
  n = p * q;
  f = (p - 1) * (q - 1);
  e1 = genCoprime(f);
  d = gend(f, e1);

  encrypt(out, text, e1, n);

  textBox3->Text = marshal_as<System::String^>(out);
  textBox4->Text= marshal_as<System::String^>(to_string(p));
  textBox5->Text = marshal_as<System::String^>(to_string(q));
  textBox6->Text = marshal_as<System::String^>(to_string(n));
  textBox7->Text = marshal_as<System::String^>(to_string(f));
  textBox8->Text = marshal_as<System::String^>(to_string(e1));
  textBox9->Text = marshal_as<System::String^>(to_string(d));

  return System::Void();
}
//--------------------------------------------------------------------------------------
//Функция, вызываемая при нажатии на кнопку "Расшифровать" в форме.
//Устанавливает в текстовое поле 12 результат функции расшифрования.
System::Void LR5UI::RSA_form::button2_Click(System::Object^ sender, System::EventArgs^ e){
  int d, n;
  string text = "";
  string out = "";
  string d_string = "";
  string n_string = "";

  text = marshal_as<string>(textBox2->Text);
  d_string = marshal_as<string>(textBox11->Text);
  n_string = marshal_as<string>(textBox10->Text);

  d = stoll(d_string);
  n = stoll(n_string);

  decrypt(out, text, d, n);

  textBox12->Text = marshal_as<System::String^>(out);

  return System::Void();
}
