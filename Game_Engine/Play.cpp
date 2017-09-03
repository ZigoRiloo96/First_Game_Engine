#include "Engine.h"

void Engine::Play(sf::Time timeSinceLastUpdate, sf::Time timePerFrame,sf::Time dt)
{
    //while (timeSinceLastUpdate < timePerFrame) {
        
        timeSinceLastUpdate += dt;

        update(timePerFrame.asSeconds());
    //}
}
