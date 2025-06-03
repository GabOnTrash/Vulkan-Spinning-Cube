# Vulkan-Spinning-Cube

This project is a minimal C++20 application that demonstrates how to render a rotating 3D cube using the Vulkan graphics API. It is designed for educational purposes and as a starting point for more complex Vulkan-based applications.

---

## Features

- **Vulkan API**: Modern, explicit graphics API for high-performance rendering.
- **GLFW**: Cross-platform window and input management.
- **GLM**: Mathematics library for graphics software (vectors, matrices, transformations).
- **C++20**: Uses modern C++ features for clarity and safety.
- **Rotating Cube**: Renders a colored, indexed 3D cube with basic camera and transformation logic.
- **Validation Layers**: Optional Vulkan validation for debugging and learning.

---

## Prerequisites

- **Windows 10/11** (tested)
- **Visual Studio 2022** (or later)
- **Vulkan SDK** (https://vulkan.lunarg.com/)
- **GLFW** (https://www.glfw.org/)
- **GLM** (https://github.com/g-truc/glm)
- **vcpkg** (recommended for dependency management)

---

## Building

### 1. Install Dependencies

It is recommended to use [vcpkg](https://github.com/microsoft/vcpkg):

Make sure the Vulkan SDK is installed and its `Bin` and `Lib` folders are in your system `PATH`.

### 2. Open the Project

- Open `Vulkan.sln` in Visual Studio 2022.
- Ensure the `x64` configuration is selected.

### 3. Configure Include and Library Paths

- If you use vcpkg, integrate it with Visual Studio:
  - `vcpkg integrate install`
- Otherwise, manually add the include and lib directories for GLFW, GLM, and Vulkan SDK in your project settings.

### 4. Build

- Build the solution (`Ctrl+Shift+B`).

---

## Running

- Run the application (`F5` or `Ctrl+F5`).
- A window titled **"Vulkan Triangle"** will appear, displaying a rotating 3D cube.

---

## File Structure

- `Vulkan.cpp` — Entry point (`WinMain`), creates and runs the `Cube` application.
- `Cube.h` / `Cube.cpp` — Main application logic: Vulkan setup, rendering loop, resource management.
- `shaders/` — SPIR-V vertex and fragment shaders (see below).

---

## Shaders

The application expects precompiled SPIR-V shaders at:

- `shaders/basic.vert.spv`
- `shaders/basic.frag.spv`

You can compile GLSL shaders using `glslangValidator` from the Vulkan SDK:


---

## Controls

- The cube rotates automatically.
- Close the window to exit.

---

## Troubleshooting

- **Validation Layer Errors**: Make sure the Vulkan SDK is installed and up to date.
- **Missing DLLs**: Ensure all dependencies are in your system `PATH`.
- **Swapchain/Device Errors**: Your GPU and drivers must support Vulkan 1.0+.

---

## License

This project is provided for educational purposes. See individual library licenses for GLFW, GLM, and Vulkan SDK.

---

## References

- [Vulkan Documentation](https://vulkan.lunarg.com/doc/)
- [GLFW Documentation](https://www.glfw.org/docs/latest/)
- [GLM Documentation](https://glm.g-truc.net/0.9.9/index.html)


