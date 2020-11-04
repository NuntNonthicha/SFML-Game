#pragma once
#include<SFML\Graphics.hpp>
#include"Collider.h"

class Platform
{
public:
	Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, int blockType, bool showhitbox);
	~Platform();

	void Draw(sf::RenderWindow& window);
	Collider GetCollider() { return Collider(hitBox); }

	void setTexture(sf::Texture* texture);

	int getBlockType();

private:
	sf::RectangleShape body;
	int blockType = 0;
	bool showHitbox = false;
	sf::RectangleShape hitBox;

};

