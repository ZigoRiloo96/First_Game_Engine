#include "Tile.h"


Tile::Tile(sf::Vector2i pos,const sf::IntRect r,const sf::Texture& t):
    m_Position(pos),
    m_Rect(r)
{
    m_Sprite.setPosition((sf::Vector2f)pos);
    m_Sprite.setTexture(t);
    m_Sprite.setTextureRect(r);
}

void Tile::setPosition(sf::Vector2i pos)
{
    m_Position = pos;
    m_Sprite.setPosition((sf::Vector2f)pos);
}

void Tile::setSprite(sf::Texture t, sf::IntRect r)
{
    m_Sprite.setTexture(t);
    m_Sprite.setTextureRect(r);
}

const sf::IntRect& Tile::getRect()
{
    return m_Rect;
}

const sf::Sprite & Tile::getSprite()
{
    return m_Sprite;
}

const sf::Vector2i & Tile::getPosition()
{
    return m_Position;
}

const sf::Texture& Tile::getTexture()
{
    return (*m_Sprite.getTexture());
}
