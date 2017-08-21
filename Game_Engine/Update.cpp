#include "Engine.h"
#include <iostream>
#include <vector>

using namespace sf;

float TimeUpdateAnim = 0.1f;

void Engine::update()
{


	m_Window.setView(m_View);
}

void Engine::update(float dtAsSeconds)
{
	TimeUpdateAnim -= dtAsSeconds;
	if (TimeUpdateAnim < 0)
	{
		TimeUpdateAnim = 0.2f;
		m_gowno.update();
		if (m_DoorTrigger->OnTrigger((IntRect)m_Player->getRect()))
		{
			m_Door->setState(false);
			m_Door->Open();
		}
		else
		{
			m_Door->setState(true);
			m_Door->Close();
		}

	}

	m_Player->update(dtAsSeconds, m_Objects, m_Colliders);


	if (m_Player->getPosition().x + 35
		< m_View.getCenter().x - 105)
		m_View.setCenter(m_View.getCenter().x - 200 * dtAsSeconds * .47f
			, m_View.getCenter().y);

	if (m_Player->getPosition().x + 35
		> m_View.getCenter().x + 105)
		m_View.setCenter(m_View.getCenter().x + 200 * dtAsSeconds * .47f
			, m_View.getCenter().y);

	if (m_Player->getPosition().y + 35
		< m_View.getCenter().y - 70)
		m_View.setCenter(m_View.getCenter().x
			, m_View.getCenter().y - 200 * dtAsSeconds * .47f);

	if (m_Player->getPosition().y + 35
		> m_View.getCenter().y + 70)
		m_View.setCenter(m_View.getCenter().x
			, m_View.getCenter().y + 200 * dtAsSeconds * .47f);

	//if (!m_Colliders.empty())
	//{
	//	for (Collider* col : m_Colliders)
	//	{
	//		if (window == Window::EDITOR)
	//		{
	//		}
	//		else if (window == Window::GAME)
	//			if (col->isCollide((sf::IntRect)m_Player->getRect()))
	//			{
	//				m_Player->setPosition(Vector2f(col->getPosition().x - 18 * 0.65f, col->getPosition().y - 57 * 0.65f));
	//				m_Player->setRect((sf::IntRect)m_Player->getRect());
	//			}
	//	}
	//}
	
	texture.setView(m_View);
	m_Window.setView(m_View_Window);
}