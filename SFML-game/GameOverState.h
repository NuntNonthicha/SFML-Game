#pragma once
#include <SFML\Graphics.hpp>

class GameOverState
{
private:
	sf::RectangleShape container;
	sf::Font font1;
	sf::Text gameOverText;

	sf::RectangleShape background;

	sf::RenderWindow* window;

	void initBackground();
	void initFont();
public:
	GameOverState(sf::RenderWindow* window);
	~GameOverState();

	void render(sf::RenderTarget* target = NULL);
};

