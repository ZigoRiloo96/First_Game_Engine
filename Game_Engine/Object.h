#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace sf;

enum class MODE
{
	NORMAL,
	STATIC,
	COLIDER
};

class Object
{
private:

	MODE m_Mode;

	Vector2f m_Position;

	Texture m_Texture_hide;
	Texture m_Texture;

	Sprite m_Sprite_hide;
	Sprite m_Sprite;

	FloatRect m_Rect_down;
	FloatRect m_Rect_top;

	RectangleShape m_RS;

public:
	Object(Vector2f pos, FloatRect r, std::string t_hide, std::string t);
	Object(Vector2f pos, FloatRect r, FloatRect topRect, std::string t_hide, std::string t);
	Object(Vector2f pos, sf::Texture t_hide, sf::Texture t);
	Object(Vector2f pos, FloatRect r, std::string t);
	Object(FloatRect r);

	MODE getMode();

	Vector2f getPosition();

	Sprite getSprite_hide();
	Sprite getSprite();

	FloatRect getRect_down();
	FloatRect getRect_top();

	void setRect_top(sf::FloatRect r);

	RectangleShape getRS();

};