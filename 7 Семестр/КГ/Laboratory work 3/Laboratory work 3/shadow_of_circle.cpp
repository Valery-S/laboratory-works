#include "shadow_of_circle.h"
#include<Windows.h>
#include<cmath>
#include<List>
using namespace System;
using namespace System::Windows::Forms;
using namespace std;

void main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);

	Laboratorywork3::shadow_of_circle form;
	Application::Run(% form);
}

System::Void Laboratorywork3::shadow_of_circle::shadow_of_circle_Load(System::Object^ sender, System::EventArgs^ e) {
	//canvas
	Bitmap^ Img = gcnew Bitmap(pictureBox1->Width, pictureBox1->Height);
	canvas = Graphics::FromImage(Img);
	pictureBox1->Image = Img;
	pictureBox1->BackColor = Color::White;
	print_border();
	//pen
	color = Color::Red;
	brush = gcnew SolidBrush(Color::Yellow);
	size = 4;
	pen = gcnew Pen(color, size);
	//program_step
	program_step = 1;
	//coordinates
	light_source.X = 0;
	light_source.Y = 0;
	circle.X = 0;
	circle.Y = 0;
	radius_light_source = 10;
	radius_circle = 30;
	A.X = 0; A.Y = 0; B.X = 0; B.Y = 0;
	is_A = false; is_B = false;
	distance = 0;
	numericUpDown1->Hide();
	trackBar1->Maximum = 100;
	trackBar1->Value = 30;
	trackBar1->Minimum = 0;
	trackBar1->TickFrequency = 10;
	label10->Text = "" + trackBar1->Value;
	label5->Text = "";
	return System::Void();
}

System::Void Laboratorywork3::shadow_of_circle::button2_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	print_border();
	light_source.X = 0;
	light_source.Y = 0;
	circle.X = 0;
	circle.Y = 0;
	radius_circle = (int)numericUpDown1->Value;
	A.X = 0; A.Y = 0; B.X = 0; B.Y = 0;
	is_A = false; is_B = false;
	flag_is_shadow = false;
	distance = 0;
	program_step = 1;
	label5->Text = "";
	pictureBox1->Invalidate();
	return System::Void();
}

System::Void Laboratorywork3::shadow_of_circle::button1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	print_shadow();
	pictureBox1->Invalidate();
	return System::Void();
}

System::Void Laboratorywork3::shadow_of_circle::pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){
	switch (program_step) {
	case 1:
		light_source.X = e->Location.X;
		light_source.Y = e->Location.Y;
		break;
	case 2:
		if (A.X == 0 && A.Y == 0 && B.X == 0 && B.Y == 0) {
			A.X = e->Location.X;
			A.Y = e->Location.Y;
			is_A = true;
		}
		else {
			B.X = e->Location.X;
			B.Y = e->Location.Y;
			is_B = true;
		}
		break;
	case 3:
		circle.X = e->Location.X;
		circle.Y = e->Location.Y;
		break;
	default:
		break;
	}

	pictureBox1->Invalidate();
	return System::Void();
}

System::Void Laboratorywork3::shadow_of_circle::pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e){
	moving_A = false;
	moving_B = false;
	moving_circle = false;
	moving_light_source = false;

	pictureBox1->Invalidate();
	return System::Void();
}

