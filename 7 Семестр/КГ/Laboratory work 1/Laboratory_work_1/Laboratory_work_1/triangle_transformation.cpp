#include "triangle_transformation.h"
#include<Windows.h>
#include<cmath>
#include <msclr\marshal_cppstd.h>
#include<string>
#include"windows.h"
# define M_PI           3.14159265358979323846
using namespace System;
using namespace System::Windows::Forms;
using namespace std;
using namespace msclr::interop;


string l[3];

void main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Laboratorywork1::triangle_transformation form;
	Application::Run(% form);
}

System::Void Laboratorywork1::triangle_transformation::triangle_transformation_Load(System::Object^ sender, System::EventArgs^ e){
	//canvas
	Bitmap^ Img = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
	canvas = Graphics::FromImage(Img);
	pictureBox1->Image = Img;
	pictureBox1->BackColor = Color::White;
	l[0] = 'A'; l[1] = 'B'; l[2] = 'C';
	print_border();
	program_step = 1;
	label4->ForeColor = Color::Red;
	label5->ForeColor = Color::Blue;
	label6->ForeColor = Color::Green;
	label7->ForeColor = Color::LightGreen;
	label8->ForeColor = Color::BurlyWood;
	label9->ForeColor = Color::Gray;
	label10->ForeColor = Color::Aqua;
	label11->ForeColor = Color::BlueViolet;
	radioButton1->Checked = true;
	radioButton2->Checked = false;
	A.X = -1; A.Y = -1; A1.X = -1; A1.Y = -1;
	B.X = -1; B.Y = -1; B1.X = -1; B1.Y = -1;
	C.X = -1; C.Y = -1; C1.X = -1; C1.Y = -1;
	return System::Void();
}

System::Void Laboratorywork1::triangle_transformation::pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){
	switch (program_step) {
	case 2:
		A.X = e->Location.X;
		A.Y = e->Location.Y;
		break;
	case 4:
		B.X = e->Location.X;
		B.Y = e->Location.Y;
		break;
	case 6:
		C.X = e->Location.X;
		C.Y = e->Location.Y;
		break;
	case 8:
		A1.X = e->Location.X;
		A1.Y = e->Location.Y;
		break;
	case 10:
		B1.X = e->Location.X;
		B1.Y = e->Location.Y;
		break;
	case 12:
		C1.X = e->Location.X;
		C1.Y = e->Location.Y;
		break;
	default:
		break;
	}
	pictureBox1->Invalidate();
	return System::Void();
}

System::Void Laboratorywork1::triangle_transformation::pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	moving_A = false;
	moving_B = false;
	moving_C = false;
	moving_A1 = false;
	moving_B1 = false;
	moving_C1 = false;
	pictureBox1->Invalidate();
	return System::Void();
}

