#include "bullet.h"
#include<iostream>

bullet::bullet(sf::Texture* texture, sf::Vector2f size,  float speed, float posx, float posy, bool directionFire)
	
{
	this->speed = speed;
	body.setTexture(texture);
	body.setSize(sf::Vector2f(32, 32));
	body.setPosition(sf::Vector2f(posx,posy));
	faceRight = directionFire;
}

bullet::~bullet()
{
}

void bullet::Update(float deltaTime)
{
	velocity.x = 0.0f;
	if (faceRight) {
		velocity.x += 2 * speed * 4.0f;
	}
	else {
	
		velocity.x -= 2 * speed * 4.0f;
	}
	body.move(velocity * deltaTime);
	//std::cout << body.getPosition().x << "   " << body.getPosition().y<<std::endl; //����� printf ���


}

void bullet::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

//void bullet::OnCollision(sf::Vector2f direction)
//{
//}

void bullet::setPosition(sf::Vector2f position)
{
	body.setPosition(position);
}
