#include "UI.h"
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>

using namespace std;

UI::UI() :  
    Generate(screenWidth/2-200/2, screenHeight/2+100/2, 200, 100, 4, SKYBLUE, 
             Color{255, 237, 100, 200}, "Generate", Color{255, 237, 100, 200},
             screenWidth/2-float(200/2) + 230 / 2 - float(MeasureText("Generate", 40)) / 2, 
             screenHeight/2+100/2 + 90 / 2 - 20 / 2, 40),
    Maze_Setting(screenWidth/2-float(200/2), screenHeight/2+400/2, 200, 100, 4, SKYBLUE,
                  Color{255, 237, 100, 200}, "Maze Setting", Color{255, 237, 100, 200},
                  screenWidth/2-float(200/2) + 200 / 2 - float(MeasureText("Maze Setting", 30)) / 2 +7, 
                  screenHeight/2+400/2 + 100 / 2 - 20 / 2, 30),
    Exit(screenWidth/2-float(200/2), screenHeight/2+700/2, 200, 100, 4, SKYBLUE,
         Color{255, 237, 100, 200}, "Exit", Color{255, 237, 100, 200},
         screenWidth/2-float(200/2) + 200 / 2 - float(MeasureText("Exit", 40)) / 2, 
         screenHeight/2+700/2 + 100 / 2 - 20 / 2-1, 40),
    Back(30, 70, 105, 55, 2, SKYBLUE, Color{255, 237, 100, 200}, "Back",
         Color{255, 237, 100, 200}, 30 + float(105) / 2 - float(MeasureText("Back", 30)) / 2, 
         70 + float(55) / 2 - 30 / 2, 30),
    PRIM_For_Creation(300, mazeHeight+30, 200, 100, 4, SKYBLUE, Color{255, 237, 100, 200}, 
                      "PRIM", Color{255, 237, 100, 200}, 
                      300 + float(200) / 2 - float(MeasureText("PRIM", 40)) / 2, 
                      mazeHeight+30 + float(100) / 2 - 40 / 2, 40),
    DFS_For_Creation(850, mazeHeight+30, 200, 100, 4, SKYBLUE, Color{255, 237, 100, 200}, 
                     "DFS", Color{255, 237, 100, 200}, 
                     850 + float(200) / 2 - float(MeasureText("DFS", 40)) / 2, 
                     mazeHeight+30 + float(100) / 2 - 40 / 2, 40),
    ELLER_For_Creation(1400, mazeHeight+30, 200, 100, 4, SKYBLUE, Color{255, 237, 100, 200}, 
                       "ELLER", Color{255, 237, 100, 200}, 
                       1400 + float(200) / 2 - float(MeasureText("ELLER", 40)) / 2, 
                       mazeHeight+30 + float(100) / 2 - 40 / 2, 40),
    DFS_For_Solution(300, mazeHeight+30, 200, 100, 4, SKYBLUE, Color{255, 237, 100, 200}, 
                     "DFS", Color{255, 237, 100, 200}, 
                     300 + float(200) / 2 - float(MeasureText("DFS", 40)) / 2, 
                     mazeHeight+30 + float(100) / 2 - 40 / 2, 40), 
    two_For_Solution(850, mazeHeight+30, 200, 100, 4, SKYBLUE, Color{255, 237, 100, 200}, 
                     "2", Color{255, 237, 100, 200}, 
                     850 + float(200) / 2 - float(MeasureText("2", 40)) / 2, 
                     mazeHeight+30 + float(100) / 2 - 40 / 2, 40),
    three_For_Solution(1400, mazeHeight+30, 200, 100, 4, SKYBLUE, Color{255, 237, 100, 200}, 
                       "3", Color{255, 237, 100, 200}, 
                       1400 + float(200) / 2 - float(MeasureText("3", 40)) / 2, 
                       mazeHeight+30 + float(100) / 2 - 40 / 2, 40),
    settingResetButton(1630, 750, 230, 100, 4, SKYBLUE, Color{255, 237, 100, 200}, 
                        "Reset Settings", Color{255, 237, 100, 200}, 
                        1630 + float(230) / 2 - float(MeasureText("Reset Settings", 32)) / 2+15, 
                        750 + float(100) / 2 - 30 / 2, 32),
    mazeResetButton(1630, 70, 230, 100, 4, SKYBLUE, Color{255, 237, 100, 200}, 
                    "Reset Maze", Color{255, 237, 100, 200}, 
                    1630 + float(230) / 2 - float(MeasureText("Reset Maze", 32)) / 2+15, 
                    70 + float(100) / 2 - 30 / 2, 32),
    exitWindow(true),
    menu(true),
    customizationMenu(false),
    dfs_for_creation(false),
    prim_for_creation(false),
    eller_for_creation(false),
    dfs_for_solution(false),
    two_for_solution(false),
    three_for_solution(false),
    width(40.0),
    borderThickness(0.1),
    creationSpeed(0.00),
    wallColour(BLACK),
    cellColour(WHITE),
    vCellColour(Color{200,191,255,255}),
    bCellColour(Color{255,191,246,255}) {
    
    // BUG FIX #11: Initialize random seed
    srand(time(nullptr));
    
    maze = Maze(width, borderThickness, wallColour, cellColour);
    maze.set_VCell_Colour(vCellColour);
    maze.set_BCell_Colour(bCellColour);

    // BUG FIX #9: Use relative path instead of hardcoded absolute path
    string imagePath = "src/images/mazwWiz.png";
    Image image = LoadImage(imagePath.c_str()); 
    logoTexture = LoadTextureFromImage(image);
    UnloadImage(image);

    for(int i = 0; i < 50; i++) {
        StarPositionX[i] = rand() % screenWidth;
        StarPositionY[i] = rand() % screenHeight;
        for(int j = 0; j < i; j++) {
            if(StarPositionX[j] - StarPositionX[i] < 200 && StarPositionX[j] - StarPositionX[i] > 0) {
                StarPositionX[i] += 200;                        
            }                
            if(StarPositionX[j] - StarPositionX[i] > -200 && StarPositionX[j] - StarPositionX[i] < 0) {
                StarPositionX[i] -= 200;                        
            }                
            if(StarPositionY[j] - StarPositionY[i] < 200 && StarPositionY[j] - StarPositionY[i] > 0) {
                StarPositionY[i] += 200;                        
            }                
            if(StarPositionY[j] - StarPositionY[i] > -200 && StarPositionY[j] - StarPositionY[i] < 0) {
                StarPositionY[i] -= 200;                        
            }                
        }
        // BUG FIX #10: Removed debug output
        string temp = "src/images/" + to_string(i%8) + ".png";
        image = LoadImage(temp.c_str()); 
        StarsTexture[i] = LoadTextureFromImage(image);
        UnloadImage(image);
        destRect[i] = {StarPositionX[i], StarPositionY[i], (float)StarsTexture[i].width, (float)StarsTexture[i].height};
    }
}