System::Void Laboratorywork1::triangle_transformation::pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e) {
	switch (program_step) {
	case 2:
		drawBrush->Color = Color::Red;
		canvas->DrawString("A", fn, drawBrush, A.X - 40, A.Y - 40);
		canvas->FillEllipse(gcnew SolidBrush(Color::Red), A.X - 8, A.Y - 8, 16, 16);
		break;
	case 4:
		drawBrush->Color = Color::Red;
		canvas->DrawString("B", fn, drawBrush, B.X - 40, B.Y - 40);
		canvas->FillEllipse(gcnew SolidBrush(Color::Red), B.X - 8, B.Y - 8, 16, 16);
		break;
	case 6:
		drawBrush->Color = Color::Red;
		canvas->FillEllipse(gcnew SolidBrush(Color::Red), C.X - 8, C.Y - 8, 16, 16);
		l[0] = "A"; l[1] = "B"; l[2] = "C";
		draw_triangle(A, B, C, Color::Red,1);
		break;
	case 8:
		drawBrush->Color = Color::Blue;
		canvas->DrawString("A'", fn, drawBrush, A1.X - 40, A1.Y - 40);
		canvas->FillEllipse(gcnew SolidBrush(Color::Blue), A1.X - 8, A1.Y - 8, 16, 16);
		break;
	case 10:
		drawBrush->Color = Color::Blue;
		canvas->DrawString("B'", fn, drawBrush, B1.X - 40, B1.Y - 40);
		canvas->FillEllipse(gcnew SolidBrush(Color::Blue), B1.X - 8, B1.Y - 8, 16, 16);
		break;
	case 12:
		drawBrush->Color = Color::Blue;
		canvas->FillEllipse(gcnew SolidBrush(Color::Blue), C1.X - 8, C1.Y - 8, 16, 16);
		l[0] = "A'"; l[1] = "B'"; l[2] = "C'";
		draw_triangle(A1, B1, C1, Color::Blue,1);
		break;
	default:
		break;
	}
	if (program_step >= 6) {
		Point center_coordinat;
		center_coordinat.X = pictureBox1->Width / 2;
		center_coordinat.Y = pictureBox1->Height / 2;
		tmp_A_X = int(float(A.X- center_coordinat.X) / float(60) * 10) / 10.0;
		tmp_B_X = int(float(B.X- center_coordinat.X) / float(60) * 10) / 10.0;
		tmp_C_X = int(float(C.X- center_coordinat.X) / float(60) * 10) / 10.0;

		tmp_A_Y = int(float(-A.Y + center_coordinat.Y) / float(60) * 10) / 10.0;
		tmp_B_Y = int(float(-B.Y + center_coordinat.Y) / float(60) * 10) / 10.0;
		tmp_C_Y = int(float(-C.Y + center_coordinat.Y) / float(60) * 10) / 10.0;
		label4->Text = "       |" + tmp_A_X + "\t\t" + tmp_A_Y + "\t\t1 |\n"
			             "P = |" + tmp_B_X + "\t\t"+ tmp_B_Y +"\t\t1 |\n"
			             "       |" + tmp_C_X + "\t\t" + tmp_C_Y + "\t\t1 |\n";
	}
	if (program_step >= 12) {
		Point center_coordinat;
		center_coordinat.X = pictureBox1->Width / 2;
		center_coordinat.Y = pictureBox1->Height / 2;
		tmp_A1_X = int(float(A1.X - center_coordinat.X) / float(60) * 10) / 10.0;
		tmp_B1_X = int(float(B1.X - center_coordinat.X) / float(60) * 10) / 10.0;
		tmp_C1_X = int(float(C1.X - center_coordinat.X) / float(60) * 10) / 10.0;

		tmp_A1_Y = int(float(-A1.Y + center_coordinat.Y) / float(60) * 10) / 10.0;
		tmp_B1_Y = int(float(-B1.Y + center_coordinat.Y) / float(60) * 10) / 10.0;
		tmp_C1_Y = int(float(-C1.Y + center_coordinat.Y) / float(60) * 10) / 10.0;
		label5->Text = "       |" + tmp_A1_X + "\t\t" + tmp_A1_Y + "\t\t1 |\n"
			             "P'= |" + tmp_B1_X + "\t\t" + tmp_B1_Y + "\t\t1 |\n"
			             "       |" + tmp_C1_X + "\t\t" + tmp_C1_Y + "\t\t1 |\n";
	}
	program_step++;
	return System::Void();
}

