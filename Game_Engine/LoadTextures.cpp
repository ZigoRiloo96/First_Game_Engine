#include "Engine.h"
#include <iostream>
#include <fstream>

void Engine::loadTexturesFromPath()
{
    std::string filename{ "" };
    std::ifstream file("path/grass_textures.txt");

    while (file >> filename) {
        m_pEntityTextures.push_back(new sf::Texture());
        if (!m_pEntityTextures.back()->loadFromFile(filename))
            std::cout<<"err..";
        m_pEntitySprites.push_back(new sf::Sprite);
        m_pEntitySprites.back()->setTexture(*m_pEntityTextures.back());
    }
}