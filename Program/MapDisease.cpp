#include "MapDisease.h"
#include <random>
#include <vector>
#include <cliext/iterator>

MapDisease::MapDisease() {
	Network = nullptr;
	Duration.Incubation = 0;
	Duration.Illness = 0;
	Picture = gcnew System::Windows::Forms::PictureBox();
	Processing = gcnew System::Windows::Forms::Timer();
	Processing->Enabled = false;
	Processing->Tick += gcnew System::EventHandler(this, &MapDisease::EndDay);
}

/* ����������� ����� ����������� 
 * Dimension - ����������� �����
 * Size - ������ ������ �����
 */
void MapDisease::SetMapDisease(int Dimension, int Size, int interval, System::Windows::Forms::Control::ControlCollection^ container) {
	this->Dimension = Dimension;													//����������� �����
	Network = gcnew array<Human^>(Dimension * Dimension);							//��������� ������ ��� ������ �������� Human
	int PixelSize = (Size + 2) * Dimension;											//������ ����� ����������� (� ��������)
	Map = gcnew System::Drawing::Bitmap(PixelSize, PixelSize, System::Drawing::Imaging::PixelFormat::Format32bppArgb);
	//�������� ����� �����������
	for (int row = 0; row < Dimension; row++) {
		//�������� ������ ����� �����������
		for (int colum = 0; colum < Dimension; colum++) {												//���� �������� ����� 
			int position = row * Dimension + colum;														//������� � �������
			Network[position] = gcnew Human(row, colum, Size);											//��������� ������ ��� ������ Human
			Network[position]->ChangeColor(Map);
		}
	}
	//������� ��������
	int position = Dimension * Dimension / 2;																	//������� �������� �� �������� �����
	Network[position]->Color = System::Drawing::Color::FromArgb(255, 192, 192);									//��������� ����� �������� �� ����������
	Network[position]->ChangeColor(Map);																		//��������� ����� �� �����
	Ills.push_back(Network[position]);																			//���������� �������� � ������ ��������� � ����������
	int around_position[4] = { position - Dimension, position + Dimension, position - 1, position + 1 };
	for each (int point in around_position) {																	//��������� ��������� ��������� � ������� ����������
		Network[point]->Color = System::Drawing::Color::FromArgb(255, 192, 192);								//��������� ����� �� ����������
		Network[point]->ChangeColor(Map);																		//��������� ������� �����
		Ills.push_back(Network[point]);																			//���������� � ������
	}

	//���� ������ ����� �����������
	Picture = gcnew System::Windows::Forms::PictureBox();												//��������� ������ ��� PictureBox
	Picture->Size = System::Drawing::Size(PixelSize, PixelSize);										//����������� ��������
	Picture->Location = System::Drawing::Point(0, 0);													//�������
	Picture->Image = Map;																				//������� ��������
	container->Add(Picture);																			//�����, ��� ����� �������� ��������� ����������

	//������ ��� ������������� ��������������
	Processing = gcnew System::Windows::Forms::Timer();													//��������� ������ 
	Processing->Interval = interval;																	//�������� (� ������������)
	Processing->Enabled = false;																		//���������� �������
	Processing->Tick += gcnew System::EventHandler(this, &MapDisease::EndDay);							//���������� ������� "��������� ��������� �������"
}


