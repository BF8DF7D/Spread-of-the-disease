#include "Human.h"
#include <cliext/vector> 
#pragma once

ref class MapDisease
{
private:
	System::Windows::Forms::PictureBox^ Picture;//����������� �����
	System::Drawing::Bitmap^ Map;				//�����
	int Dimension;								//����������� ����� ��������
	array<Human^>^ Network;						//����� ��������
	cliext::vector<Human^> Ills;				//���������� ���� (�������� � ����������)
	System::Windows::Forms::Timer^ Processing;	//������ ��������� ��������

public:
	property bool Activate {
		bool get() {
			return Processing->Enabled;
		}
		void set(bool value) {
			Processing->Enabled = value;
		}
	}


	ref struct Duration							//������ ������������ ��������� (� ����)
	{
		int Incubation,							//��������� 
			Illness,							//������� �������
			Spreading;
	} Duration;

	ref struct Interactions {					//������ �������������� �����
		int touch,								//���������� ��������� � ����
			distance;							//��������� 
	} Interactions;

	System::Void EndDay(System::Object^ sender, System::EventArgs^ e);
	void ReStart();

	MapDisease();																															//����������� ����������� ����� ��������
	void SetMapDisease(int Dimension, int Size, int interval, System::Windows::Forms::Control::ControlCollection^ container);				//����������� ����� �������� c ������� �� �����
	~MapDisease() {};																														//����������
};

