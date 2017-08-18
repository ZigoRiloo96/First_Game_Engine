#pragma once

#include <SFML\Graphics.hpp>
#include "Object_2.h"

class Box : Object_2
{
private:
	sf::IntRect m_Rect;

public:
	Box(sf::Vector2i pos) : Object_2(pos)
	{
		m_Texture.loadFromFile("Sprites/boxes_01.png");
		m_Sprite.setTexture(m_Texture);
		m_Sprite.setPosition((sf::Vector2f)pos);
	}

	~Box();

	void setPosition(sf::Vector2i pos);

	const sf::Sprite& getSprite();

	const sf::IntRect& getRect();

	void update();
};

