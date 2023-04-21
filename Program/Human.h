
#pragma once

ref class Human
{
internal:
	ref struct Location {					//Структура расположения ячейки
		int X, Y,							//Кординаты вернего левого угла																
			Size;							//Размер ячейки
	} Location;
	ref struct Position {
		int Row, Colum;						//Номер строки и столбца на карте
	}Position;
	bool AllInfected;

	System::Drawing::Color Color;			//Визуализация состояния (Цвет ячейки)
	unsigned char ConditionTime;			//Время состояния объекта

public:
	void ChangeColor(System::Drawing::Bitmap^ Map);
	Human();
	Human(int X, int Y, int Size);
	~Human() {};
};

/*	property Human^ Connect[int]{			//Получение связей вне сборки
		Human ^ get(int index) {
			return Сonnection[index];
		}
	};
	property int Condit {					//Получение состояния объекта вне сборки
		int get() {
			return ConditionTime;
		}
	};
	*/