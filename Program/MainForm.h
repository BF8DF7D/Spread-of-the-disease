#pragma once

#include "MapDisease.h"

namespace Program {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::SplitContainer^ splitContainer;

	private: System::Windows::Forms::Button^ button2;

	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::NumericUpDown^ Numbers;

	private: System::Windows::Forms::NumericUpDown^ Length;

	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::NumericUpDown^ Illnesed;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::NumericUpDown^ Incubation;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::NumericUpDown^ Spreading;







	private: System::ComponentModel::IContainer^ components;






	protected:

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
			this->components = (gcnew System::ComponentModel::Container());
			this->splitContainer = (gcnew System::Windows::Forms::SplitContainer());
			this->Spreading = (gcnew System::Windows::Forms::NumericUpDown());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->Illnesed = (gcnew System::Windows::Forms::NumericUpDown());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->Incubation = (gcnew System::Windows::Forms::NumericUpDown());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->Length = (gcnew System::Windows::Forms::NumericUpDown());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->Numbers = (gcnew System::Windows::Forms::NumericUpDown());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer))->BeginInit();
			this->splitContainer->Panel1->SuspendLayout();
			this->splitContainer->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Spreading))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Illnesed))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Incubation))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Length))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Numbers))->BeginInit();
			this->SuspendLayout();
			// 
			// splitContainer
			// 
			this->splitContainer->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->splitContainer->FixedPanel = System::Windows::Forms::FixedPanel::Panel1;
			this->splitContainer->IsSplitterFixed = true;
			this->splitContainer->Location = System::Drawing::Point(0, 0);
			this->splitContainer->Name = L"splitContainer";
			// 
			// splitContainer.Panel1
			// 
			this->splitContainer->Panel1->Controls->Add(this->Spreading);
			this->splitContainer->Panel1->Controls->Add(this->textBox5);
			this->splitContainer->Panel1->Controls->Add(this->button1);
			this->splitContainer->Panel1->Controls->Add(this->button3);
			this->splitContainer->Panel1->Controls->Add(this->Illnesed);
			this->splitContainer->Panel1->Controls->Add(this->textBox4);
			this->splitContainer->Panel1->Controls->Add(this->Incubation);
			this->splitContainer->Panel1->Controls->Add(this->textBox3);
			this->splitContainer->Panel1->Controls->Add(this->Length);
			this->splitContainer->Panel1->Controls->Add(this->textBox2);
			this->splitContainer->Panel1->Controls->Add(this->textBox1);
			this->splitContainer->Panel1->Controls->Add(this->Numbers);
			this->splitContainer->Panel1->Controls->Add(this->button2);
			// 
			// splitContainer.Panel2
			// 
			this->splitContainer->Panel2->Enabled = false;
			this->splitContainer->Size = System::Drawing::Size(855, 664);
			this->splitContainer->SplitterDistance = 176;
			this->splitContainer->TabIndex = 5;
			// 
			// Spreading
			// 
			this->Spreading->Location = System::Drawing::Point(3, 377);
			this->Spreading->Name = L"Spreading";
			this->Spreading->Size = System::Drawing::Size(143, 20);
			this->Spreading->TabIndex = 13;
			this->Spreading->ValueChanged += gcnew System::EventHandler(this, &MainForm::ChangeSpreading);
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(3, 351);
			this->textBox5->Name = L"textBox5";
			this->textBox5->ReadOnly = true;
			this->textBox5->Size = System::Drawing::Size(143, 20);
			this->textBox5->TabIndex = 12;
			this->textBox5->Text = L"Вероятность заболевания";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(55, 46);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(68, 35);
			this->button1->TabIndex = 11;
			this->button1->Text = L"Restart";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(55, 87);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(68, 36);
			this->button3->TabIndex = 10;
			this->button3->Text = L"Start";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MainForm::button3_Click);
			// 
			// Illnesed
			// 
			this->Illnesed->Location = System::Drawing::Point(3, 221);
			this->Illnesed->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->Illnesed->Name = L"Illnesed";
			this->Illnesed->Size = System::Drawing::Size(143, 20);
			this->Illnesed->TabIndex = 9;
			this->Illnesed->ValueChanged += gcnew System::EventHandler(this, &MainForm::ChangeIllness);
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(3, 195);
			this->textBox4->Name = L"textBox4";
			this->textBox4->ReadOnly = true;
			this->textBox4->Size = System::Drawing::Size(143, 20);
			this->textBox4->TabIndex = 8;
			this->textBox4->Text = L"Время болезни\r\n";
			// 
			// Incubation
			// 
			this->Incubation->Location = System::Drawing::Point(3, 169);
			this->Incubation->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->Incubation->Name = L"Incubation";
			this->Incubation->Size = System::Drawing::Size(143, 20);
			this->Incubation->TabIndex = 7;
			this->Incubation->ValueChanged += gcnew System::EventHandler(this, &MainForm::ChangeIncubation);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(3, 143);
			this->textBox3->Name = L"textBox3";
			this->textBox3->ReadOnly = true;
			this->textBox3->Size = System::Drawing::Size(143, 20);
			this->textBox3->TabIndex = 6;
			this->textBox3->Text = L"Время инкубации";
			// 
			// Length
			// 
			this->Length->Location = System::Drawing::Point(3, 325);
			this->Length->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 20, 0, 0, 0 });
			this->Length->Name = L"Length";
			this->Length->Size = System::Drawing::Size(143, 20);
			this->Length->TabIndex = 5;
			this->Length->ValueChanged += gcnew System::EventHandler(this, &MainForm::ChangeLength);
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(3, 299);
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(143, 20);
			this->textBox2->TabIndex = 4;
			this->textBox2->Text = L"Дальность контактов ";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(3, 247);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(143, 20);
			this->textBox1->TabIndex = 3;
			this->textBox1->Text = L"Кол-во контактов в день";
			// 
			// Numbers
			// 
			this->Numbers->Location = System::Drawing::Point(3, 273);
			this->Numbers->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 10, 0, 0, 0 });
			this->Numbers->Name = L"Numbers";
			this->Numbers->Size = System::Drawing::Size(143, 20);
			this->Numbers->TabIndex = 2;
			this->Numbers->ValueChanged += gcnew System::EventHandler(this, &MainForm::ChandeNumbers);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::CornflowerBlue;
			this->button2->Location = System::Drawing::Point(3, 46);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(46, 77);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Step";
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(867, 671);
			this->Controls->Add(this->splitContainer);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->splitContainer->Panel1->ResumeLayout(false);
			this->splitContainer->Panel1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->splitContainer))->EndInit();
			this->splitContainer->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Spreading))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Illnesed))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Incubation))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Length))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Numbers))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion
		MapDisease^ Map = gcnew MapDisease();

	private: System::Void MainForm_Load(System::Object^ sender, System::EventArgs^ e) {
		Map->SetMapDisease(81, 6, 10, splitContainer->Panel2->Controls);
	}


	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		Map->EndDay(nullptr, nullptr);
	}

	private: System::Void ChandeNumbers(System::Object^ sender, System::EventArgs^ e) {
		Map->Interactions.touch = Convert::ToInt32(Numbers->Value);
	}

	private: System::Void ChangeLength(System::Object^ sender, System::EventArgs^ e) {
		Map->Interactions.distance = Convert::ToInt32(Length->Value);
	}
	private: System::Void ChangeIncubation(System::Object^ sender, System::EventArgs^ e) {
		Map->Duration.Incubation = Convert::ToInt32(Incubation->Value);
	}

	private: System::Void ChangeIllness(System::Object^ sender, System::EventArgs^ e) {
		Map->Duration.Illness = Convert::ToInt32(Illnesed->Value);
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		if (Map->Activate == false) {
			Map->Activate = true;
		}
		else {
			Map->Activate = false;
		}
	}
	private: System::Void ChangeSpreading(System::Object^ sender, System::EventArgs^ e) {
		Map->Duration.Spreading = Convert::ToInt32(Spreading->Value);
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		Map->ReStart();
	}
	};
}