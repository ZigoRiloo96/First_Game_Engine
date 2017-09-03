#include "Engine.h"

void Engine::begin()
{
    //Objects

    //m_Objects.push_back(new Object(Vector2f(465, 267), FloatRect(465, 321, 61, 15), "Sprites/shkaf1hide.png", "Sprites/shkaf1.png"));
    //m_Objects.push_back(new Object(Vector2f(464, 345), FloatRect(464, 396, 32, 15), "Sprites/shkaf3hide.png", "Sprites/shkaf3.png"));
    //m_Objects.push_back(new Object(Vector2f(544, 304), FloatRect(544, 359, 32, 15), "Sprites/shkaf5hide.png", "Sprites/shkaf5.png"));
    //m_Objects.push_back(new Object(Vector2f(464, 188), FloatRect(464, 242, 61, 15), "Sprites/shkaf6hide.png", "Sprites/shkaf6.png"));
    //m_Objects.push_back(new Object(Vector2f(225, 481), FloatRect(225, 546, 442, 1), "Sprites/wallHide.png", "Sprites/wall.png"));
    m_Objects.push_back(new Object(Vector2f(1027 - 684, 232 - 32), FloatRect(1027 - 684, 340 - 32, 96, 155), "Sprites/dom_1_h.png", "Sprites/dom_1.png"));
    m_Objects.push_back(new Object(Vector2f(1123 - 684, 270 - 32), FloatRect(1123 - 684, 340 - 32, 295, 130), "Sprites/dom_2_h.png", "Sprites/dom_2.png"));
    m_Objects.push_back(new Object(Vector2f(973 - 684, 224 - 32), FloatRect(973 - 684, 224 - 32, 9, 352), "Sprites/zabor_left.png"));
    m_Objects.push_back(new Object(Vector2f(1588 - 684, 224 - 32), FloatRect(1588 - 684, 224 - 32, 9, 352), "Sprites/zabor_right.png"));
    m_Objects.push_back(new Object(Vector2f(973 - 684, 193 - 32), FloatRect(973 - 684, 216 - 32, 623, 6), "Sprites/zabor_back_h.png", "Sprites/zabor_back.png"));
    m_Objects.push_back(new Object(Vector2f(982 - 684, 544 - 32), FloatRect(982 - 684, 569 - 32, 220, 6), "Sprites/zabor_down_1_h.png", "Sprites/zabor_down_1.png"));
    m_Objects.push_back(new Object(Vector2f(764, 138), FloatRect(818, 241, 17, 7), "Sprites/derewo_01.png", "Sprites/derewo_01.png"));
    m_Objects.push_back(new Object(Vector2f(345, 445), FloatRect(345, 475, 66, 18), "Sprites/boxes_01_h.png", "Sprites/boxes_01.png"));
    m_Objects.push_back(new Object(Vector2f(765, 280), FloatRect(765, 295, 70, 15), "Sprites/ozerco.png", "Sprites/ozerco.png"));
    m_Objects.push_back(new Object(Vector2f(772, 247), FloatRect(772, 263, 18, 11), "Sprites/vedro.png", "Sprites/vedro.png"));
    m_Objects.push_back(new Object(Vector2f(780, 445), FloatRect(785, 490, 16, 14), FloatRect(785, 445, 77, 48), "Sprites/sushka.png", "Sprites/sushka.png"));
    m_Objects.push_back(new Object(FloatRect(845, 490, 16, 14)));
    m_Objects.push_back(new Object(Vector2f(557, 512), FloatRect(557, 535, 347, 7), "Sprites/zabor_front_h.png", "Sprites/zabor_front.png"));

    //StandartObjects
    m_pTexture = new sf::Texture();
    m_pTexture->loadFromFile("Sprites/trawka_01.png");
    
    //m_StandartObjects.push_back(new StandartObject(788, 313, m_pTexture));
    //m_StandartObjects.push_back(new StandartObject(858, 458, m_pTexture));
    //m_StandartObjects.push_back(new StandartObject(620, 415, m_pTexture));
    //m_StandartObjects.push_back(new StandartObject(665, 415, m_pTexture));
    //m_StandartObjects.push_back(new StandartObject(700, 415, m_pTexture));

    m_g_texture.loadFromFile("Sprites/gowno.png");
    m_gowno = Animation(Vector2f(100,100), m_g_texture,Vector2i(24,24),3,Vector2i(0,0));

    m_DoorTrigger = new Trigger(IntRect(Vector2i(1201 - 684, 470 - 32),Vector2i(64, 32)));

    m_DoorTexture.loadFromFile("Sprites/door.png");
    m_Door = new Animation(Vector2i(1201 - 684,504 - 129), m_DoorTexture, Vector2i(64,56), 4);

}