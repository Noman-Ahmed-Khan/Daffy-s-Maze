#include "Maze.h"
#include <cstdlib>
#include <ctime>
#include <random>
#include <algorithm>
#include <cfloat>
#include <iostream>
#include <functional>

using namespace std;

Maze::Maze(int w, float bWThickness, Color wColour, Color uVCColour) 
    : width(w), borderWidthThickness(bWThickness), wall_Colour(wColour), 
      un_Visited_Cell_Colour(uVCColour) {
    cols = mazeWidth / width;
    rows = mazeHeight / width;
    borderWidth = width*borderWidthThickness;
    initialized = false;
    solving = false;
    creating = true;

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            grid.push_back(Cell(i, j, width, borderWidth, wall_Colour, un_Visited_Cell_Colour));
        }
    }

    current = &grid[0];
    current->setCurrent(true);
    current->visitCell(visited_Cell_Colour);
    primCell.push_back(current);
    cellTrail.push(current);
    kruskalWalls.clear();
    kruskalWallIndex = 0;
    if (kruskalDS) { delete kruskalDS; kruskalDS = nullptr; }
    kruskalInitialized = false;
}

Maze::~Maze() {
    if (kruskalDS) {
        delete kruskalDS;
        kruskalDS = nullptr;
    }
}

void Maze::openPath(Cell* current, Cell* neighbor) {
    if ((current->getx()) - (neighbor->getx()) == 1) {
        current->removeBorders(0);
        neighbor->removeBorders(1);
    } else if ((current->getx()) - (neighbor->getx()) == -1) {
        current->removeBorders(1);
        neighbor->removeBorders(0);
    } else if ((current->gety()) - (neighbor->gety()) == 1) {
        current->removeBorders(2);
        neighbor->removeBorders(3);
    } else if (current->gety() - neighbor->gety() == -1) {
        current->removeBorders(3);
        neighbor->removeBorders(2);
    }
}

void Maze::solveMazeByBFS(vector<Cell>& maze) {
    static queue<Cell*> bfsQueue;
    static vector<int> parent;
    static bool bfsInitialized = false;
    static bool pathFound = false;
    static int exitIndex = -1;

    if (!bfsInitialized) {
        for (size_t i = 0; i < maze.size(); i++) {
            maze[i].unVisitCell();
            maze[i].setColor(WHITE);
        }
        current = &maze[0];
        current->visitCell(visited_Cell_Colour);
        current->setColor(GREEN);
        maze[maze.size() - 1].setColor(GREEN);
        bfsQueue = queue<Cell*>();
        parent.assign(maze.size(), -1);
        bfsQueue.push(current);
        bfsInitialized = true;
        pathFound = false;
        // BUG FIX #3: Fixed exit index calculation - use cols instead of rows
        exitIndex = (maze[maze.size() - 1].getx() * cols) + maze[maze.size() - 1].gety();
    }

    if (!pathFound && !bfsQueue.empty()) {
        Cell* node = bfsQueue.front();
        bfsQueue.pop();
        int nodeIndex = node->getx() * cols + node->gety();

        if (nodeIndex == exitIndex) {
            pathFound = true;
            // Color the path from exit to start
            int idx = nodeIndex;
            while (idx != -1) {
                maze[idx].setColor(GREEN);
                idx = parent[idx];
            }
            return;
        }

        // Explore neighbors
        for (int dir = 0; dir < 4; dir++) {
            int nx = node->getx(), ny = node->gety();
            if (dir == 0) nx--; // left
            if (dir == 1) nx++; // right
            if (dir == 2) ny--; // up
            if (dir == 3) ny++; // down
            int neighborIdx = (nx >= 0 && nx < rows && ny >= 0 && ny < cols) ? nx * cols + ny : -1;
            if (neighborIdx != -1 && !maze[neighborIdx].isVisited() && !node->getBorders(dir)) {
                maze[neighborIdx].visitCell(visited_Cell_Colour);
                maze[neighborIdx].setColor(BLUE);
                parent[neighborIdx] = nodeIndex;
                bfsQueue.push(&maze[neighborIdx]);
            }
        }
    }
    else if (bfsQueue.empty() && !pathFound) {
        bfsInitialized = false; // No path found, reset for next run
    }
}

void Maze::resetAStarSolver() {
    // These must match the static variables in solveMazeByAStar
    struct Node {
        int idx;
        float f, g, h;
        bool operator>(const Node& other) const { return f > other.f; }
    };
    static priority_queue<Node, vector<Node>, greater<Node>> openSet;
    static vector<float> gScore, fScore;
    static vector<int> parent;
    static vector<bool> inOpenSet;
    static bool aStarInitialized = false;
    static bool pathFound = false;
    static int exitIndex = -1;

    // Reset all static variables
    openSet = priority_queue<Node, vector<Node>, greater<Node>>();
    gScore.clear();
    fScore.clear();
    parent.clear();
    inOpenSet.clear();
    aStarInitialized = false;
    pathFound = false;
    exitIndex = -1;
}

