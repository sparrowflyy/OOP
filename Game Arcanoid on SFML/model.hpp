#pragma once
#include <SFML/Graphics.hpp"
#include <SFML/Window.hpp>
#include <vector>
#include <SFML/Audio.hpp>
constexpr int menu{ 200 };
constexpr float ball_rad{ 5.f }, ball_velocity{8.5 };
constexpr int Window_width{600 }, Window_height{800 };										  //�������� ��������� ������
constexpr float platform_width{ 60.f }, platform_height{ 15.f }, platform_velocity{ 8.f };
constexpr float brick_width{ 20.f }, brick_height{ 20.f };
class Ball {
public:								//����� ������
	Ball() {
		shape.setRadius(ball_rad);
		shape.setFillColor(sf::Color::Red);
		shape.setOrigin(ball_rad, ball_rad);
		shape.setOutlineThickness(-2.5);
		shape.setOutlineColor(sf::Color::Cyan);
		isMoving = false;
	};
	bool isMoving;
	sf::CircleShape shape;
	sf::Vector2f velocity;		//������ �������� ����
	void set(float x, float y) { shape.setPosition(x, y); };
  };

class Rectangle {										 //����� ���������������, �� ���� ����������� ���������	� �����
public:
	sf::RectangleShape shape;
	
	float x() const { return shape.getPosition().x; };
    float y() const { return shape.getPosition().y; }
	float left() { return x() - shape.getSize().x / 2.f; }
	float right() { return x() + shape.getSize().x / 2.f; }
	float top() { return y() - shape.getSize().y / 2.f; }
	float bottom() { return y() + shape.getSize().y / 2.f; }
	
};

class Platform:public Rectangle {
public:
	Platform() {												   //���������
		shape.setPosition(0, 0);
		shape.setSize({platform_width, platform_height});
		shape.setFillColor(sf::Color::Blue);
		shape.setOrigin(platform_width / 2.f, platform_height / 2.f);
		velocity = { 0,0 };
		shape.setOutlineThickness(-4.f);
		shape.setOutlineColor(sf::Color::Cyan);
	}
	sf::Vector2f velocity;				   //������ ��������
	void set(float x, float y) { shape.setPosition(x, y); };   //���������� ��������� ����
 };
class Brick :public Rectangle {
public:
	Brick(float x,float y, bool condition) {						  //�����
		shape.setPosition(x, y);
		shape.setSize({ brick_width, brick_height });
		if(condition)shape.setFillColor(sf::Color::Blue);
		else  shape.setFillColor(sf::Color::Red);
		shape.setOrigin(brick_width / 2.f, brick_height / 2.f);
		shape.setOutlineThickness(-2.f);
		shape.setOutlineColor(sf::Color(100, 250, 50));
		destroyable = condition;
	 }
	bool destroyable;	 //���� �����������, ���� �������������
};
class Model {
public:
	Model();
	int score; //����
	Platform player;   //�����
	Ball ball;		   //	���
	sf::RenderWindow window;	 //����
	std::vector<Brick> bricks;	  //������ ������ �� ������� ����
	bool InGame;				//� ���� �� ����� ( �� �������� ��)
	bool victory;			 //������� ��� ��������
};