System::Void Laboratorywork1::triangle_transformation::pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){
	if (program_step > 12) {
		//Если нажата левая кнопка, проверяем совпадение позиции с элементами на холсте
		if (e->Button == Windows::Forms::MouseButtons::Left) {
			//Точка А
			if (e->Location.X >= A.X - 8 && e->Location.X <= A.X + 8 &&
				e->Location.Y >= A.Y - 8 && e->Location.Y <= A.Y + 8 &&
				moving_B == false && moving_C == false && moving_A1 == false &&
				moving_B1 == false && moving_C1 == false)
			{
				A.X = e->Location.X;
				A.Y = e->Location.Y;
				moving_A = true;
			}
			//Точка B
			if (e->Location.X >= B.X - 8 && e->Location.X <= B.X + 8 &&
				e->Location.Y >= B.Y - 8 && e->Location.Y <= B.Y + 8 &&
				moving_A == false && moving_C == false && moving_A1 == false &&
				moving_B1 == false && moving_C1 == false)
			{
				B.X = e->Location.X;
				B.Y = e->Location.Y;
				moving_B = true;
			}
			//Точка C
			if (e->Location.X >= C.X - 8 && e->Location.X <= C.X + 8 &&
				e->Location.Y >= C.Y - 8 && e->Location.Y <= C.Y + 8 &&
				moving_A == false && moving_B == false && moving_A1 == false &&
				moving_B1 == false && moving_C1 == false)
			{
				C.X = e->Location.X;
				C.Y = e->Location.Y;
				moving_C = true;
			}
			//Точка А1
			if (e->Location.X >= A1.X - 8 && e->Location.X <= A1.X + 8 &&
				e->Location.Y >= A1.Y - 8 && e->Location.Y <= A1.Y + 8 &&
				moving_B == false && moving_C == false && moving_A == false &&
				moving_B1 == false && moving_C1 == false)
			{
				A1.X = e->Location.X;
				A1.Y = e->Location.Y;
				moving_A1 = true;
			}
			//Точка B1
			if (e->Location.X >= B1.X - 8 && e->Location.X <= B1.X + 8 &&
				e->Location.Y >= B1.Y - 8 && e->Location.Y <= B1.Y + 8 &&
				moving_A == false && moving_C == false && moving_A1 == false &&
				moving_B == false && moving_C1 == false)
			{
				B1.X = e->Location.X;
				B1.Y = e->Location.Y;
				moving_B1 = true;
			}
			//Точка C1
			if (e->Location.X >= C1.X - 8 && e->Location.X <= C1.X + 8 &&
				e->Location.Y >= C1.Y - 8 && e->Location.Y <= C1.Y + 8 &&
				moving_A == false && moving_B == false && moving_A1 == false &&
				moving_B1 == false && moving_C == false)
			{
				C1.X = e->Location.X;
				C1.Y = e->Location.Y;
				moving_C1 = true;
			}
			drawBrush->Color = Color::Red;
			print_border();
			l[0] = "A"; l[1] = "B"; l[2] = "C";
			draw_triangle(A, B, C, Color::Red,1);
			drawBrush->Color = Color::Blue;
			l[0] = "A'"; l[1] = "B'"; l[2] = "C'";
			draw_triangle(A1, B1, C1, Color::Blue,1);
			pictureBox1->Invalidate();
			if (radioButton2->Checked == true) {
				label6->Text = "";
				label7->Text = "";
				label8->Text = "";
				label9->Text = "  -1  |            |\n"
					"P  = |            |\n"
					"        |            |\n";
				label10->Text = "B  = |            |\n";
				label11->Text = "        |            |\n"
					"A  = |            |\n";
				label12->Text = "        |            |\n"
					"C =  |            |\n"
					"        |            |\n";
			}
			if (radioButton1->Checked == true) {
				label6->Text = "        |            |\n"
					"C1= |            |\n"
					"        |            |\n";
				label7->Text = "        |            |\n"
					"C2= |            |\n"
					"        |            |\n";
				label8->Text = "        |            |\n"
					"C3= |            |\n"
					"        |            |\n";
				label9->Text = "        |            |\n"
					"C4= |            |\n"
					"        |            |\n";
				label10->Text = "        |            |\n"
					"C5= |            |\n"
					"        |            |\n";
				label11->Text = "        |            |\n"
					"C6= |            |\n"
					"        |            |\n";
				label12->Text = "        |            |\n"
					"C =  |            |\n"
					"        |            |\n";
			}
		}
	}
	return System::Void();
}



