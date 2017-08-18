#include "StandartObject.h"



StandartObject::StandartObject(int posX, int posY, std::string t)
{
	//textures
	m_Texture.loadFromFile(t);

	//sprites
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setPosition((float)posX, (float)posY);

	//top_rect
	m_Rect_top = sf::IntRect(posX, posY, m_Texture.getSize().x, m_Texture.getSize().y-1);
	m_Rect_down = sf::IntRect(posX, posY + m_Texture.getSize().y - 1, m_Texture.getSize().x, 1);
}


StandartObject::~StandartObject()
{
}

const sf::Sprite& StandartObject::mf_getSprite()
{
	return m_Sprite;
}

const bool StandartObject::isPlayerUp(int playerYpos)
{
	return (m_Rect_down.top < playerYpos) ? true : false;
}
