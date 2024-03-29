#include"Player.h"
#include<iostream>

Player::Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight, bool showhitbox) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	this->jumpHeight = jumpHeight;
	this->showhitbox = showhitbox;
	row = 0;
	dmg = 50;
	faceRight = true;

	canJump = true;
	body.setSize(sf::Vector2f(80.0f, 100.0f));
	hitBox.setSize(sf::Vector2f(40.f, 80.0f));
	body.setOrigin(body.getSize() / 2.f);
	hitBox.setOrigin(hitBox.getSize()/ 2.f);
	body.setPosition(-400.0f, 50.0f); 
	hitBox.setPosition(-400.0f, 50.0f);
	hitBox.setFillColor(sf::Color::Transparent);
	hitBox.setOutlineColor(sf::Color::Transparent);
	hitBox.setOutlineThickness(3.f);
	body.setTexture(texture);
	spacebarClock.restart();

	playerHitbox.setPosition(hitBox.getPosition());
	playerHitbox.setFillColor(sf::Color::Transparent);
	playerHitbox.setSize(sf::Vector2f(40.f, 80.f));
	playerHitbox.setOrigin(hitBox.getSize() / 2.f);
}

Player::~Player()
{
}

void Player::Update(float deltaTime)
{
	velocity.x = 0.0f;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		velocity.x -= 1.5 * speed * 2.0f;
		faceRight = false;
		row = 1;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		velocity.x += 1.51 * speed * 2.0f;
		faceRight = true;
		row = 1;
	}
	else if (velocity.x == 0.0f) //if stop movement
	{
		row = 0;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && canJump == true)
	{
		canJump = false;
		velocity.y = -sqrtf(3.8f * 981.0f * jumpHeight); //square root(2.0f * gravity * jumpHeight)
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && spacebarClock.getElapsedTime().asMilliseconds() > 1500)
	{
		row = 2;
		shoot = true;
		spacebarClock.restart();
	}
	else{
		shoot = false;
	}

	velocity.y += 981.0f * deltaTime;

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	hitBox.move(velocity * deltaTime);
	body.setPosition(hitBox.getPosition());
}

void Player::Draw(sf::RenderWindow& window)
{
	window.draw(body);

	if (this->showhitbox) {
		window.draw(hitBox);
	}
	

}

void Player::OnCollision(sf::Vector2f direction)
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
		canJump = true;
	}
	else if (direction.y > 0.0f)
	{
		//Collision on the top
		velocity.y = 0.0f;
	}
}

void Player::setPosition(sf::Vector2f position)
{
	this->hitBox.setPosition(position);
}

const sf::FloatRect Player::getPlayerGlobalbounds() const
{
	return this->hitBox.getGlobalBounds();
}

const sf::Vector2f& Player::getPosition() const
{
	return this->hitBox.getPosition();
}