System::Void Laboratorywork1::triangle_transformation::print_border(){
	canvas->Clear(Color::White);
	canvas->DrawRectangle(gcnew Pen(Color::Black, 2), 0, 0, pictureBox1->Width, pictureBox1->Height);
	/*Сетка*/	
	Point temp1, temp2, temp3, temp4;
	temp1.X = 0; temp1.Y = 0;
	temp2.X = pictureBox1->Width; temp2.Y = 0;
	temp3.X = 0; temp3.Y = 0;
	temp4.X = 0; temp4.Y = pictureBox1->Height;
	for (int i = 0; i < 10; i++) {
		canvas->DrawLine(gcnew Pen(Color::Black, 1), temp1, temp2);
		canvas->DrawLine(gcnew Pen(Color::Black, 1), temp3, temp4);
		temp1.Y = temp1.Y + 60;
		temp2.Y = temp2.Y + 60;
		temp3.X = temp3.X + 60;
		temp4.X = temp4.X + 60;
	}
	canvas->DrawLine(gcnew Pen(Color::Black, 5), pictureBox1->Width / 2, 0, pictureBox1->Width / 2, pictureBox1->Height);
	canvas->DrawLine(gcnew Pen(Color::Black, 5), 0, pictureBox1->Height / 2, pictureBox1->Width, pictureBox1->Height / 2);
	canvas->DrawLine(gcnew Pen(Color::Black, 5), pictureBox1->Width, pictureBox1->Height / 2, pictureBox1->Width - 20, pictureBox1->Height / 2 + 20);
	canvas->DrawLine(gcnew Pen(Color::Black, 5), pictureBox1->Width, pictureBox1->Height / 2, pictureBox1->Width - 20, pictureBox1->Height / 2 - 20);
	canvas->DrawLine(gcnew Pen(Color::Black, 5), pictureBox1->Width / 2, 0, pictureBox1->Width / 2 - 20, 20);
	canvas->DrawLine(gcnew Pen(Color::Black, 5), pictureBox1->Width / 2, 0, pictureBox1->Width / 2 + 20, 20);


	return System::Void();
}

System::Void Laboratorywork1::triangle_transformation::draw_triangle(Point a,Point b,Point c, Color col,int type_line){
	canvas->DrawString(marshal_as<System::String^>(l[0]) , fn, drawBrush, a.X - 40, a.Y - 40);
	canvas->DrawString(marshal_as<System::String^>(l[1]), fn, drawBrush, b.X - 40, b.Y - 40);
	canvas->DrawString(marshal_as<System::String^>(l[2]), fn, drawBrush, c.X - 40, c.Y - 40);
	canvas->FillEllipse(gcnew SolidBrush(col), a.X - 10, a.Y - 8, 16, 16);
	canvas->FillEllipse(gcnew SolidBrush(col), b.X - 10, b.Y - 8, 16, 16);
	canvas->FillEllipse(gcnew SolidBrush(col), c.X - 10, c.Y - 8, 16, 16);
	if (type_line==1) {
		canvas->DrawLine(gcnew Pen(col, 4), a, b);
		canvas->DrawLine(gcnew Pen(col, 4), a, c);
		canvas->DrawLine(gcnew Pen(col, 4), c, b);
	}
	if (type_line == 2) {
		Pen^ dotpen = gcnew Pen(col, 4);
		dotpen->DashStyle = System::Drawing::Drawing2D::DashStyle::DashDotDot;
		canvas->DrawLine(dotpen, a, b);
		canvas->DrawLine(dotpen, a, c);
		canvas->DrawLine(dotpen, c, b);
	}
	return System::Void();
}
System::Void Laboratorywork1::triangle_transformation::radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (radioButton1->Checked == true) {
		label6->Text = "        |            |\n"
									 "C1= |            |\n"
									 "        |            |\n";
		label7->Text = "        |            |\n"
									 "C2= |            |\n"
									 "        |            |\n";
		label8->Text = "        |            |\n"
									 "C3= |            |\n"
									 "        |            |\n";
		label9->Text = "        |            |\n"
									 "C4= |            |\n"
								 	 "        |            |\n";
		label10->Text = "        |            |\n"
										"C5= |            |\n"
										"        |            |\n";
		label11->Text = "        |            |\n"
										"C6= |            |\n"
										"        |            |\n";
		label12->Text = "        |            |\n"
										"C =  |            |\n"
										"        |            |\n";
	}
	return System::Void();
}
System::Void Laboratorywork1::triangle_transformation::radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
	if (radioButton2->Checked == true) {
		label6->Text = "";
		label7->Text = "";
		label8->Text = "";
		label9->Text = "  -1  |            |\n"
									 "P  = |            |\n"
									 "        |            |\n";
		label10->Text ="B  = |            |\n";
		label11->Text = "        |            |\n"
										"A  = |            |\n";
		label12->Text = "        |            |\n"
										"C =  |            |\n"
										"        |            |\n";
	}
	return System::Void();
}


