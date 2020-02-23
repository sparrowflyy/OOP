#include "controller.hpp"
#include <cmath>
#include <algorithm> 



void Controller::control_player() {											//������������ �������� ���������
	_model->player.shape.move(_model->player.velocity);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && _model->player.left()-brick_width > 0)
		_model->player.velocity.x = -platform_velocity;
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) &&
		_model->player.right()+ brick_width < Window_width)
		_model->player.velocity.x = platform_velocity;
	else
		_model->player.velocity.x = 0;

}

void Controller::control_ball() {									  //������������ �������� ����, � ������ ��������� ���� � ��������, ������������ �������� 
	float player_x = _model->player.x();
	float player_y = _model->player.y();
	float ball_x = _model->ball.shape.getPosition().x;
	float ball_y = _model->ball.shape.getPosition().y;
	if (ball_y > Window_height || ball_y < 0 || ball_x <0 || ball_x>Window_width) _model->InGame = false;
	if (_model->ball.isMoving) {
		if (col_brick == _model->bricks.end() || abs(col_brick->y() - Window_height + brick_height/2) < ball_velocity) {	 //���� ��� ����� ���� � �������
			if (abs(ball_y - Window_height + platform_height+ball_rad) < ball_velocity) {
				if (abs(ball_x - player_x) < platform_width / 2 + ball_rad && ball_x >= player_x) _model->ball.velocity = { ball_velocity, -ball_velocity };
				if (abs(ball_x-player_x)<platform_width/2+ball_rad && ball_x <= player_x  ) _model->ball.velocity = { -ball_velocity, -ball_velocity };
				control_bricks();
				control_collision();																					 //��� ��� ������ ������� ���������
			}
		}
		 if (distance_to_ball(next_collision_x,next_collision_y,ball_x,ball_y)<1.4*ball_velocity){		   //��������� , ������� �� ����� �� ����� , ��� �� ���������
			_model->ball.velocity = next_velocity;
			control_bricks();
			control_collision();
		}
		_model->ball.shape.move(_model->ball.velocity);
	}
	else{																			//���� ����� �� �����, �� ����� �� ��������� => ��������� ������ � ���, �� ������ ���������
		_model->ball.set(_model->player.x(), _model->player.y()  - platform_height);
																						//���� ��������� � ����� �������� ����� - ��� ����� �����
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space)) {										  //���� ��������� � ������ - ��� ����� ������
			if(player_x < Window_width/2) _model->ball.velocity = { -ball_velocity,-ball_velocity };
			else _model->ball.velocity = { ball_velocity,-ball_velocity };
			_model->ball.isMoving = true;
			control_collision();
			}
	}
}

Line::Line(sf::Vector2f& velocity, sf::Vector2f& ball_point) {
	a = 1;
	b = -velocity.x / velocity.y;
	c = -a * ball_point.x - b * ball_point.y;
}

Line::Line(float x1, float y1, float x2, float y2) {
	a = y1 - y2;
	b = x2 - x1;
	c = x1 * y2 - x2 * y1;
}

float Line::check_distance(float x, float y) {
	return abs((a * x + b * y + c) / sqrt(a * a + b * b));
}

inline float scalar_mult(sf::Vector2f& v1, sf::Vector2f& v2) {
	return (v1.x*v2.x + v1.y*v2.y);
}

