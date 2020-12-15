#pragma once
#include<SFML/Graphics.hpp>
#include "Animation.h"
#include "Collider.h"
class Item
{
public:
	Item(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, sf::Vector2f position, unsigned int row);
	~Item();
	void Update(float deltatime);
	void Draw(sf::RenderWindow& window);
	void Oncollision(sf::Vector2f direction);
	sf::Vector2f GetPosition() { return item.getPosition(); }
	Collider GetCollider() { return Collider(item); }
	void SetPosition(sf::Vector2f(position)) { item.setPosition(position); }
	bool faceRight;
	unsigned int ItemRow() { return row; }

private:
	sf::RectangleShape item;
	sf::RectangleShape texture;
	Animation animation;
	sf::Vector2f velocity;
	unsigned int row;
};