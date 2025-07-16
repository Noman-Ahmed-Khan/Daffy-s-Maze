
#include <iostream>
#include <raylib.h>
#include <math.h>
#include <vector>
#include <stack>
#include <cstdlib> 
#include <ctime>
#include <algorithm>
#include <iomanip> 

using namespace std;
class Cell;
    // 0 is left 
    // 1 is right
    // 2 is top
    // 3 is bottom
const int screenWidth = 1900;
const int screenHeight = 1000;
const int mazeWidth = 800;
const int mazeHeight = 800;


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
    Cell() {}
    Cell(int i = 0, int j = 0, float _width = 0, float _borderWidth = 0,Color _wall_Colour=BLACK,Color _cell_Colour=WHITE) 
        : x(i), y(j), visited(false), isCurrent(false),width(_width), borderWidth(_borderWidth), wall_Colour(_wall_Colour),cell_Colour(_cell_Colour) {
        for (int i = 0; i < 4; i++) {
            borders[i] = true;
        }
        mainBox = Rectangle {(x * width) + (screenWidth-mazeWidth)/2, y * width, width, width};
    }

    void show() {
        if (!isCurrent) {
            DrawRectangleRec(mainBox, cell_Colour);

            if (borders[0]) DrawRectangle(x * width + (screenWidth-mazeWidth)/2, y * width, borderWidth, width, wall_Colour);
            if (borders[1]) DrawRectangle((x * width) + width - borderWidth + (screenWidth-mazeWidth)/2, y * width, borderWidth, width, wall_Colour);
            if (borders[2]) DrawRectangle(x * width + (screenWidth-mazeWidth)/2, y * width, width, borderWidth, wall_Colour);
            if (borders[3]) DrawRectangle(x * width+ + (screenWidth-mazeWidth)/2, (y * width) + width - borderWidth, width, borderWidth, wall_Colour);
        } else {
            DrawRectangle(x * width + (screenWidth-mazeWidth)/2, y * width, width, width, BLACK);
        }
    }


    int Index(int _x, int _y, int rows, int cols) {
        if (x + _x > rows - 1 || y + _y > cols - 1 || x + _x < 0 || y + _y < 0) {
            return -1;
        }
        return ((x + _x) * rows + ((y + _y))); 
    }
    bool getBorders(int temp) const { return borders[temp]; }
    int getNeighbor(const vector<Cell>& grid, int rows, int cols, bool forCreation) {
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
        } else{
        // left neighbors
        if(Index(-1,0,rows,cols)!=-1 && !borders[0] && !grid[Index(-1,0,rows,cols)].visited){
            neighbors.push_back(Index(-1,0,rows,cols));
        }
        
        // right neigbors
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
        
        
        if (neighbors.size() > 0) {
            return neighbors[rand() % neighbors.size()];
        }
        return -1;
    }

    void removeBorders(int temp) {
        if (temp == 0) borders[0] = false;
        else if (temp == 1) borders[1] = false;
        else if (temp == 2) borders[2] = false;
        else if (temp == 3) borders[3] = false;
    }

    void setCurrent(bool temp) { isCurrent = temp; }

    void setColor(Color col) { cell_Colour = col; }

    bool isVisited() { return visited; }

    void visitCell(Color col) {
        visited = true;
        setColor(col);
    }

    void unVisitCell() { visited = false; }

    void setIsCurrent(bool temp) { isCurrent = temp; }

    float getWidth() { return width; }
    float getBorderWidth() { return borderWidth; }
    int getx() { return x; }
    int gety() { return y; }
};

