#include "model.hpp"

 Model::Model() {
	window.create(sf::VideoMode(Window_width+menu, Window_height), "Arcanoid");
	window.setFramerateLimit(60);
	ball.set(Window_width / 2, Window_height-2*ball_rad-platform_height);
	player.set(Window_width / 2, Window_height - platform_height/2);
	int i, j;
	for (i = 0; i < Window_width; i = i + brick_width) {
		Brick tmp(i + brick_width / 2, brick_height / 2, false);
		bricks.push_back(tmp);
	}
	for (i = 0; i < Window_height; i = i + brick_height) {
		Brick tmp1(brick_width/2, brick_height / 2+i, false);
		Brick tmp2(Window_width-brick_width/2, brick_height / 2+i, false);
		bricks.push_back(tmp1);
		bricks.push_back(tmp2);
	}
	bool destroy = true;
	for (i = 50; i < Window_width - brick_width-brick_width/2; i += 20) {
		for (int j = 50; j < Window_height/3 - brick_height; j += 20) {
			Brick tmp(i, j, destroy);
			bricks.push_back(tmp);
		}
	}
	score = 0;
	InGame = true;
	victory = false;
	
}
