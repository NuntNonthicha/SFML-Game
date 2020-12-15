#pragma once
#include <SFML\Graphics.hpp>

class victory
{
private:
	sf::RectangleShape container;
	sf::Font font1;
	sf::Text victoryText;

	sf::RectangleShape background;

	sf::RenderWindow* window;

	void initBackground();
	void initFont();
public:
	victory(sf::RenderWindow* window);
	~victory();

	void render(sf::RenderTarget* target = NULL);
};

