#pragma once
#include<SFML\Graphics.hpp>
#include"Collider.h"
#include"Animation.h"

class enemy
{
public:
	enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float posx, float posy);
	~enemy();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void setPosition(sf::Vector2f position);
	void OnCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }


private:
	sf::Vector2f velocity;
	sf::RectangleShape body;
	float speed;
	bool faceRight;

	Animation animation;
	unsigned int row;


};

