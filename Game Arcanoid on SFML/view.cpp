#include "view.hpp"


View::View(Model* mod) {
	_model = mod;
	score.setFillColor(sf::Color::White);
	font.loadFromFile("retro.ttf");
	score.setCharacterSize(50);
	score.setFont(font);
	
}
void View::draw_score(float x, float y) {
	score.setPosition(x, y);
	char buffer[10];												//отрисовка счета справа от игрового поля
	sprintf(buffer, "%d", _model->score * 10);
	score.setString(buffer);
	_model->window.draw(score);
};
void View::draw() {
	sf::Event event;
	while (_model->window.pollEvent(event))	 //чтобы окошко не лагало
	{
		if (event.type == sf::Event::Closed)
			_model->window.close();									 //отрисовка игрового процесса
	}
	_model->window.clear(sf::Color::Black);
	_model->window.draw(_model->player.shape);
	_model->window.draw(_model->ball.shape);
	for (auto it = _model->bricks.begin(); it != _model->bricks.end(); ++it) {
		_model->window.draw(it->shape);
	}
	draw_score(Window_width + menu - 180, menu);
	_model->window.display();
}
void View::intro() {
	
	_model->window.clear(sf::Color::Black);
	sf::Font font;
	font.loadFromFile("retro.ttf");
	sf::Text text;
	text.setFont(font);																//отрисовка интро с инструкцией и названием
	
	while (_model->window.isOpen()) {
		sf::Event event;
		while (_model->window.pollEvent(event))		  //чтобы окошко не лагало
		{
			if (event.type == sf::Event::Closed)
				_model->window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) _model->window.close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) break;
		text.setFillColor(sf::Color::Cyan);
		text.setString("ARCANOID");
		text.setCharacterSize(54);
		text.setPosition((Window_width+menu) /3.5, Window_height / 5);
		_model->window.draw(text);
		text.setFillColor(sf::Color::White);
		text.setPosition((Window_width + menu) / 30, Window_height / 2.5);
		text.setCharacterSize(25);
		text.setString(" Press 'Left', 'Right' to move platform!");
		_model->window.draw(text);
		text.setPosition((Window_width + menu) /6, Window_height / 2);
		text.setString(" Press 'Space' to fire the ball!");
		_model->window.draw(text);
		text.setString(" Press 'Enter' to start!");
		text.setPosition((Window_width + menu) / 3.5, Window_height / 1.5);
		_model->window.draw(text);
		text.setString(" Vorobyov Nikita 17345 AFTI 2019");
		text.setCharacterSize(20);
		text.setPosition((Window_width + menu) / 4, Window_height / 1.1);
		_model->window.draw(text);
		_model->window.display();
	}
	
}
void View::end() {

	sf::Text text;
	text.setFont(font);
	if (_model->victory)  text.setString("VICTORY!");
	else text.setString("GAME OVER!");
	sf::Text points;
	points.setFont(font);														//экран победы или поражения с полученными очками в течении игры
	text.setFillColor(sf::Color::Cyan);
	text.setCharacterSize(54);
	text.setPosition((Window_width + menu) / 3.7, Window_height / 3);
	points.setString("SCORE: ");
	points.setFillColor(sf::Color::Cyan);
	points.setCharacterSize(54);
	points.setPosition((Window_width + menu) / 3.7 - 100, Window_height / 3 + 100);

	while (_model->window.isOpen()) {
		sf::Event event;
		while (_model->window.pollEvent(event))			//чтобы окошко не лагало
		{
			if (event.type == sf::Event::Closed)
				_model->window.close();
		}
		_model->window.clear(sf::Color::Black);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) {
			_model->window.close();
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
			return;
		}
		draw_score((Window_width + menu) / 3.7+200, Window_height / 3 + 100);
		_model->window.draw(points);
		_model->window.draw(text);
		_model->window.display();
	}
}