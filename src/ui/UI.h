#ifndef UI_H
#define UI_H

#include <raylib.h>
#include <vector>
#include "Button.h"
#include "MazeSettings.h"
#include "../maze/Maze.h"
#include "../utils/Constants.h"

class UI {
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
    UI();
    ~UI();
    
    void resetCreation();
    void showMenu();
    void HideMenu();
    void ShowCustomizationMenu();
    void HideCustomizationMenu();
    void resetSettings();
    void resetMaze();
    void closeWindow();
    bool getExitWindow();
    void useDFS_For_Creation();
    void usePRIM_For_Creation();
    void useELLER_For_Creation();
    void useDFS_For_Solution();
    void usetwo_For_Solution();
    void usethree_For_Solution();
    void start();
};

#endif // UI_H
