#include "Cell.h"
#include <cstdlib>
#include <ctime>
#include <algorithm>

Cell::Cell() {}

Cell::Cell(int i, int j, float _width, float _borderWidth, Color _wall_Colour, Color _cell_Colour) 
    : x(i), y(j), visited(false), isCurrent(false), width(_width), borderWidth(_borderWidth), 
      wall_Colour(_wall_Colour), cell_Colour(_cell_Colour) {
    for (int i = 0; i < 4; i++) {
        borders[i] = true;
    }
    mainBox = Rectangle {(x * width) + (screenWidth-mazeWidth)/2, y * width, width, width};
}

void Cell::show() {
    if (!isCurrent) {
        DrawRectangleRec(mainBox, cell_Colour);

        if (borders[0]) DrawRectangle(x * width + (screenWidth-mazeWidth)/2, y * width, borderWidth, width, wall_Colour);
        if (borders[1]) DrawRectangle((x * width) + width - borderWidth + (screenWidth-mazeWidth)/2, y * width, borderWidth, width, wall_Colour);
        if (borders[2]) DrawRectangle(x * width + (screenWidth-mazeWidth)/2, y * width, width, borderWidth, wall_Colour);
        // BUG FIX #1: Fixed double plus operator (was: x * width+ +)
        if (borders[3]) DrawRectangle(x * width + (screenWidth-mazeWidth)/2, (y * width) + width - borderWidth, width, borderWidth, wall_Colour);
    } else {
        DrawRectangle(x * width + (screenWidth-mazeWidth)/2, y * width, width, width, BLACK);
    }
}

int Cell::Index(int _x, int _y, int rows, int cols) {
    if (x + _x > rows - 1 || y + _y > cols - 1 || x + _x < 0 || y + _y < 0) {
        return -1;
    }
    // BUG FIX #2: Fixed index calculation - use cols instead of rows for y coordinate
    return ((x + _x) * cols + ((y + _y)));
}

bool Cell::getBorders(int temp) const { 
    return borders[temp]; 
}

int Cell::getNeighbor(const vector<Cell>& grid, int rows, int cols, bool forCreation) {
    neighbors.clear();

    if(forCreation){
        if (Index(-1, 0, rows, cols) != -1 && !grid[Index(-1, 0, rows, cols)].visited) {
            neighbors.push_back(Index(-1, 0, rows, cols));
        }
        if (Index(1, 0, rows, cols) != -1 && !grid[Index(1, 0, rows, cols)].visited) {
            neighbors.push_back(Index(1, 0, rows, cols));
        }
        if (Index(0, -1, rows, cols) != -1 && !grid[Index(0, -1, rows, cols)].visited) {
            neighbors.push_back(Index(0, -1, rows, cols));
        }
        if (Index(0, 1, rows, cols) != -1 && !grid[Index(0, 1, rows, cols)].visited) {
            neighbors.push_back(Index(0, 1, rows, cols));
        }
        // BUG FIX #6: Added missing return statement for creation path
        if (neighbors.size() > 0) {
            return neighbors[rand() % neighbors.size()];
        }
        return -1;
    } else {
        // left neighbors
        if(Index(-1,0,rows,cols)!=-1 && !borders[0] && !grid[Index(-1,0,rows,cols)].visited){
            neighbors.push_back(Index(-1,0,rows,cols));
        }
        
        // right neighbors (BUG FIX #8: Fixed typo "neigbors" -> "neighbors")
        if(Index(1,0,rows,cols)!=-1 && !borders[1] && !grid[Index(1,0,rows,cols)].visited){
            neighbors.push_back(Index(1,0,rows,cols));
        }
        
        // top neighbors
        if(Index(0,-1,rows,cols)!=-1 && !borders[2] && !grid[Index(0,-1,rows,cols)].visited){
            neighbors.push_back(Index(0,-1,rows,cols));
        }
        
        // bottom neighbors
        if(Index(0,1,rows,cols)!=-1 && !borders[3] && !grid[Index(0,1,rows,cols)].visited){
            neighbors.push_back(Index(0,1,rows,cols));
        }
        
        if(neighbors.size()>0){
            return neighbors[(rand()%neighbors.size())];
        }
        return -1;
    }
    // BUG FIX #4: Removed unreachable code (lines 115-119)
}

void Cell::removeBorders(int temp) {
    if (temp == 0) borders[0] = false;
    else if (temp == 1) borders[1] = false;
    else if (temp == 2) borders[2] = false;
    else if (temp == 3) borders[3] = false;
}

void Cell::setCurrent(bool temp) { 
    isCurrent = temp; 
}

void Cell::setColor(Color col) { 
    cell_Colour = col; 
}

bool Cell::isVisited() { 
    return visited; 
}

void Cell::visitCell(Color col) {
    visited = true;
    setColor(col);
}

void Cell::unVisitCell() { 
    visited = false; 
}

void Cell::setIsCurrent(bool temp) { 
    isCurrent = temp; 
}

float Cell::getWidth() { 
    return width; 
}

float Cell::getBorderWidth() { 
    return borderWidth; 
}

int Cell::getx() { 
    return x; 
}

int Cell::gety() { 
    return y; 
}
