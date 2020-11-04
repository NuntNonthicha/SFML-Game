#pragma once
#include<SFML\Graphics.hpp>
#include"Animation.h"
#include"Collider.h"

class Player
{
public:
	Player(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, float jumpHeight, bool showhitbox);
	~Player();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f direction);
	void setPosition(sf::Vector2f position);

	sf::Vector2f GetPosition() { return hitBox.getPosition(); }
	Collider GetCollider() { return Collider(hitBox); }

	bool isShoot() { return shoot; }


private:
	sf::RectangleShape body;
	sf::RectangleShape hitBox;
	Animation animation;
	unsigned int row; 
	float speed;
	bool faceRight;

	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;

	bool showhitbox = false;
	bool shoot = false;

	sf::Clock spacebarClock;
};

	


