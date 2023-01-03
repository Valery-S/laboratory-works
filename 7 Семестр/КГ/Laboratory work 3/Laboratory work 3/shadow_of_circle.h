#pragma once

namespace Laboratorywork3 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Collections::Generic;

	/// <summary>
	/// Сводка для shadow_of_circle
	/// </summary>
	public ref class shadow_of_circle : public System::Windows::Forms::Form
	{
	public:
		shadow_of_circle(void){
			InitializeComponent();
			this->Select();
		}

	protected:
		~shadow_of_circle()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::NumericUpDown^ numericUpDown1;
	private: System::Windows::Forms::Label^ label7;

	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;

	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label13;




	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->numericUpDown1 = (gcnew System::Windows::Forms::NumericUpDown());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Location = System::Drawing::Point(536, 22);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(540, 600);
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &shadow_of_circle::pictureBox1_Paint);
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &shadow_of_circle::pictureBox1_MouseDown);
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &shadow_of_circle::pictureBox1_MouseMove);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &shadow_of_circle::pictureBox1_MouseUp);
			// 
			// button2
			// 
			this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button2->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->button2->Location = System::Drawing::Point(278, 490);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(242, 93);
			this->button2->TabIndex = 7;
			this->button2->Text = L"Очистить рабочее поле";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &shadow_of_circle::button2_MouseDown);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::Control;
			this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			this->button1->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(12, 490);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(242, 93);
			this->button1->TabIndex = 8;
			this->button1->Text = L"Построить габаритные лучи и тень";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &shadow_of_circle::button1_MouseDown);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Broadway", 26.25F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->label1->Location = System::Drawing::Point(161, 12);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(219, 40);
			this->label1->TabIndex = 9;
			this->label1->Text = L"Инструкция";
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(11, 80);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(509, 50);
			this->label2->TabIndex = 10;
			this->label2->Text = L"1) Установить положение ближнего источника \r\nсвета с помощью ЛКМ.";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(11, 150);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(486, 25);
			this->label3->TabIndex = 11;
			this->label3->Text = L"2) Задать положение прямой двумя точками.";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			this->label4->Location = System::Drawing::Point(12, 199);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(454, 25);
			this->label4->TabIndex = 12;
			this->label4->Text = L"3) Задать положение центра окружности.";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(12, 392);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(217, 25);
			this->label6->TabIndex = 15;
			this->label6->Text = L"Радиус окружности";
			// 
			// numericUpDown1
			// 
			this->numericUpDown1->Location = System::Drawing::Point(63, 512);
			this->numericUpDown1->Name = L"numericUpDown1";
			this->numericUpDown1->Size = System::Drawing::Size(120, 20);
			this->numericUpDown1->TabIndex = 16;
			this->numericUpDown1->ValueChanged += gcnew System::EventHandler(this, &shadow_of_circle::numericUpDown1_ValueChanged);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Cambria", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(449, 433);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(71, 19);
			this->label7->TabIndex = 17;
			this->label7->Text = L"max 100";
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(250, 385);
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(270, 45);
			this->trackBar1->TabIndex = 19;
			this->trackBar1->Scroll += gcnew System::EventHandler(this, &shadow_of_circle::trackBar1_Scroll);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Cambria", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(246, 433);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(50, 19);
			this->label8->TabIndex = 20;
			this->label8->Text = L"min 0";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(363, 357);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(17, 25);
			this->label9->TabIndex = 21;
			this->label9->Text = L" ";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Cambria", 12, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(364, 357);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(13, 19);
			this->label10->TabIndex = 22;
			this->label10->Text = L" ";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Cambria", 15.75F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			this->label5->ForeColor = System::Drawing::Color::Red;
			this->label5->Location = System::Drawing::Point(12, 246);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(70, 25);
			this->label5->TabIndex = 24;
			this->label5->Text = L"label5";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(109, 533);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(0, 13);
			this->label11->TabIndex = 25;
			this->label11->Visible = false;
			this->label11->Click += gcnew System::EventHandler(this, &shadow_of_circle::label11_Click);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Cambria", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label13->Location = System::Drawing::Point(8, 600);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(171, 22);
			this->label13->TabIndex = 28;
			this->label13->Text = L"©Сухоруков 19ВМ";
			// 
			// shadow_of_circle
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1105, 644);
			this->Controls->Add(this->label13);
			this->Controls->Add(this->label11);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label10);
			this->Controls->Add(this->label9);
			this->Controls->Add(this->label8);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->numericUpDown1);
			this->Name = L"shadow_of_circle";
			this->StartPosition = System::Windows::Forms::FormStartPosition::Manual;
			this->Text = L"Построение габаритных лучей и тени окружности на прямую от ближнего источника.";
			this->Load += gcnew System::EventHandler(this, &shadow_of_circle::shadow_of_circle_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numericUpDown1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		Graphics^ canvas;
		Pen^ pen;
		Brush^ brush;
		Color color;
		int size;
		Bitmap^ background;
		int program_step;
		Point light_source;
		int radius_light_source;
		Point circle;
		int radius_circle;
		//Точки прямой
		Point A; Point B;
		//Точки пересечения с прямой
		Point p1;	Point p2;
		bool is_A; bool is_B;
		double distance;
		bool flag_is_shadow = false;
		bool moving_A = false;
		bool moving_B = false;
		bool moving_circle = false;
		bool moving_light_source = false;
	private: System::Void shadow_of_circle_Load(System::Object^ sender, System::EventArgs^ e);

	private: System::Void button2_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
  private: System::Void button1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

	private: System::Void pictureBox1_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void pictureBox1_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);
	private: System::Void pictureBox1_Paint(System::Object^ sender, System::Windows::Forms::PaintEventArgs^ e);
	private: System::Void pictureBox1_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e);

	private: System::Void numericUpDown1_ValueChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e);

	private: System::Void my_Draw_line();
	private: System::Void my_Draw_light_source();
	private: System::Void my_Draw_circle();
	private: System::Void print_border();
	private: System::Void print_shadow();
	
private: System::Void label11_Click(System::Object^ sender, System::EventArgs^ e) {}
};
}