System::Void Laboratorywork3::shadow_of_circle::pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e){
	switch (program_step){
	case 1:
		my_Draw_light_source();
		break;
	case 2:
		my_Draw_line();
		break;
	case 3:
		my_Draw_circle();
		break;
	default:
		print_border();
		my_Draw_light_source();
		my_Draw_line();
		my_Draw_circle();
		if(flag_is_shadow==true){ print_shadow(); }
		break;
	}
	return System::Void();
}
System::Void Laboratorywork3::shadow_of_circle::pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	if (program_step > 3) {
		//Если нажата левая кнопка, проверяем совпадение позиции с элементами на холсте
		if (e->Button == Windows::Forms::MouseButtons::Left) {
			//Точка А
			if (e->Location.X >= A.X - 5 && e->Location.X <= A.X + 5 &&
				e->Location.Y >= A.Y - 5 && e->Location.Y <= A.Y + 5 &&
				moving_B == false && moving_light_source == false && moving_circle == false)
			{
				A.X = e->Location.X;
				A.Y = e->Location.Y;
				moving_A = true;
			}
			//Точка B
			if (e->Location.X >= B.X - 5 && e->Location.X <= B.X + 5 &&
				e->Location.Y >= B.Y - 5 && e->Location.Y <= B.Y + 5 &&
				moving_A == false && moving_light_source == false && moving_circle == false)
			{
				B.X = e->Location.X;
				B.Y = e->Location.Y;
				moving_B = true;
			}
			//Источник света
			if (e->Location.X >= light_source.X - 5 && e->Location.X <= light_source.X + 5 &&
				e->Location.Y >= light_source.Y - 5 && e->Location.Y <= light_source.Y + 5 &&
				moving_B == false && moving_A == false && moving_circle == false)
			{
				light_source.X = e->Location.X;
				light_source.Y = e->Location.Y;
				moving_light_source = true;
			}
			//Окружность
			if (e->Location.X >= circle.X - 5 && e->Location.X <= circle.X + 5 &&
				e->Location.Y >= circle.Y - 5 && e->Location.Y <= circle.Y + 5 &&
				moving_B == false && moving_light_source == false && moving_A == false)
			{
				circle.X = e->Location.X;
				circle.Y = e->Location.Y;
				moving_circle = true;
			}
			print_border();
			my_Draw_light_source();
			my_Draw_line();
			my_Draw_circle();
			if (flag_is_shadow == true) { print_shadow(); }
			pictureBox1->Invalidate();
		}
	}
	return System::Void();
}
System::Void Laboratorywork3::shadow_of_circle::my_Draw_line(){
	if (is_A == true && is_B == true) {
		canvas->DrawLine(pen, A, B);
		canvas->DrawEllipse(pen, A.X - 5, A.Y - 5, 10, 10);
		canvas->DrawEllipse(pen, B.X - 5, B.Y - 5, 10, 10);
		canvas->FillEllipse(gcnew SolidBrush(Color::Red), A.X - 5, A.Y - 5, 10, 10);
		canvas->FillEllipse(gcnew SolidBrush(Color::Red), B.X - 5, B.Y - 5, 10, 10);

		Point temp1,temp2;
		temp1.X = 535; temp2.X = 0;
		if (B.X - A.X != 0) {
			temp1.Y = (temp1.X * (B.Y - A.Y) - A.X * B.Y + B.X * A.Y) / (B.X - A.X);
			temp2.Y = (temp2.X * (B.Y - A.Y) - A.X * B.Y + B.X * A.Y) / (B.X - A.X);
		}
		else {
			temp1.Y = (temp1.X * (B.Y - A.Y) - A.X * B.Y + B.X * A.Y);
			temp2.Y = (temp2.X * (B.Y - A.Y) - A.X * B.Y + B.X * A.Y);
		}

		canvas->DrawLine(pen, temp1, temp2);

		program_step++;
	}
	else {
		if (is_A) {
			canvas->DrawEllipse(pen, A.X - 5, A.Y - 5, 10, 10);
			canvas->FillEllipse(gcnew SolidBrush(Color::Red), A.X - 5, A.Y - 5, 10, 10);
		}
	}
	return System::Void();
}

System::Void Laboratorywork3::shadow_of_circle::my_Draw_light_source() {
	if (light_source.X > 0 && light_source.Y > 0) {
		canvas->DrawEllipse(gcnew Pen(Color::Yellow, size), light_source.X - radius_light_source, light_source.Y - radius_light_source, radius_light_source * 2, radius_light_source * 2);
		canvas->FillEllipse(brush, light_source.X - radius_light_source, light_source.Y - radius_light_source, radius_light_source * 2, radius_light_source * 2);
		program_step++;
	}
	return System::Void();
}

System::Void Laboratorywork3::shadow_of_circle::my_Draw_circle() {
	if (circle.X > 0 && circle.Y > 0) {
		radius_circle = (int)trackBar1->Value;
		canvas->FillEllipse(gcnew SolidBrush(Color::Green), circle.X - 5, circle.Y - 5, 10, 10);
		canvas->DrawEllipse(gcnew Pen(Color::Green, size), circle.X - radius_circle, circle.Y - radius_circle, radius_circle * 2, radius_circle * 2);
		program_step++;
	}
	return System::Void();
}

System::Void Laboratorywork3::shadow_of_circle::numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	radius_circle = int(numericUpDown1->Value);
	print_border();
	program_step = 1;
	my_Draw_light_source();
	my_Draw_line();
	my_Draw_circle();
	if (flag_is_shadow == true) { print_shadow(); }
	pictureBox1->Invalidate();
	return System::Void();
}
System::Void Laboratorywork3::shadow_of_circle::trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e) {
	numericUpDown1->Value = trackBar1->Value;
	label10->Text = "" + trackBar1->Value;	
	return System::Void();
}


System::Void Laboratorywork3::shadow_of_circle::print_border() {
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
	return System::Void();
}

