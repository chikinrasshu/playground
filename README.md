# chkPlayground
simple 2D engine for learning how to implement stuff...

> [!NOTE]
> Current feature in focus:  
> - [ ] Asset packing

## Features
- [ ] Simple 2D rendering
- [ ] Asset packing and managing
- [ ] Stereo sound mixing and playback
- [ ] Separate internal resolution
- [ ] Input handling with scaled coordinates
- [ ] Gamepad support for up to 4 controllers
- [ ] Console-like menu-layer for settings
- [ ] Immediate Mode GUI for debugging

## License
MIT license, see [LICENSE.md](LICENSE.md) for more information.

## Building
Must have VCPKG_ROOT environment variable set to a working [vcpkg](https://github.com/microsoft/vcpkg) installation.  
If using vscode, install the C++ Extension pack (or manually install CMake Tools) and press `⚙ Build`  
Otherwise, you need to set CMAKE_TOOLCHAIN_FILE to `$env{VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake` then run cmake as always.

- [x] `core`: Library used by all the others. Common types, core functionality and types for assets and simple algorithms.
- [x] `packer`: Parses the assets_raw directory, searching asset files on common formats, packing them in `.chk` files for consumption by the `chk_asset_manager`.
- [ ] `sys`: Main launcher that implements the debug ui, the system overlay and provides the environment where the `plugins` get their memory and render target. Handles asset loading/streaming, audio playback and rendering.
- [ ] `plugin`: Library used by plugins for running on the `sys` environment.

## Libraries used
* MIT - [cwalk](https://github.com/likle/cwalk) by likle - for path manipulations in logs and file loading.
* MIT - [dirent](https://github.com/tronkko/dirent) by tronkko - implementation of `dirent` for MS Windows, used on packer for tree-like directory navigation.
* MIT - [stb](https://github.com/nothings/stb) by Sean Barrett - public domain single-header libraries. So far, used stb_image and stb_truetype
* zlib - [SDL3](https://github.com/libsdl-org/SDL) by libsdl-org - cross-platform library designed to make it easy to write multi-media software, such as games and emulators.
