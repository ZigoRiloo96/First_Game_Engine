#pragma once

#include "SFML/Graphics.hpp"
#include "Tile.h"

class TileSet
{
private:
    sf::Texture m_Texture;
    sf::IntRect m_Rect;

public:
    TileSet();
    TileSet(sf::Texture t);

    Tile **makeTile(int size);

    void setTexture(const sf::Texture& t);
};

