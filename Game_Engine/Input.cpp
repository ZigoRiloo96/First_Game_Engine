#include "Engine.h"
#include <iostream>
#include <cmath>

//mouse
#define mouseMid (Mouse::isButtonPressed(Mouse::Middle))
//keys
#define keyA (Keyboard::isKeyPressed(Keyboard::A))
#define keyD (Keyboard::isKeyPressed(Keyboard::D))
#define keyW (Keyboard::isKeyPressed(Keyboard::W))
#define keyS (Keyboard::isKeyPressed(Keyboard::S))
#define uArow (Keyboard::isKeyPressed(Keyboard::Up))
#define dArow (Keyboard::isKeyPressed(Keyboard::Down))
#define rArow (Keyboard::isKeyPressed(Keyboard::Right))
#define lArow (Keyboard::isKeyPressed(Keyboard::Left))
//buttons
#define joyL ((int)sf::Joystick::getAxisPosition(0, sf::Joystick::PovX)<0)
#define joyR ((int)sf::Joystick::getAxisPosition(0, sf::Joystick::PovX)>0)
#define joyU ((int)sf::Joystick::getAxisPosition(0, sf::Joystick::PovY)<0)
#define joyD ((int)sf::Joystick::getAxisPosition(0, sf::Joystick::PovY)>0)
//axis
#define joyAl (posX<0)
#define joyAr (posX>0)
#define joyAu (posY<0)
#define joyAd (posY>0)


