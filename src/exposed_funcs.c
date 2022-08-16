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

#include "exposed_funcs.h"

unsigned char SelectedColor[4] = { 255, 255, 255, 255 };

int lua_GoxSetColor(lua_State* L) {
	int NewColor[3], isNum;

	for (int i = 0; i < 3; ++i) {
		NewColor[i] = (int)lua_tonumberx(L, i+1, &isNum);
		if (isNum == false) {
			break;
		}
	}

	if (isNum != false) {
		// Clamp The Values Between 0 & 255
		for (int i = 0; i < 3; ++i) {
			SelectedColor[i] = NewColor[i] <= 0 ? 0 : NewColor[i];
			SelectedColor[i] = NewColor[i] >= 255 ? 255 : NewColor[i];
		}
	}

	printf("[C] - GoxSetColor(%d, %d, %d);\n", SelectedColor[0], SelectedColor[1], SelectedColor[2]);
	return 3;
}

int lua_GoxCreateBoxAt(lua_State* L) {
	int x, y, z;
	x = (int)lua_tonumber(L, 1);
	y = (int)lua_tonumber(L, 2);
	z = (int)lua_tonumber(L, 3);

	mesh_iterator_t it = mesh_get_iterator(goxel.image->active_layer->mesh, MESH_ITER_VOXELS);
	mesh_set_at(
		goxel.image->active_layer->mesh, // Mesh To Draw At
		&it, // Iterator
		(int[3]) { x, y, z }, // Position
		SelectedColor // Color
	);

	printf("[C] - GoxCreateBoxAt(%d, %d, %d);\n", x, y, z);
	return 3;
}

int lua_GoxRemoveBoxAt(lua_State* L) {
	int x, y, z;
	x = (int)lua_tonumber(L, 1);
	y = (int)lua_tonumber(L, 2);
	z = (int)lua_tonumber(L, 3);

	mesh_iterator_t it = mesh_get_iterator(goxel.image->active_layer->mesh, MESH_ITER_VOXELS);
	mesh_clear_block(
		goxel.image->active_layer->mesh, // Mesh To Draw At
		&it, // Iterator
		(int[3]) { x, y, z } // Position
	);

	printf("[C] - GoxRemoveBoxAt(%d, %d, %d);\n", x, y, z);
	return 3;
}
