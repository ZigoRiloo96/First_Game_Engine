#pragma once
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "Object.h"
#include "Collider.h"

using namespace sf;

class Player
{
private:
	Vector2f m_Position;
	Sprite m_Sprite;
	Texture m_Texture;
	IntRect m_RectSp;
	FloatRect m_MoveRect;

	//Collider
	Collider* m_Collider;
	sf::IntRect oldRect;
	sf::Vector2f oldPosition;

	bool m_leftPressed;
	bool m_rightPressed;
	bool m_downPressed;
	bool m_upPressed;

	float m_Speed;
	float m_TimeUpdateAnim;

	Animation m_Animation;

	RectangleShape m_RS;

	//JOY
	int posX;
	int posY;

	int biggest();

	//Colliders
	bool isCollide = false;

public:
	Player();
	void setRect(sf::IntRect ir);
	FloatRect& getRect();
	Sprite& getSprite();
	Vector2f& getPosition();
	void setPosition(Vector2f v);
	void moveLeft();
	void moveRight();
	void moveDown();
	void moveUp();
	void joyMoveLeft();
	void joyMoveRight();
	void joyMoveDown();
	void joyMoveUp();
	void stopLeft();
	void stopRight();
	void stopDown();
	void stopUp();
	void stopAnimation();

	RectangleShape getRS();

	void update(const float &elapsedTime, std::vector<Object*> &v, std::vector<Collider*> &col);
};
