#pragma once
#include<SFML\Graphics.hpp>
#include"Collider.h"
#include"Animation.h"

class bullet
{
public:
	bullet(sf::Texture* texture, sf::Vector2f size, float speed, float posx, float posy);
	~bullet();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	//void OnCollision(sf::Vector2f direction);
	void setPosition(sf::Vector2f position);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

	
private:
	sf::Vector2f velocity;
	sf::RectangleShape body;
	float speed;
};

