#include "Engine.h"

enum Objects
{
	box = 0,
	Other = 1
};

sf::Sprite* pSp(Tile* &tile)
{
	Sprite *sp = new Sprite(tile->getTexture(), tile->getRect());
	sp->setPosition((sf::Vector2f)tile->getPosition());
	return sp;
}

void Engine::EntityWindow(bool* p_open)
{
	if (!ImGui::Begin("Entity_Window", p_open, ImGuiWindowFlags_AlwaysVerticalScrollbar))
	{
		ImGui::End();
		return;
	}

	ImGui::TextWrapped("Entity:");
	static int entity_pressed_count = 0;
	int entityNum = 0;

	//if (!ImGui::IsMouseHoveringAnyWindow())
	//	entityIsActive = false;
	//else
	//	entityIsActive = true;

	if (!m_pEntitySprites.empty())
	{
		for (sf::Sprite* s : m_pEntitySprites)
		{
			if (ImGui::ImageButton(*s))
			{
				entityIsActive = true;
				delete(m_pEntitySprite);
				entity_pressed_count += 1;
				m_pEntitySprite = new Sprite(*s);
				m_entityID = entityNum;
			}
			++entityNum;
			ImGui::NewLine();
		}
	}
	if (ImGui::Button("clear"))
	{
		entityIsActive = false;
		delete(m_pEntitySprite);
		m_pEntitySprite = nullptr;
	}

	ImGui::End();
}

void Engine::GameWindow(bool* p_open)
{

	if (!ImGui::Begin("game_window", p_open, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
		if (m_Player != nullptr)
		{
			delete(m_Player);
			m_Player = nullptr;
		}
		return;
	}

	ImVec2 tex_screen_pos = ImGui::GetCursorScreenPos();
	float tex_w = (float)texture.getSize().x;
	float tex_h = (float)texture.getSize().y;

	ImGui::Text("%.0fx%.0f", tex_w, tex_h);
	ImGui::SameLine();
	ImGui::Text("%i", window);

	ImGui::SameLine();
	if (ImGui::Button("save_colliders",sf::Vector2i(0,12))) {
		testDataSave("data/test.db");
	}

	ImGui::SameLine();
	if (ImGui::Button("save_object", sf::Vector2i(0, 12))) {
		testDataSave("data/test.db");
	}

	ImGui::PushID(0);

	ImGui::Image(sf::Sprite(texture.getTexture()));


	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		float focus_sz = 32.0f;
		gameWindowPosX = ImGui::GetMousePos().x - tex_screen_pos.x; if (focus_x < 0.0f) focus_x = 0.0f; else if (focus_x > tex_w - focus_sz) focus_x = tex_w - focus_sz;
		gameWindowPosY = ImGui::GetMousePos().y - tex_screen_pos.y - focus_sz * 0.5f; if (focus_y < 0.0f) focus_y = 0.0f; else if (focus_y > tex_h - focus_sz) focus_y = tex_h - focus_sz;
		ImGui::Text("Min: (%.2f, %.2f)", gameWindowPosX, gameWindowPosY);
		ImGui::Text("Max: (%.2f, %.2f)", gameWindowPosX + focus_sz, gameWindowPosY + focus_sz);
		entityIsActive = true;
		ImGui::EndTooltip();
	}
	else
	{
		entityIsActive = false;
	}

	ImGui::PopID();
	ImGui::End();

	Play(timeSinceLastUpdate, timePerFrame, dt);
}

