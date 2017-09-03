#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

enum class Nap
{
    Down,
    Left,
    Right,
    Up
};

class Animation
{
private:

    int m_yStrat;
    bool m_Move;
    Nap m_Nap;

    bool m_Open;

    Vector2i m_Position;
    Texture m_Texture;
    Sprite m_Sprite;
    IntRect m_Rect;
    int m_slidesNum;
    int m_n;
    Vector2i m_startPos;
    float m_TimeUpdateAnim;

public:
    Animation();
    Animation(Vector2f pos, Texture& t, Vector2i pix, int slidesNum, Vector2i startP);
    Animation(Vector2i pos, Texture& t, Vector2i pix, int slidesNum);

    Sprite& getSprite();

    void setNap(Nap n);
    void Play();
    void Open();
    void Close();
    void Stop();

    bool getState();
    void setState(bool st);

    void update(const float &elapsedTime, Sprite &sp, IntRect &rt);
    void update();
};