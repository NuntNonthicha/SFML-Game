#include "Boss.h"

Boss::Boss(sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed, sf::Vector2f position) :
	animation(texture, imageCount, switchTime)
{
	this->speed = speed;
	row = 0;
	faceRight = true;

	body.setSize(sf::Vector2f(400.0f, 450.0f));
	body.setOrigin(body.getSize() / 2.0f);
	body.setPosition(position);
	body.setTexture(texture);

}

Boss::~Boss()
{

}

void Boss::Update(float deltaTime)
{

	velocity.x = 0;

	if (GetPosition().x < 0)
		d = 1;
	if (GetPosition().x > 1000)
		d = 0;

	if (d == 0)
		velocity.x -= speed;
	if (d == 1)
		velocity.x += speed;





	velocity.y += 100.0f * deltaTime;
	MoveCheck(deltaTime);

}

void Boss::Update2(float deltaTime)
{
	velocity.x = 0;
	row = 1;

	
	velocity.y += 100.0f * deltaTime;
	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);


}

void Boss::MoveCheck(float deltaTime)
{
	//velocity.y += 100.0f * deltaTime;

	if (velocity.x == 0.0f) //if stop movement
	{
		row =0;
	}
	else
	{
		row = 2;

		if (velocity.x > 0.0f)
			faceRight = true;
		else
			faceRight = false;
	}

	animation.Update(row, deltaTime, faceRight);
	body.setTextureRect(animation.uvRect);
	body.move(velocity * deltaTime);
}

void Boss::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}

void Boss::OnCollision(sf::Vector2f directionM)
{
	if (directionM.x < 0.0f)
	{
		//Collision on the left.
		velocity.x = 0.0f;
	}
	else if (directionM.x > 0.0f)
	{
		//velocity on the right.
		velocity.x = 0.0f;
	}
	if (directionM.y < 0.0f)
	{
		//Collision on the bottom.
		velocity.y = 0.0f;
	}
	else if (directionM.y > 0.0f)
	{
		//Collision on the top.
		velocity.y = 0.0f;

	}

}
void Boss::BottomPlayer(sf::Vector2f directionR)
{
	if (directionR.y > 0.0f)
	{
		//Collision on the top.
		velocity.y = 0.0f;
		body.move(1000, 1000);

	}
}

void Boss::CalPlayer(sf::Vector2f directionR)
{
	if (directionR.x < 0.0f)
	{
		//Collision on the left.
		velocity.x = 0.0f;
	}
	else if (directionR.x > 0.0f)
	{
		//velocity on the right.
		velocity.x = 0.0f;
	}
	if (directionR.y < 0.0f)
	{
		//Collision on the bottom.
		velocity.y = 0.0f;
	}

}