System::Void MapDisease::EndDay(System::Object^ sender, System::EventArgs^ e) {
//	int Count = 0;
	for (auto iterator = Ills.rbegin(); iterator != Ills.rend(); iterator.next()) {
//		Count += 1;
		Human^ diseased = iterator.get_ref();									//��������� �������� �� ���������
		diseased->ConditionTime += 1;											//���������� ������� ���������� � ��������� 
		
		//�������� ��������� � �����ب���� ����������
		if (diseased->Color == System::Drawing::Color::FromArgb(255, 192, 192)	//���������
			&& diseased->ConditionTime >= Duration.Incubation) {
			diseased->Color = System::Drawing::Color::Red;						//�� ��������� ���������� � �������
			diseased->ChangeColor(Map);											//�������� ���� ����� �������� �� �����
			diseased->ConditionTime = 0;										//�������� �������
		}
		else if (diseased->Color == System::Drawing::Color::Red					//�������
			&& diseased->ConditionTime >= Duration.Illness) {					//
			diseased->Color = System::Drawing::Color::DarkGray;					//�� ��������� ���������� � ������������
			diseased->ChangeColor(Map);											//�������� ���� ����� �������� �� �����
			Ills.erase(Ills.begin() + iterator.get_bias() - 1);					//������� ���� ������� �� ������� ��������� � ����������
		}

		if (diseased->Color != System::Drawing::Color::CornflowerBlue			//���� ������ �� �����
			&& diseased->AllInfected == false) {								//� ������ ���� ���� �� ��������� �������
			diseased->AllInfected = true;										//�������������� ������� ��� ������� � ������� ����������
			//��������������� �������
			for (int touch = 0; touch < Interactions.touch; touch++) {			//���������� ��������� �� ����
				std::random_device seed;										//����
				std::default_random_engine random(seed());						//�����������
				Human^ Infected = nullptr;
				for (int step = 0; step < 3 && Infected == nullptr; step++) {	//��������� ����� ������� �� ����� (3 �������)
					std::uniform_int_distribution<int> row_random(-Interactions.distance, Interactions.distance);	//�������� ����� � ������ �������������� �����������
					int row = row_random(random),																	//��������� �������� � ����������� � ��������� �������������
						colum_distanse = Interactions.distance - std::labs(row);									//���������� ������ ������������� ���������� �� ��������
					std::uniform_int_distribution<int> colum_random(-colum_distanse, colum_distanse);				//�������� ���������� ��������� �����
					int colum = colum_random(random);																//��������� �������� �� �������� 
					int position = (row + diseased->Position.Row) * Dimension + colum + diseased->Position.Colum;	//���������� ����� �������
					if (position < Dimension * Dimension && position >= 0) {										//������� �� ������� �� ������� ���������?
						if (Network[position]->Color == System::Drawing::Color::Gainsboro)							//���->������ �������� �������?
							Infected = Network[position];															//��->������� � �������� �������������
					}
				}
				std::uniform_int_distribution<int> Chance_Spreading(1, 100);										//�������� ����� ���������
				if (Infected != nullptr && Chance_Spreading(random) <= Duration.Spreading) {						//���� ������ ������������ � ���� ������� ������������� �������
					diseased->AllInfected = false;																	//��������������� ��������� �������� �� ����������
					Infected->Color = System::Drawing::Color::FromArgb(255, 192, 192);								//�������� ���� �� ����������
					Infected->ChangeColor(Map);																		//����������� �� �����
					Ills.push_back(Infected);																		//�������� � ������ �������� � ����������
				}
			}
		}
	}
	Picture->Image = Map;
	if (Ills.empty()) {
		Activate = false;
		System::Windows::Forms::MessageBox::Show("End");
	}
}

void MapDisease::ReStart() {
	for each (Human ^ element in Network) {
		element->AllInfected = false;
		element->ConditionTime = 0;
		element->Color = System::Drawing::Color::Gainsboro;
		element->ChangeColor(Map);
	}
	Ills.clear();
	int position = Dimension / 2 * (Dimension + 1);																//������� �������� �� �������� �����
	Network[position]->Color = System::Drawing::Color::FromArgb(255, 192, 192);									//��������� ����� �������� �� ����������
	Network[position]->ChangeColor(Map);																		//��������� ����� �� �����
	Ills.push_back(Network[position]);																			//���������� �������� � ������ ��������� � ����������
	int around_position[4] = { position - Dimension, position + Dimension, position - 1, position + 1 };
	for each (int point in around_position) {																	//��������� ��������� ��������� � ������� ����������
		Network[point]->Color = System::Drawing::Color::FromArgb(255, 192, 192);								//��������� ����� �� ����������
		Network[point]->ChangeColor(Map);																		//��������� ������� �����
		Ills.push_back(Network[point]);																			//���������� � ������
	}
	Picture->Image = Map;
}



//	System::Windows::Forms::MessageBox::Show("���������� ������: " + System::Convert::ToString(row) + "\n"
//		+ " ���������� �������: " + System::Convert::ToString(colum) + "\n"
//		+ " �������: " + System::Convert::ToString(position) + "\n");
//	System::Windows::Forms::MessageBox::Show(" Count array: " + System::Convert::ToString(Count) + "\n");
		//						+ " random_index: " + System::Convert::ToString(random_index) + "\n");


