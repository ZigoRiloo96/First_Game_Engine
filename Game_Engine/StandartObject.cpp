#include "StandartObject.h"



StandartObject::StandartObject(int posX, int posY, const sf::Texture *t, int ID)
    :m_textureID(ID)
{
    //textures
    //m_Texture.loadFromFile(t);

    //sprites
    m_Sprite.setTexture(*t);
    m_Sprite.setPosition((float)posX, (float)posY);

    //top_rect
    m_Rect_top = sf::IntRect(posX, posY, t->getSize().x, t->getSize().y-1);
    m_Rect_down = sf::IntRect(posX, posY + t->getSize().y - 1, t->getSize().x, 1);
}

StandartObject::StandartObject(int posX, int posY, const sf::Texture *t)
{
    //textures
    //m_Texture.loadFromFile(t);

    //sprites
    m_Sprite.setTexture(*t);
    m_Sprite.setPosition((float)posX, (float)posY);

    //top_rect
    m_Rect_top = sf::IntRect(posX, posY, t->getSize().x, t->getSize().y - 1);
    m_Rect_down = sf::IntRect(posX, posY + t->getSize().y - 1, t->getSize().x, 1);
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

const sf::Vector2i& StandartObject::getPosition()
{
    return (sf::Vector2i)m_Position;
}

const int& StandartObject::getID()
{
    return m_textureID;
}

void StandartObject::setID(int id)
{
    m_textureID = id;
}
