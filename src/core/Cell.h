#ifndef CELL_H
#define CELL_H

#include <raylib.h>
#include <vector>
#include "../utils/Constants.h"

using std::vector;

class Cell {
private:
    int x, y;
    float width;
    float borderWidth;
    bool borders[4];
    bool visited;
    bool isCurrent;
    Color wall_Colour;
    Color cell_Colour;
    Rectangle mainBox;
    vector<int> neighbors;

public:
    Cell();
    Cell(int i, int j, float _width, float _borderWidth, Color _wall_Colour, Color _cell_Colour);
    
    void show();
    int Index(int _x, int _y, int rows, int cols);
    bool getBorders(int temp) const;
    int getNeighbor(const vector<Cell>& grid, int rows, int cols, bool forCreation);
    void removeBorders(int temp);
    void setCurrent(bool temp);
    void setColor(Color col);
    bool isVisited();
    void visitCell(Color col);
    void unVisitCell();
    void setIsCurrent(bool temp);
    float getWidth();
    float getBorderWidth();
    int getx();
    int gety();
};

#endif // CELL_H
