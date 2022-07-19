# Goxel2

![Stable Release](https://github.com/pegvin/goxel2/actions/workflows/release.yml/badge.svg)
![Nightly Release](https://github.com/pegvin/goxel2/actions/workflows/nightly.yml/badge.svg)

Official webpage: https://pegvin.github.io/goxel2/

---
# About

You can use goxel to create voxel graphics (3D images formed of cubes). It
works on Windows, Linux and macOS.

---
# Features

- 24 bits RGB colors.
- Unlimited scene size.
- Unlimited undo buffer.
- Layers.
- Marching Cube rendering.
- Procedural rendering.
- Export to obj, pyl, png, magica voxel, qubicle.
- Ray tracing.

---
# Todo
- [ ] Lua for scripting
- [ ] Fix High CPU Usage On Idle
- [ ] Fix Key Mapping in Settings
- [ ] Improve UI
- [ ] Create A Updater To Check For Updates

---
# Download

You can download latest stable release from [here](https://github.com/pegvin/goxel2/releases/latest), For Many Reasons Goxel2 Has Dropped Support For Android, IOS & Web.

Usage
-----

- Left click: apply selected tool operation.
- Middle click: rotate the view.
- right click: pan the view.
- Left/Right arrow: rotate the view.
- Mouse wheel: zoom in and out.


Building
--------

The building system uses scons.  You can compile in debug with 'scons', and in
release with 'scons mode=release'.  On Windows, currently possible to build
with [msys2](https://www.msys2.org/) or try prebuilt
[goxel](https://packages.msys2.org/base/mingw-w64-goxel) package directly.
The code is in C99, using some gnu extensions, so it does not compile
with msvc.

# Linux/BSD

Install dependencies using your package manager. On Debian/Ubuntu:

    - scons
    - pkg-config
    - libglfw3-dev
    - libgtk-3-dev

Then to build, run the command:

    make release

# Windows

You need to install msys2 mingw, and the following packages:

    pacman -S mingw-w64-x86_64-gcc
    pacman -S mingw-w64-x86_64-glfw
    pacman -S mingw-w64-x86_64-libtre-git
    pacman -S scons
    pacman -S make

Then to build:

    make release


---
# Thanks
