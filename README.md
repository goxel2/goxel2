# Goxel2

[![Stable Release](https://github.com/pegvin/goxel2/actions/workflows/release.yml/badge.svg)](https://github.com/pegvin/goxel2/releases)
[![Nightly Release](https://github.com/pegvin/goxel2/actions/workflows/nightly.yml/badge.svg)](https://github.com/pegvin/goxel2/actions/workflows/nightly.yml)

[![Open Issues](https://img.shields.io/github/issues/pegvin/goxel2)](https://github.com/pegvin/goxel2/issues)
[![AUR Badge](https://img.shields.io/aur/version/goxel2-git)](https://aur.archlinux.org/packages/goxel2-git)
[![Discord Chat](https://img.shields.io/discord/998971119623209090?color=7289DA&label=discord)](https://discord.gg/YXx3afnzzW)
[![Total Downloads](https://img.shields.io/github/downloads/pegvin/goxel2/total)](https://github.com/pegvin/goxel2/releases)

Official webpage: https://pegvin.github.io/goxel2

---
## Features

- Layers.
- Ray tracing.
- Unlimited scene size.
- Marching Cube rendering.
- Available For x64 & x86 Based Systems.
- Extendable using Lua (WIP)
- Export to obj, pyl, png, magica voxel, qubicle & many more.

---
## Todo
- [ ] Lua/Julia for scripting
- [ ] Fix High Resource Usage
	- [ ] CPU
	- [ ] GPU
	- [ ] RAM

- [ ] Fix Key Mapping in Settings
- [ ] Improve UI
- [ ] Create A Updater To Check For Updates

---
## Download

You can download latest stable release from [here](https://github.com/pegvin/goxel2/releases/latest), For Many Reasons Goxel2 Has Dropped Support For Android, IOS & Web.

---
## Usage

- Left click: apply selected tool operation.
- Middle click: rotate the view.
- right click: pan the view.
- Left/Right arrow: rotate the view.
- Mouse wheel: zoom in and out.


---
## Building from source

The building system uses scons.  You can compile in debug with 'scons', and in
release with 'scons mode=release'.  On Windows, currently possible to build
with [msys2](https://www.msys2.org/) or try prebuilt
[goxel2](https://github.com/pegvin/goxel2/releases/latest) package directly.
The code is in C99, using some gnu extensions, so it does not compile
with msvc.

### Linux/BSD

Install dependencies using your package manager.

- On Debian/Ubuntu:

```bash
sudo apt-get install scons pkg-config libglfw3-dev libgtk-3-dev
```

### Windows:

You need to install [msys2](https://www.msys2.org/), and the following packages:

```bash
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-glfw mingw-w64-x86_64-libtre-git scons make
```

and then to finally build, run the command:

```bash
make release
```

---

## Project layout

```
    ├─ .github/         GitHub related configurations & workflows
    ├─ aur/             AUR's Repository
    ├─ data/            Configurations & Data (which are converted to C Arrays)
    ├─ lib/             Third-party Libraries
    ├─ screenshots/     Some Screenshots of the application
    ├─ tools/           contains python scripts which convert all of the data inside sub-dirs in 'data' dir
    ├─ src/             application source code (see src/nvim/README.md)
    │  ├─ assets/       converted contents of 'data' folder
    │  ├─ formats/      handlers for different file formats
    │  ├─ gui/          contains different gui items
    │  ├─ lua-5.4.4/    lua's source code
    │  ├─ tools/        algorithms & functions for different tools like brush
    │  └─ utils/        simple utility functions & macros
    ├─ SConstruct/      scons configuration file
    └─ icon.png         main icon which is converted to .icns on github actions
```

some files/directories might not be included here because they are pretty self-explainatory

---

## Credits & Licenses

|       Item        |                          License                           |
|-------------------|------------------------------------------------------------|
| Goxel             | [GPL v3.0](https://github.com/guillaumechereau/goxel)      |
| inih              | [BSD 3-Clause](https://github.com/benhoyt/inih)            |
| json-parser       | [BSD 2-Clause](https://github.com/udp/json-parser)         |
| xxHash            | [BSD 2-Clause](https://github.com/Cyan4973/xxHash)         |
| cgltf             | [MIT](https://github.com/jkuhlmann/cgltf)                  |
| imgui             | [MIT](https://github.com/ocornut/imgui)                    |
| libvxl            | [MIT](https://github.com/xtreme8000/libvxl)                |
| noc_file_dialog   | [MIT](https://github.com/guillaumechereau/noc)             |
| yocto-gl          | [MIT](https://github.com/xelatihy/yocto-gl)                |
| stb               | [MIT & Unlicense](https://github.com/nothings/stb)         |
| Montserrat font   | [Open Font](https://fonts.google.com/specimen/Montserrat)  |
| glew              | [Custom](https://github.com/nigels-com/glew)               |
| uthash            | [Custom](https://github.com/troydhanson/uthash)            |

---

# Thanks
