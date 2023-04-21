#include "Human.h"
#include <cliext/vector> 
#pragma once

ref class MapDisease
{
private:
	System::Windows::Forms::PictureBox^ Picture;//Отображение карты
	System::Drawing::Bitmap^ Map;				//Карта
	int Dimension;								//Размерность карты эпидемии
	array<Human^>^ Network;						//Карта эпидемии
	cliext::vector<Human^> Ills;				//Заболевшие люди (Элементы с состоянием)
	System::Windows::Forms::Timer^ Processing;	//Таймер обработки эпидемии

public:
	property bool Activate {
		bool get() {
			return Processing->Enabled;
		}
		void set(bool value) {
			Processing->Enabled = value;
		}
	}


	ref struct Duration							//Группа длительности состояний (в днях)
	{
		int Incubation,							//Инкубация 
			Illness,							//Течение болезни
			Spreading;
	} Duration;

	ref struct Interactions {					//Группа взаимодесйтвий людей
		int touch,								//Количество контактов в день
			distance;							//Растояние 
	} Interactions;

	System::Void EndDay(System::Object^ sender, System::EventArgs^ e);
	void ReStart();

	MapDisease();																															//Стандартный конструктор карты эпидемии
	void SetMapDisease(int Dimension, int Size, int interval, System::Windows::Forms::Control::ControlCollection^ container);				//Конструктор карты эпидемии c выводом на экран
	~MapDisease() {};																														//Деструктор
};

