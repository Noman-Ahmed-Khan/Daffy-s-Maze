# Maze Generation and Pathfinding Visualization

A comprehensive C++ application for generating mazes using multiple algorithms and solving them with various pathfinding techniques. Built with Raylib for interactive visualization and real-time algorithm demonstration.

## Project Description

This application provides an interactive interface for:
- **Maze Generation**: Create mazes using DFS, Prim's, or Kruskal's algorithms
- **Pathfinding**: Solve mazes using DFS, BFS, or A* algorithms
- **Customization**: Adjust colors, cell sizes, border thickness, and animation speed
- **Visualization**: Real-time step-by-step visualization of algorithm execution

The project has been modularized into a clean, maintainable structure with all bugs fixed and proper separation of concerns.

## Repository Structure

```
maze/
├── src/
│   ├── main.cpp                    # Application entry point
│   ├── core/                       # Core data structures
│   │   ├── Cell.h / Cell.cpp      # Cell class (maze cell representation)
│   │   └── DisjointSet.h / DisjointSet.cpp  # Union-Find data structure
│   ├── maze/                       # Maze logic
│   │   ├── Maze.h / Maze.cpp      # Main maze class with algorithms
│   ├── ui/                         # User interface components
│   │   ├── Button.h / Button.cpp  # Custom button component
│   │   ├── MazeSettings.h / MazeSettings.cpp  # Settings UI
│   │   └── UI.h / UI.cpp          # Main UI controller
│   ├── utils/                      # Utility files
│   │   └── Constants.h            # Screen dimensions and constants
│   ├── Fonts/                     # Font resources
│   │   ├── Godshomedemo-K794e.ttf
│   │   ├── FeelfreePersonalUseRegular-lg2Bw.ttf
│   │   ├── LoveBox.ttf
│   │   └── Paintingwithchocolate-K5mo.ttf
│   └── images/                     # Image resources
│       ├── mazwWiz.png            # Logo
│       ├── 0-7.png               # Star decorations
│       └── sss.png
├── lib/                            # DLL dependencies (Windows)
│   ├── libgcc_s_dw2-1.dll
│   └── libstdc++-6.dll
├── Makefile                        # Build configuration
├── CODE_DOCUMENTATION.md           # Detailed code documentation
├── MODULARIZATION_SUMMARY.md       # Summary of modularization changes
└── README.md                       # This file
```

## Installation

### Prerequisites

