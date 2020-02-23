#pragma once

#include "model.hpp"

class View {
public:
	View(Model* mod) ;
	void intro();	   //��������� �����
	void draw();		//��������� �������� ��������
	void end();			  //��������� ������ �����
	void draw_score(float x,float y);	//������ ����
private:
	sf::Font font;		 //����� ��� ���������
	sf::Text score;		   // ����
	Model *_model;		   //������
};