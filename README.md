# FURY Game Engine

Welcome to the **FANTASTIC UNIFIED RENDERING YIELD (FURY) Game-Engine**, a high-performance game engine tailored for Windows 64-bit platforms. FURY is a personal project dedicated to building a robust foundation for game development with a strong emphasis on rendering capabilities and performance optimization.


*Started on*: **December 5, 2023**. 

*Last update to the ReadMe*: **Januray 15, 2024**.

## Documentation
In this section, you will find detailed documentation on various aspects of the FURY Game Engine. The documentation covers everything from the basic setup to advanced features, ensuring both beginners and experienced developers can make the most out of FURY.

In this section, you will find detailed documentation on various aspects of the FURY Game Engine. The documentation covers everything from the basic setup to advanced features, ensuring both beginners and experienced developers can make the most out of FURY.

- **Time Scale and Delta Time:** Timescale default value is retrived on seconds, but it can be retrived in miliseconds if specifing ts.GetMilliseconds().
- **API Calls:** FURY will draw on the API that better fits the platform utilizing the Engine. If you want to learn more about the Rendering architecture, jump into FURY/src/FURY/Renderer..
- **Additional Resources:** TODO: Links to more in-depth guides, tutorials, and examples to help you understand and use the FURY Game Engine to its full potential.

## Features

- **Dynamic Libraries**: Setup with dynamic library management for ease of development.
- **Automated Project Generation**: Jumpstart your work with `GenerateProject.bat` to set up the build system.
- **Logging System**: In-depth logging for effective debugging and development tracking.
- **Event System**: A versatile event-handling system to manage in-game actions and triggers.
- **Multi-Application Framework**: Supports the game and the engine applications within the same framework.
- **Active Development**: Regularly updated with new features as the engine evolves.

## Main features to come
- Fast 2D rendering (UI, particles, sprites, etc.)
- High-fidelity Physically-Based 3D rendering (this will be expanded later, 2D to come first)
- Support for Mac, Linux, Android and iOS
- Native rendering API support (DirectX, Vulkan, Metal)
- Fully featured viewer and editor applications
- Fully scripted interaction and behavior
- Integrated 3rd party 2D and 3D physics engine
- Procedural terrain and world generation
- Artificial Intelligence
- Audio system

## Getting Started

### Prerequisites

- Operating System: Windows 64-bit
- Recommended IDE: Visual Studio 2017 for optimal compatibility

### Cloning the Repository

Clone the FURY repository and its submodules using the command:

```bash
git clone --recursive https://github.com/Miguel-202/FURY.git
```

NOTE: There is an issue when replcating the submodules of FURY Engine, the "glfw" module gets cloned from the original glfw library isntead of my forked version. For now it can be fixed by clonning manually the following version: https://github.com/Miguel-202/glfw/tree/FuryGLFW into FURY/vendor/GLFW


If the repository was cloned non-recursively initially, retrieve the submodules with:

```bash
git submodule update --init
```

### Project Setup

Within the cloned directory, execute:

```bash
GenerateProject.bat
```

This script will configure dynamic libraries and generate the necessary Visual Studio project files.

## Development Progress

The FURY engine is currently in the early stages of development. As a self-taught project, I am diligently working on it daily, focusing on implementing new features and learning about memory optimization techniques for game engines.

## License

The FURY Game Engine is licensed under the Apache License 2.0. For more details, see the [LICENSE](LICENSE) file in the repository.

## Contact

For any inquiries or if you wish to know more about the FURY Game Engine, please visit my [website](https://miguelmartinezolivares.com/).

