/* Goxel2 - 3D Voxel Art Editor
 *
 * This is free and unencumbered software released into the public domain.
 *
 * Anyone is free to copy, modify, publish, use, compile, sell, or
 * distribute this software, either in source code form or as a compiled
 * binary, for any purpose, commercial or non-commercial, and by any means.
 *
 * In jurisdictions that recognize copyright laws, the author or authors
 * of this software dedicate any and all copyright interest in the
 * software to the public domain. We make this dedication for the benefit
 * of the public at large and to the detriment of our heirs and
 * successors. We intend this dedication to be an overt act of
 * relinquishment in perpetuity of all present and future rights to this
 * software under copyright law.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR
 * OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
 * ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
 * OTHER DEALINGS IN THE SOFTWARE.
 *
 * For more information, please refer to <http://unlicense.org/>
*/

#include "lua_plugins.h"

#define NUM_OF_STATES 100
lua_State* StateArr[NUM_OF_STATES] = { NULL };

bool check_lua(lua_State* L, int r) {
	if (r != LUA_OK) {
		LOG_E("[Lua] - %s\n", lua_tostring(L, -1));
		return false;
	}
	return true;
}

void ReleaseAllLuaVMs() {
	int releasedVMCount = 0;
	for (int i = 0; i < NUM_OF_STATES; ++i) {
		if (StateArr[i] != NULL) {
			lua_close(StateArr[i]);
			StateArr[i] = NULL;
			releasedVMCount++;
		}
	}

	LOG_I("Released Lua VMs");
}

lua_State* NewLuaVM() {
	lua_State* L = luaL_newstate();
	luaL_openlibs(L);
	lua_register(L, "GoxCreateBoxAt", lua_GoxCreateBoxAt);
	lua_register(L, "GoxRemoveBoxAt", lua_GoxRemoveBoxAt);
	lua_register(L, "GoxSetColor", lua_GoxSetColor);

	// Vector3 Math Library
	check_lua(L, luaL_dostring(L, assets_get("asset://data/lua/vector3.lua", NULL)));

	for (int i = 0; i < NUM_OF_STATES; ++i) {
		if (StateArr[i] == NULL) {
			StateArr[i] = L;
			check_lua(L, luaL_dostring(L, "print('Lua Virtual Machine Initialized!')\n"));
			return L;
		}
	}

	// If the function reaches at this point, it means the StateArr is full so we do all the clean up here.
	lua_close(L);
	LOG_E("Unable to initialize a new LUA VM, States Are Full");
	return NULL;
}

static void open_run_lua_plugin(void) {
	const char *filePath;
	filePath = noc_file_dialog_open(NOC_FILE_DIALOG_OPEN, "lua\0*.lua\0", NULL, NULL);
	if (!filePath) return;

	lua_State* L = NewLuaVM();
	if (L == NULL) return;

	check_lua(L, luaL_dofile(L, filePath));
}

ACTION_REGISTER(open_run_lua_plugin,
	.help = "Run Plugin",
	.cfunc = open_run_lua_plugin,
)
