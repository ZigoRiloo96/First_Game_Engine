#pragma once

#include <SFML/Graphics.hpp>

class Trigger
{
private:
    sf::IntRect m_Rect;

public:
    Trigger(sf::IntRect ir);
    ~Trigger();

    sf::IntRect getRect();
    bool OnTrigger(sf::IntRect r);
};

