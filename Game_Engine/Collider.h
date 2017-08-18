#pragma once

#include <SFML/Graphics.hpp>

class Collider
{
private:
	std::string m_Name;
	sf::IntRect m_Rect;
	sf::RectangleShape m_RectShape;
	bool isVisible;

public:
	Collider(std::string name,sf::IntRect rect);
	const bool& getVisible();
	void setVisible(bool param);
	const sf::Vector2i& getSize();
	void setSize(sf::Vector2i v);
	const sf::RectangleShape& getRectShape();
	const sf::Vector2i& getPosition();
	void setPosition(sf::Vector2i pos);

	bool isCollide(sf::IntRect ir);
};