void Controller::place_of_collision(Line& trajectory) {
	if (col_brick == _model->bricks.end()) return;
	Line diagonal(col_brick->left(), col_brick->top(), col_brick->right(), col_brick->bottom());	 
	sf::Vector2f v_diagonal = { diagonal.a,diagonal.b };
	sf::Vector2f v_trajectory = { trajectory.a,trajectory.b };
	sf::Vector2f ball_position = _model->ball.shape.getPosition();					 // �������� ����������� �� ����� ����� ����������� ���
	float bx = ball_position.x;														  //1.���������� ���� ��������, �������� ������, ���������� ����� ��������� ����������
	float by = ball_position.y;														  //2. ������� ��������� ������������ �������� � ���������� ���� � � ��������� 
	if (scalar_mult(v_diagonal, v_trajectory) == 0) {								  //3. ���� ��� ������������, �� �������� ����� 4 ������,���� �� ������������, �� 4 ������
		if (_model->ball.shape.getPosition().y < col_brick->y()) {					  //(� ��� ����� ����� ���� ��������������� ���� ���, ��� ��� ���� 45 ��������)
			if (col_brick->y() <= trajectory.getY(col_brick->x())) {				  //4. ����� ����������� ���������� �������� ����� � ��������� ���������� ����,
																					  //� � ����������� �� ��������, ���������� Y ���������� ����� ���� ��� ���� �������� �����								
				next_collision_x = col_brick->right();
				next_collision_y = trajectory.getY(col_brick->right());	 //�������� ������ �� ������ �����
				next_velocity = { (-1)*_model->ball.velocity.x,_model->ball.velocity.y };
			}
			else {
				next_collision_x = trajectory.getX(col_brick->top());														  //������ �� ������� �����
				next_collision_y = col_brick->top();
				next_velocity = { _model->ball.velocity.x,_model->ball.velocity.y*(-1) };
			}
		}
		else {
			if (col_brick->y() >= trajectory.getY(col_brick->x())) {							 //�������� ����� �� ����� �����
				next_collision_x = col_brick->left();
				next_collision_y = trajectory.getY(col_brick->left());
				next_velocity = { (-1)*_model->ball.velocity.x,_model->ball.velocity.y };
			}
			else {
				next_collision_x = trajectory.getX(col_brick->bottom());						 //����� �� ������ �����
				next_collision_y = col_brick->bottom();
				next_velocity = { _model->ball.velocity.x,_model->ball.velocity.y*(-1) };
			}
		}
	}
	else {
		if (_model->ball.shape.getPosition().y <= col_brick->y()) {
			if (col_brick->y() <= trajectory.getY(col_brick->x())) { //�������� ������ �� ����� �����
				next_collision_x = col_brick->left();
				next_collision_y = trajectory.getY(col_brick->left());
				next_velocity = { (-1)*_model->ball.velocity.x,_model->ball.velocity.y };
			}
			else {
				next_collision_x = trajectory.getX(col_brick->top());								 //������ �� ������� �����
				next_collision_y = col_brick->top();
				next_velocity = { _model->ball.velocity.x,_model->ball.velocity.y*(-1) };
			}
		}
		else {
			if (col_brick->y() >= trajectory.getY(col_brick->x())) { //�������� ����� �� ������ �����
				next_collision_x = col_brick->right();
				next_collision_y = trajectory.getY(col_brick->right());
				next_velocity = { (-1)*_model->ball.velocity.x,_model->ball.velocity.y };
			}
			else {
				next_collision_x = trajectory.getX(col_brick->bottom());				//����� �� ������ �����
				next_collision_y = col_brick->bottom();
				next_velocity = { _model->ball.velocity.x,_model->ball.velocity.y*(-1) };
			}
		}
	}
	}
inline float distance_to_ball(float brick_x, float brick_y, float ball_x, float ball_y) {	 
	return sqrt((ball_y - brick_y)*(ball_y - brick_y) + (ball_x - brick_x)*(ball_x - brick_x));
}
void Controller::control_bricks() {
	if (col_brick == _model->bricks.end()) return;
	if (!col_brick->destroyable) {
		col_brick->shape.setFillColor(sf::Color::Red);
		return;
	}
	_model->score++;
	_model->bricks.erase(col_brick);
	if (_model->score==2600) _model->victory = true;
	col_brick = _model->bricks.end();
}

std::vector<Brick>::iterator* Controller::find_nearest(std::vector<std::vector<Brick>::iterator>& susp) {		  //����� ����������
	std::vector<Brick>::iterator* nearest = &susp[0];
	float ball_x = _model->ball.shape.getPosition().x;
	float ball_y = _model->ball.shape.getPosition().y;
	float min_distance = distance_to_ball((*nearest)->x(), (*nearest)->y(), ball_x, ball_y);
	float tmp_dist=min_distance;
	for (int i = 1; i < susp.size(); i++) {
		tmp_dist = distance_to_ball(susp[i]->x(), susp[i]->y(), ball_x, ball_y);
		if (tmp_dist < min_distance) {
			min_distance = tmp_dist;
			nearest = &susp[i];

		}
	}
	return nearest;
}
void Controller::control_collision() {
	sf::Vector2f ball_position = _model->ball.shape.getPosition();
	float ball_x = ball_position.x;
	float ball_y = ball_position.y;
	Line trajectory(_model->ball.velocity, ball_position);
	std::vector<std::vector<Brick>::iterator> suspects;
	for (auto it = _model->bricks.begin(); it != _model->bricks.end(); it++) {		//�������� "�������������" ������
		sf::Vector2f ball_brick_vector( it->x() - ball_x, it->y() - ball_y);	//�������� ��, ������� ��������� �� ������, �� � ������ ������� �� ����������� ��������
		if (trajectory.check_distance(it->x(), it->y()) < max_distance_to_collide && scalar_mult(_model->ball.velocity, ball_brick_vector)>=0) suspects.push_back(it);
	}
	if (suspects.size() != 0) {
															  //���� ��������� ����� �������������
		col_brick = *find_nearest(suspects);
		suspects.clear();
		col_brick->shape.setFillColor(sf::Color::White);
		this->place_of_collision(trajectory);
	}
	else {
		col_brick = _model->bricks.end();			 //���� ������������� ���, ������ �� ������ ����, ��� ��� ����� ��� ������ �������
		}
	
}
