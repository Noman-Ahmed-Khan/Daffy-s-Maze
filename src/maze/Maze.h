#ifndef MAZE_H
#define MAZE_H

#include <raylib.h>
#include <vector>
#include <stack>
#include <queue>
#include <tuple>
#include "../core/Cell.h"
#include "../core/DisjointSet.h"
#include "../utils/Constants.h"

using std::vector;
using std::stack;
using std::queue;
using std::pair;
using std::tuple;

class Maze {
private:
    Color un_Visited_Cell_Colour;
    Color visited_Cell_Colour;
    Color backtracked_Cell_Colour;
    Color wall_Colour;
    Color path_Colour;
    float width, borderWidthThickness;
    int cols, rows;
    float borderWidth;
    vector<Cell> grid;
    Cell* current;
    stack<Cell*> flood;
    vector<Cell*> primCell;
    stack<Cell*> cellTrail;
    bool initialized;
    bool solving;
    bool creating;
    vector<tuple<int, int, int>> kruskalWalls;
    int kruskalWallIndex;
    DisjointSet* kruskalDS;
    bool kruskalInitialized;

public:
    Maze(int w = 40, float bWThickness = 0.1, Color wColour = BLACK, Color uVCColour = WHITE);
    ~Maze();
    
    void openPath(Cell* current, Cell* neighbor);
    void solveMazeByBFS(vector<Cell>& maze);
    void resetAStarSolver();
    void solveMazeByAStar(vector<Cell>& maze);
    void solveMazeByDFS(vector<Cell>& maze);
    pair<Cell, int> getRandomPrimCellIndex();
    void generateMazeByPrim();
    void generateMazeByDFS();
    void generateMazeByKruskal();
    void showGrid();
    void draw(bool& dfs_for_creation, bool& prim_for_creation, bool& eller_for_creation, 
              bool& dfs_for_solution, bool& two_for_solution, bool& three_for_solution, 
              float creationSpeed);
    
    vector<Cell> getGrid();
    bool isCreating();
    void set_Cell_Colour(Color temp);
    void set_Wall_Colour(Color temp);
    void set_VCell_Colour(Color temp);
    void set_BCell_Colour(Color temp);
};

#endif // MAZE_H
