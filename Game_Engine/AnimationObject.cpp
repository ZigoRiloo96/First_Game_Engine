#include "AnimationObject.h"

#include <iostream>

//Vector2i  m_Position
//Texture   m_Texture
//IntRect   m_TextureRect
//Sprite    m_Sprite

AnimationObject::AnimationObject(string img, Vector2i pos, Frame frame, int frames, Direction d) :
    m_Position(pos),
    m_Direction(d),
    m_Frames(frames),
    m_Frame(frame)
{
    m_TextureRect = IntRect(frame.position.x, frame.position.y, frame.width, frame.height);

    m_Texture.loadFromFile(img);
    m_Sprite.setTexture(m_Texture);
    m_Sprite.setTextureRect(m_TextureRect);

    m_Iter = frames;
}

AnimationObject::AnimationObject(string img, Vector2i pos, IntRect textureRect, int frames, Direction d) :
    m_Position(pos),
    m_TextureRect(textureRect),
    m_Direction(d),
    m_Frames(frames)
{
    m_Texture.loadFromFile(img);
    m_Sprite.setTexture(m_Texture);
    m_Sprite.setTextureRect(m_TextureRect);

    m_Iter = frames;
}
AnimationObject::AnimationObject(Texture tex, Vector2i pos, IntRect textureRect, int frames, Direction d) :
    m_Texture(tex),
    m_Position(pos),
    m_TextureRect(textureRect),
    m_Direction(d),
    m_Frames(frames)
{
    m_Iter = frames;
}

AnimationObject::~AnimationObject()
{
}

AnimationObject::AnimationObject(const AnimationObject& rhs)
{
}

const Sprite& AnimationObject::getSprite()
{
    return m_Sprite;
}

const bool& AnimationObject::isPlaying()
{
    return m_isPlay;
}

void AnimationObject::Play()
{
    m_isPlay = true;
}
void AnimationObject::Stop()
{
    m_isPlay = false;
}

void AnimationObject::Update(float dt)
{
    if (m_isPlay)
    {
        if (m_Iter == 1)
        {
            m_Iter = m_Frames;
            m_TextureRect.left = m_Frame.position.x;
            m_TextureRect.top = m_Frame.position.y;
        }
        else 
        {
            ((m_Direction == Direction::from_Left) || (m_Direction == Direction::from_Right))
                ? ((m_Direction == Direction::from_Left) ? m_TextureRect.left += m_TextureRect.width
                    : m_TextureRect.left -= m_TextureRect.width)
                : ((m_Direction == Direction::from_Up) ? m_TextureRect.top += m_TextureRect.height
                    : m_TextureRect.top -= m_TextureRect.height);

            m_Iter--;
        }
        //cout << m_Iter << ": " << m_TextureRect.top << "\n";

        m_Sprite.setTextureRect(m_TextureRect);
    }
}