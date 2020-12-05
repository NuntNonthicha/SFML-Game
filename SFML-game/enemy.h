#pragma once
#include<SFML\Graphics.hpp>
#include"Collider.h"
#include"Animation.h"
#include"bullet.h"

class enemy
{
public:
	enemy(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float posx, float posy);
	~enemy();

	bool updateBulletCollision(bullet* bullet);
	void Update(float deltaTime);
	void Draw(sf::RenderWindow& window);
	void setPosition(sf::Vector2f position);
	void OnCollision(sf::Vector2f direction);

	sf::Vector2f GetPosition() { return body.getPosition(); }
	Collider GetCollider() { return Collider(body); }

	int hit()
	{
		if (count == 1) {
			count--;
			return 1;
		}
	}
	
	const sf::FloatRect getEnemyGloabalbounds() const;

private:
	sf::Vector2f velocity;
	sf::RectangleShape body;
	sf::RectangleShape enemyHitbox;
	float speed;
	bool faceRight;

	const sf::Vector2f& getPosition() const;

	Animation animation;
	unsigned int row;
	int count;
	int hpdown;
	int check() {
		if (hpdown == 1) {
			hpdown--;
			return 1;
		}
	}
	

};

