#include "Object_2.h"


Object_2::Object_2(sf::Vector2i pos) :
	m_Position(pos)
{
}


Object_2::~Object_2()
{
}

void Object_2::setPosition(sf::Vector2i pos)
{
	m_Sprite.setPosition((sf::Vector2f)pos);
}

const sf::Vector2f& Object_2::getPosition()
{
	return m_Sprite.getPosition();
}

const sf::Sprite & Object_2::getSprite()
{
	return m_Sprite;
}

const int & Object_2::getLayer()
{
	return m_Layer;
}
