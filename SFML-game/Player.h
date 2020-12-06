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

	const sf::FloatRect getPlayerGlobalbounds() const;

	bool isShoot() { return shoot; }
	bool faceRight;

private:
	sf::RectangleShape body;
	sf::RectangleShape hitBox;

	sf::RectangleShape playerHitbox;

	Animation animation;
	unsigned int row; 
	float speed;


	const sf::Vector2f& getPosition() const;

	sf::Vector2f velocity;
	bool canJump;
	float jumpHeight;

	bool showhitbox = false;
	bool shoot = false;

	sf::Clock spacebarClock;
};

	


