#include "Trigger.h"


Trigger::Trigger(sf::IntRect ir)
	: m_Rect(ir)
{

}

Trigger::~Trigger()
{
}

sf::IntRect Trigger::getRect()
{
	return m_Rect;
}

bool Trigger::OnTrigger(sf::IntRect r)
{
	if (r.intersects(m_Rect))
	{
		return true;
	}
	return false;
}
