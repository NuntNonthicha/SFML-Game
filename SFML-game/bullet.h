#pragma once
#include<SFML\Graphics.hpp>
#include"Collider.h"
#include"Animation.h"


class bullet
{
public:
	bullet(sf::Texture* texture, sf::Vector2f size, float switchTime , float speed, float posx, float posy, bool directionFire);
	~bullet();

	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void setPosition(sf::Vector2f position);
	void OnCollision(sf::Vector2f direction);
	void del();
	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

	

	
private:
	sf::Vector2f velocity;
	sf::RectangleShape body;
	float speed;
	bool faceRight;

	sf::FloatRect getBounds() const;
	
};

