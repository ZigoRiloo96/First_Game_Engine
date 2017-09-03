#include "Object.h"
#include <iostream>

Object::Object(Vector2f pos, FloatRect r, std::string t_hide, std::string t) :
    m_Rect_down(r),
    m_Position(pos),
    m_Mode(MODE::NORMAL)
{
    //textures
    m_Texture_hide.loadFromFile(t_hide);
    m_Texture.loadFromFile(t);

    //sprites
    m_Sprite_hide.setTexture(m_Texture_hide);
    m_Sprite.setTexture(m_Texture);
    m_Sprite_hide.setPosition(pos);
    m_Sprite.setPosition(pos);

    //top_rect
    m_Rect_top = FloatRect(r.left, pos.y, r.width, r.top - pos.y);


    //testing
    {
        m_RS.setSize(Vector2f(r.width, r.height));
        m_RS.setFillColor(Color::Green);
        m_RS.setPosition(Vector2f(r.left, r.top));
    }
}

Object::Object(Vector2f pos, FloatRect r, FloatRect topRect, std::string t_hide, std::string t) :
    m_Rect_down(r),
    m_Position(pos),
    m_Mode(MODE::NORMAL),
    m_Rect_top(topRect)
{
    //textures
    m_Texture_hide.loadFromFile(t_hide);
    m_Texture.loadFromFile(t);

    //sprites
    m_Sprite_hide.setTexture(m_Texture_hide);
    m_Sprite.setTexture(m_Texture);
    m_Sprite_hide.setPosition(pos);
    m_Sprite.setPosition(pos);


    //testing
    {
        m_RS.setSize(Vector2f(r.width, r.height));
        m_RS.setFillColor(Color::Green);
        m_RS.setPosition(Vector2f(r.left, r.top));
    }
}

Object::Object(Vector2f pos, sf::Texture t_hide, sf::Texture t) :
    m_Position(pos),
    m_Mode(MODE::NORMAL),
    m_Rect_top(sf::FloatRect(sf::Vector2f(0,0), sf::Vector2f(0, 0)))
{
    //textures
    m_Texture_hide = t_hide;
    m_Texture = t;

    //sprites
    m_Sprite_hide.setTexture(m_Texture_hide);
    m_Sprite.setTexture(m_Texture);
    m_Sprite_hide.setPosition(pos);
    m_Sprite.setPosition(pos);


    //testing
    //{
    //    m_RS.setSize(Vector2f(r.width, r.height));
    //    m_RS.setFillColor(Color::Green);
    //    m_RS.setPosition(Vector2f(r.left, r.top));
    //}
}

Object::Object(Vector2f pos, FloatRect r, std::string t) :
    m_Rect_down(r),
    m_Position(pos),
    m_Mode(MODE::STATIC)
{
    //textures
    if (m_Texture.loadFromFile(t))
    {
        std::cout << "Load of: " << t << " - OPENED.\n";
    } else 
        std::cout << "Load of: " << t << " - Err.\n";

    //sprites
    m_Sprite_hide.setTexture(m_Texture_hide);
    m_Sprite.setTexture(m_Texture);
    m_Sprite_hide.setPosition(pos);
    m_Sprite.setPosition(pos);

    //top_rect
    m_Rect_top = FloatRect(r.left, pos.y, r.width, r.top - pos.y);


    //testing
    {
        m_RS.setSize(Vector2f(r.width, r.height));
        m_RS.setFillColor(Color::Green);
        m_RS.setPosition(Vector2f(r.left, r.top));
    }
}

Object::Object(FloatRect r) :
    m_Rect_down(r),
    m_Mode(MODE::COLIDER)
{}

MODE Object::getMode()
{
    return m_Mode;
}
Vector2f Object::getPosition()
{
    return m_Position;
}
FloatRect Object::getRect_down()
{
    return m_Rect_down;
}
FloatRect Object::getRect_top()
{
    return m_Rect_top;
}
void Object::setRect_top(sf::FloatRect r)
{
    m_Rect_top = r;
    m_RS.setPosition(r.left,r.top);
    m_RS.setSize(sf::Vector2f(r.width, r.height));
}
Sprite Object::getSprite_hide()
{
    return m_Sprite_hide;
}
Sprite Object::getSprite()
{
    return m_Sprite;
}
RectangleShape Object::getRS()
{
    return m_RS;
}

