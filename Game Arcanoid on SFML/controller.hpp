#pragma once
#include "model.hpp"

class Line;
class Controller {
	
public:
	Controller(Model* mod) { _model = mod; max_distance_to_collide = sqrt(brick_width*brick_width + brick_height * brick_height)/2; col_brick = _model->bricks.end();};
	void control_player();	  //контролирование движение платформы
	void control_ball();	//контролирование движения шара									  							//функции контроля
	void control_collision();	 //определение блока, от которого шар отскочит
	void place_of_collision(Line& trajectory);		  //определение грани, от которой отскочит шар
	void control_bricks();		 // удаление/перекраска блоков
	std::vector<Brick>::iterator* find_nearest(std::vector<std::vector<Brick>::iterator>& susp); //функция поиска ближаешего к шарику блока

	friend Line;

private:

	float next_collision_x;		  //координаты столкновения 
	float next_collision_y;
	sf::Vector2f next_velocity;		//следующая скорость, которая будет после отскока				 
	std::vector<Brick>::iterator col_brick;		//итератор на блок, от которого остскочит шар
	Model *_model;					  //модель игры
	float max_distance_to_collide;	  // половина диагонали 
};

static inline float scalar_mult(sf::Vector2f& v1, sf::Vector2f& v2);	 //скалярное произведение двух векторов
static inline float distance_to_ball(float brick_x, float brick_y, float ball_x, float ball_y);	 // расчет расстояние от блока до шара

class Line {				//класс работы с прямыми линиями
public:
	Line(sf::Vector2f& velocity, sf::Vector2f& ball_point);	 //задание прямой через вектор скорости и координаты шарика
	Line(float x1, float y1, float x2, float y2);			 //прямая по двум точкам
	float check_distance(float x, float y);					 //расчет расстояния от прямой до точки
	float getY(float x) {return (-c - a * x) / b;};			//подставляем в уравнение одну из координат и смотрим вторую
	float getX(float y) {return (-c - b * y) / a;};

	float a;
	float b;
	float c;
};