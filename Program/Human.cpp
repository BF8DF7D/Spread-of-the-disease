#include "Human.h"

Human::Human() {};

Human::Human(int row, int colum, int Size) {
	Position.Row = row;
	Position.Colum = colum;
	Location.X = row * (Size + 2) + 2;
	Location.Y = colum * (Size + 2) + 2;
	Location.Size = Size;
	AllInfected = false;
	Color = System::Drawing::Color::Gainsboro;
}

//Перекраска яечкий на карте
void Human::ChangeColor(System::Drawing::Bitmap^ Map) {
	for (int CordX = Location.X; CordX < Location.X + Location.Size; CordX++)
		for (int CordY = Location.Y; CordY < Location.Y + Location.Size; CordY++)
			Map->SetPixel(CordX, CordY, Color);
}