System::Void Laboratorywork1::triangle_transformation::transformation(){
	Point center_coordinat;
	//Матрица C1 - перенос A в начало координат
	center_coordinat.X = pictureBox1->Width / 2;
	center_coordinat.Y = pictureBox1->Height / 2;
	Point transfer;
	transfer.X = A.X - center_coordinat.X;
	transfer.Y = A.Y - center_coordinat.Y;
	C1_A.X = A.X - transfer.X; C1_A.Y = A.Y - transfer.Y;
	C1_B.X = B.X - transfer.X; C1_B.Y = B.Y - transfer.Y;
	C1_C.X = C.X - transfer.X; C1_C.Y = C.Y - transfer.Y;
	//Матрица C6 - перенос A1 в начало координат
	center_coordinat.X = pictureBox1->Width / 2;
	center_coordinat.Y = pictureBox1->Height / 2;
	Point transfer1;
	transfer1.X = A1.X - center_coordinat.X;
	transfer1.Y = A1.Y - center_coordinat.Y;
	C6_A.X = A1.X - transfer1.X; C6_A.Y = A1.Y - transfer1.Y;
	C6_B.X = B1.X - transfer1.X; C6_B.Y = B1.Y - transfer1.Y;
	C6_C.X = C1.X - transfer1.X; C6_C.Y = C1.Y - transfer1.Y;
	//Матрица С2 - вращение треугольника 
	Point vector_B;
	vector_B.X = C1_B.X - center_coordinat.X;
	vector_B.Y = C1_B.Y - center_coordinat.Y;
	double phi = my_atan2(vector_B.X,vector_B.Y);
	C2_A = C1_A, C2_B = C1_B, C2_C = C1_C;
	double tmp_c2_b_x = C2_B.X - center_coordinat.X;
	double tmp_c2_b_y = -C2_B.Y + center_coordinat.Y;
	double tmp_c2_c_x = C2_C.X - center_coordinat.X;
	double tmp_c2_c_y = -C2_C.Y + center_coordinat.Y;
	C2_B.X = tmp_c2_b_x * cos(phi) - tmp_c2_b_y * sin(phi);
	C2_B.Y = tmp_c2_b_x * sin(phi) + tmp_c2_b_y * cos(phi);
	C2_C.X = tmp_c2_c_x * cos(phi) - tmp_c2_c_y * sin(phi);
	C2_C.Y = tmp_c2_c_x * sin(phi) + tmp_c2_c_y * cos(phi);
	C2_B.X = center_coordinat.X+ C2_B.X;
	C2_C.X = center_coordinat.X+ C2_C.X;
	C2_B.Y = center_coordinat.Y- C2_B.Y;
	C2_C.Y = center_coordinat.Y- C2_C.Y;
	//Матрица С5 - вращение треугольника 
	Point vector_B1;
	vector_B1.X = C6_B.X - center_coordinat.X;
	vector_B1.Y = C6_B.Y - center_coordinat.Y;
	double phi1 = my_atan2(vector_B1.X, vector_B1.Y);
	C5_A = C6_A, C5_B = C6_B, C5_C = C6_C;
	double tmp_c5_b_x = C5_B.X - center_coordinat.X;
	double tmp_c5_b_y = -C5_B.Y + center_coordinat.Y;
	double tmp_c5_c_x = C5_C.X - center_coordinat.X;
	double tmp_c5_c_y = -C5_C.Y + center_coordinat.Y;
	C5_B.X = tmp_c5_b_x * cos(phi1) - tmp_c5_b_y * sin(phi1);
	C5_B.Y = tmp_c5_b_x * sin(phi1) + tmp_c5_b_y * cos(phi1);
	C5_C.X = tmp_c5_c_x * cos(phi1) - tmp_c5_c_y * sin(phi1);
	C5_C.Y = tmp_c5_c_x * sin(phi1) + tmp_c5_c_y * cos(phi1);
	C5_B.X = center_coordinat.X + C5_B.X;
	C5_C.X = center_coordinat.X + C5_C.X;
	C5_B.Y = center_coordinat.Y - C5_B.Y;
	C5_C.Y = center_coordinat.Y - C5_C.Y;
	//Матрица С3 - масштабирование. C5_B.X=C2_B.X, C5_C.Y=C2_C.Y
	double mx = double(C5_B.X - center_coordinat.X) / double(C2_B.X - center_coordinat.X);
	double my = double(C5_C.Y- center_coordinat.Y) / double(C2_C.Y- center_coordinat.Y);
	C3_A = C2_A, C3_B = C2_B, C3_C = C2_C;
	C3_B.Y = (C3_B.Y - center_coordinat.Y) * my + center_coordinat.Y;
	C3_B.X = (C3_B.X - center_coordinat.X) * mx + center_coordinat.X;
	C3_C.Y = (C3_C.Y - center_coordinat.Y) * my + center_coordinat.Y;
	C3_C.X = (C3_C.X - center_coordinat.X) * mx + center_coordinat.X;
	//Матрица С4 - сдвиг C3_C в C5_C
	double Syx = double(C5_C.X - C3_C.X)/ (center_coordinat.Y-C3_C.Y);
	C4_A = C3_A, C4_B = C3_B, C4_C = C3_C;
	C4_C.X = C3_C.X + Syx* (center_coordinat.Y - C3_C.Y);

	drawBrush->Color = Color::Green;
	l[0] = "a1"; l[1] = "b1"; l[2] = "c1";
	draw_triangle(C1_A, C1_B, C1_C, Color::Green, 2);
	drawBrush->Color = Color::LightGreen;
	l[0] = "a2"; l[1] = "b2"; l[2] = "c2";
	draw_triangle(C2_A, C2_B, C2_C, Color::LightGreen, 2);
	drawBrush->Color = Color::BurlyWood;
	l[0] = "a3"; l[1] = "b3"; l[2] = "c3";
	draw_triangle(C3_A, C3_B, C3_C, Color::BurlyWood, 2);
	drawBrush->Color = Color::Gray;
	l[0] = "a4"; l[1] = "b4"; l[2] = "c4";
	draw_triangle(C4_A, C4_B, C4_C, Color::Gray, 2);
	drawBrush->Color = Color::Aqua;
	l[0] = "a5"; l[1] = "b5"; l[2] = "c5";
	draw_triangle(C5_A, C5_B, C5_C, Color::Aqua, 2);
	drawBrush->Color = Color::BlueViolet;
	l[0] = "a6"; l[1] = "b6"; l[2] = "c6";
	draw_triangle(C6_A, C6_B, C6_C, Color::BlueViolet, 2);
	pictureBox1->Invalidate();

	tmp_transfer_X= -1*int(float(transfer.X) / float(60) * 10) / 10.0;
	tmp_transfer_Y = int(float(transfer.Y) / float(60) * 10) / 10.0;
	label6->Text ="          |1    \t\t 0    \t\t0 |\n"
								"С1 =  |0    \t\t 1    \t\t0 |\n"
								"          |"+tmp_transfer_X + "   \t\t" + tmp_transfer_Y + "   \t\t1 |\n";

	tmp_transfer1_X = int(float(transfer1.X) / float(60) * 10) / 10.0;
	tmp_transfer1_Y = -1*int(float(transfer1.Y) / float(60) * 10) / 10.0;
	label11->Text = "          |1    \t\t 0    \t\t0 |\n"
		"С6 =  |0    \t\t 1    \t\t0 |\n"
		"          |" + tmp_transfer1_X + "\t\t" + tmp_transfer1_Y + "\t\t1 |\n";

	tmp_cos_phi = int(cos(phi) * 1000) / 1000.0;
	tmp_sin_phi = int(sin(phi) * 1000) / 1000.0;
	label7->Text = "         |" + tmp_cos_phi + "\t\t" + tmp_sin_phi + "\t\t0 |\n"
								"C2 = |" + -1 * tmp_sin_phi + "\t\t" + tmp_cos_phi + "\t\t0 |\n"
								"         |0            0           1 |\n";

	tmp_cos_phi1 = int(cos(phi1) * 1000) / 1000.0;
	tmp_sin_phi1 = int(sin(phi1) * 1000) / 1000.0;
	label10->Text = "         |" + tmp_cos_phi1 + "\t\t" +-tmp_sin_phi1 + "\t\t0 |\n"
		"C5 = |" +  tmp_sin_phi1 + "\t\t" + tmp_cos_phi1 + "\t\t0 |\n"
		"         |0            0           1 |\n";

	mx = double(C5_B.X - center_coordinat.X) / double(C2_B.X - center_coordinat.X);
	my = double(-C5_C.Y + center_coordinat.Y) / double(-C2_C.Y + center_coordinat.Y);
	tmp_mx = int(mx * 1000) / 1000.0;
	my = double(-C5_C.Y + center_coordinat.Y) / double(-C2_C.Y + center_coordinat.Y);
	tmp_my = int(my * 1000) / 1000.0;
	label8->Text = "         |" + tmp_mx + " 0         0|\n"
								 "C3 = |0        " + tmp_my+ "  0|\n"
								 "         |0        0          1|\n";
	Syx = double(C5_C.X - C3_C.X) / (center_coordinat.Y - C3_C.Y);
	tmp_Syx = int(Syx * 1000) / 1000.0;
	label9->Text = "         |1            0         0|\n"
								 "C4 = |" + tmp_Syx + "     1         0|\n"
								 "         |0            0         1|\n";

	get_C();
		
	return System::Void();
}
System::Void Laboratorywork1::triangle_transformation::get_C() {
	float c1 [3][3] = { {1, 0, 0}, {0, 1, 0}, {tmp_transfer_X, tmp_transfer_Y, 1} };
	float c2 [3][3] = { {tmp_cos_phi,tmp_sin_phi, 0}, {-1 * tmp_sin_phi, tmp_cos_phi, 0}, {0, 0, 1} };
	float c3[3][3] = { {tmp_mx, 0, 0}, {0, tmp_my, 0}, {0, 0, 1} };
	float c4[3][3] = { {1, 0, 0}, {tmp_Syx, 1, 0}, {0, 0, 1} };
	float c5[3][3] = { {tmp_cos_phi1,  -1 * tmp_sin_phi1, 0}, {tmp_sin_phi1,tmp_cos_phi1, 0}, {0, 0, 1} };
	float c6[3][3] = { {1, 0, 0}, {0, 1, 0}, {tmp_transfer1_X, tmp_transfer1_Y, 1} };

	float tmp_c12[3][3]={ {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	float tmp_c34[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	float tmp_c56[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	float tmp_c1234[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };

	float c[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			for (int u = 0; u < 3; u++) {
				tmp_c12[i][j] += c1[i][u] * c2[u][j];
				tmp_c34[i][j] += c3[i][u] * c4[u][j];
				tmp_c56[i][j] += c5[i][u] * c6[u][j];
			}
		}
	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			for (int u = 0; u < 3; u++) {
				tmp_c1234[i][j] += tmp_c12[i][u] * tmp_c34[u][j];
			}
		}

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			for (int u = 0; u < 3; u++) {
				c[i][j] += tmp_c1234[i][u] * tmp_c56[u][j];
			}
		}
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			c[i][j] = int(c[i][j] * 100) / 100.0;
		}
	}
	label12->Text = "         |" + c[0][0] + "   "+ c[0][1]+ "   " + c[0][2] + "| \n"
									" C =  |" + c[1][0] + "   " + c[1][1] + "   " + c[1][2] + "| \n"
									"         |" + c[2][0] + "   " + c[2][1] + "   " + c[2][2] + "| \n";

	return System::Void();
}

