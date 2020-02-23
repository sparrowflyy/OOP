#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "model.hpp"
#include "view.hpp"
#include "controller.hpp"
int main()
{
	while (true) {
		Model model;
		View view(&model);
		Controller controller(&model);
		sf::Music music;
		music.openFromFile("arcanoid_intro.ogg");
		music.setVolume(50);
		music.play();
		music.setLoop(true);
		view.intro();
		while (model.window.isOpen()) {

			if (model.InGame == false || (model.victory)) break;
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) model.window.close();
			controller.control_ball();
			controller.control_player();
			view.draw();
		}

		view.end();
		if (!model.window.isOpen()) break;

	}
	return 0;
}