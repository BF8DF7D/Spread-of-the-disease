
#pragma once

ref class Human
{
internal:
	ref struct Location {					//��������� ������������ ������
		int X, Y,							//��������� ������� ������ ����																
			Size;							//������ ������
	} Location;
	ref struct Position {
		int Row, Colum;						//����� ������ � ������� �� �����
	}Position;
	bool AllInfected;

	System::Drawing::Color Color;			//������������ ��������� (���� ������)
	unsigned char ConditionTime;			//����� ��������� �������

public:
	void ChangeColor(System::Drawing::Bitmap^ Map);
	Human();
	Human(int X, int Y, int Size);
	~Human() {};
};

/*	property Human^ Connect[int]{			//��������� ������ ��� ������
		Human ^ get(int index) {
			return �onnection[index];
		}
	};
	property int Condit {					//��������� ��������� ������� ��� ������
		int get() {
			return ConditionTime;
		}
	};
	*/