double Laboratorywork1::triangle_transformation::my_atan2(int x, int y){
	double res;
	if (x != 0) {
		res = atan(double(y) / double(x));
	}
	if (x < 0) {
		res = res + M_PI;
	}
	return res;
}

System::Void Laboratorywork1::triangle_transformation::paired_points(){

	float c[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	float p_obr[3][3] = { {0, 0, 0}, {0, 0, 0}, {0, 0, 0} };
	float p[3][3] = { {tmp_A_X, tmp_A_Y, 1}, {tmp_B_X, tmp_B_Y, 1}, {tmp_C_X, tmp_C_Y, 1} };
	float p1[3][3] = {{tmp_A1_X, tmp_A1_Y, 1}, {tmp_B1_X, tmp_B1_Y, 1}, {tmp_C1_X, tmp_C1_Y, 1}};

	float d = 0;
	d += p[0][0] * p[1][1] * p[2][2];
	d += p[0][1] * p[1][2] * p[2][0];
	d += p[1][0] * p[2][1] * p[0][2];
	d -= p[0][2] * p[1][1] * p[2][0];
	d -= p[0][1] * p[1][0] * p[2][2];
	d -= p[0][0] * p[1][2] * p[2][1];
	double invdet = 1 / d;
	p_obr[0][0] = (p[1][1] * p[2][2] - p[2][1] * p[1][2]) * invdet;
	p_obr[1][0] = (p[1][2] * p[2][0] - p[1][0] * p[2][2]) * invdet;
	p_obr[2][0] = (p[1][0] * p[2][1] - p[2][0] * p[1][1]) * invdet;
	p_obr[0][1] = (p[0][2] * p[2][1] - p[0][1] * p[2][2]) * invdet;
	p_obr[1][1] = (p[0][0] * p[2][2] - p[0][2] * p[2][0]) * invdet;
	p_obr[2][1] = (p[2][0] * p[0][1] - p[0][0] * p[2][1]) * invdet;
	p_obr[0][2] = (p[0][1] * p[1][2] - p[0][2] * p[1][1]) * invdet;
	p_obr[1][2] = (p[1][0] * p[0][2] - p[0][0] * p[1][2]) * invdet;
	p_obr[2][2] = (p[0][0] * p[1][1] - p[1][0] * p[0][1]) * invdet;

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++) {
			for (int u = 0; u < 3; u++) {
				c[i][j] += p_obr[i][u] * p1[u][j];
			}
		}

	drawBrush->Color = Color::Red;
	print_border();
	l[0] = "A"; l[1] = "B"; l[2] = "C";
	draw_triangle(A, B, C, Color::Red, 1);
	drawBrush->Color = Color::Blue;
	l[0] = "A'"; l[1] = "B'"; l[2] = "C'";
	draw_triangle(A1, B1, C1, Color::Blue, 1);
	pictureBox1->Invalidate();

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			c[i][j] = int(c[i][j] * 100) / 100.0;
			p_obr[i][j] = int(p_obr[i][j] * 100) / 100.0;
		}
	}
	label9->Text = "   -1   |" + p_obr[0][0] + "   " + p_obr[0][1] + "   " + p_obr[0][2] + "| \n"
								 " P =  |" + p_obr[1][0] + "   " + p_obr[1][1] + "   " + p_obr[1][2] + "| \n"
								 "         |" + p_obr[2][0] + "   " + p_obr[2][1] + "   " + p_obr[2][2] + "| \n";
	label11->Text = "         |" + c[0][0] + "   " + c[0][1]  + "| \n"
									" A =  |" + c[1][0] + "   " + c[1][1]+ "| \n";

	label10->Text =	"B  = |" + c[2][0] + "   " + c[2][1] + " | \n";

	label12->Text = "         |" + c[0][0] + "   " + c[0][1] + "   " + c[0][2] + "| \n"
									" C =  |" + c[1][0] + "   " + c[1][1] + "   " + c[1][2] + "| \n"
									"         |" + c[2][0] + "   " + c[2][1] + "   " + c[2][2] + "| \n";

	return System::Void();
}

System::Void Laboratorywork1::triangle_transformation::button1_Click(System::Object^ sender, System::EventArgs^ e) {
	if (program_step > 12) {
		if (radioButton1->Checked == true) {
			transformation();
		}
		else {
			paired_points();
		}
	}
	
	return System::Void();
}

System::Void Laboratorywork1::triangle_transformation::button2_Click(System::Object^ sender, System::EventArgs^ e) {
	print_border();
	program_step = 1;
	A.X = -1; A.Y = -1; A1.X = -1; A1.Y = -1;
	B.X = -1; B.Y = -1; B1.X = -1; B1.Y = -1;
	C.X = -1; C.Y = -1; C1.X = -1; C1.Y = -1;
	pictureBox1->Invalidate();
	return System::Void();
}