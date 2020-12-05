#include "Platform.h"

Platform::Platform(sf::Texture* texture, sf::Vector2f size, sf::Vector2f position, int blockType, bool showHitbox)
{

    this->blockType = blockType;
    this->showHitbox = showHitbox;
    body.setSize(size);
    body.setOrigin(size / 2.0f);
    body.setTexture(texture);
    body.setPosition(position);

    hitBox.setPosition(body.getPosition());
    hitBox.setSize(size);
    hitBox.setOrigin(size / 2.0f);
    hitBox.setOutlineColor(sf::Color::Red);
    hitBox.setOutlineThickness(3.f);
}

Platform::~Platform()
{
}

void Platform::Draw(sf::RenderWindow& window) 
{
 
    window.draw(body);
   /* if (showHitbox && blockType == 1) {
        window.draw(hitBox);
    }*/
}

void Platform::setTexture(sf::Texture* texture)
{
    body.setTexture(texture);
}

int Platform::getBlockType()
{
    return this->blockType;
}
