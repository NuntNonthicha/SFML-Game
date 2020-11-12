#include "Item.h"

Item::Item(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float posx, float posy) :
	animation(texture, imageCount, switchTime)
{
	row = 0;
	body.setTexture(texture);
	body.setSize(sf::Vector2f(50, 90));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(sf::Vector2f(posx, posy));
}

Item::~Item()
{
}


void Item::Update(float deltaTime , Player player)
{
	animation.Update(row, deltaTime,0);
	body.setTextureRect(animation.uvRect);

	//if (player.GetCollider().CheckCollision(this->GetCollider()))
	//{
	//	body.setPosition(-3000.0f, 350.0f); //ชนเเล้วให้ไปอยุ่หลังฉาก
	//}
}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}




