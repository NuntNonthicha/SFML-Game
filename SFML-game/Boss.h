#pragma once
#include <SFML\Graphics.hpp>
#include "Animation.h"
#include "Collider.h"

class Boss
{
public:
	Boss(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position);
	~Boss();

	void Update(float deltaTime);
	void Update2(float deltaTime);
	void MoveCheck(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void OnCollision(sf::Vector2f directionM);
	void BottomPlayer(sf::Vector2f directionM);
	void CalPlayer(sf::Vector2f directionM);
	void setPosition(sf::Vector2f position);


	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }
	sf::RectangleShape body;

	sf::Vector2f velocity;
	float speed;
	unsigned int row;

private:

	Animation animation;
	bool faceRight;
	int d = 0;


};