void Engine::Testing(bool* p_open)
{
	if (!ImGui::Begin("testing_window", p_open, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
		return;
	}

	m_io = ImGui::GetIO();
	m_mousePos.x = m_io.MousePos.x;
	m_mousePos.y = m_io.MousePos.y;
	ImGui::Text("MousePos: (%g, %g)", m_io.MousePos.x, m_io.MousePos.y);
	m_mousePos_sfml = (sf::Vector2i)m_Window.mapPixelToCoords(sf::Mouse::getPosition(m_Window));
	ImGui::Text("MousePos(SFML): (%i, %i)", m_mousePos_sfml.x, m_mousePos_sfml.y);

	ImGui::Text("Joy button: (0:%i, 1:%i, 2:%i, 3:%i)", sf::Joystick::isButtonPressed(0, 0), sf::Joystick::isButtonPressed(0, 1)
		, sf::Joystick::isButtonPressed(0, 2), sf::Joystick::isButtonPressed(0, 3));
	ImGui::Text("Joy move: (X:%i, Y:%i)", posX, posY);
	ImGui::Text("Joy pov move: (X:%i, Y:%i)", (int)sf::Joystick::getAxisPosition(0, sf::Joystick::PovX)
		, (int)sf::Joystick::getAxisPosition(0, sf::Joystick::PovY));


	ImGui::Checkbox("clear_combo", &m_item_hide);

	if (m_item_hide && m_inProcess) //TODO: right mouse click
	{
		m_item = -1;

		delete(m_obj);
		delete(m_pTile);
		m_obj = nullptr;
		m_pTile = nullptr;
		m_inProcess = false;
	}

	if (m_item == -1)
		m_item_hide = false;

	ImGui::Combo("Objects", &m_item, m_items, IM_ARRAYSIZE(m_items));

	if (m_item == Objects::box && !m_inProcess)
	{
		m_obj = new Box(m_mousePos_sfml); //(Box*)malloc(sizeof(Box));// (int *)&mmm
	}

	if (m_obj != nullptr)
	{
		m_inProcess = true;
		m_obj->setPosition(m_mousePos_sfml);
	}


	//if (p_tile != nullptr)
	//{
	//	m_inProcess = true;

	//	for (int i = 0; i < w; i++)
	//	{
	//		for (int j = 0; j < h; j++)
	//		{
	//			if (grid[i][j].rect.contains(m_mousePos_sfml))
	//			{
	//				p_tile->setPosition(sf::Vector2i(grid[i][j].rect.left, grid[i][j].rect.top));
	//			}
	//		}
	//	}
	//}

	ImGui::Text("Mouse clicked:");  for (int i = 0; i < IM_ARRAYSIZE(m_io.MouseDown); i++) if (ImGui::IsMouseClicked(i)) { ImGui::SameLine(); ImGui::Text("b%i", i); }

	if (ImGui::IsMouseClicked(1) && m_inProcess && m_obj != nullptr)
	{
		m_Boxes.push_back(new Box(m_mousePos_sfml));
	}

	if (ImGui::IsMouseClicked(1) && m_inProcess && m_pTile != nullptr)
	{
		//m_Tiles.push_back(new Tile(p_tile->getPosition(), p_tile->getRect(), t)); //TODO: sprite push
		m_spriteTiles.push_back(pSp(m_pTile));
	}

	ImVec2 tex_screen_pos = ImGui::GetCursorScreenPos();
	float tex_w = (float)ImGui::GetIO().Fonts->TexWidth;
	float tex_h = (float)ImGui::GetIO().Fonts->TexHeight;
	ImTextureID tex_id = ImGui::GetIO().Fonts->TexID;

	//ImTextureID tex_id = 


	//for (int i = 0; i < 8; i++)
	//{
	//	ImGui::PushID(i);
	//	int frame_padding = -1 + i;     // -1 = uses default padding
	//	if (ImGui::ImageButton(tex_id, ImVec2(32, 32), ImVec2(0, 0), ImVec2(32.0f / tex_w, 32 / tex_h), frame_padding, ImColor(0, 0, 0, 255)))
	//		pressed_count += 1;
	//	ImGui::PopID();
	//	ImGui::SameLine();
	//}

	static char text1[16];
	static string text21;

	
	ImGui::InputText("(Name img)", text1, sizeof(text1), 1);
	//ImGui::SameLine();
	text21 = "tiles/";
	text21 += text1;
	text21 += ".png";
	if (ImGui::Button("load")) {
		m_tilesTexture.loadFromFile(text21);
		m_tileSet.setTexture(m_tilesTexture);
		//TODO: delete for malloc
		//tile = tileSet.makeTile(t_size);
	}

	ImGui::TextWrapped("textured buttons:");
	static int pressed_count = 0;

	for (int j = 0; j < (int)(m_tilesTexture.getSize().y / m_tilesSize); j++)
	{
		ImGui::PushID(j);
		for (int i = 0; i < (int)(m_tilesTexture.getSize().x / m_tilesSize); i++)
		{
			ImGui::PushID(i);
			if (ImGui::ImageButton(m_pTiles[i][j].getSprite(), sf::Vector2f(25, 25), 1))
			{
				pressed_count += 1;
				if (m_pTile == nullptr)
					m_pTile = new Tile(m_mousePos_sfml, m_pTiles[i][j].getRect(), m_tilesTexture);
				else
				{
					delete(m_pTile);
					m_pTile = new Tile(m_mousePos_sfml, m_pTiles[i][j].getRect(), m_tilesTexture);
				}
			}
			//ImGui::Image(tex);
			ImGui::PopID();
			ImGui::SameLine(0, 1);
		}
		ImGui::PopID();
		ImGui::NewLine();
	}

	//ImGui::Text("Hello");
	ImGui::End();
}

void Engine::TileEditor(bool* p_open)
{
	if (!ImGui::Begin("TileEditor", p_open, ImGuiWindowFlags_AlwaysAutoResize))
	{
		ImGui::End();
		return;
	}

	ImVec2 tex_screen_pos = ImGui::GetCursorScreenPos();
	float tex_w = (float)texture.getSize().x;
	float tex_h = (float)texture.getSize().y;

	static char text[16];
	static string text2;

	ImGui::Text("%.0fx%.0f", tex_w, tex_h);
	ImGui::SameLine();
	ImGui::InputText("(Name of the image)", text, sizeof(text));
	ImGui::SameLine();
	text2 = text;
	text2 += ".png";
	if (ImGui::Button("save")) {
		texture_shot.getTexture().copyToImage().saveToFile(text2);

		for (std::vector<sf::Sprite*>::iterator sp = m_spriteTiles.begin(); sp != m_spriteTiles.end(); ++sp)
		{
			delete (*sp);
		}
			
		m_spriteTiles.clear();
		delete(m_TextureTileMap);

		for (int i = 0; i < w_tile; i++)
		{
			for (int j = 0; j < h_tile; j++)
			{
				tileGrid[i][j].isEmpty = true;
			}
		}

		m_TextureTileMap = new Texture();
		m_TextureTileMap->loadFromFile(text2);
		m_SpriteTileMap = new Sprite();
		m_SpriteTileMap->setTexture(*m_TextureTileMap);
		m_spriteTiles.push_back(m_SpriteTileMap);
	}

	ImGui::Image(sf::Sprite(texture_tile.getTexture()));


	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		float focus_sz = 32.0f;
		focus_x = ImGui::GetMousePos().x - tex_screen_pos.x ; if (focus_x < 0.0f) focus_x = 0.0f; else if (focus_x > tex_w) focus_x = tex_w - focus_sz;
		focus_y = ImGui::GetMousePos().y - tex_screen_pos.y - focus_sz * 0.5f; if (focus_y < 0.0f) focus_y = 0.0f; else if (focus_y > tex_h) focus_y = tex_h - focus_sz;
		ImGui::Text("Min: (%.2f, %.2f)", focus_x, focus_y);
		ImGui::EndTooltip();
	}

	if (m_pTile != nullptr)
	{
		m_inProcess = true;

		for (int i = 0; i < w_tile; i++)
		{
			for (int j = 0; j < h_tile; j++)
			{
				if (tileGrid[i][j].rect.contains((sf::Vector2i)texture_tile.mapPixelToCoords(sf::Vector2i((int)focus_x , (int)focus_y))))
				{
					m_pTile->setPosition(sf::Vector2i(tileGrid[i][j].rect.left, tileGrid[i][j].rect.top));
				}
			}
		}
	}

	static char text_l[16];
	static string text_l2;

	ImGui::InputText("(Name of the load image)", text_l, sizeof(text_l));
	ImGui::SameLine();
	text_l2 = text_l;
	text_l2 += ".png";
	if (ImGui::Button("load")) {
		m_spriteTiles.clear();
		delete(m_TextureTileMap);
		delete(m_SpriteTileMap);

		m_TextureTileMap = new Texture();
		m_TextureTileMap->loadFromFile(text_l2);
		m_SpriteTileMap = new Sprite();
		m_SpriteTileMap->setTexture(*m_TextureTileMap);
		m_spriteTiles.push_back(m_SpriteTileMap);
	}

	ImGui::End();
}


void Engine::GUI()
{

	static bool m_pIsGameWindowOpen = false;
	static bool m_pIsTileEditorWindowOpen = false;
	static bool m_pIsTestingWindowOpen = false;
	static bool m_pIsEntityWindowOpen = false;


	if (m_pIsGameWindowOpen) GameWindow(&m_pIsGameWindowOpen);
	if (m_pIsTileEditorWindowOpen) TileEditor(&m_pIsTileEditorWindowOpen);
	if (m_pIsTestingWindowOpen) Testing(&m_pIsTestingWindowOpen);
	if (m_pIsEntityWindowOpen) EntityWindow(&m_pIsEntityWindowOpen);


	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("GameWindow"))
			{
				m_Player = new Player();
				m_pIsGameWindowOpen = true;
			}
			if (ImGui::MenuItem("TileEditorWindow"))
			{
				m_pIsTileEditorWindowOpen = true;
			}
			if (ImGui::MenuItem("TestingWindow"))
			{
				m_pIsTestingWindowOpen = true;
			}
			if (ImGui::MenuItem("EntityWindow"))
			{
				m_pIsEntityWindowOpen = true;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	//ImGui::ShowTestWindow();
}