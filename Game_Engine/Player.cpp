#include "Player.h"

#include <iostream>

IntRect rect(0, 0, 0, 0);

int Player::biggest()
{
    if (posX != 0 || posY != 0)
    {
        if (abs(posX) > abs(posY))
        {
            //std::cout << (float)(posX / 1000) << "X\n";
            return ((float)posX / 1000);
        }
        //std::cout << "Y\n";
        return ((float)posY / 1000);
    }
    //std::cout << "0.09\n";
    return 0.09f;
}

Player::Player()
{
    m_Speed = 100;
    m_Texture.loadFromFile("lila.png");
    m_Texture.setSmooth(true);
    m_RectSp = IntRect(0, 0, 70, 70);

    m_MoveRect = FloatRect(250, 400, 34 * 0.65f, 13 * 0.65f);

    m_Sprite.setTexture(m_Texture);
    m_Sprite.setTextureRect(m_RectSp);
    m_TimeUpdateAnim = 0.09f;
    m_Sprite.setScale(0.65f, 0.65f);

    m_RS.setSize(Vector2f(m_MoveRect.width, m_MoveRect.height));
    m_RS.setPosition(Vector2f(m_MoveRect.left, m_MoveRect.top));

    m_RS.setFillColor(Color::Green);

    m_Position.x = m_MoveRect.left - (34 * 0.65f) / 2;
    m_Position.y = m_MoveRect.top - 57 * 0.65f;

    m_Collider = new Collider("playerCol", (sf::IntRect)m_MoveRect);
}

Sprite& Player::getSprite()
{
    return m_Sprite;
}

Vector2f& Player::getPosition()
{
    return m_Position;
}

void Player::setPosition(Vector2f v)
{
    m_Position = v;
}

void Player::setRect(sf::IntRect ir)
{
    m_MoveRect = (sf::FloatRect)ir;
    m_Collider->setPosition(sf::Vector2i(ir.left, ir.top));
}

FloatRect& Player::getRect()
{
    return m_MoveRect;
}

void Player::moveLeft()
{
    if (!m_rightPressed && !m_downPressed && !m_upPressed)
    {
        m_leftPressed = true;
        m_Animation.Play();
        m_Animation.setNap(Nap::Left);
    }
}

void Player::moveRight()
{
    if (!m_leftPressed && !m_downPressed && !m_upPressed)
    {
        m_rightPressed = true;
        m_Animation.Play();
        m_Animation.setNap(Nap::Right);
    }
}

void Player::moveDown()
{
    if (!m_rightPressed && !m_leftPressed && !m_upPressed)
    {
        m_downPressed = true;
        m_Animation.Play();
        m_Animation.setNap(Nap::Down);
    }
}

void Player::moveUp()
{
    if (!m_rightPressed && !m_downPressed && !m_leftPressed)
    {
        m_upPressed = true;
        m_Animation.Play();
        m_Animation.setNap(Nap::Up);
    }
}

//joyMoves
void Player::joyMoveLeft()
{
    m_Animation.Play();
    m_Animation.setNap(Nap::Left);
}

void Player::joyMoveRight()
{
    m_Animation.Play();
    m_Animation.setNap(Nap::Right);
}

void Player::joyMoveDown()
{
    m_Animation.Play();
    m_Animation.setNap(Nap::Down);
}

void Player::joyMoveUp()
{
    m_Animation.Play();
    m_Animation.setNap(Nap::Up);
}


void Player::stopLeft()
{
    m_leftPressed = false;
}

void Player::stopRight()
{
    m_rightPressed = false;
}

void Player::stopDown()
{
    m_downPressed = false;
}

void Player::stopUp()
{
    m_upPressed = false;
}

void Player::stopAnimation()
{
    m_Animation.Stop();
}

RectangleShape Player::getRS()
{
    return m_RS;
}



