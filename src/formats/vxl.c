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

// Support for Ace of Spades map files (vxl)
// Author: https://github.com/xtreme8000

#include "goxel.h"
#include "file_format.h"
#include "../../lib/libvxl/libvxl.h" // Using the Relative path cause i don't have money to buy a mac and change stuff for osx

#define RGB(r, g, b) (((b) << 16) | ((g) << 8) | (r))
#define RED(c) ((c)&0xFF)
#define GREEN(c) (((c) >> 8) & 0xFF)
#define BLUE(c) (((c) >> 16) & 0xFF)

static int import_vxl(image_t* image, const char* path) {
	if (!path) {
		return -1;
	}

	int file_size;
	void* file_data = read_file(path, &file_size);

	size_t map_size, map_depth;

	if(!libvxl_size(&map_size, &map_depth, file_data, file_size)) {
		return -1;
	}

	struct libvxl_map map;

	if(!libvxl_create(&map, map_size, map_size, map_depth, file_data, file_size)) {
		return -1;
	}

	mesh_iterator_t it = mesh_get_iterator(image->active_layer->mesh, MESH_ITER_VOXELS);

	for (size_t x = 0; x < map_size; x++) {
		for (size_t y = 0; y < map_size; y++) {
			for (size_t z = 0; z < map_depth; z++) {
				if (libvxl_map_issolid(&map, x, y, z)) {
					uint32_t color = libvxl_map_get(&map, x, y, z);
					mesh_set_at(
						image->active_layer->mesh, &it,
						(int[3]) {map_size / 2 - 1 - x,
						y - map_size / 2,
						map_depth / 2 - 1 - z},
						(uint8_t[4]) { BLUE(color), GREEN(color), RED(color), 0xFF }
					);
				}
			}
		}
	}

	libvxl_free(&map);

	if(!box_is_null(image->box)) {
		bbox_from_extents(
			image->box,
			vec3_zero,
			map_size / 2.0F,
			map_size / 2.0F,
			map_depth / 2.0F
		);
	}

	return 0;
}

static int export_as_vxl(const image_t* image, const char* path) {
	if (!path) {
		return -1;
	}

	const mesh_t* mesh = goxel_get_layers_mesh(image);

	int bbox[2][3];
	if (!mesh_get_bbox(mesh, bbox, true)) {
		return -1;
	}

	struct libvxl_map map;

	if (!libvxl_create(
			&map,
			bbox[1][0] - bbox[0][0],
			bbox[1][1] - bbox[0][1],
			bbox[1][2] - bbox[0][2],
			NULL, 0 )) {
		return -1;
	}

	int pos[3];
	mesh_iterator_t it = mesh_get_iterator(mesh, MESH_ITER_SKIP_EMPTY);

	while(mesh_iter(&it, pos)) {
		uint8_t color[4];
		mesh_get_at(mesh, &it, pos, color);

		if (color[3] > 0) {
			libvxl_map_set(
				&map,
				bbox[1][0] - 1 - pos[0],
				pos[1] - bbox[0][1],
				bbox[1][2] - 1 - pos[2],
				RGB(color[2], color[1], color[0])
			);
		}
	}

	libvxl_writefile(&map, (char*)path);
	libvxl_free(&map);

	return 0;
}

FILE_FORMAT_REGISTER(vxl,
	.name = "vxl",
	.ext = "vxl\0*.vxl\0",
	.import_func = import_vxl,
	.export_func = export_as_vxl
)