void Maze::solveMazeByAStar(vector<Cell>& maze) {
    struct Node {
        int idx;
        float f, g, h;
        bool operator>(const Node& other) const { return f > other.f; }
    };

    static priority_queue<Node, vector<Node>, greater<Node>> openSet;
    static vector<float> gScore, fScore;
    static vector<int> parent;
    static vector<bool> inOpenSet;
    static bool aStarInitialized = false;
    static bool pathFound = false;
    static int exitIndex = -1;

    if (!aStarInitialized) {
        for (size_t i = 0; i < maze.size(); i++) {
            maze[i].unVisitCell();
            maze[i].setColor(WHITE);
        }
        int rows = mazeHeight / maze[0].getWidth();
        int cols = mazeWidth / maze[0].getWidth();
        int startIdx = 0;
        // BUG FIX #3: Fixed exit index calculation - use cols instead of rows
        exitIndex = (maze[maze.size() - 1].getx() * cols) + maze[maze.size() - 1].gety();

        gScore.assign(maze.size(), FLT_MAX);
        fScore.assign(maze.size(), FLT_MAX);
        parent.assign(maze.size(), -1);
        inOpenSet.assign(maze.size(), false);

        gScore[startIdx] = 0;
        int sx = maze[0].getx(), sy = maze[0].gety();
        int ex = maze[maze.size() - 1].getx(), ey = maze[maze.size() - 1].gety();
        float h = abs(sx - ex) + abs(sy - ey);
        fScore[startIdx] = h;

        openSet = priority_queue<Node, vector<Node>, greater<Node>>();
        openSet.push({startIdx, h, 0, h});
        inOpenSet[startIdx] = true;

        maze[startIdx].visitCell(visited_Cell_Colour);
        maze[startIdx].setColor(GREEN);
        maze[exitIndex].setColor(GREEN);

        aStarInitialized = true;
        pathFound = false;
    }

    if (!pathFound && !openSet.empty()) {
        Node currentNode = openSet.top();
        openSet.pop();
        int nodeIndex = currentNode.idx;
        inOpenSet[nodeIndex] = false;

        if (nodeIndex == exitIndex) {
            pathFound = true;
            int idx = nodeIndex;
            while (idx != -1) {
                maze[idx].setColor(GREEN);
                idx = parent[idx];
            }
            return;
        }

        int rows = mazeHeight / maze[0].getWidth();
        int cols = mazeWidth / maze[0].getWidth();

        for (int dir = 0; dir < 4; dir++) {
            int nx = maze[nodeIndex].getx(), ny = maze[nodeIndex].gety();
            if (dir == 0) nx--; // left
            if (dir == 1) nx++; // right
            if (dir == 2) ny--; // up
            if (dir == 3) ny++; // down
            int neighborIdx = (nx >= 0 && nx < rows && ny >= 0 && ny < cols) ? nx * cols + ny : -1;
            if (neighborIdx != -1 && !maze[nodeIndex].getBorders(dir)) {
                float tentative_g = gScore[nodeIndex] + 1;
                if (tentative_g < gScore[neighborIdx]) {
                    parent[neighborIdx] = nodeIndex;
                    gScore[neighborIdx] = tentative_g;
                    int ex = maze[exitIndex].getx(), ey = maze[exitIndex].gety();
                    float h = abs(nx - ex) + abs(ny - ey);
                    fScore[neighborIdx] = tentative_g + h;
                    if (!inOpenSet[neighborIdx]) {
                        openSet.push({neighborIdx, fScore[neighborIdx], tentative_g, h});
                        inOpenSet[neighborIdx] = true;
                        maze[neighborIdx].visitCell(visited_Cell_Colour);
                        maze[neighborIdx].setColor(ORANGE);
                    }
                }
            }
        }
    } else if (openSet.empty() && !pathFound) {
        aStarInitialized = false; // No path found, reset for next run
    }
}

void Maze::solveMazeByDFS(vector<Cell>& maze) {
    if(!initialized){
        for(size_t i=0 ;  i<maze.size() ; i++){
            maze[i].unVisitCell();
            maze[i].setColor(WHITE);
        }
        current=&maze[0];
        current->visitCell(visited_Cell_Colour);
        current->setColor(GREEN);
        maze[maze.size()-1].setColor(GREEN);
        flood.push(current);
        initialized=true;
    }

    if(!solving){
        int currentIndex=(current->getx()*cols)+current->gety();
        int exitIndex=(maze[maze.size()-1].getx()*cols)+maze[maze.size()-1].gety();
        if(currentIndex==exitIndex){
            solving=true;
        }
    }

    if(!solving){
        int neighbor=current->getNeighbor(maze, rows, cols, false);
        if(neighbor>-1 && !maze[neighbor].isVisited()){
            current=&maze[neighbor];
            current->visitCell(visited_Cell_Colour);
            current->setColor(BLUE);
            flood.push(current);

        } else if(!flood.empty()){
            flood.pop();
            if(!flood.empty()){                                       
                current=flood.top();
            }
        } 
    } else if(!flood.empty()){
        flood.pop();
        if(!flood.empty()){
            current->setColor(GREEN);
            current=flood.top();
        }
    }
}

