#include "Engine.h"

void Engine::draw()
{
	m_Window.clear(Color::Black);
	
	texture.clear(Color::Black);
	m_Window.clear(Color::Black);

	texture.draw(m_BackgroundSprite);
	m_Window.draw(m_sProgramBackground);

	texture_tile.clear();
	//texture_tile.draw(sf::Sprite(gridTex));

	//if (!m_Tiles.empty())
	//{
	//	for (Tile* n : m_Tiles)
	//	{
	//		//texture.draw(n->getSprite());
	//		//m_Window.draw(n->getSprite());
	//		texture_tile.draw(n->getSprite());
	//		texture_shot.draw(n->getSprite());
	//	}
	//}

	//m_spriteTiles
	if (!m_spriteTiles.empty())
	{
		for (sf::Sprite* n : m_spriteTiles)
		{
			//texture.draw(n->getSprite());
			//m_Window.draw(n->getSprite());
			texture_tile.draw(*n);
			texture_shot.draw(*n);
		}
	}

	if (m_Player != nullptr)
	{
		//Objects
		for (Object* n : m_Objects)
		{
			if (!m_Player->getRect().intersects(n->getRect_top())
				&& n->getMode() != MODE::COLIDER)
			{
				texture.draw(n->getSprite());
				//m_Window.draw(n->getSprite());
			}
		}
		//StandartObjects
		for (StandartObject* n : m_StandartObjects)
		{
			if (n->isPlayerUp((int)(m_Player->getRect().top + m_Player->getRect().height / 2)))
			{
				texture.draw(n->mf_getSprite());
				//m_Window.draw(n->mf_getSprite());
			}
		}
	}

	texture.draw(m_gowno.getSprite());
	texture.draw(m_Door->getSprite());

	if (m_Player != nullptr)
	{
		texture.draw(m_Player->getSprite());
		//m_Window.draw(m_Player.getSprite());

		//Objects
		for (Object* n : m_Objects)
		{
			if (n->getMode() == MODE::NORMAL)
				if (m_Player->getRect().intersects(n->getRect_top())
					&& n->getMode() != MODE::COLIDER)
				{
					texture.draw(n->getSprite_hide());
					//m_Window.draw(n->getSprite());
				}
		}
		//StandartObjects
		for (StandartObject* n : m_StandartObjects)
		{
			if (!n->isPlayerUp((int)(m_Player->getRect().top + m_Player->getRect().height / 2)))
			{
				texture.draw(n->mf_getSprite());
				//m_Window.draw(n->mf_getSprite());
			}
		}

		//texture.draw(m_Player->getRS());
	}

	for (Box* n : m_Boxes)
	{
		texture.draw(n->getSprite());
		//m_Window.draw(n->getSprite());
	}


	if (m_obj != nullptr)
	{
		texture.draw(m_obj->getSprite());
		//m_Window.draw(m_obj->getSprite());
	}

	if (m_pTile != nullptr)
	{
		//texture.draw(p_tile->getSprite());
		//m_Window.draw(p_tile->getSprite());
		texture_tile.draw(m_pTile->getSprite());
	}

	//COLLIDERS
	if (isColVisible)
	{
		if (m_pCollider != nullptr)
		{
			if (window == Window::EDITOR)
				texture_tile.draw(m_pCollider->getRectShape());
			else if (window == Window::GAME)
				texture.draw(m_pCollider->getRectShape());
		}
		if (!m_Colliders.empty())
		{
			for (Collider* col : m_Colliders)
			{
				if (window == Window::EDITOR)
					texture_tile.draw(col->getRectShape());
				else if (window == Window::GAME)
					texture.draw(col->getRectShape());
			}

		}
	}

	if (m_pEntitySprite != nullptr)
	{
		texture.draw(*m_pEntitySprite);
	}

	//if (!m_pEntityDraw.empty())
	//{
	//	for (StandartObject* s : m_pEntityDraw)
	//	{
	//		texture.draw(s->mf_getSprite());
	//	}
	//}
	
	texture.display();
	texture_tile.display();
	texture_shot.display();
	//texture_creat.display();
	
	//m_Window.draw(m_Player.getRS());
	ImGui::SFML::Render(m_Window);


	m_Window.display();
}