/*
Human^ MapDisease::LocateInfected(Human^ disease, int u) {
	Human^ Infected = nullptr;
		std::random_device r;
		for (int step = 0; step < 3 && Infected == nullptr; step++) {
			std::default_random_engine e1(r());
			std::uniform_int_distribution<int> row_random(-Interactions.distance, Interactions.distance);
			int row = row_random(e1),
				colum_distanse = Interactions.distance - std::labs(row);
			std::uniform_int_distribution<int> colum_random(-colum_distanse, colum_distanse);
			int colum = colum_random(e1);
			int position = (row + disease->Position.Row) * Dimension + colum + disease->Position.Colum;
			//	System::Windows::Forms::MessageBox::Show("���������� ������: " + System::Convert::ToString(row) + "\n"
			//		+ " ���������� �������: " + System::Convert::ToString(colum) + "\n"
			//		+ " �������: " + System::Convert::ToString(position) + "\n");
			if (position < Dimension * Dimension && position >= 0) {
				if (Network[position]->Color == System::Drawing::Color::Gainsboro)
					Infected = Network[position];
			}
		}
	return Infected;
}
*/
/*
void ListInfected(Human^ diseased, int number_touch, System::Collections::Generic::List<Human^>^ Infected) {

//	System::Windows::Forms::MessageBox::Show(" T before exit: " + System::Convert::ToString(number_touch) + "\n");

	if (number_touch >= 0 && diseased->Color == System::Drawing::Color::Gainsboro) {
		Infected->Add(diseased);
	}
	if (number_touch > 0) {
		diseased->AllInfected = true;
		for (int step = 0; step < diseased->Quantity_conection; step++) {
//			System::Windows::Forms::MessageBox::Show(" X: " + System::Convert::ToString(diseased->Position.Colum) + "\n"
//				+ " Y: " + System::Convert::ToString(diseased->Position.Row) + "\n"
//				+ " T: " + System::Convert::ToString(number_touch) + "\n");


			if (diseased->�onnection[step]->AllInfected != true)
				ListInfected(diseased->�onnection[step], number_touch - 1, Infected);
		}
		diseased->AllInfected = false;
	}
}

Human^ LocateInfected(Human^ diseased, int number_touch) {

	if (number_touch <= 0) {
		if (diseased->Color == System::Drawing::Color::Gainsboro) {
//			System::Windows::Forms::MessageBox::Show("return");
			return diseased;

		}
		else {
//			System::Windows::Forms::MessageBox::Show("nullptr");
			return nullptr;
		}
	}
	else {
		diseased->AllInfected = true;
		Human^ Infected = nullptr;
		cliext::random_shuffle(diseased->�onnection.begin(), diseased->�onnection.end());

		for (int step = 0; Infected == nullptr && step < diseased->Quantity_conection; step++) {

//			System::Windows::Forms::MessageBox::Show(" ������� ������ ��������� �������" + System::Convert::ToString(number_touch) + "\n"
//				+ " ������ �����: " + System::Convert::ToString(index) + "\n"
//				+ " ����� ������� ������: " + System::Convert::ToString(all_interaction.Count) + "\n"
//				+ " ������ ������ �� ����: " +System::Convert::ToString(all_interaction.Count != 0));

			if (diseased->�onnection[step]->AllInfected != true)
				Infected = LocateInfected(diseased->�onnection[step], number_touch - 1);
		}
		diseased->AllInfected = false;
		return Infected;
	}
}
*/
/*
		//����������� ������ ��������� �����
		for (int colum = 0; colum < Dimension - 1; colum++) {
			//����� ��������� ������
			short int position = row * Dimension + colum;												//������� � �������
			Network[position]->�onnection.push_back(Network[position + 1]);								//����� �������� �������� ������ �� ����������
			Network[position]->Quantity_conection += 1;													//��������� ���������� ������ �������� ��������
			Network[position + 1]->�onnection.push_back(Network[position]);								//����� ���������� �������� � �������
			Network[position + 1]->Quantity_conection += 1;												//��������� ���������� ������ ���������� ��������
			//����� ��������� �������
			if (row != 0) {																				//���� ��� �� ������ ������ 
				Network[position - Dimension]->�onnection.push_back(Network[position]);					//������� ���� ������� ������� � �������
				Network[position - Dimension]->Quantity_conection += 1;									//��������� ���������� ������ �������� ���� �������
				Network[position]->�onnection.push_back(Network[position - Dimension]);					//������� ������� ������� � ��������� ����
				Network[position]->Quantity_conection += 1;												//��������� ���������� ������ ����������������
			}
		}
	}
	*/

