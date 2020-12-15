#include "GameOverState.h"
#include<iostream>

void GameOverState::initBackground()
{

}

void GameOverState::initFont()
{
	if (!this->font1.loadFromFile("Font/8-BIT WONDER.TTF"))//Font/ROGFonts-Regular.otf
	{
		std::cout << "ERROR TO LOAD FONT FROM GAMEOVERSTATE" << "\n";
	}
}

GameOverState::GameOverState(sf::RenderWindow* window)
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

	this->gameOverText.setFont(font1);
	this->gameOverText.setFillColor(sf::Color::White);
	this->gameOverText.setCharacterSize(50);
	this->gameOverText.setString("GAMEOVER");
	this->gameOverText.setPosition((this->container.getPosition().x + this->container.getSize().x / 2.f - this->gameOverText.getGlobalBounds().width / 2.f) - 140.f,
		this->container.getPosition().y + 40.f);


}

GameOverState::~GameOverState()
{

}

void GameOverState::render(sf::RenderTarget* target)
{
	target->draw(this->container);

	target->draw(this->gameOverText);

//arget->draw(this->background);
}