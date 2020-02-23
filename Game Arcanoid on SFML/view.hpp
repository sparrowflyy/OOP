#pragma once

#include "model.hpp"

class View {
public:
	View(Model* mod) ;
	void intro();	   //отрисовка интро
	void draw();		//отрисовка игрового процесса
	void end();			  //отрисовка экрана конца
	void draw_score(float x,float y);	//рисуем счет
private:
	sf::Font font;		 //шрифт для отрисовки
	sf::Text score;		   // счет
	Model *_model;		   //модель
};