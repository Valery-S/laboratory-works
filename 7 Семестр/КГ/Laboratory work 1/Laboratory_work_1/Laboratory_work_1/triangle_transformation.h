#pragma once
#include<vector>
#include<string>
namespace Laboratorywork1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для triangle_transformation
	/// </summary>
	public ref class triangle_transformation : public System::Windows::Forms::Form
	{
	public:
		triangle_transformation(void)
		{
			InitializeComponent();
			this->Select();
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~triangle_transformation()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^ label1;
	protected:
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Label^ label14;

	private: System::ComponentModel::IContainer^ components;



	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Broadway", 26.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label1->Location = System::Drawing::Point(35, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(219, 40);
			this->label1->TabIndex = 10;
			this->label1->Text = L"Инструкция";
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(342, 12);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(600, 600);
			this->pictureBox1->TabIndex = 11;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &triangle_transformation::pictureBox1_Paint);
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &triangle_transformation::pictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &triangle_transformation::pictureBox1_MouseMove);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &triangle_transformation::pictureBox1_MouseUp);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(37, 69);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(239, 75);
			this->label2->TabIndex = 12;
			this->label2->Text = L"1) Задать положение\r\nпервого треугольника\r\nтретя точками";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(37, 160);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(246, 75);
			this->label3->TabIndex = 13;
			this->label3->Text = L"2) Задать положение \r\nвторого треугольника\r\nтремя точками ";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::Control;
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(42, 371);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(250, 98);
			this->button1->TabIndex = 14;
			this->button1->Text = L"Построить преобразования треугольника";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &triangle_transformation::button1_Click);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::SystemColors::Control;
			this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(42, 514);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(250, 98);
			this->button2->TabIndex = 15;
			this->button2->Text = L"Очистить поле";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &triangle_transformation::button2_Click);
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(406, 624);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(121, 75);
			this->label4->TabIndex = 16;
			this->label4->Text = L"       |            |\r\n P= |            |\r\n       |            |\r\n";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(720, 624);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(126, 75);
			this->label5->TabIndex = 17;
			this->label5->Text = L"        |            |\r\n P\'= |            |\r\n        |            |\r\n";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(948, 12);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(137, 75);
			this->label6->TabIndex = 18;
			this->label6->Text = L"          |            |\r\n C1 = |            |\r\n          |            |\r\n";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(948, 110);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(137, 75);
			this->label7->TabIndex = 19;
			this->label7->Text = L"          |            |\r\n C2 = |            |\r\n          |            |\r\n";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(948, 207);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(137, 75);
			this->label8->TabIndex = 20;
			this->label8->Text = L"          |            |\r\n C3 = |            |\r\n          |            |\r\n";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(948, 300);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(137, 75);
			this->label9->TabIndex = 21;
			this->label9->Text = L"          |            |\r\n C4 = |            |\r\n          |            |\r\n";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(948, 394);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(137, 75);
			this->label10->TabIndex = 22;
			this->label10->Text = L"          |            |\r\n C5 = |            |\r\n          |            |\r\n";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(948, 477);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(137, 75);
			this->label11->TabIndex = 23;
			this->label11->Text = L"          |            |\r\n C6 = |            |\r\n          |            |\r\n";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label12->Location = System::Drawing::Point(948, 563);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(136, 75);
			this->label12->TabIndex = 24;
			this->label12->Text = L"          |            |\r\n C =   |            |\r\n          |            |\r\n";
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButton1->Location = System::Drawing::Point(42, 268);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(231, 29);
			this->radioButton1->TabIndex = 25;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Метод разложения";
			this->radioButton1->UseVisualStyleBackColor = true;
			this->radioButton1->CheckedChanged += gcnew System::EventHandler(this, &triangle_transformation::radioButton1_CheckedChanged);
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->radioButton2->Location = System::Drawing::Point(42, 316);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(246, 29);
			this->radioButton2->TabIndex = 26;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Метод парных точек";
			this->radioButton2->UseVisualStyleBackColor = true;
			this->radioButton2->CheckedChanged += gcnew System::EventHandler(this, &triangle_transformation::radioButton2_CheckedChanged);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Cambria", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label13->Location = System::Drawing::Point(38, 675);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(171, 22);
			this->label13->TabIndex = 27;
			this->label13->Text = L"©Сухоруков 19ВМ";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Cambria", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label14->Location = System::Drawing::Point(949, 638);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(220, 66);
			this->label14->TabIndex = 28;
			this->label14->Text = L"Возможны расхождения\r\nмежду методами\r\nиз-за округления";
			// 
			// triangle_transformation
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1194, 706);
			this->Controls->Add(this->label14);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->label12);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->label1);
			this->MaximizeBox = false;
			this->Name = L"triangle_transformation";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"Расчёт матрицы преобразований треугольника методами разложения и парных точек";
			this->Load += gcnew System::EventHandler(this, &triangle_transformation::triangle_transformation_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private:
	Graphics^ canvas;
	System::Drawing::Font^ fn=gcnew System::Drawing::Font (L"Cambria", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
		System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204));
	System::Drawing::SolidBrush^ drawBrush = gcnew SolidBrush(Color::Fuchsia);
	//Точки треугольников
	Point A;	Point B; Point C;
	Point A1;	Point B1; Point C1;
	//Шаг программы
	int program_step;
	//Промежуточные точки
	Point C1_A, C1_B, C1_C;
	Point C2_A , C2_B, C2_C ;
	Point C3_A, C3_B, C3_C;
	Point C4_A, C4_B, C4_C;
	Point C5_A, C5_B, C5_C;
	Point C6_A, C6_B, C6_C;
	//Перемещение точек
	bool moving_A = false;
	bool moving_B = false;
	bool moving_C = false;
	bool moving_A1 = false;
	bool moving_B1 = false;
	bool moving_C1 = false;
	//Координаты
	float tmp_A_X; float tmp_A_Y;
	float tmp_B_X; float tmp_B_Y;
	float tmp_C_X; float tmp_C_Y;
	float tmp_A1_X; float tmp_A1_Y;
	float tmp_B1_X; float tmp_B1_Y;
	float tmp_C1_X; float tmp_C1_Y;
	//Сдвиг
	float tmp_transfer_X; float tmp_transfer_Y;
	float tmp_transfer1_X; float tmp_transfer1_Y;
	//Поворот
	float tmp_cos_phi; float tmp_cos_phi1;
	float tmp_sin_phi; float tmp_sin_phi1;
	//Масштабируемость
	float tmp_mx; float tmp_my;
	//Сдвиг
	float tmp_Syx;


	private: System::Void print_border();
	private: System::Void draw_triangle(Point a, Point b, Point c, Color col, int type_line);
	private: System::Void transformation();
	private: System::Void paired_points();
	private: double my_atan2(int x,int y);
  private: System::Void get_C();

	private: System::Void triangle_transformation_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
	private: System::Void pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void radioButton1_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void radioButton2_CheckedChanged(System::Object^ sender, System::EventArgs^ e);
};
}
