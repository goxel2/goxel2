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
