#include "Collider.h"



Collider::Collider(std::string name, sf::IntRect rect)
	:m_Name(name),
	m_Rect(rect),
	isVisible(true)
{
	m_RectShape.setPosition(sf::Vector2f(rect.left,rect.top));  // mousePos
	m_RectShape.setSize(sf::Vector2f(rect.width, rect.height)); // 0,0
	m_RectShape.setFillColor(sf::Color(195,20,20,50));
}

const bool& Collider::getVisible()
{
	return isVisible;
}

void Collider::setVisible(bool param)
{
	isVisible = param;
}

const sf::Vector2i & Collider::getSize()
{
	return sf::Vector2i(m_Rect.width, m_Rect.height);
}

void Collider::setSize(sf::Vector2i v)
{
	if (v.x >= 0)
		m_Rect.width = v.x;
	else
		m_Rect.left = v.x;

	if (v.y >= 0)
		m_Rect.height = v.y;
	else
		m_Rect.top = v.y;


	m_RectShape.setSize((sf::Vector2f)v);
	//if (v.x > 0 && v.y > 0)
	//	m_RectShape.setSize((sf::Vector2f)v);
	//else if (v.x > 0)
	//{
	//	m_RectShape.setPosition(sf::Vector2f(m_RectShape.getPosition().x, v.y));
	//	m_RectShape.setSize(sf::Vector2f(v.x, v.y));
	//}
	//else if (v.y > 0)
	//{
	//	m_RectShape.setPosition(sf::Vector2f(v.x, v.y));
	//	m_RectShape.setSize(sf::Vector2f(v.x, v.y));
	//}

}

const sf::RectangleShape & Collider::getRectShape()
{
	return m_RectShape;
} 

const sf::Vector2i & Collider::getPosition()
{
	return sf::Vector2i(m_Rect.left, m_Rect.top);
}

bool Collider::isCollide(sf::IntRect ir)
{
	if (m_Rect.intersects(ir))
		return true;
	else
		return false;
}

void Collider::setPosition(sf::Vector2i pos)
{
	m_Rect.left = pos.x;
	m_Rect.top = pos.y;
}
