#include "Menu.h"
Menu::Menu(float width, float height)
{
	if (!font.loadFromFile("Font/ROGFonts-Regular.otf"))
	{
		//handle error ถ้าหาฟ้อนไม่เจอ ก้จะรันต่อได้ 
	}
	menu[0].setFont(font);
	menu[0].setCharacterSize(72);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Start");
	menu[0].setOrigin(menu[0].getLocalBounds().width / 2, menu[0].getLocalBounds().height / 2);
	menu[0].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 1));

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("How to play");
	menu[1].setOrigin(menu[1].getLocalBounds().width / 2, menu[1].getLocalBounds().height / 2);
	menu[1].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 2));

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Leaderboard");
	menu[2].setOrigin(menu[2].getLocalBounds().width / 2, menu[2].getLocalBounds().height / 2);
	menu[2].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 3));

	menu[3].setFont(font);
	menu[3].setFillColor(sf::Color::White);
	menu[3].setString("Exit");
	menu[3].setOrigin(menu[3].getLocalBounds().width / 2, menu[3].getLocalBounds().height / 2);
	menu[3].setPosition(sf::Vector2f(width / 2, height / (MAX_ITEMS + 1) * 4));
}

Menu::~Menu()
{

}

void Menu::Draw(sf::RenderWindow& window)
{
	for (int i = 0; i < MAX_ITEMS; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp()
{
	if (selectedItem - 1 >= 0)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
			selectedItem--; //ลบเเกนเข้าไป
		menu[selectedItem].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if (selectedItem + 1 < MAX_ITEMS)
	{
		menu[selectedItem].setFillColor(sf::Color::White);
			selectedItem++; //เพิ่มเเกนเข้าไป
		menu[selectedItem].setFillColor(sf::Color::Red);
	}
}