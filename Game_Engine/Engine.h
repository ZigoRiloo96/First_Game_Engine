#pragma once

#include "imgui.h"
#include "imgui-sfml.h"
#include "imgui_internal.h"

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Player.h"
#include "Object.h"
#include "Trigger.h"
#include "AnimationObject.h"
#include "agdlib.h"
#include <vector>
#include "StandartObject.h"
#include "Object_2.h"
#include "Box.h"
#include "Tile.h"
#include "TileSet.h"
#include "Collider.h"

#include "sqlite3.h"

using namespace sf;

struct Grid
{
	sf::IntRect rect;
	bool isEmpty;
};

class Engine
{
private:

	//TIME
	Clock clock;
	sf::Time timeSinceLastUpdate, dt;
	const sf::Time timePerFrame = seconds(1.0f / 60.0f);

	//WNDOW setUp
	Vector2i m_Resolution;
	RenderWindow m_Window;
	Vector2f m_WindowSize;

	//GAME BACKGROUND
	Sprite m_BackgroundSprite;
	Texture m_BackgroundTexture;
	Vector2f m_BackgroundSizeTexture;

	//PROGRAM BACKGROUND
	Texture m_tProgramBackground;
	Sprite m_sProgramBackground;

	//INPUT
	Event m_event;
	ImGuiIO& m_io = ImGui::GetIO();
	sf::Vector2i m_mousePos;
	sf::Vector2i m_mousePos_sfml;
	bool lastKeyState = false;

	//TESTING
	View m_View;
	View m_View_Window;

	//PLAYER
	Player* m_Player;

	//OBJECT GUI
	const char* m_items[2] = { "Box", "Other" };
	bool m_item_hide = true;
	int m_item = -1;
	Box* m_obj = nullptr;
	bool m_inProcess = false;
	std::vector<Box*> m_Boxes;

	//TILES
	sf::Texture m_tilesTexture;
	int m_tilesSize;
	TileSet m_tileSet;
	Tile **m_pTiles;
	Tile *m_pTile = nullptr;
	//std::vector<Tile*> m_Tiles;
	//DOING: sprite vector insted of tile vector
	std::vector<Sprite*> m_spriteTiles;

	Grid **m_pGrid = nullptr;
	int m_gridSize = 128;

	int m_gridWidth;
	int m_gridHeight;


	//controller 
	int posX;
	int posY;

	//Objects
	std::vector<Object*> m_Objects;

	//Standart Objects
	std::vector<StandartObject*> m_StandartObjects;

	//StandartObject *m_trawka_01;

	Texture m_DoorTexture;
	Animation* m_Door;
	Trigger* m_DoorTrigger;

	Texture m_g_texture;
	Animation m_gowno;

	void begin();
	void input();
	void GUI();
	void update();
	void update(float dtAsSeconds);
	void draw();

	Grid **gridSetUp(int sizeX,int sizeY, int size);

	//gameWindow
	sf::RenderTexture texture;
	sf::RenderTexture texture_creat;
	float gameWindowPosX;
	float gameWindowPosY;
	enum Window
	{
		NOTHING,
		GAME,
		EDITOR
	};
	Window window = Window::NOTHING;
	

	//tileEditorWindow
	sf::RenderTexture texture_tile;
	sf::RenderTexture texture_shot;
	Grid** tileGrid;
	int w_tile;
	int h_tile;
	Vector2i viewPos;
	View m_View_tile;
	Texture* tiles;
	int files;
	Texture gridTex;
	sf::Texture *m_TextureTileMap = nullptr;
	sf::Sprite *m_SpriteTileMap = nullptr;

	//COLLIDERS
	std::vector<Collider*> m_Colliders;
	Collider* m_pCollider = nullptr;
	bool isColVisible = true;
	bool lastVkeyState = false;

	//BEGIN TEXTURES
	//std::vector<sf::Texture*> textures;
	sf::Texture* m_pTexture;
	
	//loadEntityTextures
	std::vector<sf::Texture*> m_pEntityTextures;
	std::vector<sf::Sprite*> m_pEntitySprites;
	void loadTexturesFromPath();
	void EntityWindow(bool* p_open);
	sf::Sprite* m_pEntitySprite = nullptr;
	int m_entityID = 0;
	bool entityIsActive = false;
	std::vector<StandartObject*> m_pEntityDraw;
	void alternativeSave();
	bool lastLeftKeyState = false;

	//Render
	std::vector<sf::Sprite*> m_RenderSprites;

public:

	//gameWindow
	void GameWindow(bool* p_open);

	//tileEditorWindow
	void TileEditor(bool* p_open);
	Grid** &MakeGrid(int width, int height);
	float focus_x = 0, focus_y = 0; //timed

	//testingWindow
	void Testing(bool* p_open);

	//input
	void OnKeyReleased();

	//lua_scripting

	//SQL
	void testDataLoad();
	void testDataSave();

	//playGame
	void Play(sf::Time timeSinceLastUpdate, sf::Time timePerFrame, sf::Time dt);

	Vector2i getResolution();
	Engine();
	void start();
};