System::Void Laboratorywork3::shadow_of_circle::print_shadow() {
	if (program_step>3) {
		label5->Text = "";
		flag_is_shadow = true;
		Point Q = light_source;
		Point W1; Point W2;
		Point R = circle;
		double len_QR = pow((Q.X - R.X) * (Q.X - R.X) + (Q.Y - R.Y) * (Q.Y - R.Y), 0.5);
		double len_RW = radius_circle;
		double len_QW = len_QR * len_QR - len_RW * len_RW;
		if (len_QW < 0) {
			label5->Text = "Тени нет.\nИсточник света внутри окружности.";
			label5->ForeColor = Color::Purple;
			return System::Void();
		}
		else {
			len_QW = pow(len_QW, 0.5);
		}
		double a = Q.Y;
		double b = Q.X;
		double c = R.X;
		double d = R.Y;
		double k = len_RW / len_QW;
		double x,y;
		y = (-k * c + k * k * a + k * b + d) / (k * k + 1);
		x = c + k * y - k * a;
		W1.X = x;
		W1.Y = y;
		y = (k * c + k * k * a - k * b + d) / (k * k + 1);
		x = c - k * y + k * a;
		W2.X = x;
		W2.Y = y;

		double m, t, u, n;
		double m1, t1, u1, n1;
		t = (B.X - A.X) * (Q.Y - A.Y) + (B.Y - A.Y) * (A.X - Q.X);
		u =  (B.Y - A.Y)* (W1.X - Q.X)- (W1.Y - Q.Y) * (B.X - A.X);
		m = t / u;
		if(B.X - A.X!=0){ n = (Q.X - A.X + m * (W1.X - Q.X)) / (B.X - A.X); }
		else { n = (Q.X - A.X + m * (W1.X - Q.X)); }
		p1.X = A.X + n * (B.X - A.X);
		p1.Y = A.Y + n * (B.Y - A.Y);

		t1 = (B.X - A.X) * (Q.Y - A.Y) + (B.Y - A.Y) * (A.X - Q.X);
		u1 = (B.Y - A.Y) * (W2.X - Q.X) - (W2.Y - Q.Y) * (B.X - A.X);
		m1 = t1 / u1;
		if(B.X - A.X!=0){ n1 = (Q.X - A.X + m1 * (W2.X - Q.X)) / (B.X - A.X); }
		else{ n1 = (Q.X - A.X + m1 * (W2.X - Q.X)); }
		p2.X = A.X + n1 * (B.X - A.X);
		p2.Y = A.Y + n1 * (B.Y - A.Y);


		Point W3; Point W4;
		W4.X = (W2.X - Q.X) * 800;
		W4.Y = (W2.Y - Q.Y) * 800;
		W3.X = (W1.X - Q.X) * 800;
		W3.Y = (W1.Y - Q.Y) * 800;
		//Точки тени
		Point shadow1, shadow2;
		shadow1 = p1;
		shadow2 = p2;
		bool flag_sh1 = true;
		//Точки пересечения с окружностью
		canvas->FillEllipse(gcnew SolidBrush(Color::Red), W1.X - 5, W1.Y - 5, 10, 10);
		canvas->FillEllipse(gcnew SolidBrush(Color::Red), W2.X - 5, W2.Y - 5, 10, 10);
		//Первый луч
		if ((m < 1) && (m > 0)) {
			Pen^ dotpen = gcnew Pen(Color::Purple, 5);
			dotpen->DashStyle = System::Drawing::Drawing2D::DashStyle::DashDotDot;
			canvas->DrawLine(dotpen, Q, W1);
		}
		else {
			if (m > 1) {
				canvas->DrawLine(gcnew Pen(Color::Yellow, size), Q, p1);
			}
			if (m < 0) {
				canvas->DrawLine(gcnew Pen(Color::Yellow, size), Q, W3);
				if (p1.X < circle.X) {
					if (light_source.Y < circle.Y) {
						shadow1.X = 540;
					}
					else {
						shadow1.X = 0;
					}
					if (B.X - A.X != 0) { shadow1.Y = A.Y + (shadow1.X - A.X) * (B.Y - A.Y) / (B.X - A.X); }
					else { shadow1.Y = A.Y + (shadow1.X - A.X) * (B.Y - A.Y); }
				}
			}
		}
		//Второй луч
		if ((m1 < 1) && (m1 > 0)) {
			Pen^ dotpen = gcnew Pen(Color::Purple, 5);
			dotpen->DashStyle = System::Drawing::Drawing2D::DashStyle::DashDotDot;
			canvas->DrawLine(dotpen, Q, W2);
		}
		else {
			if (m1 > 1) {
				canvas->DrawLine(gcnew Pen(Color::Yellow, size), Q, p2);
			}
			if (m1 < 0) {
				canvas->DrawLine(gcnew Pen(Color::Yellow, size), Q, W4);
				if (p2.X > circle.X) {
					shadow2.X = 0;
					if (B.X - A.X != 0) { shadow2.Y = A.Y + (shadow2.X - A.X) * (B.Y - A.Y) / (B.X - A.X); }
					else { shadow2.Y = A.Y + (shadow2.X - A.X) * (B.Y - A.Y); }
				}
			}
		}
		if ((m1 < 0) &&(m<0)){
			flag_sh1 = false;
		}
		//Тень
		if (flag_sh1 == true) {
			if (!(m1 < 0 && m < 0)) {
				canvas->DrawLine(gcnew Pen(Color::Blue, size), shadow1, shadow2);
			}
		}

	}
	return System::Void();
}
