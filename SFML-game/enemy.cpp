#include "enemy.h"
#include<iostream>

enemy::enemy(sf::Texture* texture,sf::Vector2u imageCount,float switchTime, float posx, float posy , float speed, int hp):
animation(texture, imageCount, switchTime)
{
	this->hp = hp;
	this->speed = speed;
	this->faceRight = false;
	body.setTexture(texture);
	body.setSize(sf::Vector2f(50, 70));
	body.setOrigin(sf::Vector2f(25, 35));
	body.setPosition(sf::Vector2f(posx, posy));


	enemyHitbox.setPosition(body.getPosition());
	enemyHitbox.setFillColor(sf::Color::Transparent);
	enemyHitbox.setOrigin(sf::Vector2f(25, 45));
	enemyHitbox.setSize(sf::Vector2f(50.f, 50.f));
}

enemy::~enemy()
{
}

bool enemy::updateBulletCollision(bullet* bullet)
{
	if (bullet->GetCollider().CheckCollision(this->GetCollider()))
	{
		//hpdown++;
		//count++;
		//row = 1;

		body.setPosition(-1000.0f, 350.0f);
		return true;
	}
	else
	{
		return false;
	}
}

void enemy::Update(float deltaTime)
{
	//velocity.x = -50.0f;
	velocity.x = -speed;
	velocity.y += 981.0f * deltaTime;
	row = 0;
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);

	//std::cout << body.getPosition().x << "   " << body.getPosition().y<<std::endl; //คำสั่ง printf ค่า
	enemyHitbox.setPosition(body.getPosition());

}


void enemy::Draw(sf::RenderWindow& window)
{
	window.draw(enemyHitbox);
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
		speed = speed + 200.0f;
		faceRight = false;
	}
	else if (direction.x > 0.0f)
	{
		//Collision on the right
		speed = speed - 200.0f;
		faceRight = true;
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

const sf::FloatRect enemy::getEnemyGloabalbounds() const
{
	return this->enemyHitbox.getGlobalBounds();
}

const sf::Vector2f& enemy::getPosition() const
{
	return this->body.getPosition();
}




