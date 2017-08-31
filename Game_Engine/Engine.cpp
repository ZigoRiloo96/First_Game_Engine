#include "Engine.h"

#include <string>
#include <iostream>

#define IM_ARRAYSIZE(_ARR)  ((int)(sizeof(_ARR)/sizeof(*_ARR)))


Engine::Engine()
{
	begin();

	m_Resolution.x = VideoMode::getDesktopMode().width;
	m_Resolution.y = VideoMode::getDesktopMode().height;

	m_WindowSize = Vector2f((float)m_Resolution.x , (float)m_Resolution.y);

	m_Window.create(VideoMode(m_Resolution.x, m_Resolution.y)
		, "Engine", Style::Default);

	m_Window.setFramerateLimit(60);

	//m_Window.setPosition(Vector2i(resolution.x / 2, resolution.y / 2));

	m_View_Window.setCenter(Vector2f((float)m_Resolution.x/2, (float)m_Resolution.y/2));
	m_View_Window.setSize(m_WindowSize);
	m_Window.setView(m_View_Window);

	ImGui::SFML::Init(m_Window);

	//ImGui::SetNextWindowPosCenter();

	m_tilesSize = 16;
	m_tilesTexture.loadFromFile("Sprites/tiles_02.png");
	m_tileSet.setTexture(m_tilesTexture);
	m_pTiles = m_tileSet.makeTile(m_tilesSize);

	//--------------------------------

	m_BackgroundTexture.loadFromFile("game_map/ground.png");
	m_BackgroundSizeTexture = Vector2f(m_BackgroundTexture.getSize().x/2, m_BackgroundTexture.getSize().y / 2);
	m_BackgroundSprite.setTexture(m_BackgroundTexture);

	m_tProgramBackground.loadFromFile("pic.png");
	m_sProgramBackground.setTexture(m_tProgramBackground);

	//TEST
	texture.create(500, 500);
	texture_creat.create(500, 500);

	//tileEditorWindow
	texture_tile.create(500, 500);
	texture_shot.create(500, 500);
	w_tile = (int)(texture_tile.getSize().x / m_tilesSize);
	h_tile = (int)(texture_tile.getSize().y / m_tilesSize);
	//MakeGrid(tileGrid, w_tile, h_tile);
	tileGrid = MakeGrid(w_tile, h_tile);
	viewPos.x = texture_tile.getSize().x / 4;
	viewPos.y = texture_tile.getSize().y / 4;
	m_View_tile.setSize(texture_tile.getSize().x/2, texture_tile.getSize().y/2);
	m_View_tile.setCenter(viewPos.x, viewPos.y);
	texture_tile.setView(m_View_tile);
	gridTex.loadFromFile("grid.png");
	
	//Player
	m_Player = nullptr;

	//m_View.setCenter(m_BackgroundSizeTexture);
	m_View.setSize(500, 500);

	texture.setView(m_View);
	texture_creat.setView(m_View);

	m_gridWidth = (int)(m_gridSize / m_tilesSize);
	m_gridHeight = (int)(m_gridSize / m_tilesSize);

	m_pGrid = MakeGrid(m_gridWidth, m_gridHeight);

	//Entity
	loadTexturesFromPath();

	//
	object_sprite = nullptr;
	object_texture.create(250,250);
	object_view.setSize(100, 100);
	object_view.setCenter(50, 50);
	object_texture.setView(object_view);
	pObject = nullptr;

	//
	windowChoice = 0;
	wc = windowCh::GM;
}

Grid** &Engine::MakeGrid(int width, int height)
{
	Grid** g = (Grid**)malloc(height * sizeof(Grid*));
	for (int i = 0; i < height; i++)
		g[i] = (Grid*)malloc(width * sizeof(Grid));

	for (int x = 0, i = 0; i < width; x += m_tilesSize, i++)
	{
		for (int y = 0, j = 0; j < height; y += m_tilesSize, j++)
		{
			g[i][j].isEmpty = true;
			g[i][j].rect.left = x;
			g[i][j].rect.top = y;
			g[i][j].rect.width = m_tilesSize;
			g[i][j].rect.height = m_tilesSize;
		}
	}

	return g;
}

Vector2i Engine::getResolution()
{
	return m_Resolution;
}

Grid **Engine::gridSetUp(int sizeX, int sizeY, int size)
{
	int w = (int)(sizeX / size);
	int h = (int)(sizeY / size);

	Grid **g = (Grid**)malloc(h*sizeof(Grid*));
	for (int i = 0; i < w; i++)
		g[i] = (Grid*)malloc(sizeof(Grid));

	for (int x = 0,i=0; x < sizeX; x+=size, i++)
	{
		for (int y = 0,j=0; y < sizeY; y+=size, j++)
		{
			g[i][j].isEmpty = true;
			g[i][j].rect.left = x;
			g[i][j].rect.top = y;
			g[i][j].rect.width = size;
			g[i][j].rect.height = size;
		}
	}

	return g;
}

void Engine::start()
{
	testDataLoad("data/test.db");
	
	timeSinceLastUpdate = Time::Zero;

	while (m_Window.isOpen())
	{
		dt = clock.restart();

		timeSinceLastUpdate = sf::Time::Zero;

		input();

		ImGui::SFML::Update(m_Window, dt);

		GUI();

		draw();
	}
	ImGui::SFML::Shutdown();
}