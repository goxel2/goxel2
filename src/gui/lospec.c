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
