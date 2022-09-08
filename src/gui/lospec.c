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

/*
	Support For Importing Palettes From LoSpec (lospec.com)
*/

#include "goxel.h"
#include "downloader.h"
#include <errno.h>

// https://lospec.com/palette-list/.gpl - Length 36
#define PaletteURLSize 40 // Length of the URL without palette Name: 36, using 40 for no reason.
#define PaletteNameSize 2048 // Length of the Name of the palette, too big just to be "safe"?

char PaletteName[PaletteNameSize] = {0};
char PaletteURL[PaletteURLSize + PaletteNameSize] = {0};

int gui_lospec_importer_popup(void *data)
{
	gui_text("Enter a LoSpec Palette Name");
	gui_input_text("", PaletteName, 2048);
	gui_text("program might freeze, it's not a crash...");

	if (gui_button("Ok", 0, 0)) {
	    char *filePath;
	    if (sys_get_user_dir()) {
	        asprintf(&filePath, "%s/lospec/%s.gpl", sys_get_user_dir(), PaletteName);
	        sys_make_dir(filePath); // Ensure the directory exists
			sprintf(PaletteURL, "https://lospec.com/palette-list/%s.gpl", PaletteName);
			printf("%s\n%s\n%s\n", PaletteURL, PaletteName, filePath);
			DownloadFileFrom(PaletteURL, filePath);
	        free(filePath);
	        palette_load_all(&goxel.palettes);
	    }
		return 1;
	}

	gui_same_line();
	return gui_button("Cancel", 0, 0);
}
