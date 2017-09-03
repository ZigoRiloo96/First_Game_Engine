#include "Animation.h"
#include <iostream>

Animation::Animation()
{
    m_yStrat = 0;
    m_Move = false;
    m_Nap = Nap::Down;
}
Animation::Animation(Vector2f pos, Texture& t, Vector2i pix, int slidesNum, Vector2i startP):
    m_slidesNum(slidesNum),
    m_startPos(startP)
{
    m_n = 1;
    m_Rect = IntRect(startP, pix);
    m_Sprite.setTexture(t);
    m_Sprite.setTextureRect(m_Rect);
    m_Sprite.setPosition(pos);
}
Animation::Animation(Vector2i pos, Texture& t, Vector2i pix, int slidesNum):
m_slidesNum(slidesNum)
{
    m_Open = false;
    m_n = 1;
    m_Rect = IntRect(Vector2i(0,168), pix);
    m_Sprite.setTexture(t);
    m_Sprite.setTextureRect(m_Rect);
    m_Sprite.setPosition((Vector2f)pos);
}
void Animation::Play()
{
    m_Move = true;
}

void Animation::Open()
{
    if (!m_Open)
    {
        if (m_n == 1)
        {
            m_Open = true;
        }
        else
        {
            m_Rect.top += m_Rect.height;
            m_n--;
        }
        m_Sprite.setTextureRect(m_Rect);
    }
}

void Animation::Close()
{
    if (m_Open)
    {
        if (m_n == m_slidesNum)
        {
            m_Open = false;
        }
        else
        {
            m_Rect.top -= m_Rect.height;
            m_n++;
        }
        m_Sprite.setTextureRect(m_Rect);
    }
}

void Animation::Stop()
{
    m_Move = false;
}

bool Animation::getState()
{
    if (m_Open)
        return true;
    return false;
}

void Animation::setState(bool st)
{
    m_Open = st;
}

Sprite& Animation::getSprite()
{
    return m_Sprite;
}

void Animation::update(const float &elapsedTime, Sprite  &sp, IntRect &rt)
{
    if (m_Nap == Nap::Down)
        m_yStrat = 0;
    else if (m_Nap == Nap::Left)
        m_yStrat = 70;
    else if (m_Nap == Nap::Right)
        m_yStrat = 140;
    else
        m_yStrat = 210;

    rt.top = m_yStrat;

    if (m_Move)
    {
        if (rt.left == 490)
            rt.left = 0;
        else
            rt.left += 70;
    }
    else
    {
        rt.left = 0;
    }


    sp.setTextureRect(rt);
}

void Animation::update()
{
    if (m_n == 1)
    {
        m_n = m_slidesNum;
        m_Rect.left = 0;
    }
    else
    {
        m_Rect.left += m_Rect.width;
        m_n--;
    }
    m_Sprite.setTextureRect(m_Rect);
}

void Animation::setNap(Nap n)
{
    m_Nap = n;
}