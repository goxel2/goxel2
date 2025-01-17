/* Goxel 3D voxels editor
 *
 * copyright (c) 2022 Aditya Mishra
 *
 * Goxel is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.

 * Goxel is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more
 * details.

 * You should have received a copy of the GNU General Public License along with
 * goxel.  If not, see <http://www.gnu.org/licenses/>.
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