void Player::update(const float &elapsedTime, std::vector<Object*> &v, std::vector<Collider*> &col)
{    
    //keys move
    if (m_rightPressed)
    {
        m_Position.x += m_Speed * elapsedTime;
        m_MoveRect.left += m_Speed * elapsedTime;
    }
    else
    if (m_leftPressed)
    {
        m_Position.x -= m_Speed * elapsedTime;
        m_MoveRect.left -= m_Speed * elapsedTime;
    }
    else
    if (m_downPressed)
    {
        m_Position.y += m_Speed * elapsedTime;
        m_MoveRect.top += m_Speed * elapsedTime;
    }
    else
    if (m_upPressed)
    {
        m_Position.y -= m_Speed * elapsedTime;
        m_MoveRect.top -= m_Speed * elapsedTime;
    }

    //JOY move
    posY = (int)sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
    posX = (int)sf::Joystick::getAxisPosition(0, sf::Joystick::X);

    (posY > -10 && posY < 10) ? posY = 0 : posY;

    (posX > -10 && posX < 10) ? posX = 0 : posX;

    if (posX>0)
    {
        m_Position.x += posX * elapsedTime;
        m_MoveRect.left += posX * elapsedTime;
    }
    if (posX<0)
    {
        m_Position.x -= -1 * posX * elapsedTime;
        m_MoveRect.left -= -1 * posX * elapsedTime;
    }
    if (posY<0)
    {
        m_Position.y += posY * elapsedTime;
        m_MoveRect.top += posY * elapsedTime;
    }
    if (posY>0)
    {
        m_Position.y -= -1 * posY * elapsedTime;
        m_MoveRect.top -= -1 * posY * elapsedTime;
    }
    //end joy move

    if (!col.empty())
    {
        for (Collider* c : col)
        {
            if (c->isCollide((IntRect)m_MoveRect))
            {
                m_Position = Vector2f(rect.left - 18 * 0.65f, rect.top - 57 * 0.65f);
                m_MoveRect = (FloatRect)rect;
            }
        }

        int size_col = col.size();

        for (Collider* c : col)
        {
            if (!c->isCollide((IntRect)m_MoveRect))
            {
                size_col--;
            }
            if (size_col == 0)
            {
                rect = (IntRect)m_MoveRect;
            }
        }
    }

    //for (Object* n : v)
    //{
    //    if (m_MoveRect.intersects(n->getRect_down()))
    //    {
    //        m_Position = Vector2f(rect.left - 18 * 0.65f, rect.top - 57 * 0.65f);
    //        m_MoveRect = (FloatRect)rect;
    //    }
    //}

    //int size = v.size();

    //for (Object* n : v)
    //{
    //    if (!m_MoveRect.intersects(n->getRect_down()))
    //    {
    //        size--;
    //    }
    //    if (size == 0)
    //    {
    //        rect = (IntRect)m_MoveRect;
    //    }
    //}

    //m_TimeUpdateAnim -= elapsedTime;
    //if (m_TimeUpdateAnim < 0)
    //{
    //    m_TimeUpdateAnim = 0.09f;
    //    m_Animation.update(elapsedTime, m_Sprite, m_RectSp);
    //}

    m_TimeUpdateAnim -= elapsedTime;
    //std::cout << m_TimeUpdateAnim << "\n";
    if (m_TimeUpdateAnim < 0)
    {
        if (posX != 0 || posY != 0)
        {
            if (abs(posX) > abs(posY))
            {
                m_TimeUpdateAnim = 0.09f * 100 / abs(posX);
            }
            if(posY != 0)
                m_TimeUpdateAnim = 0.09f * 100 / abs(posY);
        }
        else
            m_TimeUpdateAnim = 0.09f;//0.09f
        
        m_Animation.update(elapsedTime, m_Sprite, m_RectSp);
    }

    m_RS.setSize(Vector2f(m_MoveRect.width, m_MoveRect.height));
    m_RS.setPosition(Vector2f(m_MoveRect.left, m_MoveRect.top));

    m_Sprite.setPosition(m_Position);
}