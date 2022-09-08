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

#include "goxel.h"

// Free All The VMs
void ReleaseAllLuaVMs();

// Creates A New Lua VM & Pushes it Into Lua VM's Arrays, if array is full returns -1;
lua_State* NewLuaVM();
