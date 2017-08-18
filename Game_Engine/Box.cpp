#include "Box.h"
#include <iostream>



Box::~Box()
{
}

void Box::setPosition(sf::Vector2i pos)
{
	m_Sprite.setPosition((sf::Vector2f)pos);
}

const sf::Sprite & Box::getSprite()
{
	return m_Sprite;
}

const sf::IntRect & Box::getRect()
{
	return m_Rect;
}
