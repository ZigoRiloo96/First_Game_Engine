#pragma once

#include "SFML/Graphics.hpp"

class Tile
{
private:
    sf::Vector2i m_Position;
    sf::Sprite m_Sprite;
    sf::IntRect m_Rect;

public:
    Tile(sf::Vector2i pos,const sf::IntRect r, const sf::Texture& t);

    void setPosition(sf::Vector2i pos);
    void setSprite(sf::Texture t, sf::IntRect r);
    const sf::IntRect& getRect();
    const sf::Sprite& getSprite();
    const sf::Vector2i& getPosition();
    const sf::Texture& getTexture();
};

