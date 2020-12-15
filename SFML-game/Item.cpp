#include "Item.h"
Item::Item(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position, unsigned int row) :
	animation(texture, imageCount, switchTime)
{
	this->row = row;
	item.setSize(sf::Vector2f(30, 40));
	item.setOrigin(item.getSize() / 2.0f);
	item.setPosition(position);
	item.setTexture(texture);
}

Item::~Item()
{
}

void Item::Update(float deltatime)
{
	velocity.x *= 0.0f;
	animation.Update(row, deltatime, faceRight);
	item.setTextureRect(animation.uvRect);
	item.move(velocity * deltatime);
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(item);
}