void Engine::input()
{

    while (m_Window.pollEvent(m_event)) {
        ImGui::SFML::ProcessEvent(m_event);

        if (m_event.type == Event::Closed)
            m_Window.close();
        if (m_event.type == Event::Resized)
        {
            m_Window.setView(View(FloatRect(0, 0, (float)m_event.size.width, (float)m_event.size.height)));
            //sprite.Resize(renderWindow.getSize().x, renderWindow.getSize().y);
            m_View_Window.setCenter(m_BackgroundSizeTexture);
            m_WindowSize.x = (float)m_event.size.width;
            m_WindowSize.y = (float)m_event.size.height;
            m_View_Window.setSize(m_WindowSize);
        }

    }

    if (Keyboard::isKeyPressed(Keyboard::K))
    {
        window = Window::EDITOR;
    }
    else if (Keyboard::isKeyPressed(Keyboard::L))
    {
        window = Window::GAME;
    }
    else if (Keyboard::isKeyPressed(Keyboard::M))
    {
        window = Window::NOTHING;
    }

    sf::Vector2f p = texture.mapPixelToCoords(sf::Vector2i((int)gameWindowPosX, (int)gameWindowPosY));

    if (m_pEntitySprite != nullptr && entityIsActive)
    {
        m_pEntitySprite->setPosition(p);

        if (Mouse::isButtonPressed(Mouse::Button::Left))
        {
            if (!lastLeftKeyState)
            {
                m_StandartObjects.push_back(new StandartObject(m_pEntitySprite->getPosition().x, m_pEntitySprite->getPosition().y, m_pEntitySprite->getTexture(), m_entityID));
                lastLeftKeyState = true;
            }
        }
        else
        {
            if (lastLeftKeyState)
            {
                lastLeftKeyState = false;
            }
        }
    }

    if (Mouse::isButtonPressed(Mouse::Button::Right))
    {
        if (!lastKeyState)
        {
            sf::Vector2i gameMousePos = (sf::Vector2i)texture.mapPixelToCoords(sf::Vector2i((int)gameWindowPosX, (int)gameWindowPosY));
            sf::Vector2i objectMousePos = (sf::Vector2i)object_texture.mapPixelToCoords(sf::Vector2i((int)objectWindowPosX, (int)objectWindowPosY));
            //OnKeyClick();

            if (wc == windowCh::OE)
            {
                pObjectRect = new sf::IntRect(objectMousePos, sf::Vector2i(0, 0));
            }

            if (window == Window::EDITOR)
            {
                m_pCollider = new Collider("col", sf::IntRect((sf::Vector2i)texture_tile.mapPixelToCoords(sf::Vector2i((int)focus_x, (int)focus_y)),
                    sf::Vector2i(0, 0)));
            }
            else if (window == Window::GAME)
            {
                m_pCollider = new Collider("col", sf::IntRect(gameMousePos, sf::Vector2i(0, 0)));
                //m_StandartObjects.push_back(new StandartObject(gameMousePos.x, gameMousePos.y, m_pTexture));
            }

            lastKeyState = true;
        }
        //OnKeyPressed();
        if (window == Window::EDITOR)
        {
            m_pCollider->setSize(sf::Vector2i(std::abs((int)texture_tile.mapPixelToCoords(sf::Vector2i((int)focus_x, (int)focus_y)).x - m_pCollider->getPosition().x)
                , std::abs((int)texture_tile.mapPixelToCoords(sf::Vector2i((int)focus_x, (int)focus_y)).y - m_pCollider->getPosition().y)));
        }
        else if (window == Window::GAME)
        {
            m_pCollider->setSize(sf::Vector2i(std::abs((int)texture.mapPixelToCoords(sf::Vector2i((int)gameWindowPosX, (int)gameWindowPosY)).x - m_pCollider->getPosition().x)
                , std::abs((int)texture.mapPixelToCoords(sf::Vector2i((int)gameWindowPosX, (int)gameWindowPosY)).y - m_pCollider->getPosition().y)));
        }    
        if (wc == windowCh::OE)
        {
            pObjectRect->width = std::abs((int)object_texture.mapPixelToCoords(sf::Vector2i((int)objectWindowPosX, (int)objectWindowPosY)).x - pObjectRect->left);
            pObjectRect->height = std::abs((int)object_texture.mapPixelToCoords(sf::Vector2i((int)objectWindowPosX, (int)objectWindowPosY)).y - pObjectRect->top);
        }
    } 
    else
    {
        if (lastKeyState)
        {
            OnKeyReleased();
            lastKeyState = false;
        }
    }

    if (Keyboard::isKeyPressed(Keyboard::V))
    {
        if (!lastVkeyState)
        {
            isColVisible = !isColVisible;
            lastVkeyState = true;
        }
    }
    else
    {
        if (lastVkeyState)
        {
            lastVkeyState = false;
        }

    }


    if (Keyboard::isKeyPressed(Keyboard::Escape) || sf::Joystick::isButtonPressed(0, 2))
        m_Window.close();

    if (m_Player != NULL)
    {
        posY = (int)sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
        posX = (int)sf::Joystick::getAxisPosition(0, sf::Joystick::X);

        (posY > -10 && posY < 10) ? posY = 0 : posY;

        (posX > -10 && posX < 10) ? posX = 0 : posX;

        if (keyA || joyL)
            m_Player->moveLeft();
        else
            m_Player->stopLeft();

        if (keyD || joyR)
            m_Player->moveRight();
        else
            m_Player->stopRight();

        if (keyS || joyU)
            m_Player->moveDown();
        else
            m_Player->stopDown();

        if (keyW || joyD)
            m_Player->moveUp();
        else
            m_Player->stopUp();

        if (joyAl)
            m_Player->joyMoveLeft();
        if (joyAr)
            m_Player->joyMoveRight();
        if (joyAd)
            m_Player->joyMoveDown();
        if (joyAu)
            m_Player->joyMoveUp();
    }

    if (uArow)
        if (viewPos.y - (m_View_tile.getSize().y / 2) - 5 < 0)
            viewPos.y = m_View_tile.getSize().y/2;
        else
            viewPos.y -= 5;
    if (dArow)
        if (viewPos.y + (m_View_tile.getSize().y / 2) + 10 > texture_tile.getSize().y)
            viewPos.y = texture_tile.getSize().y - (m_View_tile.getSize().y / 2) - 5;
        else
            viewPos.y += 5;
    if (rArow)
        if (viewPos.x + (m_View_tile.getSize().x / 2) + 10 > texture_tile.getSize().x)
            viewPos.x = texture_tile.getSize().x - (m_View_tile.getSize().x / 2) - 5;
        else
            viewPos.x += 5;
    if (lArow)
        if (viewPos.x - (m_View_tile.getSize().x / 2) - 5 < 0)
            viewPos.x = m_View_tile.getSize().x/2;
        else
            viewPos.x -= 5;

    m_View_tile.setCenter((Vector2f)viewPos);
    texture_tile.setView(m_View_tile);

    if (!keyA && !keyW && !keyS && !keyD && !joyD && !joyL && !joyR && !joyU && !joyAd && !joyAl && !joyAr && !joyAu)
        m_Player->stopAnimation();
}