- **C++ Compiler**: GCC (MinGW on Windows) or Clang
- **Raylib**: Version 5.0 or higher
- **Make**: For building the project (or use your IDE's build system)

### Windows Installation

1. **Install Raylib**:
   - Download Raylib from [raylib.com](https://www.raylib.com/)
   - Extract to a location (e.g., `C:/raylib`)
   - Update the `RAYLIB_PATH` variable in `Makefile` if needed

2. **Install MinGW-w64** (if not already installed):
   - Download from [MinGW-w64](https://www.mingw-w64.org/)
   - Add to PATH or update `COMPILER_PATH` in `Makefile`

3. **Clone/Download the repository**:
   ```bash
   git clone <repository-url>
   cd maze
   ```

4. **Build the project**:
   ```bash
   make
   ```

   Or use your IDE (VS Code, Visual Studio, etc.) to build and run.

### Linux Installation

1. **Install dependencies**:
   ```bash
   sudo apt-get install build-essential libraylib-dev
   ```

2. **Build the project**:
   ```bash
   make
   ```

### macOS Installation

1. **Install dependencies**:
   ```bash
   brew install raylib
   ```

2. **Build the project**:
   ```bash
   make
   ```

## How to Use

### Running the Application

1. **Build the project** (see Installation section)
2. **Run the executable**:
   ```bash
   ./game  # or game.exe on Windows
   ```

### Using the Interface

#### Main Menu
- **Generate**: Start generating a new maze
- **Maze Setting**: Customize colors, sizes, and speeds
- **Exit**: Close the application

#### Maze Generation
Once in the maze view, select a generation algorithm:
- **DFS**: Depth-First Search (creates long, winding paths)
- **PRIM**: Prim's Algorithm (creates more uniform mazes)
- **ELLER**: Kruskal's Algorithm (creates unbiased mazes)

#### Pathfinding
After generation completes, select a solving algorithm:
- **DFS**: Depth-First Search solver
- **2**: Breadth-First Search (finds shortest path)
- **3**: A* Algorithm (optimal pathfinding with heuristic)

#### Customization Menu
- **Choose Cell Size**: Adjust cell width (10-150 pixels)
- **Choose Border Width**: Adjust border thickness (0.1-0.4)
- **Choose Creation Speed**: Control animation speed (0.0-0.1 seconds)
- **Color Pickers**: Customize wall, cell, visited, and backtracked colors
- **Reset Settings**: Restore default settings
- **Reset Maze**: Regenerate maze with current settings

### Controls
- **Mouse**: Click buttons and interact with UI elements
- **Back Button**: Return to main menu from any screen

## Configuration

### Build Configuration

Edit `Makefile` to customize:
- `RAYLIB_PATH`: Path to Raylib installation
- `COMPILER_PATH`: Path to compiler (Windows)
- `BUILD_MODE`: DEBUG or RELEASE
- `PLATFORM`: PLATFORM_DESKTOP, PLATFORM_RPI, etc.

### Runtime Configuration

Constants can be modified in `src/utils/Constants.h`:
- `screenWidth`, `screenHeight`: Window dimensions
- `mazeWidth`, `mazeHeight`: Maze area dimensions

### Resource Paths

All resource paths are relative:
- Fonts: `src/Fonts/`
- Images: `src/images/`

Ensure these directories exist relative to the executable when running.

## Features

### Maze Generation Algorithms
- **Depth-First Search (DFS)**: Recursive backtracking algorithm
- **Prim's Algorithm**: Randomized minimum spanning tree approach
- **Kruskal's Algorithm**: Union-Find based approach

### Pathfinding Algorithms
- **DFS Solver**: Stack-based traversal
- **BFS Solver**: Queue-based traversal (guarantees shortest path)
- **A* Solver**: Heuristic-based optimal pathfinding

### Customization Options
- 24 predefined colors for walls, cells, visited cells, and backtracked cells
- Adjustable cell size (10-150 pixels)
- Adjustable border thickness (0.1-0.4 relative to cell width)
- Adjustable animation speed (0.0-0.1 seconds per step)

## Technical Details

- **Language**: C++ (C++14 standard)
- **Graphics Library**: Raylib 5.0+
- **Build System**: Makefile-based
- **Architecture**: Modular OOP design
- **Platform**: Windows (primary), Linux, macOS (supported)

## Bug Fixes

All identified bugs have been fixed:
- ✅ Syntax errors (double plus operator)
- ✅ Index calculation bugs
- ✅ Exit index calculation in pathfinding
- ✅ Unreachable code removed
- ✅ Flag reset issues (pass by reference)
- ✅ Missing return statements
- ✅ Incorrect UI labels
- ✅ Hardcoded file paths (now relative)
- ✅ Debug output removed
- ✅ Random seed initialization
- ✅ Memory safety improvements

See `CODE_DOCUMENTATION.md` and `MODULARIZATION_SUMMARY.md` for details.

## License and Attribution

### Raylib
This project uses [Raylib](https://www.raylib.com/), a simple and easy-to-use library to enjoy videogames programming.

**Raylib License**: 
```
Copyright (c) 2013-2023 Ramon Santamaria (@raysan5)

This software is provided "as-is", without any express or implied warranty. 
In no event will the authors be held liable for any damages arising from the use of this software.

Permission is granted to anyone to use this software for any purpose, including commercial 
applications, and to alter it and redistribute it freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not claim that you 
   wrote the original software. If you use this software in a product, an acknowledgment 
   in the product documentation would be appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be misrepresented 
   as being the original software.

3. This notice may not be removed or altered from any source distribution.
```

### Fonts
The project includes custom fonts:
- **Godshomedemo-K794e.ttf**: Primary UI font
- **FeelfreePersonalUseRegular-lg2Bw.ttf**
- **LoveBox.ttf**
- **Paintingwithchocolate-K5mo.ttf**

Font licenses should be checked individually if redistributing.

### Project Code
This project code is provided as-is for educational and demonstration purposes.

## Contributing

Contributions are welcome! Please ensure:
- Code follows the existing modular structure
- All bugs are fixed before submitting
- Documentation is updated accordingly

## Documentation

- **CODE_DOCUMENTATION.md**: Detailed line-by-line code analysis
- **MODULARIZATION_SUMMARY.md**: Summary of modularization and bug fixes
- **README.md**: This file

## Support

For issues or questions:
1. Check `CODE_DOCUMENTATION.md` for detailed code explanations
2. Review `MODULARIZATION_SUMMARY.md` for recent changes
3. Ensure all dependencies are properly installed
4. Verify resource paths are correct

## Acknowledgments

- Raylib community for the excellent graphics library
- Algorithm implementations based on standard computer science algorithms
- Original template structure from Raylib C++ Starter Template
