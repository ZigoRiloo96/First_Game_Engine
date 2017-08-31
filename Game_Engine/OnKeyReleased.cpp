#include "Engine.h"

void Engine::OnKeyReleased()
{
	if (m_pCollider != nullptr)
	{
		m_Colliders.push_back(m_pCollider);
		m_pCollider = nullptr;
	}
	if (pObjectRect != nullptr)
	{
		pObject->setRect_top((sf::FloatRect)*pObjectRect);
	}
}