#include "Princess.h"

Princess::Princess(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f size, sf::Vector2f position) :
	animation(texture, imageCount, switchTime)
{
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(60.0f, 60.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

Princess::~Princess()
{

}

void Princess::Update(float deltaTime)
{
	row = 0;

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}

void Princess::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Princess::setTexture(sf::Texture* texture)
{
	body.setTexture(texture);
}

