#include "Coin.h"

Coin::Coin(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f size, sf::Vector2f position) :
	animation(texture, imageCount, switchTime)
{
	row = 0;
	faceRight = true;

	body.setSize(size);
	body.setOrigin(body.getSize() / 2.0f);
	body.setTexture(texture);
	body.setPosition(position);
}

Coin::~Coin()
{

}

void Coin::Update(float deltaTime)
{
	row = 0;

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
}

void Coin::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Coin::setTexture(sf::Texture* texture)
{
	body.setTexture(texture);
}

//void coin::OnCollision(sf::Vector2f direction)
//{
//
//}