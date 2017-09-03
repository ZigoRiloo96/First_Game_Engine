#pragma once

#include <SFML\Graphics.hpp>

class Object_2
{
private:
    sf::Vector2i m_Position;
    int m_Layer;

protected:
    sf::Texture m_Texture;
    sf::Sprite m_Sprite;

public:
    Object_2(sf::Vector2i pos);
    ~Object_2();

    void setPosition(sf::Vector2i pos);

    const sf::Vector2f& getPosition();

    const sf::Sprite& getSprite();

    const int& getLayer();

    void update();
};


