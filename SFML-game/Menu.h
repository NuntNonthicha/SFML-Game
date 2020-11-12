#pragma once
#include<SFML\Graphics.hpp>
#define MAX_ITEMS 4  //start , how to play , leaderboard , exit

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void Draw(sf::RenderWindow& window);
	void MoveUp();
	void MoveDown();


private:
	int selectedItem = 0;
	sf::Font font;
	sf::Text menu[MAX_ITEMS];

};
