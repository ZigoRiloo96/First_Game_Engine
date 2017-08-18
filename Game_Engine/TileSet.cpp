#include "TileSet.h"


TileSet::TileSet()
{
}

TileSet::TileSet(sf::Texture t):
	m_Texture(t)
{
}

Tile **TileSet::makeTile(int size)
{
	sf::Vector2i startP(0,0);
	int i = (int)(m_Texture.getSize().x / size);
	int j = (int)(m_Texture.getSize().y / size);

	Tile **tile = (Tile**)malloc(i*sizeof(Tile*));
	for (int k = 0; k < j; k++)
		tile[k] = (Tile*)malloc(j*sizeof(Tile));

	for (int k = 0; k < i; k++)
	{
		for (int g = 0; g < j; g++)
		{
			tile[k][g] = Tile(startP, sf::IntRect(startP, sf::Vector2i(size, size)), m_Texture);

			startP.y += size;
		}
		startP.x += size;
		startP.y = 0;
	}

	return tile;
}

void TileSet::setTexture(const sf::Texture & t)
{
	m_Texture = t;
}