class Maze{
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

public:
    Maze(int w=40,float bWThickness=0.1,Color wColour=BLACK,Color uVCColour=WHITE) : width(w), borderWidthThickness(bWThickness), wall_Colour(wColour), un_Visited_Cell_Colour(uVCColour) {
        cols = mazeWidth / width;
        rows = mazeHeight / width;
        borderWidth = width*borderWidthThickness;
        initialized = false;
        solving = false;
        creating = true;

        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                grid.push_back(Cell(i, j, width, borderWidth,wall_Colour,un_Visited_Cell_Colour));
            }
        }

        current = &grid[0];
        current->setCurrent(true);
        current->visitCell(visited_Cell_Colour);
        primCell.push_back(current);
        cellTrail.push(current);
    }

    void openPath(Cell* current, Cell* neighbor) {
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

    void solveMazeByDFS(vector<Cell>& maze) {
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
            int currentIndex=(current->getx()*rows)+current->gety();
            int exitIndex=(maze[maze.size()-1].getx()*rows)+maze[maze.size()-1].gety();
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

    pair<Cell, int> getRandomPrimCellIndex() {
        int CellIndex = rand() % primCell.size();
        int CellIndexNeighbor = primCell[CellIndex]->getNeighbor(grid, rows, cols, true);
        if (CellIndexNeighbor == -1) {
            primCell.erase(primCell.begin() + CellIndex);
        }
        return pair<Cell, int>(*primCell[CellIndex], CellIndexNeighbor);
    }


void generateMazeByPrim() {
    if (!primCell.empty()) {
        pair<Cell, int> cellAndIndex = getRandomPrimCellIndex();
        if (cellAndIndex.second > -1) {
            openPath(&cellAndIndex.first, &grid[cellAndIndex.second]);
            grid[cellAndIndex.first.getx() * cols + cellAndIndex.first.gety()] = cellAndIndex.first;
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
    void generateMazeByBFS() {
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


    void showGrid() {
        for (size_t i = 0; i < grid.size(); i++) {
            grid[i].show();
        }
    }

    void draw(bool dfs_for_creation,bool prim_for_creation,bool eller_for_creation,bool dfs_for_solution,bool two_for_solution,bool three_for_solution, float creationSpeed) {
        showGrid();
        if(creating && dfs_for_creation){
            generateMazeByBFS();
        } else if(creating && prim_for_creation){
            generateMazeByPrim();
        } else if(creating && eller_for_creation){
            // ellers algo;
        } else if(!creating && dfs_for_solution){
            solveMazeByDFS(grid);
        } else if(!creating && two_for_solution){
            // algo two for solving
        } else if(!creating && three_for_solution){
            // algp three for solving
        }

        WaitTime(creationSpeed);
        
    }

    vector<Cell> getGrid() { return grid; }
    bool isCreating(void){return creating; }


            void set_Cell_Colour(Color temp){
                un_Visited_Cell_Colour= temp;
            }
            void set_Wall_Colour(Color temp){
                wall_Colour= temp;
            }
            void set_VCell_Colour(Color temp){
                visited_Cell_Colour= temp;
            }
            void set_BCell_Colour(Color temp){
                backtracked_Cell_Colour= temp;
            }




};

class MazeSettings{
    protected:
        int MAX_COLORS_COUNT=24;
        vector<Color> colours; 
        const char* colourNames[24];
        vector<Rectangle> coloursRecs;
        vector<bool> colourState;
        Font customFont;
    public: 
        MazeSettings() {      
        
        customFont = LoadFont("D:/projects/maze/src/Fonts/Godshomedemo-K794e.ttf");

        colours.insert(colours.end(),
        {BLACK, DARKGRAY, MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, DARKBROWN, Color{255,249,246,225},
        GRAY, RED, GOLD, LIME, BLUE, VIOLET, BROWN, WHITE ,LIGHTGRAY, PINK, YELLOW,
        GREEN, SKYBLUE, PURPLE, BEIGE} );

        colourNames[0 ]= "BLACK";
        colourNames[1 ]= "DARKGRAY";
        colourNames[2 ]= "MAROON";
        colourNames[3 ]= "ORANGE";
        colourNames[4 ]= "DARKGREEN";
        colourNames[5 ]= "DARKBLUE";
        colourNames[6 ]= "DARKPURPLE";
        colourNames[7 ]= "DARKBROWN";
        colourNames[8 ]= "OFFWHITE";
        colourNames[9 ]= "GRAY";
        colourNames[10]= "RED";
        colourNames[11]= "GOLD";
        colourNames[12]= "LIME";
        colourNames[13]= "BLUE";
        colourNames[14]= "VIOLET";
        colourNames[15]= "BROWN";
        colourNames[16]= "WHITE";
        colourNames[17]= "LIGHTGRAY";
        colourNames[18]= "PINK";
        colourNames[19]= "YELLOW";
        colourNames[20]= "GREEN";
        colourNames[21]= "SKYBLUE";
        colourNames[22]= "PURPLE";
        colourNames[23]= "BEIGE";

        coloursRecs.resize(MAX_COLORS_COUNT);
        for (int i = 0; i < MAX_COLORS_COUNT; i++)
        {
            coloursRecs[i].x =0;
            coloursRecs[i].y =0;
            coloursRecs[i].width  = 45.0f;
            coloursRecs[i].height = 45.0f;
        }
        colourState.resize(MAX_COLORS_COUNT,false);
    }
    
    void colourPalette(Color& temp,float tempX, float tempY, float textX, float textY){

        for (int i = 0; i < MAX_COLORS_COUNT; i++)
        {
            coloursRecs[i].x = tempX + 45.0f *(i%8) + 7.0f *(i%8);
            coloursRecs[i].y = tempY + 45.0f *(i/8) + 7.0f *(i/8);
        }

        for (int i = 0; i < MAX_COLORS_COUNT; i++)
        {
            if (CheckCollisionPointRec(GetMousePosition(), coloursRecs[i])) colourState[i] = 1;
            else colourState[i] = 0;
        }

        // DrawText("press SPACE to see all colors", GetScreenWidth() - 180, GetScreenHeight() - 40, 10, GRAY);

        for (int i = 0; i < MAX_COLORS_COUNT; i++)    // Draw all rectangles
        {
            DrawRectangleRec(coloursRecs[i], Fade(colours[i], colourState[i]? 0.6f : 1.0f));
            DrawRectangleLinesEx(coloursRecs[i], 1, BLACK);

            if (colourState[i])
            {
                DrawRectangle((int)coloursRecs[i].x, (int)(coloursRecs[i].y + coloursRecs[i].height - 26), (int)coloursRecs[i].width, 10, BLACK);
                DrawRectangleLinesEx(coloursRecs[i], 6, WHITE);
                DrawTextEx(customFont, colourNames[i], Vector2{textX, textY}, 25, 1, BLACK);
                if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && colourState[i]){
                    temp=colours[i];
                }

            }
        }

 }

    void choose_Wall_Colour(Color& wall_Colour){
        DrawTextEx(customFont,"CHOOSE WALL COLOUR:", Vector2{20, 175}, 25, 1, BLACK);
        DrawText(":", 2+MeasureText("CHOOSE WALL COLOUR:",25), 165, 40, BLACK);
        colourPalette(wall_Colour,80,200,MeasureText("CHOOSE WALL COLOUR:",25)+20,175);
    }

    void choose_Cell_Colour(Color& un_Visited_Cell_Colour){
        DrawTextEx(customFont,"CHOOSE CELL COLOUR:", Vector2{25, 375},  25, 1, BLACK);
        DrawText(":", 2+MeasureText("CHOOSE CELL COLOUR:",25), 365, 40, BLACK);
        colourPalette(un_Visited_Cell_Colour,80,400,MeasureText("CHOOSE CELL COLOUR:",25)+20,375);
    }

    void choose_VCell_Colour(Color& visited_Cell_Colour){
        
        DrawTextEx(customFont,"CHOOSE WALL COLOUR:", Vector2{25, 575},  25, 1, BLACK);
        DrawText(":", 2+MeasureText("CHOOSE WALL COLOUR:",25), 565, 40, BLACK);
        colourPalette(visited_Cell_Colour,80,600,MeasureText("CHOOSE VISITED CELL COLOUR:",25)-90,575);
    }

    void choose_BCell_Colour(Color& backtracked_Cell_Colour){
        DrawTextEx(customFont,"CHOOSE WALL COLOUR:", Vector2{25, 775},  25, 1, BLACK);
        DrawText(":", 2+MeasureText("CHOOSE WALL COLOUR:",25), 765, 40, BLACK);
        colourPalette(backtracked_Cell_Colour,80,800,MeasureText("CHOOSE BACKTRACED CELL COLOUR:",25)-170,775);    
    }
    
    

    void choose_Width(float& w, float lowerLimit, float upperLimit, float perClick, string str, float PosX=0, float PosY=0){
    
        Rectangle minus{655+PosX,225+PosY,80,55};
        Rectangle minusSign{675+PosX,249+PosY,40,7};
        Color minusColour;
        Color minusSignColour;
        if(CheckCollisionPointRec(GetMousePosition(),minus)){
            minusSignColour=WHITE;
            minusColour=BLACK;
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                if(w>lowerLimit){
                    w-=perClick;
                    WaitTime(0.2);
                }
            }
        } else {
            minusSignColour=BLACK;
            minusColour=WHITE;
        }
        
        Color plusSignColour;
        Color plusColour;
        Rectangle plus{825+PosX,225+PosY,80,55};
        Rectangle plusSign1{845+PosX,249+PosY,40,7};    
        Rectangle plusSign2{861.5f+PosX,233.5f+PosY,7,40};
        if(CheckCollisionPointRec(GetMousePosition(),plus)){
            plusSignColour=WHITE;
            plusColour=BLACK;
            if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
                if(w<upperLimit){
                    w+=perClick;
                    WaitTime(0.2);
                }
            }
        } else {
            plusSignColour=BLACK;
            plusColour=WHITE;
        }

        DrawTextEx(customFont,str.c_str(),Vector2{645+PosX,185+PosY}, 25, 1, BLACK);
        DrawText(":",635+PosX+MeasureText(str.c_str(),25),175+PosY, 40, BLACK);
        DrawRectangleRec(Rectangle{650+PosX,220+PosY,260,65}, BLACK);
        DrawRectangleRec(Rectangle{655+PosX,225+PosY,250,55}, WHITE);

        ostringstream oss;
        oss << fixed << setprecision(2) << w;
        string formattedW = oss.str();


        DrawRectangleRec(minus,minusColour);
        DrawRectangleRec(minusSign,minusSignColour);
        DrawText(formattedW.c_str(),780-MeasureText(formattedW.c_str(),30)/2+PosX,225+55/2-30/2+PosY,30,BLACK);
        DrawRectangleRec(plus,plusColour);
        DrawRectangleRec(plusSign1,plusSignColour);
        DrawRectangleRec(plusSign2,plusSignColour);

    }

    void display_Current(Color& wall_ColourColor,Color& un_Visited_Cell_Colour,Color& visited_Cell_ColourColor,Color& backtracked_Cell_ColourColor){
        Rectangle w_colour =  Rectangle{screenWidth-200 ,screenHeight-760, 45.0f , 45.0f};
        Rectangle c_colour =  Rectangle{screenWidth-200 ,screenHeight-700, 45.0f , 45.0f};
        Rectangle v_colour=  Rectangle{screenWidth-200 ,screenHeight-640, 45.0f , 45.0f};
        Rectangle b_colour =  Rectangle{screenWidth-200 ,screenHeight-580, 45.0f , 45.0f};

        DrawTextEx(customFont,"Wall Colour", Vector2{w_colour.x-MeasureText("Wall Colour",30)-5,w_colour.y} ,30,1,BLACK);
        DrawText(":",w_colour.x-9,w_colour.y-5,40,BLACK);
        DrawRectangleRec(w_colour,wall_ColourColor);
        DrawRectangleLinesEx(w_colour,1,BLACK);
        
        DrawTextEx(customFont,"Cell Colour", Vector2{c_colour.x-MeasureText("Cell Colour",30)-5,c_colour.y} ,30,1,BLACK);
        DrawText(":",c_colour.x-15,c_colour.y-4,40,BLACK);
        DrawRectangleRec(c_colour,un_Visited_Cell_Colour);
        DrawRectangleLinesEx(c_colour,1,BLACK);

        DrawTextEx(customFont,"Visited Cell Colour", Vector2{v_colour.x-MeasureText("Visited Cell Colour",30)-3,v_colour.y} ,30,1,BLACK);
        DrawText(":",v_colour.x-15,v_colour.y-4,40,BLACK);
        DrawRectangleRec(v_colour,visited_Cell_ColourColor);
        DrawRectangleLinesEx(v_colour,1,BLACK);
        
        DrawTextEx(customFont,"Backtracked Colour", Vector2{b_colour.x-MeasureText("Backtracked Colour",30)-3,b_colour.y} ,30,1,BLACK);
        DrawText(":",b_colour.x-15,b_colour.y-4,40,BLACK);
        DrawRectangleRec(b_colour,backtracked_Cell_ColourColor);
        DrawRectangleLinesEx(b_colour,1,BLACK);

    }

};

class UI;
typedef void (UI::*ButtonAction)();

class myButton{
    private:
            Rectangle buttonRect;
            float xButtonPosition;
            float yButtonPosition;
            float buttonWidth;
            float buttonHeight;
            float shadowThickness;
            Color buttonColor;
            Color _buttonColor;
            Color _shadowColor;
            Color shadowColor;
            char* text;
            float textx;
            float texty;
            float textSize;
            Color textColor;
            Color textColorTemp;
            Font customFont;
            ButtonAction action;
            // char* _temp;

    public:
        myButton(float _xButtonPosition,float _yButtonPosition,float _buttonWidth,float _buttonHeight,float _shadowThickness, Color _buttonColor, Color _shadowColor, char* _text, Color _textColor, float _textx,float _texty,float _textSize) : xButtonPosition(_xButtonPosition), yButtonPosition(_yButtonPosition), buttonWidth(_buttonWidth), buttonHeight(_buttonHeight),shadowThickness(_shadowThickness), buttonColor(_buttonColor), shadowColor(_shadowColor), text(_text), textColor(_textColor), textx(_textx), texty(_texty), textSize(_textSize){
            // _temp = new char[100];
            this -> _buttonColor=_buttonColor;
            this -> _shadowColor=_shadowColor;
            this -> textColorTemp=_textColor;
            customFont = LoadFont("D:/projects/maze/src/Fonts/Godshomedemo-K794e.ttf");
            
            buttonRect=(Rectangle){xButtonPosition,yButtonPosition,buttonWidth,buttonHeight}; 
        }

            void createButton(void){
                float xShadowPosition=((((GetMouseX()-(xButtonPosition+buttonWidth/2))/buttonWidth)*shadowThickness)+xButtonPosition);
                      xShadowPosition = (CheckCollisionPointRec(GetMousePosition(), buttonRect))? xButtonPosition+shadowThickness*2 : xShadowPosition;
                float yShadowPosition=((((GetMouseY()-(yButtonPosition+buttonHeight/2))/buttonHeight)*shadowThickness)+yButtonPosition);
                      yShadowPosition = (CheckCollisionPointRec(GetMousePosition(), buttonRect))? yButtonPosition+shadowThickness*2 : yShadowPosition;
            
                Rectangle shadowRect=(Rectangle){xShadowPosition,yShadowPosition,buttonWidth,buttonHeight};
                
                DrawRectangleRounded(shadowRect,1000 ,1000,shadowColor);
                DrawRectangleRounded(buttonRect,1000 ,1000,buttonColor);
                DrawTextEx(customFont, text, Vector2{textx,texty}, textSize, 0.5, textColor);
                // DrawText(text, xButtonPosition+buttonWidth/2-MeasureText(text, 20)/2,yButtonPosition+buttonHeight/2-20/2,20,textColor);
            }
            
            void mouseHover(){
                if(CheckCollisionPointRec(GetMousePosition(), buttonRect)){
                    buttonColor=Color{ 200, 191, 255, 255 };
                    shadowColor=Color{255, 200, 200, 200};
                    textColor=Color{255, 200, 200, 200};
                } else {
                    buttonColor=_buttonColor;
                    shadowColor=_shadowColor;
                    textColor=textColorTemp;
                }
            }

            void assignMemberFunc(ButtonAction a){
                action=a;
            }


            void clicked(UI* ui){
                if(CheckCollisionPointRec(GetMousePosition(),buttonRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)){
                    if(ui && action){
                        (ui->*action)();
                    }
                
                }
            }
            void ShowButton(void){
                createButton();
                mouseHover();
            }

        void runFunc(void (*funcPtr)()) {
            if (CheckCollisionPointRec(GetMousePosition(), buttonRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
            void (*funcPtr)();
            }
        }

 
        ~myButton(){
                UnloadFont(customFont);
        }
    };






class UI{
private:
    myButton Generate;
    myButton Maze_Setting;
    myButton Exit;
    myButton Back;
    myButton PRIM_For_Creation;
    myButton DFS_For_Creation;
    myButton ELLER_For_Creation;
    myButton DFS_For_Solution;
    myButton two_For_Solution;
    myButton three_For_Solution;
    myButton settingResetButton;
    myButton mazeResetButton;
    Maze maze;
    MazeSettings mazeSetup;
    Color wallColour;
    Color cellColour;
    Color vCellColour;
    Color bCellColour;
    bool exitWindow;
    bool menu;
    bool customizationMenu;
    bool dfs_for_creation;
    bool prim_for_creation;
    bool eller_for_creation;
    bool dfs_for_solution;
    bool two_for_solution;
    bool three_for_solution;
    float width;
    float borderThickness;
    float creationSpeed;
    Texture2D logoTexture;
    Texture2D StarsTexture[50];
    Rectangle destRect[50];
    float StarPositionX[50];
    float StarPositionY[50];
public:
    UI() :  Generate( screenWidth/2-200/2,screenHeight/2+100/2,200,100,4,SKYBLUE,Color{255, 237, 100, 200},"Generate",Color{255, 237, 100, 200},screenWidth/2-float(200/2) + 230 / 2 - float(MeasureText("Generate", 40)) / 2, screenHeight/2+100/2 + 90 / 2 - 20 / 2,40),
            Maze_Setting ( screenWidth/2-float(200/2),screenHeight/2+400/2,200,100,4,SKYBLUE,Color{255, 237, 100, 200},"Maze Setting",Color{255, 237, 100, 200},screenWidth/2-float(200/2) + 200 / 2 - float(MeasureText("Maze Setting", 30)) / 2 +7, screenHeight/2+400/2 + 100 / 2 - 20 / 2,30),
            Exit    ( screenWidth/2-float(200/2),screenHeight/2+700/2,200,100,4,SKYBLUE,Color{255, 237, 100, 200},"Exit",Color{255, 237, 100, 200},screenWidth/2-float(200/2) + 200 / 2 - float(MeasureText("Exit", 40)) / 2, screenHeight/2+700/2 + 100 / 2 - 20 / 2-1,40),
            Back    ( 30  , 70 , 105, 55 , 2, SKYBLUE, Color{255, 237, 100, 200}, "Back"   , Color{255, 237, 100, 200}, 30   + float(105) / 2 - float(MeasureText("Back"   , 30)) / 2, 70  + float(55 ) / 2 - 30 / 2, 30),
            PRIM_For_Creation ( 300 , mazeHeight+30, 200, 100, 4, SKYBLUE, Color{255, 237, 100, 200}, "PRIM", Color{255, 237, 100, 200}, 300  + float(200) / 2 - float(MeasureText("PRIM", 40)) / 2, mazeHeight+30 + float(100) / 2 - 40 / 2, 40),
            DFS_For_Creation     ( 850 , mazeHeight+30, 200, 100, 4, SKYBLUE, Color{255, 237, 100, 200}, "DFS"    , Color{255, 237, 100, 200}, 850  + float(200) / 2 - float(MeasureText("DFS"    , 40)) / 2, mazeHeight+30 + float(100) / 2 - 40 / 2, 40),
            ELLER_For_Creation     ( 1400, mazeHeight+30, 200, 100, 4, SKYBLUE, Color{255, 237, 100, 200}, "ELLER"    , Color{255, 237, 100, 200}, 1400 + float(200) / 2 - float(MeasureText("ELLER"    , 40)) / 2, mazeHeight+30 + float(100) / 2 - 40 / 2, 40),
            DFS_For_Solution ( 300 , mazeHeight+30, 200, 100, 4, SKYBLUE, Color{255, 237, 100, 200}, "DFS", Color{255, 237, 100, 200}, 300  + float(200) / 2 - float(MeasureText("DFS", 40)) / 2, mazeHeight+30 + float(100) / 2 - 40 / 2, 40), 
            two_For_Solution ( 850 , mazeHeight+30, 200, 100, 4, SKYBLUE, Color{255, 237, 100, 200}, "2"    , Color{255, 237, 100, 200}, 850  + float(200) / 2 - float(MeasureText("2"    , 40)) / 2, mazeHeight+30 + float(100) / 2 - 40 / 2, 40),
            three_For_Solution  ( 1400, mazeHeight+30, 200, 100, 4, SKYBLUE, Color{255, 237, 100, 200}, "3"    , Color{255, 237, 100, 200}, 1400 + float(200) / 2 - float(MeasureText("3"    , 40)) / 2, mazeHeight+30 + float(100) / 2 - 40 / 2, 40),
            settingResetButton(1630, 750, 230, 100, 4, SKYBLUE, Color{255, 237, 100, 200}, "Reset Settings"    , Color{255, 237, 100, 200}, 1630 + float(230) / 2 - float(MeasureText("Reset Settings"    , 32)) / 2+15, 750 + float(100) / 2 - 30 / 2, 32),
            mazeResetButton(1630, 70, 230, 100, 4, SKYBLUE, Color{255, 237, 100, 200}, "Reset Maze"    , Color{255, 237, 100, 200}, 1630 + float(230) / 2 - float(MeasureText("Reset Maze"    , 32)) / 2+15, 70 + float(100) / 2 - 30 / 2, 32),
            exitWindow(true),
            menu    (true),
            customizationMenu (false),
            dfs_for_creation (false),
            prim_for_creation (false),
            eller_for_creation (false),
            dfs_for_solution (false),
            two_for_solution (false),
            three_for_solution (false),
            width(40.0),
            borderThickness(0.1),
            creationSpeed(0.00),
            wallColour(BLACK),
            cellColour(WHITE),
            vCellColour(Color{200,191,255,255}),
            bCellColour(Color{255,191,246,255}){
        


            maze=Maze(width,borderThickness,wallColour,cellColour);
            maze.set_VCell_Colour(vCellColour);
            maze.set_BCell_Colour(bCellColour);

            Image image = LoadImage("D:/projects/maze/src/images/mazwWiz.png"); 
            logoTexture = LoadTextureFromImage(image);
            UnloadImage(image);

            for(int i=0 ; i<50 ; i++){

                StarPositionX[i]= rand()%screenWidth;
                StarPositionY[i]= rand()%screenHeight;
                for(int j=0 ; j<i ; j++){
                    if(StarPositionX[j]-StarPositionX[i]<200 && StarPositionX[j]-StarPositionX[i]>0){
                            StarPositionX[i]+=200;                        
                    }                
                    if(StarPositionX[j]-StarPositionX[i]>-200 && StarPositionX[j]-StarPositionX[i]<0){
                            StarPositionX[i]-=200;                        
                    }                
                    if(StarPositionY[j]-StarPositionY[i]<200 && StarPositionY[j]-StarPositionY[i]>0){
                            StarPositionY[i]+=200;                        
                    }                
                    if(StarPositionY[j]-StarPositionY[i]>-200 && StarPositionY[j]-StarPositionY[i]<0){
                            StarPositionY[i]-=200;                        
                    }                
                }
                cout<<StarPositionX[i]<<"  "<<StarPositionY[i]<<endl;
                string temp="D:/projects/maze/src/images/"+to_string(i%8)+".png";
                image = LoadImage(temp.c_str()); 
                StarsTexture[i] = LoadTextureFromImage(image);
                UnloadImage(image);
                destRect[i] = {StarPositionX[i],StarPositionY[i], (float)StarsTexture[i].width, (float)StarsTexture[i].height };
            }


            };

        void resetCreation(void){
            dfs_for_creation=false;
            prim_for_creation=false;
            eller_for_creation=false;
            dfs_for_solution=false;
            two_for_solution=false;
            three_for_solution=false;
        }

        void showMenu(void){
            menu=true;
            resetCreation();
        }

        void HideMenu(void){
            menu=false;
        }

        void ShowCustomizationMenu(void){
            customizationMenu=true;
            HideMenu();
        }
        
        void HideCustomizationMenu(void){
            customizationMenu=false;
            showMenu();
        }
        
        void resetSettings(void){
            wallColour=BLACK;
            cellColour=WHITE;
            vCellColour=Color{200,191,255,255};
            bCellColour=Color{255,191,246,255};
            width=40;
            borderThickness=0.1;
        }

        void resetMaze(void){
            maze=Maze(width,borderThickness,wallColour,cellColour);
            maze.set_VCell_Colour(vCellColour);
            maze.set_BCell_Colour(bCellColour);
            resetCreation();
        }



        void closeWindow(void){
            exitWindow=false;
        }

        bool getExitWindow(void){
            return exitWindow;
        }

        void useDFS_For_Creation(void){
            dfs_for_creation=!dfs_for_creation;
        }
        void usePRIM_For_Creation(void){
            prim_for_creation=!prim_for_creation;
        }
        void useELLER_For_Creation(void){
            eller_for_creation=!eller_for_creation;
        }

        void useDFS_For_Solution(void){
            dfs_for_solution=!dfs_for_solution;
        }
        void usetwo_For_Solution(void){
            two_for_solution=!two_for_solution;
        }
        void usethree_For_Solution(void){
            three_for_solution=!three_for_solution;
        }
    void start() {
        if(menu){

            DrawTexture(logoTexture,screenWidth/3-150,screenHeight/3-logoTexture.height/3-50,WHITE);

            
            for(int i=0 ; i<50 ; i++){
                
                DrawTexturePro(StarsTexture[i], (Rectangle){ 0, 0, StarsTexture[i].width, StarsTexture[i].height }, destRect[i], (Vector2){0,0}, 0, WHITE);

            }


            Generate.ShowButton();
            Generate.assignMemberFunc(&UI::HideMenu);
            Generate.clicked(this);

            Maze_Setting.ShowButton();
            Maze_Setting.assignMemberFunc(&UI::ShowCustomizationMenu);
            Maze_Setting.clicked(this);

            Exit.ShowButton();
            Exit.assignMemberFunc(&UI::closeWindow);
            Exit.clicked(this);

        } else if(customizationMenu){
            Back.ShowButton();
            Back.assignMemberFunc(&UI::HideCustomizationMenu);
            Back.clicked(this);

            mazeSetup.choose_Cell_Colour(cellColour);
            mazeSetup.choose_Wall_Colour(wallColour);
            mazeSetup.choose_Width(width,10,150,10,"Choose Cell Size:");
            mazeSetup.choose_Width(borderThickness,0.1,0.4,0.1,"Choose Border Width",0,200);
            if(width!=0.0){
                maze=Maze(width,borderThickness,wallColour,cellColour);            
            }

            mazeSetup.choose_VCell_Colour(vCellColour);
            mazeSetup.choose_BCell_Colour(bCellColour);
            maze.set_VCell_Colour(vCellColour);
            maze.set_BCell_Colour(bCellColour);

            mazeSetup.display_Current(wallColour,cellColour,vCellColour,bCellColour);
            mazeSetup.choose_Width(creationSpeed,0.0,0.1,0.01,"Choose Creation Speed",0,400);
            
            settingResetButton.ShowButton();
            settingResetButton.assignMemberFunc(&UI::resetSettings);
            settingResetButton.clicked(this);

        }else{
            Back.ShowButton();
            Back.assignMemberFunc(&UI::showMenu);
            Back.clicked(this);

            if(maze.isCreating()){

                PRIM_For_Creation.ShowButton();
                PRIM_For_Creation.assignMemberFunc(&UI::usePRIM_For_Creation);
                PRIM_For_Creation.clicked(this);

                DFS_For_Creation.ShowButton();
                DFS_For_Creation.assignMemberFunc(&UI::useDFS_For_Creation);
                DFS_For_Creation.clicked(this);

                ELLER_For_Creation.ShowButton();
                ELLER_For_Creation.assignMemberFunc(&UI::useELLER_For_Creation);
                ELLER_For_Creation.clicked(this);

            } else {

                DFS_For_Solution.ShowButton();
                DFS_For_Solution.assignMemberFunc(&UI::useDFS_For_Solution);
                DFS_For_Solution.clicked(this);

                two_For_Solution.ShowButton();
                two_For_Solution.assignMemberFunc(&UI::usetwo_For_Solution);
                two_For_Solution.clicked(this);

                three_For_Solution.ShowButton();
                three_For_Solution.assignMemberFunc(&UI::usethree_For_Solution);
                three_For_Solution.clicked(this);
            }

            mazeResetButton.ShowButton();
            mazeResetButton.assignMemberFunc(&UI::resetMaze);
            mazeResetButton.clicked(this);
            maze.draw(dfs_for_creation, prim_for_creation, eller_for_creation, dfs_for_solution, two_for_solution, three_for_solution, creationSpeed);
        }
        
    }
    ~UI(){
        UnloadTexture(logoTexture);
        for(int i=0 ; i<50 ; i++){
            UnloadTexture(StarsTexture[i]);
        }
    }
};

int main() {
    
    InitWindow(1900, 1000, "Menu");
    SetTargetFPS(1000);

    UI interface;
    while (!WindowShouldClose() && interface.getExitWindow()) {
        BeginDrawing();
        ClearBackground(WHITE);
        interface.start();
        DrawFPS(8, 8);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
