# Maze Generation and Pathfinding Application - Detailed Documentation

## Table of Contents
1. [Overview](#overview)
2. [Code Stack](#code-stack)
3. [Architecture](#architecture)
4. [Features](#features)
5. [Line-by-Line Code Analysis](#line-by-line-code-analysis)
6. [Class Structure](#class-structure)
7. [Algorithms Implementation](#algorithms-implementation)
8. [Bugs and Issues](#bugs-and-issues)
9. [Missing Implementations](#missing-implementations)
10. [Theme, Styling and Visual Effects](#theme-styling-and-visual-effects)

---

## Overview

This is a comprehensive maze generation and pathfinding visualization application built in C++ using the Raylib graphics library. The application provides an interactive interface for generating mazes using multiple algorithms and solving them with various pathfinding techniques, all with customizable visual settings.

**Total Lines of Code:** 1,238 lines

---

## Code Stack

### Core Technologies
- **Language:** C++ (C++11/14 standard)
- **Graphics Library:** Raylib (v4.0+)
- **Build System:** Makefile-based compilation
- **Platform:** Windows (with DLL dependencies: libgcc_s_dw2-1.dll, libstdc++-6.dll)

### Standard Library Dependencies
```cpp
#include <iostream>      // I/O operations
#include <vector>        // Dynamic arrays
#include <stack>         // Stack data structure
#include <queue>         // Queue data structure
#include <algorithm>     // STL algorithms (shuffle, etc.)
#include <random>        // Random number generation
#include <cstdlib>       // Standard library functions
#include <ctime>         // Time functions
#include <iomanip>       // Input/output manipulators
#include <tuple>         // Tuple data structure
#include <cfloat>        // Floating point limits
#include <math.h>        // Mathematical functions
```

### External Resources
- **Fonts:** Custom TTF fonts (Godshomedemo-K794e.ttf, FeelfreePersonalUseRegular-lg2Bw.ttf, LoveBox.ttf, Paintingwithchocolate-K5mo.ttf)
- **Images:** PNG textures for logo and decorative elements (0-7.png, mazwWiz.png, sss.png)

---

## Architecture

### Screen Configuration
- **Screen Dimensions:** 1900x1000 pixels
- **Maze Area:** 800x800 pixels (centered)
- **Maze Position:** Centered horizontally with offset calculation: `(screenWidth-mazeWidth)/2`

### Design Pattern
- **Object-Oriented Design:** Classes for modularity
- **State Management:** Boolean flags for UI states and algorithm states
- **Callback System:** Member function pointers for button actions

---

## Features

### 1. Maze Generation Algorithms

#### Depth-First Search (DFS) - Lines 476-497
- **Method:** Recursive backtracking
- **Data Structure:** Stack (`cellTrail`)
- **Characteristics:** Creates long, winding paths with few branches
- **Visual Feedback:** Current cell highlighted in black, visited cells colored, backtracked cells in different color

#### Prim's Algorithm - Lines 451-475
- **Method:** Randomized Prim's algorithm
- **Data Structure:** Vector of frontier cells (`primCell`)
- **Characteristics:** Creates more uniform mazes with better distribution
- **Visual Feedback:** Randomly selects from frontier cells, opens paths progressively

#### Kruskal's Algorithm (ELLER) - Lines 538-584
- **Method:** Union-Find (Disjoint Set) based
- **Data Structure:** DisjointSet structure, vector of walls
- **Characteristics:** Creates mazes with no bias toward any particular pattern
- **Visual Feedback:** Processes walls one at a time, uses union-find to avoid cycles

### 2. Pathfinding Algorithms

#### Depth-First Search Solver - Lines 406-449
- **Method:** Stack-based DFS traversal
- **Data Structure:** Stack (`flood`)
- **Visual States:** 
  - Green: Start and end cells
  - Blue: Currently exploring
  - Green path: Final solution path
- **Line Usage:** 44 lines

#### Breadth-First Search Solver - Lines 226-285
- **Method:** Queue-based BFS traversal
- **Data Structure:** Queue (`bfsQueue`), parent array for path reconstruction
- **Visual States:**
  - Green: Start and end cells
  - Blue: Explored cells
  - Green path: Shortest path (guaranteed)
- **Line Usage:** 60 lines
- **Advantage:** Finds shortest path in unweighted graph

#### A* Algorithm Solver - Lines 311-405
- **Method:** Heuristic-based best-first search
- **Data Structure:** Priority queue, gScore/fScore arrays
- **Heuristic:** Manhattan distance (`abs(sx - ex) + abs(sy - ey)`)
- **Visual States:**
  - Green: Start and end cells
  - Orange: Cells in open set
  - Green path: Optimal path
- **Line Usage:** 95 lines
- **Advantage:** Most efficient pathfinding with heuristic guidance

### 3. Customization Features

#### Color Customization - Lines 692-750
- **24 Predefined Colors:** BLACK, DARKGRAY, MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, DARKBROWN, OFFWHITE, GRAY, RED, GOLD, LIME, BLUE, VIOLET, BROWN, WHITE, LIGHTGRAY, PINK, YELLOW, GREEN, SKYBLUE, PURPLE, BEIGE
- **Customizable Elements:**
  - Wall Color (Lines 727-731)
  - Cell Color (Lines 733-737)
  - Visited Cell Color (Lines 739-744)
  - Backtracked Cell Color (Lines 746-750)
- **Interactive Palette:** 8x3 grid layout with hover effects

#### Size Customization - Lines 754-810
- **Cell Width:** Adjustable from 10 to 150 pixels (Lines 1151)
- **Border Thickness:** Adjustable from 0.1 to 0.4 (relative to cell width) (Lines 1152)
- **Creation Speed:** Adjustable from 0.0 to 0.1 seconds per step (Lines 1163)
- **UI Controls:** Plus/minus buttons with visual feedback

#### Reset Functionality
- **Settings Reset:** Restores default colors and sizes (Lines 1073-1080)
- **Maze Reset:** Regenerates maze with current settings (Lines 1082-1088)

### 4. User Interface

#### Menu System - Lines 1054-1210
- **Main Menu:** Logo display, decorative stars, three main buttons
- **Customization Menu:** Color pickers, size controls, speed adjustment
- **Maze View:** Real-time generation/solving visualization with algorithm selection buttons

#### Custom Button Class - Lines 845-932
- **Features:**
  - Dynamic shadow effect based on mouse position
  - Hover state with color change
  - Member function pointer callbacks
  - Custom font rendering
- **Line Usage:** 88 lines

#### Visual Elements
- **Logo:** Loaded from `mazwWiz.png` (Lines 1012-1014)
- **Decorative Stars:** 50 randomly positioned star textures (0-7.png) (Lines 1016-1040)
- **FPS Display:** Top-left corner (Line 1229)

---

## Line-by-Line Code Analysis

### Constants and Configuration (Lines 1-24)
```cpp
Lines 1-15:   Standard library includes
Lines 16-20:  Direction constants (0=left, 1=right, 2=top, 3=bottom)
Lines 21-24:  Screen and maze dimensions
```

### Cell Class (Lines 27-148)
**Purpose:** Represents a single cell in the maze grid

**Key Methods:**
- **Constructor (Lines 42-48):** Initializes cell with position, size, colors, and borders
- **show() (Lines 50-61):** Renders cell with borders or highlights current cell
- **Index() (Lines 64-69):** Calculates 1D index from 2D coordinates with bounds checking
- **getNeighbor() (Lines 71-120):** Finds unvisited neighbors for generation or accessible neighbors for solving
- **removeBorders() (Lines 122-127):** Removes specific wall (0-3 direction)
- **Color/State Methods (Lines 129-147):** Getters and setters for cell properties

**Line Distribution:**
- Class definition: 122 lines
- Core functionality: ~80 lines
- Helper methods: ~42 lines

### DisjointSet Structure (Lines 149-161)
**Purpose:** Union-Find data structure for Kruskal's algorithm

**Methods:**
- **find() (Lines 154-157):** Path compression for efficient root finding
- **unite() (Lines 158-160):** Union operation

**Line Usage:** 13 lines

### Maze Class (Lines 162-636)
**Purpose:** Main maze generation and solving controller

**Private Members (Lines 163-183):**
- Color settings (5 colors)
- Grid dimensions and cell properties
- Algorithm state variables
- Data structures for each algorithm

**Key Methods:**

#### Generation Methods:
- **generateMazeByDFS() (Lines 476-497):** 22 lines
- **generateMazeByPrim() (Lines 461-475):** 15 lines
- **generateMazeByKruskal() (Lines 538-584):** 47 lines

#### Solving Methods:
- **solveMazeByDFS() (Lines 406-449):** 44 lines
- **solveMazeByBFS() (Lines 226-285):** 60 lines
- **solveMazeByAStar() (Lines 311-405):** 95 lines
- **resetAStarSolver() (Lines 286-310):** 25 lines

#### Utility Methods:
- **openPath() (Lines 210-224):** Removes walls between two cells (15 lines)
- **showGrid() (Lines 585-589):** Renders all cells (5 lines)
- **draw() (Lines 591-614):** Main draw loop with algorithm selection (24 lines)
- **Color setters (Lines 620-631):** 12 lines

**Total Maze Class:** 475 lines

### MazeSettings Class (Lines 638-840)
**Purpose:** UI for maze customization

**Key Methods:**
- **Constructor (Lines 647-690):** Initializes 24 colors and UI rectangles (44 lines)
- **colourPalette() (Lines 692-725):** Interactive color picker (34 lines)
- **choose_Wall_Colour() (Lines 727-731):** 5 lines
- **choose_Cell_Colour() (Lines 733-737):** 5 lines
- **choose_VCell_Colour() (Lines 739-744):** 6 lines
- **choose_BCell_Colour() (Lines 746-750):** 5 lines
- **choose_Width() (Lines 754-810):** Adjustable parameter control with +/- buttons (57 lines)
- **display_Current() (Lines 812-838):** Shows current color settings (27 lines)

**Total MazeSettings Class:** 203 lines

### myButton Class (Lines 845-932)
**Purpose:** Custom interactive button with visual effects

**Key Methods:**
- **Constructor (Lines 868-876):** Initializes button properties and loads font (9 lines)
- **createButton() (Lines 878-890):** Renders button with dynamic shadow (13 lines)
- **mouseHover() (Lines 892-902):** Handles hover state color changes (11 lines)
- **clicked() (Lines 909-916):** Executes callback on click (8 lines)
- **ShowButton() (Lines 917-920):** Public interface (4 lines)
- **Destructor (Lines 929-931):** Cleans up font (3 lines)

**Total myButton Class:** 88 lines

### UI Class (Lines 939-1217)
**Purpose:** Main application controller and state manager

**Private Members (Lines 940-975):**
- 11 button instances
- Maze and MazeSettings objects
- Color variables
- State flags (menu, customization, algorithm selection)
- Texture resources

**Key Methods:**
- **Constructor (Lines 976-1043):** Initializes all buttons, maze, textures, and stars (68 lines)
- **resetCreation() (Lines 1045-1052):** Resets algorithm flags (8 lines)
- **showMenu() / HideMenu() (Lines 1054-1061):** Menu state management (8 lines)
- **ShowCustomizationMenu() / HideCustomizationMenu() (Lines 1063-1071):** Customization state (9 lines)
- **resetSettings() (Lines 1073-1080):** Restores defaults (8 lines)
- **resetMaze() (Lines 1082-1088):** Regenerates maze (7 lines)
- **Algorithm toggles (Lines 1100-1118):** 6 methods, 19 lines total
- **start() (Lines 1119-1210):** Main render loop (92 lines)
  - Menu rendering: Lines 1120-1143 (24 lines)
  - Customization rendering: Lines 1144-1168 (25 lines)
  - Maze view rendering: Lines 1169-1208 (40 lines)

**Total UI Class:** 279 lines

### Main Function (Lines 1219-1237)
**Purpose:** Application entry point

**Flow:**
1. Initialize window (1900x1000, "Menu") - Line 1221
2. Set target FPS to 1000 - Line 1222
3. Create UI instance - Line 1224
4. Main loop (Lines 1225-1232):
   - Check window close and exit flag
   - Clear background
   - Render UI
   - Display FPS
5. Cleanup and exit - Lines 1234-1236

**Total Main Function:** 19 lines

---

## Class Structure

### Inheritance Hierarchy
```
No inheritance - composition-based design
```

### Class Relationships
```
UI
├── Contains: Maze
├── Contains: MazeSettings
├── Contains: 11x myButton
└── Manages: Textures, Colors, State

Maze
├── Contains: vector<Cell>
├── Contains: DisjointSet* (for Kruskal)
└── Uses: stack, queue, priority_queue

Cell
└── Standalone entity

MazeSettings
└── Standalone utility class

myButton
└── Standalone UI component
```

### Memory Management
- **Stack Allocation:** Most objects (Cell, Maze, UI, etc.)
- **Dynamic Allocation:** DisjointSet pointer in Maze class (Lines 182, 542, 580)
- **Resource Management:** Raylib textures and fonts loaded/unloaded in constructors/destructors

---

## Algorithms Implementation

### Maze Generation Complexity

#### DFS Generation
- **Time Complexity:** O(n) where n = number of cells
- **Space Complexity:** O(n) for stack
- **Implementation:** Lines 476-497

#### Prim's Algorithm
- **Time Complexity:** O(n log n) average case
- **Space Complexity:** O(n) for frontier vector
- **Implementation:** Lines 451-475

#### Kruskal's Algorithm
- **Time Complexity:** O(n log n) with union-find
- **Space Complexity:** O(n) for disjoint set
- **Implementation:** Lines 538-584

### Pathfinding Complexity

#### DFS Solver
- **Time Complexity:** O(n) worst case
- **Space Complexity:** O(n) for stack
- **Path Quality:** Not guaranteed shortest
- **Implementation:** Lines 406-449

#### BFS Solver
- **Time Complexity:** O(n)
- **Space Complexity:** O(n) for queue
- **Path Quality:** Guaranteed shortest (unweighted)
- **Implementation:** Lines 226-285

#### A* Solver
- **Time Complexity:** O(n log n) with good heuristic
- **Space Complexity:** O(n) for priority queue
- **Path Quality:** Optimal with admissible heuristic
- **Heuristic:** Manhattan distance (admissible)
- **Implementation:** Lines 311-405

---

## Code Statistics Summary

| Component | Lines | Percentage |
|-----------|-------|------------|
| Cell Class | 122 | 9.9% |
| DisjointSet | 13 | 1.0% |
| Maze Class | 475 | 38.4% |
| MazeSettings Class | 203 | 16.4% |
| myButton Class | 88 | 7.1% |
| UI Class | 279 | 22.5% |
| Main Function | 19 | 1.5% |
| Includes/Constants | 39 | 3.2% |
| **Total** | **1,238** | **100%** |

### Algorithm Distribution
- **Generation Algorithms:** 84 lines (6.8%)
- **Solving Algorithms:** 199 lines (16.1%)
- **UI/Visualization:** 570 lines (46.0%)
- **Core Logic:** 385 lines (31.1%)

---

## Key Design Patterns

1. **State Machine Pattern:** Boolean flags manage UI states (menu, customization, creation, solving)
2. **Callback Pattern:** Member function pointers for button actions
3. **Strategy Pattern:** Multiple algorithms for generation and solving
4. **Observer Pattern:** Visual feedback during algorithm execution
5. **Resource Management:** RAII principles for Raylib resources

---

## File Structure

### Modular Structure (Current)

```
src/
├── main.cpp - Application entry point
├── core/
│   ├── Cell.h / Cell.cpp - Cell class implementation
│   └── DisjointSet.h / DisjointSet.cpp - Union-Find data structure
├── maze/
│   ├── Maze.h / Maze.cpp - Main maze class with generation and solving
├── ui/
│   ├── Button.h / Button.cpp - Custom button component
│   ├── MazeSettings.h / MazeSettings.cpp - Settings UI
│   └── UI.h / UI.cpp - Main UI controller
├── utils/
│   └── Constants.h - Screen dimensions and constants
├── Fonts/
│   ├── Godshomedemo-K794e.ttf (Primary UI font)
│   ├── FeelfreePersonalUseRegular-lg2Bw.ttf
│   ├── LoveBox.ttf
│   └── Paintingwithchocolate-K5mo.ttf
└── images/
    ├── mazwWiz.png (Logo)
    ├── 0-7.png (Star decorations)
    └── sss.png
```

### Legacy Structure (Before Modularization)

Previously, all code was in a single `main.cpp` file (1,238 lines).

---

## Performance Considerations

- **Target FPS:** 1000 (Line 1222) - Very high for smooth animation
- **Creation Speed:** Adjustable delay (0.0-0.1s) for visualization control
- **Grid Size:** Dynamically calculated based on cell width (Lines 186-187)
- **Memory:** Efficient use of vectors and stacks, minimal dynamic allocation

---

## Future Enhancement Opportunities

1. **Additional Algorithms:**
   - Wilson's Algorithm
   - Recursive Division
   - Eller's Algorithm (proper implementation)

2. **Features:**
   - Save/Load mazes
   - Export as image
   - Step-by-step algorithm explanation
   - Performance metrics display
   - Multiple maze sizes presets

3. **Code Improvements:**
   - Separate header files for classes
   - Configuration file support
   - Better error handling
   - Cross-platform path handling

---

## Bugs and Issues

This section documents all identified bugs, logical errors, and potential issues in the codebase.

### ✅ All Critical Bugs Fixed

All critical bugs have been fixed in the modularized codebase:

1. ✅ **Syntax Error: Double Plus Operator** - Fixed in `Cell.cpp` line 57
2. ✅ **Index Calculation Bug** - Fixed in `Cell.cpp` line 68 (uses `cols` instead of `rows`)
3. ✅ **Exit Index Calculation Bug** - Fixed in `Maze.cpp` (BFS and A* solvers now use `cols`)

### ✅ All Logic Bugs Fixed

4. ✅ **Unreachable Code** - Removed from `Cell.cpp`
5. ✅ **Flag Reset Ineffectiveness** - Fixed by passing flags by reference in `Maze::draw()`
6. ✅ **Missing Return Statement** - Added return statement in `Cell::getNeighbor()` forCreation path

### ✅ All UI/Display Bugs Fixed

7. ✅ **Incorrect Text Labels** - Fixed in `MazeSettings.cpp` (correct labels for visited and backtracked cell colors)
8. ✅ **Typo in Comment** - Fixed in `Cell.cpp` (corrected "neigbors" to "neighbors")

### ✅ All Runtime Issues Fixed

9. ✅ **Hardcoded File Paths** - Replaced with relative paths in:
   - `Button.cpp` - Font loading
   - `MazeSettings.cpp` - Font loading
   - `UI.cpp` - Image loading (logo and stars)

10. ✅ **Debug Output** - Removed `cout` statement from `UI.cpp` constructor

11. ✅ **Uninitialized Random Seed** - Added `srand(time(nullptr))` in `UI.cpp` constructor

12. ✅ **Memory Leak Risk in Prim's Algorithm** - Added safety check for empty vector in `Maze::generateMazeByPrim()`

### Summary of Bug Fixes

| Bug # | Severity | Type | Status |
|-------|----------|------|--------|
| 1 | Critical | Syntax | ✅ Fixed |
| 2 | Critical | Logic | ✅ Fixed |
| 3 | Critical | Logic | ✅ Fixed |
| 4 | Medium | Dead Code | ✅ Fixed |
| 5 | Medium | Logic | ✅ Fixed |
| 6 | High | Logic | ✅ Fixed |
| 7 | Low | UI | ✅ Fixed |
| 8 | Very Low | Documentation | ✅ Fixed |
| 9 | High | Portability | ✅ Fixed |
| 10 | Low | Cleanliness | ✅ Fixed |
| 11 | Medium | Logic | ✅ Fixed |
| 12 | Medium | Safety | ✅ Fixed |

**All bugs have been successfully fixed in the modularized codebase.**

---

## Missing Implementations

This section documents incomplete features, commented-out code, and planned but unimplemented functionality.

### 1. Commented-Out Kruskal Implementation (Lines 500-536)
**Status:** Old implementation exists but is commented out  
**Current State:** A new step-by-step implementation exists (Lines 538-584), but the original batch implementation is preserved in comments  
**Reason:** Likely replaced to support step-by-step visualization  
**Impact:** None - new implementation works, but old code should be removed for cleanliness

### 2. Incomplete `runFunc` Method (Lines 922-926)
**Location:** `myButton` class  
**Issue:** Method signature exists but implementation is incomplete
```cpp
void runFunc(void (*funcPtr)()) {
    if (CheckCollisionPointRec(GetMousePosition(), buttonRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        void (*funcPtr)();  // Declares but never calls
    }
}
```
**Status:** Method is defined but never used, and doesn't actually call the function pointer  
**Impact:** Unused code, potential confusion  
**Recommendation:** Remove or implement properly

### 3. Eller's Algorithm Mislabeling
**Location:** UI button label (Line 983)  
**Issue:** Button labeled "ELLER" but implements Kruskal's algorithm  
**Current Implementation:** Kruskal's algorithm (union-find based)  
**True Eller's Algorithm:** Row-by-row generation algorithm (not implemented)  
**Impact:** Misleading button label  
**Status:** Algorithm works but name is incorrect

### 4. Missing Solver Reset Functions
**Location:** `Maze` class  
**Issue:** Only A* solver has a reset function (`resetAStarSolver()` at Line 286)  
**Missing:**
- `resetBFSSolver()` - BFS uses static variables that persist
- `resetDFSSolver()` - DFS uses static variables that persist  
**Impact:** Solvers may not reset properly when maze is regenerated  
**Status:** Partial implementation - only A* is reset

### 5. Missing Path Visualization for DFS Solver
**Location:** `solveMazeByDFS()` (Lines 406-449)  
**Issue:** DFS solver finds the path but doesn't clearly mark the final solution path like BFS and A* do  
**Current Behavior:** Colors cells blue during exploration, green when backtracking  
**Missing:** Clear final path highlighting from start to end  
**Impact:** Harder to see the solution path

### 6. No Error Handling for File Loading
**Location:** Multiple locations (Lines 649, 873, 1012, 1035)  
**Issue:** No checks if fonts/images fail to load  
**Impact:** Application may crash if resources are missing  
**Status:** No validation implemented

### 7. Missing Input Validation
**Location:** `choose_Width()` method (Lines 754-810)  
**Issue:** No validation for edge cases:
- What if width becomes 0?
- What if borderThickness exceeds width?
- What if creationSpeed is negative?  
**Impact:** Potential crashes or visual glitches  
**Status:** Basic bounds checking exists but no edge case handling

### 8. No Save/Load Functionality
**Status:** Completely missing  
**Impact:** Users cannot save mazes or settings  
**Recommendation:** Implement serialization for:
- Maze state (grid, walls)
- Color settings
- Size preferences

### 9. No Export Functionality
**Status:** Completely missing  
**Impact:** Cannot export mazes as images  
**Recommendation:** Use Raylib's `ExportImage()` or `TakeScreenshot()`

### 10. Missing Algorithm Explanation/Info
**Status:** No documentation within the app  
**Impact:** Users may not understand differences between algorithms  
**Recommendation:** Add info tooltips or help screen

### 11. No Performance Metrics Display
**Status:** Missing  
**Impact:** Cannot see algorithm performance (cells visited, time taken, path length)  
**Recommendation:** Add metrics overlay during solving

### 12. Incomplete Color Customization
**Status:** Partial  
**Missing:**
- No RGB color picker (only 24 predefined colors)
- No alpha/transparency control
- No custom color saving  
**Impact:** Limited customization options

### 13. Missing Maze Size Presets
**Status:** Not implemented  
**Issue:** Users must manually adjust cell width to change maze size  
**Recommendation:** Add preset buttons (Small, Medium, Large, Custom)

### 14. No Undo/Redo Functionality
**Status:** Missing  
**Impact:** Cannot revert changes or settings  
**Recommendation:** Implement state history

### 15. Missing Keyboard Shortcuts
**Status:** No keyboard controls implemented  
**Impact:** Mouse-only interaction, less efficient  
**Recommendation:** Add shortcuts for:
- Space: Pause/Resume
- R: Reset maze
- S: Save settings
- 1-3: Select generation algorithm
- 4-6: Select solving algorithm

### 16. No Fullscreen Mode
**Status:** Missing  
**Impact:** Fixed window size only  
**Recommendation:** Add fullscreen toggle (F11)

### 17. Missing Animation Speed Presets
**Status:** Partial  
**Issue:** Slider exists but no quick presets (Slow, Normal, Fast, Instant)  
**Impact:** Less user-friendly

### 18. No Multi-threading Support
**Status:** Missing  
**Impact:** UI may freeze during large maze generation  
**Recommendation:** Separate generation thread

### Summary of Missing Features

| Feature | Priority | Complexity | Impact |
|---------|----------|------------|--------|
| Fix Index Calculation Bugs | Critical | Low | High |
| Solver Reset Functions | High | Low | Medium |
| Error Handling | High | Medium | High |
| Save/Load Mazes | Medium | High | Medium |
| Export Images | Medium | Low | Low |
| Keyboard Shortcuts | Medium | Medium | Medium |
| Algorithm Info | Low | Low | Low |
| Performance Metrics | Low | Medium | Low |

---

## Theme, Styling and Visual Effects

This section provides a comprehensive overview of all visual design elements, styling choices, and visual effects implemented in the application.

### Overall Theme

**Design Philosophy:** Modern, playful, and educational  
**Color Scheme:** Light and vibrant with customizable options  
**Visual Style:** Clean UI with decorative elements and smooth animations

### Color Palette

#### Default Color Scheme
- **Background:** White (`WHITE`) - Clean, minimal
- **Primary Buttons:** Sky Blue (`SKYBLUE`) - RGB(135, 206, 250)
- **Button Shadows:** Yellow with transparency (`Color{255, 237, 100, 200}`) - Warm, friendly
- **Button Hover:** Purple tint (`Color{200, 191, 255, 255}`) - Interactive feedback
- **Text:** Black (`BLACK`) - High contrast, readable
- **Walls:** Black (`BLACK`) - Default, customizable
- **Cells:** White (`WHITE`) - Default, customizable
- **Visited Cells:** Light Purple (`Color{200, 191, 255, 255}`) - Default
- **Backtracked Cells:** Light Pink (`Color{255, 191, 246, 255}`) - Default

#### Available Custom Colors (24 Total)
Located in `MazeSettings` constructor (Lines 651-654):
1. **BLACK** - Pure black
2. **DARKGRAY** - Dark gray
3. **MAROON** - Dark red
4. **ORANGE** - Orange
5. **DARKGREEN** - Dark green
6. **DARKBLUE** - Dark blue
7. **DARKPURPLE** - Dark purple
8. **DARKBROWN** - Dark brown
9. **OFFWHITE** - Custom `Color{255,249,246,225}` - Warm white with slight transparency
10. **GRAY** - Medium gray
11. **RED** - Bright red
12. **GOLD** - Gold/yellow
13. **LIME** - Bright green
14. **BLUE** - Standard blue
15. **VIOLET** - Violet/purple
16. **BROWN** - Brown
17. **WHITE** - Pure white
18. **LIGHTGRAY** - Light gray
19. **PINK** - Pink
20. **YELLOW** - Yellow
21. **GREEN** - Green
22. **SKYBLUE** - Sky blue
23. **PURPLE** - Purple
24. **BEIGE** - Beige

#### Color Palette Layout
- **Grid:** 8 columns × 3 rows (Lines 696-698)
- **Spacing:** 7 pixels between color swatches (Line 696)
- **Size:** 45×45 pixels per swatch (Lines 686-687)
- **Position:** Dynamically calculated based on input coordinates

### Typography

#### Primary Font
- **Font:** `Godshomedemo-K794e.ttf` (Line 649, 873)
- **Usage:** All UI text, buttons, labels
- **Style:** Decorative, hand-drawn aesthetic
- **Size Range:** 25-40 pixels
- **Rendering:** `DrawTextEx()` with custom spacing (0.5-1.0)

#### Font Loading
- **Location:** Hardcoded path `"D:/projects/maze/src/Fonts/Godshomedemo-K794e.ttf"`
- **Lifecycle:** Loaded in constructors, unloaded in destructors
- **Fallback:** None - application may crash if font missing

#### Text Styling
- **Button Text:** Custom font, size 30-40px, centered
- **Labels:** Custom font, size 25px, left-aligned
- **FPS Display:** Default font, size varies, top-left corner
- **Color Names:** Custom font, size 25px, appears on hover

### Button Design and Effects

#### Button Structure
**Class:** `myButton` (Lines 845-932)  
**Components:**
1. Main button rectangle
2. Dynamic shadow rectangle
3. Text label
4. Hover state

#### Visual Properties
- **Shape:** Rounded rectangles (`DrawRectangleRounded` with radius 1000 - effectively fully rounded)
- **Default Colors:**
  - Button: Sky Blue (`SKYBLUE`)
  - Shadow: Yellow with 200 alpha (`Color{255, 237, 100, 200}`)
  - Text: Yellow with 200 alpha (`Color{255, 237, 100, 200}`)
- **Hover Colors:**
  - Button: Purple (`Color{200, 191, 255, 255}`)
  - Shadow: Light pink (`Color{255, 200, 200, 200}`)
  - Text: Light pink (`Color{255, 200, 200, 200}`)

#### Dynamic Shadow Effect (Lines 878-884)
**Implementation:** Interactive shadow that follows mouse position
```cpp
// Shadow position calculated based on mouse distance from button center
float xShadowPosition = ((((GetMouseX()-(xButtonPosition+buttonWidth/2))/buttonWidth)*shadowThickness)+xButtonPosition);
float yShadowPosition = ((((GetMouseY()-(yButtonPosition+buttonHeight/2))/buttonHeight)*shadowThickness)+yButtonPosition);

// When hovering, shadow moves closer (shadowThickness*2 offset)
xShadowPosition = (CheckCollisionPointRec(GetMousePosition(), buttonRect))? 
    xButtonPosition+shadowThickness*2 : xShadowPosition;
```

**Effect:** Creates 3D depth illusion, shadow "pulls" toward mouse cursor  
**Shadow Thickness:** 2-4 pixels (configurable per button)

#### Hover Effect (Lines 892-902)
**Trigger:** Mouse cursor over button rectangle  
**Visual Changes:**
- Button color shifts from Sky Blue to Purple
- Shadow color shifts from Yellow to Light Pink
- Text color shifts from Yellow to Light Pink
- Shadow position moves closer to button (2× thickness)

**Smoothness:** Instant (no animation transition)

### Maze Visualization Effects

#### Cell Rendering
**Method:** `Cell::show()` (Lines 50-61)

**Normal Cell:**
- Filled rectangle with `cell_Colour`
- Four border rectangles (if borders exist) with `wall_Colour`
- Border width: `borderWidth` (calculated as `width * borderWidthThickness`)

**Current Cell (During Generation):**
- Solid black rectangle (`BLACK`)
- Overrides all other colors
- Used to highlight active cell during maze generation

#### Border Rendering
**Implementation:** Four separate rectangles for each wall
- **Left Wall (border[0]):** Vertical rectangle at left edge
- **Right Wall (border[1]):** Vertical rectangle at right edge  
- **Top Wall (border[2]):** Horizontal rectangle at top edge
- **Bottom Wall (border[3]):** Horizontal rectangle at bottom edge

**Positioning:** Calculated with maze centering offset: `(screenWidth-mazeWidth)/2`

#### Pathfinding Color States

**DFS Solver:**
- **Start/End:** Green (`GREEN`)
- **Exploring:** Blue (`BLUE`)
- **Solution Path:** Green (`GREEN`) - backtracked path

**BFS Solver:**
- **Start/End:** Green (`GREEN`)
- **Explored:** Blue (`BLUE`)
- **Solution Path:** Green (`GREEN`) - shortest path

**A* Solver:**
- **Start/End:** Green (`GREEN`)
- **Open Set:** Orange (`ORANGE`)
- **Solution Path:** Green (`GREEN`) - optimal path

### Decorative Elements

#### Logo Display
**Image:** `mazwWiz.png` (Lines 1012-1014)  
**Position:** Centered horizontally, upper third vertically
- X: `screenWidth/3-150`
- Y: `screenHeight/3-logoTexture.height/3-50`
**Rendering:** `DrawTexture()` with white tint

#### Star Decorations
**Count:** 50 stars (Lines 1016-1040)  
**Images:** `0.png` through `7.png` (8 different star textures, cycled)  
**Layout Algorithm:**
- Random initial positions
- Minimum 200-pixel spacing between stars
- Prevents overlapping
- Positions logged to console (debug output)

**Rendering:** `DrawTexturePro()` with full texture mapping  
**Effect:** Creates starfield background on main menu

### UI Layout and Spacing

#### Screen Organization
- **Total Size:** 1900×1000 pixels
- **Maze Area:** 800×800 pixels, centered horizontally
- **Menu Area:** Full screen with centered elements
- **Settings Area:** Left side (color pickers), Right side (current settings display)

#### Button Positioning
**Main Menu Buttons (Lines 977-980):**
- **Generate:** Centered, Y: `screenHeight/2+100/2`
- **Maze Setting:** Centered, Y: `screenHeight/2+400/2`
- **Exit:** Centered, Y: `screenHeight/2+700/2`
- **Back:** Top-left, X: 30, Y: 70

**Algorithm Selection Buttons (Lines 981-986):**
- **X Positions:** 300, 850, 1400 (evenly spaced)
- **Y Position:** `mazeHeight+30` (below maze)
- **Size:** 200×100 pixels

**Control Buttons:**
- **Reset Settings:** X: 1630, Y: 750
- **Reset Maze:** X: 1630, Y: 70

#### Color Picker Layout
**Wall Color:** Y: 200 (Lines 730)  
**Cell Color:** Y: 400 (Lines 736)  
**Visited Cell Color:** Y: 600 (Lines 743)  
**Backtracked Cell Color:** Y: 800 (Lines 749)

**Spacing:** 200 pixels vertical spacing between pickers

### Interactive Effects

#### Color Palette Hover (Lines 702-723)
**Detection:** `CheckCollisionPointRec()` for each color swatch  
**Visual Feedback:**
- **Normal:** Full opacity (`Fade(colours[i], 1.0f)`)
- **Hover:** Reduced opacity (`Fade(colours[i], 0.6f)`)
- **Hover Border:** White, 6-pixel thickness
- **Hover Indicator:** Black rectangle at bottom (26 pixels from top)
- **Text Display:** Color name appears at specified position

**Selection:** Click detection with `IsMouseButtonDown(MOUSE_LEFT_BUTTON)`

#### Width Control Buttons (Lines 754-810)
**Layout:**
- **Minus Button:** X: 655+PosX, Y: 225+PosY, Size: 80×55
- **Plus Button:** X: 825+PosX, Y: 225+PosY, Size: 80×55
- **Display Box:** Between buttons, 260×65 pixels

**Visual Design:**
- **Background:** Black rectangle (260×65)
- **Foreground:** White rectangle (250×55), 5-pixel inset
- **Buttons:** White/Black color swap on hover
- **Signs:** Rectangles forming + and - symbols
- **Text:** Centered, 30px, black

**Hover Effect:**
- **Normal:** White button, black sign
- **Hover:** Black button, white sign
- **Click Delay:** 0.2 seconds (`WaitTime(0.2)`) to prevent rapid clicking

### Animation and Timing

#### Creation Speed Control
**Parameter:** `creationSpeed` (0.0 to 0.1 seconds)  
**Implementation:** `WaitTime(creationSpeed)` after each step (Line 612)  
**Effect:** Controls visualization speed:
- **0.0:** Instant (no delay)
- **0.1:** Slow, visible step-by-step

#### Frame Rate
**Target FPS:** 1000 (Line 1222)  
**Purpose:** Smooth animation even with delays  
**Effect:** Ensures responsive UI during algorithm visualization

### Visual Feedback States

#### Menu States
1. **Main Menu:**
   - Logo displayed
   - Stars in background
   - Three main buttons visible
   - White background

2. **Customization Menu:**
   - Back button visible
   - Four color pickers
   - Width controls
   - Current settings display
   - Reset button

3. **Maze View:**
   - Maze grid displayed
   - Algorithm selection buttons (context-dependent)
   - Reset maze button
   - Back button

#### Algorithm State Indicators
- **Creating:** Algorithm selection buttons visible
- **Solving:** Solver selection buttons visible
- **Completed:** All cells colored, solution path highlighted

### Current Settings Display (Lines 812-838)
**Location:** Right side of screen  
**Elements:**
- Four color swatches (45×45 pixels)
- Labels with custom font
- Colons as separators
- Black borders (1 pixel)

**Layout:**
- **Wall Colour:** Y: `screenHeight-760`
- **Cell Colour:** Y: `screenHeight-700`
- **Visited Cell Colour:** Y: `screenHeight-640`
- **Backtracked Colour:** Y: `screenHeight-580`

### Special Visual Effects

#### Rounded Corners
**Usage:** All buttons  
**Method:** `DrawRectangleRounded()`  
**Radius:** 1000 (effectively fully rounded, creates pill shape)

#### Transparency Effects
**Usage:** 
- Button shadows (alpha: 200)
- Color palette hover (alpha: 0.6f fade)
- Custom OFFWHITE color (alpha: 225)

#### Text Rendering
**Method:** `DrawTextEx()` with custom font  
**Spacing:** 0.5-1.0 (configurable per text element)  
**Positioning:** Manual centering calculations

### Responsive Design Elements

#### Dynamic Positioning
- Maze centering: `(screenWidth-mazeWidth)/2`
- Button text centering: Manual calculations based on text width
- Color palette: Dynamic grid layout (8 columns)

#### Fixed vs. Dynamic
- **Fixed:** Screen size (1900×1000), button sizes, spacing
- **Dynamic:** Maze grid size (based on cell width), color positions, shadow positions

### Accessibility Considerations

#### Color Contrast
- **Text:** Black on white/light backgrounds (high contrast)
- **Buttons:** Sky blue with yellow text (good contrast)
- **Customizable:** Users can adjust all colors for accessibility

#### Visual Indicators
- Hover states clearly visible
- Button shadows provide depth cues
- Color names displayed on hover
- FPS counter for performance monitoring

### Summary of Visual Effects

| Effect | Location | Implementation | Impact |
|--------|----------|----------------|--------|
| Dynamic Shadow | Buttons | Mouse position calculation | 3D depth |
| Hover Color Change | Buttons, Colors | Color state switching | Interactive feedback |
| Rounded Corners | All buttons | DrawRectangleRounded | Modern aesthetic |
| Transparency | Shadows, Hover | Alpha channel | Layering effect |
| Step Animation | Maze generation | WaitTime delay | Visualization |
| Star Background | Main menu | 50 textured sprites | Decorative |
| Color Fade | Palette hover | Fade() function | Visual feedback |
| Text Centering | All text | Manual calculations | Professional layout |

---

## Conclusion

This is a well-structured, feature-rich maze generation and pathfinding visualization application. The code demonstrates solid understanding of:
- Graph algorithms (DFS, BFS, A*, Prim's, Kruskal's)
- Object-oriented design principles
- Interactive UI development
- Real-time visualization techniques

The application successfully combines educational value (algorithm visualization) with user engagement (customization and interactivity) in a single, cohesive codebase.
