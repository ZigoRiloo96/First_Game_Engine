#pragma once

#include "SFML/Graphics.hpp"
#include <string>

class StandartObject
{
private:


	sf::Vector2f m_Position;

	//sf::Texture m_Texture;

	sf::Sprite m_Sprite;

	sf::IntRect m_Rect_down;
	sf::IntRect m_Rect_top;

public:
	StandartObject(int posX, int posY, const sf::Texture *t);
	~StandartObject();

	const sf::Sprite& mf_getSprite();

	//const sf::IntRect& mf_getRect_down();
	//const sf::IntRect& mf_getRect_top();

	const bool isPlayerUp(int playerYpos);
};

