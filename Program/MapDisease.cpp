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

/* Конструктор карты заболевания 
 * Dimension - Размерность карты
 * Size - Размер ячейки карты
 */
void MapDisease::SetMapDisease(int Dimension, int Size, int interval, System::Windows::Forms::Control::ControlCollection^ container) {
	this->Dimension = Dimension;													//Размерность карты
	Network = gcnew array<Human^>(Dimension * Dimension);							//Выделение памяти под массив объектов Human
	int PixelSize = (Size + 2) * Dimension;											//Размер карты заболевания (в пикселях)
	Map = gcnew System::Drawing::Bitmap(PixelSize, PixelSize, System::Drawing::Imaging::PixelFormat::Format32bppArgb);
	//СОЗДАНИЕ КАРТЫ ЗАБОЛЕВАНИЯ
	for (int row = 0; row < Dimension; row++) {
		//СОЗДАНИЕ СТРОКИ КАРТЫ ЗАБОЛЕВАНИЙ
		for (int colum = 0; colum < Dimension; colum++) {												//Цикл столбцов карты 
			int position = row * Dimension + colum;														//Позиция в массиве
			Network[position] = gcnew Human(row, colum, Size);											//Выделение памяти под объект Human
			Network[position]->ChangeColor(Map);
		}
	}
	//НУЛЕВЫЕ ПАЦИЕНТЫ
	int position = Dimension * Dimension / 2;																	//Позиция элемента по середине карты
	Network[position]->Color = System::Drawing::Color::FromArgb(255, 192, 192);									//Изменение цвета элемента на заражённого
	Network[position]->ChangeColor(Map);																		//Изменение цвета на карте
	Ills.push_back(Network[position]);																			//Добавление элемента в вектор элементов с состоянием
	int around_position[4] = { position - Dimension, position + Dimension, position - 1, position + 1 };
	for each (int point in around_position) {																	//Заражение ближайших элементов к первому заражённому
		Network[point]->Color = System::Drawing::Color::FromArgb(255, 192, 192);								//Изменение цвета на заражённого
		Network[point]->ChangeColor(Map);																		//Изменение цветана карте
		Ills.push_back(Network[point]);																			//Добавление в вектор
	}

	//ОКНО ВЫВОДА КАРТЫ ЗАБОЛЕВАНИЯ
	Picture = gcnew System::Windows::Forms::PictureBox();												//Выделение памяти под PictureBox
	Picture->Size = System::Drawing::Size(PixelSize, PixelSize);										//Обределение размеров
	Picture->Location = System::Drawing::Point(0, 0);													//Позиции
	Picture->Image = Map;																				//Вставка картинки
	container->Add(Picture);																			//Вывод, как часть колекции элементов управления

	//ТАЙМЕР ДЛЯ БЕСПРЕРЫВНОГО МОДЕЛЯИРОВАНИЯ
	Processing = gcnew System::Windows::Forms::Timer();													//Выделение памяти 
	Processing->Interval = interval;																	//Интервал (в милисекундах)
	Processing->Enabled = false;																		//Активность таймера
	Processing->Tick += gcnew System::EventHandler(this, &MapDisease::EndDay);							//Обработчик события "Истечение заданного таймера"
}


