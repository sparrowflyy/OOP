#pragma once
#include "model.hpp"

class Line;
class Controller {
	
public:
	Controller(Model* mod) { _model = mod; max_distance_to_collide = sqrt(brick_width*brick_width + brick_height * brick_height)/2; col_brick = _model->bricks.end();};
	void control_player();	  //��������������� �������� ���������
	void control_ball();	//��������������� �������� ����									  							//������� ��������
	void control_collision();	 //����������� �����, �� �������� ��� ��������
	void place_of_collision(Line& trajectory);		  //����������� �����, �� ������� �������� ���
	void control_bricks();		 // ��������/���������� ������
	std::vector<Brick>::iterator* find_nearest(std::vector<std::vector<Brick>::iterator>& susp); //������� ������ ���������� � ������ �����

	friend Line;

private:

	float next_collision_x;		  //���������� ������������ 
	float next_collision_y;
	sf::Vector2f next_velocity;		//��������� ��������, ������� ����� ����� �������				 
	std::vector<Brick>::iterator col_brick;		//�������� �� ����, �� �������� ��������� ���
	Model *_model;					  //������ ����
	float max_distance_to_collide;	  // �������� ��������� 
};

static inline float scalar_mult(sf::Vector2f& v1, sf::Vector2f& v2);	 //��������� ������������ ���� ��������
static inline float distance_to_ball(float brick_x, float brick_y, float ball_x, float ball_y);	 // ������ ���������� �� ����� �� ����

class Line {				//����� ������ � ������� �������
public:
	Line(sf::Vector2f& velocity, sf::Vector2f& ball_point);	 //������� ������ ����� ������ �������� � ���������� ������
	Line(float x1, float y1, float x2, float y2);			 //������ �� ���� ������
	float check_distance(float x, float y);					 //������ ���������� �� ������ �� �����
	float getY(float x) {return (-c - a * x) / b;};			//����������� � ��������� ���� �� ��������� � ������� ������
	float getX(float y) {return (-c - b * y) / a;};

	float a;
	float b;
	float c;
};