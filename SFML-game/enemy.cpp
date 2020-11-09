#include "enemy.h"
#include<iostream>

enemy::enemy(sf::Texture* texture,sf::Vector2u imageCount,float switchTime, float posx, float posy):
animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	body.setTexture(texture);
	body.setSize(sf::Vector2f(50, 90));
	body.setOrigin(sf::Vector2f(25, 45));
	body.setPosition(sf::Vector2f(posx, posy));
}

enemy::~enemy()
{
}

void enemy::Update(float deltaTime)
{
	velocity.x = -50.0f;
	velocity.y += 981.0f * deltaTime;
	row = 0;
	animation.Update(row, deltaTime, 0);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);

	//std::cout << body.getPosition().x << "   " << body.getPosition().y<<std::endl; //คำสั่ง printf ค่า


}

void enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}


void enemy::setPosition(sf::Vector2f position)
{
	body.setPosition(position);
}

void enemy::OnCollision(sf::Vector2f direction)
{
	if (direction.x < 0.0f)
	{
		//Collision on the left
		velocity.x = 0.0f;
	}
	else if (direction.x > 0.0f)
	{
		//Collision on the right
		velocity.x = 0.0f;
	}
	if (direction.y < 0.0f)
	{
		//Collision on the bottom
		velocity.y = 0.0f;
	}
	else if (direction.y > 0.0f)
	{
		//Collision on the top
		velocity.y = 0.0f;
	}
}

