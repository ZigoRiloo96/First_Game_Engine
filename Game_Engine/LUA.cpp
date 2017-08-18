#include "Engine.h"
#include <sol.hpp>

int pre_existing_system(lua_State* L) {
	sol::state_view lua(L);
	lua.script("print('bark bark bark!')");
	return 0;
}

int player(lua_State* L) {
	sol::state_view lua(L);

	lua.load_file("Scripts/tast.lua");

	return 0;
}

void Engine::LUA()
{
	sol::state lua;

	
	
}