pair<Cell, int> Maze::getRandomPrimCellIndex() {
    int CellIndex = rand() % primCell.size();
    int CellIndexNeighbor = primCell[CellIndex]->getNeighbor(grid, rows, cols, true);
    if (CellIndexNeighbor == -1) {
        primCell.erase(primCell.begin() + CellIndex);
    }
    return pair<Cell, int>(*primCell[CellIndex], CellIndexNeighbor);
}

void Maze::generateMazeByPrim() {
    // BUG FIX #12: Added safety check for empty vector
    if (!primCell.empty()) {
        pair<Cell, int> cellAndIndex = getRandomPrimCellIndex();
        if (cellAndIndex.second > -1 && !primCell.empty()) {
            openPath(primCell.back(), &grid[cellAndIndex.second]);
            current->setCurrent(false);
            current = &grid[cellAndIndex.second];
            current->visitCell(visited_Cell_Colour);
            current->setCurrent(true);
            primCell.push_back(current);
        }
    } else {
        creating = false;
    }
}

void Maze::generateMazeByDFS() {
    int nextCellIndex = current->getNeighbor(grid, rows, cols, true);
    if (nextCellIndex > -1) {
        openPath(current, &grid[nextCellIndex]);
        current->setCurrent(false);
        current = &grid[nextCellIndex];
        current->visitCell(visited_Cell_Colour);
        current->setCurrent(true);
        cellTrail.push(current);
    } else if (!cellTrail.empty()) {
        current->setCurrent(false);
        current->setColor(backtracked_Cell_Colour);
        cellTrail.pop();
        if (!cellTrail.empty()) {
            current = cellTrail.top();
            current->setCurrent(true);
        }
        if (cellTrail.empty()) {
            creating = false;
        }
    }
}

void Maze::generateMazeByKruskal() {
    if (!kruskalInitialized) {
        int totalCells = rows * cols;
        if (kruskalDS) delete kruskalDS;
        kruskalDS = new DisjointSet(totalCells);

        kruskalWalls.clear();
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int idx = i * cols + j;
                if (j < cols - 1)
                    kruskalWalls.push_back({idx, idx + 1, 1});
                if (i < rows - 1)
                    kruskalWalls.push_back({idx, idx + cols, 3});
            }
        }
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(kruskalWalls.begin(), kruskalWalls.end(), g);

        kruskalWallIndex = 0;
        kruskalInitialized = true;
    }

    if (kruskalWallIndex < kruskalWalls.size()) {
        auto& wall = kruskalWalls[kruskalWallIndex];
        int cellA = get<0>(wall);
        int cellB = get<1>(wall);
        if (kruskalDS->find(cellA) != kruskalDS->find(cellB)) {
            openPath(&grid[cellA], &grid[cellB]);
            kruskalDS->unite(cellA, cellB);
            grid[cellA].visitCell(visited_Cell_Colour);
            grid[cellB].visitCell(visited_Cell_Colour);
        }
        kruskalWallIndex++;
    } else {
        for (auto& cell : grid) {
            cell.visitCell(visited_Cell_Colour);
        }
        creating = false;
        kruskalInitialized = false;
        if (kruskalDS) {
            delete kruskalDS;
            kruskalDS = nullptr;
        }
    }
}

void Maze::showGrid() {
    for (size_t i = 0; i < grid.size(); i++) {
        grid[i].show();
    }
}

void Maze::draw(bool& dfs_for_creation, bool& prim_for_creation, bool& eller_for_creation,
                bool& dfs_for_solution, bool& two_for_solution, bool& three_for_solution, 
                float creationSpeed) {
    showGrid();
    if(creating && dfs_for_creation){
        generateMazeByDFS();
    } else if(creating && prim_for_creation){
        generateMazeByPrim();
    } else if(creating && eller_for_creation){
        generateMazeByKruskal();
    } else if(!creating && dfs_for_solution){
        solveMazeByDFS(grid);
    } else if(!creating && two_for_solution){
        solveMazeByBFS(grid);
    } else if(!creating && three_for_solution){
       solveMazeByAStar(grid);
    }
    // BUG FIX #5: Pass flags by reference so they can be modified
    if (!creating) {
        // Maze generation finished, reset creation flags
        dfs_for_creation = false;
        prim_for_creation = false;
        eller_for_creation = false;
    }
    WaitTime(creationSpeed);
}

vector<Cell> Maze::getGrid() { 
    return grid; 
}

bool Maze::isCreating() {
    return creating; 
}

void Maze::set_Cell_Colour(Color temp){
    un_Visited_Cell_Colour = temp;
}

void Maze::set_Wall_Colour(Color temp){
    wall_Colour = temp;
}

void Maze::set_VCell_Colour(Color temp){
    visited_Cell_Colour = temp;
}

void Maze::set_BCell_Colour(Color temp){
    backtracked_Cell_Colour = temp;
}