UI::~UI() {
    UnloadTexture(logoTexture);
    for(int i = 0; i < 50; i++) {
        UnloadTexture(StarsTexture[i]);
    }
}

void UI::resetCreation() {
    dfs_for_creation = false;
    prim_for_creation = false;
    eller_for_creation = false;
    dfs_for_solution = false;
    two_for_solution = false;
    three_for_solution = false;
}

void UI::showMenu() {
    menu = true;
    resetCreation();
}

void UI::HideMenu() {
    menu = false;
}

void UI::ShowCustomizationMenu() {
    customizationMenu = true;
    HideMenu();
}

void UI::HideCustomizationMenu() {
    customizationMenu = false;
    showMenu();
}

void UI::resetSettings() {
    wallColour = BLACK;
    cellColour = WHITE;
    vCellColour = Color{200,191,255,255};
    bCellColour = Color{255,191,246,255};
    width = 40;
    borderThickness = 0.1;
}

void UI::resetMaze() {
    maze = Maze(width, borderThickness, wallColour, cellColour);
    maze.set_VCell_Colour(vCellColour);
    maze.set_BCell_Colour(bCellColour);
    maze.resetAStarSolver();
    resetCreation();
}

void UI::closeWindow() {
    exitWindow = false;
}

bool UI::getExitWindow() {
    return exitWindow;
}

void UI::useDFS_For_Creation() {
    dfs_for_creation = !dfs_for_creation;
}

void UI::usePRIM_For_Creation() {
    prim_for_creation = !prim_for_creation;
}

void UI::useELLER_For_Creation() {
    eller_for_creation = !eller_for_creation;
}

void UI::useDFS_For_Solution() {
    dfs_for_solution = !dfs_for_solution;
}

void UI::usetwo_For_Solution() {
    two_for_solution = !two_for_solution;
}

void UI::usethree_For_Solution() {
    three_for_solution = !three_for_solution;
}

void UI::start() {
    if(menu) {
        DrawTexture(logoTexture, screenWidth/3-150, screenHeight/3-logoTexture.height/3-50, WHITE);
        
        for(int i = 0; i < 50; i++) {
            DrawTexturePro(StarsTexture[i], (Rectangle){0, 0, StarsTexture[i].width, StarsTexture[i].height}, 
                          destRect[i], (Vector2){0,0}, 0, WHITE);
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

    } else if(customizationMenu) {
        Back.ShowButton();
        Back.assignMemberFunc(&UI::HideCustomizationMenu);
        Back.clicked(this);

        mazeSetup.choose_Cell_Colour(cellColour);
        mazeSetup.choose_Wall_Colour(wallColour);
        mazeSetup.choose_Width(width, 10, 150, 10, "Choose Cell Size:");
        mazeSetup.choose_Width(borderThickness, 0.1, 0.4, 0.1, "Choose Border Width", 0, 200);
        if(width != 0.0) {
            maze = Maze(width, borderThickness, wallColour, cellColour);            
        }

        mazeSetup.choose_VCell_Colour(vCellColour);
        mazeSetup.choose_BCell_Colour(bCellColour);
        maze.set_VCell_Colour(vCellColour);
        maze.set_BCell_Colour(bCellColour);

        mazeSetup.display_Current(wallColour, cellColour, vCellColour, bCellColour);
        mazeSetup.choose_Width(creationSpeed, 0.0, 0.1, 0.01, "Choose Creation Speed", 0, 400);
        
        settingResetButton.ShowButton();
        settingResetButton.assignMemberFunc(&UI::resetSettings);
        settingResetButton.clicked(this);

    } else {
        Back.ShowButton();
        Back.assignMemberFunc(&UI::showMenu);
        Back.clicked(this);

        if(maze.isCreating()) {
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
        // BUG FIX #5: Pass flags by reference so they can be modified
        maze.draw(dfs_for_creation, prim_for_creation, eller_for_creation, 
                  dfs_for_solution, two_for_solution, three_for_solution, creationSpeed);
    }
}