System::Void MapDisease::EndDay(System::Object^ sender, System::EventArgs^ e) {
//	int Count = 0;
	for (auto iterator = Ills.rbegin(); iterator != Ills.rend(); iterator.next()) {
//		Count += 1;
		Human^ diseased = iterator.get_ref();									//Получение элемента из итератора
		diseased->ConditionTime += 1;											//Увеличение времени прибывания в состоянии 
		
		//УДАЛЕНИЕ ЭЛЕМЕНТОВ С ЗАВЕРШЁННЫМ СОСТОЯНИЕМ
		if (diseased->Color == System::Drawing::Color::FromArgb(255, 192, 192)	//Заражённые
			&& diseased->ConditionTime >= Duration.Incubation) {
			diseased->Color = System::Drawing::Color::Red;						//По окончанию превратить в больных
			diseased->ChangeColor(Map);											//Изменить цвет этого элемента на карте
			diseased->ConditionTime = 0;										//Сбросить счётчик
		}
		else if (diseased->Color == System::Drawing::Color::Red					//Больные
			&& diseased->ConditionTime >= Duration.Illness) {					//
			diseased->Color = System::Drawing::Color::DarkGray;					//По окончанию превратить в переболевших
			diseased->ChangeColor(Map);											//Изменить цвет этого элемента на карте
			Ills.erase(Ills.begin() + iterator.get_bias() - 1);					//Удалить этот элемент из вектора элементов с состоянием
		}

		if (diseased->Color != System::Drawing::Color::CornflowerBlue			//Если объект не болен
			&& diseased->AllInfected == false) {								//И вокруг него есть не заражённые объекты
			diseased->AllInfected = true;										//Предварительно считать все объекты в радиусе заражёнными
			//РАСПРОСТРАНЕНИЕ БОЛЕЗНИ
			for (int touch = 0; touch < Interactions.touch; touch++) {			//Количество контактов за день
				std::random_device seed;										//Ключ
				std::default_random_engine random(seed());						//Рандомайзер
				Human^ Infected = nullptr;
				for (int step = 0; step < 3 && Infected == nullptr; step++) {	//Рандомный выбор позиции на карте (3 попытки)
					std::uniform_int_distribution<int> row_random(-Interactions.distance, Interactions.distance);	//Диапозон чисел с равным распределением вероятности
					int row = row_random(random),																	//Получение смещения в соотвествии с выбранным рандомайзером
						colum_distanse = Interactions.distance - std::labs(row);									//Вычисление модуля максимального отклонения по столбцам
					std::uniform_int_distribution<int> colum_random(-colum_distanse, colum_distanse);				//Создание рандомного диапозона чисел
					int colum = colum_random(random);																//Получение смещения по столбцам 
					int position = (row + diseased->Position.Row) * Dimension + colum + diseased->Position.Colum;	//Вычисление новой позиции
					if (position < Dimension * Dimension && position >= 0) {										//Позиция не выходит за границы диапозона?
						if (Network[position]->Color == System::Drawing::Color::Gainsboro)							//Нет->Объект здоровый человек?
							Infected = Network[position];															//Да->Выбрать в качестве инфецируемого
					}
				}
				std::uniform_int_distribution<int> Chance_Spreading(1, 100);										//Диапозон шанса заражения
				if (Infected != nullptr && Chance_Spreading(random) <= Duration.Spreading) {						//Если найден инфецируемый и шанс ммегьше установленной границы
					diseased->AllInfected = false;																	//Предворительный результат заменить на отсутствие
					Infected->Color = System::Drawing::Color::FromArgb(255, 192, 192);								//Поменять цвет на заражённого
					Infected->ChangeColor(Map);																		//Перекрасить на карте
					Ills.push_back(Infected);																		//Добавить в вектор объектов с состоянием
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
	int position = Dimension / 2 * (Dimension + 1);																//Позиция элемента по середине карты
	Network[position]->Color = System::Drawing::Color::FromArgb(255, 192, 192);									//Изменение цвета элемента на заражённого
	Network[position]->ChangeColor(Map);																		//Изменение цвета на карте
	Ills.push_back(Network[position]);																			//Добавление элемента в вектор элементов с состоянием
	int around_position[4] = { position - Dimension, position + Dimension, position - 1, position + 1 };
	for each (int point in around_position) {																	//Заражение ближайших элементов к первому заражённому
		Network[point]->Color = System::Drawing::Color::FromArgb(255, 192, 192);								//Изменение цвета на заражённого
		Network[point]->ChangeColor(Map);																		//Изменение цветана карте
		Ills.push_back(Network[point]);																			//Добавление в вектор
	}
	Picture->Image = Map;
}



//	System::Windows::Forms::MessageBox::Show("Отклонение строки: " + System::Convert::ToString(row) + "\n"
//		+ " Отклонение столбца: " + System::Convert::ToString(colum) + "\n"
//		+ " Позиция: " + System::Convert::ToString(position) + "\n");
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
			//	System::Windows::Forms::MessageBox::Show("Отклонение строки: " + System::Convert::ToString(row) + "\n"
			//		+ " Отклонение столбца: " + System::Convert::ToString(colum) + "\n"
			//		+ " Позиция: " + System::Convert::ToString(position) + "\n");
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


			if (diseased->Сonnection[step]->AllInfected != true)
				ListInfected(diseased->Сonnection[step], number_touch - 1, Infected);
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
		cliext::random_shuffle(diseased->Сonnection.begin(), diseased->Сonnection.end());

		for (int step = 0; Infected == nullptr && step < diseased->Quantity_conection; step++) {

//			System::Windows::Forms::MessageBox::Show(" Глубина поиска следующей вершины" + System::Convert::ToString(number_touch) + "\n"
//				+ " Индекс связи: " + System::Convert::ToString(index) + "\n"
//				+ " Длина массива связей: " + System::Convert::ToString(all_interaction.Count) + "\n"
//				+ " Массив связей не пуст: " +System::Convert::ToString(all_interaction.Count != 0));

			if (diseased->Сonnection[step]->AllInfected != true)
				Infected = LocateInfected(diseased->Сonnection[step], number_touch - 1);
		}
		diseased->AllInfected = false;
		return Infected;
	}
}
*/
/*
		//ОБРАЗОВАНИЕ СВЯЗЕЙ ЭЛЕМЕНТОВ КАРТЫ
		for (int colum = 0; colum < Dimension - 1; colum++) {
			//Связь элементов строки
			short int position = row * Dimension + colum;												//Позиция в массиве
			Network[position]->Сonnection.push_back(Network[position + 1]);								//Связь текущего элемента строки со следующими
			Network[position]->Quantity_conection += 1;													//Увеличить количество связей текущего элемента
			Network[position + 1]->Сonnection.push_back(Network[position]);								//Связь следующего элемента с текущим
			Network[position + 1]->Quantity_conection += 1;												//Увеличить количество связей следующего элемента
			//Связь элементов столбца
			if (row != 0) {																				//Если это не первая строка 
				Network[position - Dimension]->Сonnection.push_back(Network[position]);					//Элемент выше текуего связать с текущим
				Network[position - Dimension]->Quantity_conection += 1;									//Увеличить количество связей элемента выше текщего
				Network[position]->Сonnection.push_back(Network[position - Dimension]);					//Текущий элемент связать с элементом выше
				Network[position]->Quantity_conection += 1;												//Увеличить количество связей текущегоэлумента
			}
		}
	}
	*/

/*//СОЗДАНИЕ КАРТЫ ЗАБОЛЕВАНИЙ 
	for (short int row = 0, CordY = 2; row < Dimension; row++, CordY += uSize + 1) {											//Цикл строк карты	 
		//СОЗДАНИЕ СТРОКИ КАРТЫ ЗАБОЛЕВАНИЙ
		for (short int colum = 0, CordX = 2; colum < Dimension; colum++, CordX += uSize + 1) {								//Цикл столбцов карты 
			short int position = row * Dimension + colum;																		//Позиция в массиве
			Map[position] = gcnew Human(row, colum, uSize);																//Выделение памяти под объект Human
			Map[position]->Location = System::Drawing::Point(CordX, CordY);												//Изменение позиции объекта
//			Map[position]->BackColorChanged += gcnew System::EventHandler(this, &MapDisease::ChangeGrop);				//Каждому объекту привязать обработчик действия BackColor
			Conteiner->Add(Map[position]);																				//Добавление Объекта в список элементов
		}
		//ОБРАЗОВАНИЕ СВЯЗЕЙ ЭЛЕМЕНТОВ КАРТЫ
		for (short int colum = 0; colum < Dimension - 1; colum++) {
			//Связь элементов строки
			short int position = row * Dimension + colum;																		//Позиция в массиве
			Map[position]->Сonnection.push_back(Map[position + 1]);														//Связь текущего элемента строки со следующими
			Map[position + 1]->Сonnection.push_back(Map[position]);														//Связь следующего элемента с текущим
			//Связь элементов столбца
			if (row != 0) {																								//Если это не первая строка 
				Map[position - Dimension]->Сonnection.push_back(Map[position]);											//Элемент выше текуего связать с текущим
				Map[position]->Сonnection.push_back(Map[position - Dimension]);											//Текущий элемент связать с элементом выше
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
							Infected = Infected->Сonnection[mean];
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

//			System::Windows::Forms::MessageBox::Show(" Глубина поиска следующей вершины" + System::Convert::ToString(number_touch) + "\n"
//				+ " Индекс связи: " + System::Convert::ToString(index) + "\n"
//				+ " Длина массива связей: " + System::Convert::ToString(all_interaction.Count) + "\n"
//				+ " Массив связей не пуст: " +System::Convert::ToString(all_interaction.Count != 0));
			
			if (diseased->Сonnection[all_interaction[index]]->Cheaked != true)
				Infected = LocateInfected(diseased->Сonnection[all_interaction[index]], number_touch - 1);
			all_interaction.RemoveAt(index);
		}
		diseased->Cheaked = false;
		return Infected;
	}
}*/