/*//�������� ����� ����������� 
	for (short int row = 0, CordY = 2; row < Dimension; row++, CordY += uSize + 1) {											//���� ����� �����	 
		//�������� ������ ����� �����������
		for (short int colum = 0, CordX = 2; colum < Dimension; colum++, CordX += uSize + 1) {								//���� �������� ����� 
			short int position = row * Dimension + colum;																		//������� � �������
			Map[position] = gcnew Human(row, colum, uSize);																//��������� ������ ��� ������ Human
			Map[position]->Location = System::Drawing::Point(CordX, CordY);												//��������� ������� �������
//			Map[position]->BackColorChanged += gcnew System::EventHandler(this, &MapDisease::ChangeGrop);				//������� ������� ��������� ���������� �������� BackColor
			Conteiner->Add(Map[position]);																				//���������� ������� � ������ ���������
		}
		//����������� ������ ��������� �����
		for (short int colum = 0; colum < Dimension - 1; colum++) {
			//����� ��������� ������
			short int position = row * Dimension + colum;																		//������� � �������
			Map[position]->�onnection.push_back(Map[position + 1]);														//����� �������� �������� ������ �� ����������
			Map[position + 1]->�onnection.push_back(Map[position]);														//����� ���������� �������� � �������
			//����� ��������� �������
			if (row != 0) {																								//���� ��� �� ������ ������ 
				Map[position - Dimension]->�onnection.push_back(Map[position]);											//������� ���� ������� ������� � �������
				Map[position]->�onnection.push_back(Map[position - Dimension]);											//������� ������� ������� � ��������� ����
			}
		}
	}	*/	

	/*				Human^ Infected = diseased;
					for (int step = 0; step < Interactions.distance;) {
						std::random_device r;
						std::default_random_engine e1(r());
						std::uniform_int_distribution<int> uniform_dist(0, diseased->Quantity_conection - 1);
						int mean = uniform_dist(e1);

							System::Windows::Forms::MessageBox::Show("============"
							+ "\n Touch				 : " + System::Convert::ToString(touch)
							+ "\n Quantity connection: " + System::Convert::ToString(diseased->Quantity_conection)
							+ "\n rand: " + System::Convert::ToString(mean)
							+ "\n ============");

	//					System::Windows::Forms::MessageBox::Show(System::Convert::ToString(rand));
						if (Infected->Color == System::Drawing::Color::Gainsboro) {
							Infected = Infected->�onnection[mean];
							step++;
						}

					}
					if (Infected->Color == System::Drawing::Color::Gainsboro) {
						Infected->Color = System::Drawing::Color::FromArgb(255, 192, 192);
						Infected->ChangeColor(Map);
					}*/

/*Human^ LocateInfected(Human^ diseased, int number_touch) {

	if (number_touch <= 0) {
		if (diseased->Color == System::Drawing::Color::Gainsboro) {
//			System::Windows::Forms::MessageBox::Show("return");
			return diseased;

		}
		else {
//			System::Windows::Forms::MessageBox::Show("nullptr");
			return nullptr;
		}
	}
	else {
		System::Collections::Generic::List<int> all_interaction;
		for (int number_interaction = 0; number_interaction < diseased->Quantity_conection; number_interaction++)
			all_interaction.Add(number_interaction);

		diseased->Cheaked = true;
		Human^ Infected = nullptr;
		while (Infected == nullptr && all_interaction.Count != 0) {
			std::random_device r;
			std::default_random_engine e1(r());
			std::uniform_int_distribution<int> uniform_dist(0, all_interaction.Count - 1);
			int index = uniform_dist(e1);

//			System::Windows::Forms::MessageBox::Show(" ������� ������ ��������� �������" + System::Convert::ToString(number_touch) + "\n"
//				+ " ������ �����: " + System::Convert::ToString(index) + "\n"
//				+ " ����� ������� ������: " + System::Convert::ToString(all_interaction.Count) + "\n"
//				+ " ������ ������ �� ����: " +System::Convert::ToString(all_interaction.Count != 0));
			
			if (diseased->�onnection[all_interaction[index]]->Cheaked != true)
				Infected = LocateInfected(diseased->�onnection[all_interaction[index]], number_touch - 1);
			all_interaction.RemoveAt(index);
		}
		diseased->Cheaked = false;
		return Infected;
	}
}*/