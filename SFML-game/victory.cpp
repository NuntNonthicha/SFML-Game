#include "victory.h"
#include<iostream>

void victory::initBackground()
{

}

void victory::initFont()
{
	if (!this->font1.loadFromFile("Font/8-BIT WONDER.TTF"))//Font/ROGFonts-Regular.otf
	{
		std::cout << "ERROR TO LOAD FONT FROM GAMEOVERSTATE" << "\n";
	}
}

victory::victory(sf::RenderWindow* window)
{
	this->initBackground();
	this->initFont();

	this->container.setSize(
		sf::Vector2f(static_cast<float>(window->getSize().x) / 4.f,
			static_cast<float>(window->getSize().y)));
	this->container.setFillColor(sf::Color(255, 255, 255, 200));
	this->container.setPosition(
		sf::Vector2f(static_cast<float>(window->getSize().x) / 2.f -
			this->container.getSize().x / 2.f, 30.f));

	this->victoryText.setFont(font1);
	this->victoryText.setFillColor(sf::Color::White);
	this->victoryText.setCharacterSize(50);
	this->victoryText.setString("victory");
	this->victoryText.setPosition((this->container.getPosition().x + this->container.getSize().x / 2.f - this->victoryText.getGlobalBounds().width / 2.f) - 140.f,
		this->container.getPosition().y + 40.f);


}

victory::~victory()
{

}

void victory::render(sf::RenderTarget* target)
{
	target->draw(this->container);

	target->draw(this->victoryText);

}