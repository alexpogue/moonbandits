# SDL Project (CMake + vcpkg + Emscripten)

This project supports:
- Native desktop build
- Web build (Emscripten/WASM)
- Dependencies via **vcpkg (git submodule)**
- CMake presets for configuration

---

## Requirements

### Common
- CMake ≥ 3.20
- Git
- C++ compiler (MSVC / GCC / Clang)

### Web build
- Emscripten SDK (`emcc`, `emcmake` in PATH)

### Other prerequisites for running natively in  X11 / Wayland
- Given by command line upon build / run

---

## First-time setup

### Clone (with submodules)

```bash
git clone --recursive <repo-url>
cd <repo>
```

If already cloned:

```bash
git submodule update --init --recursive
```

## Bootstrap vcpkg

**Windows**

```bash
vcpkg/bootstrap-vcpkg.bat
```

**Mac/Linux**

```bash
vcpkg/bootstrap-vcpkg.sh
```


## Configure

**Native**

```bash
cmake --preset native
```

**Web**

```bash
cmake --preset emscripten
```

## Build

**Native**

```bash
cmake --build build-native
```

**Web**

```bash
cmake --build build-emscripten
```

## Run

**Native**

```bash
./build-native/moonbandits
```

**Web**

```bash
emrun build-emscripten/moonbandits.html
```

or if no browser is installed:

```bash
emrun --no_browser --port 8080 build-emscripten/moonbandits.html
```


