#include "MazeSettings.h"
#include <iomanip>
#include <sstream>
#include "../utils/Constants.h"

using namespace std;

MazeSettings::MazeSettings() {
    MAX_COLORS_COUNT = 24;
    
    // BUG FIX #9: Use relative path instead of hardcoded absolute path
    string fontPath = "src/Fonts/Godshomedemo-K794e.ttf";
    customFont = LoadFont(fontPath.c_str());

    colours.insert(colours.end(),
    {BLACK, DARKGRAY, MAROON, ORANGE, DARKGREEN, DARKBLUE, DARKPURPLE, DARKBROWN, 
     Color{255,249,246,225}, GRAY, RED, GOLD, LIME, BLUE, VIOLET, BROWN, WHITE,
     LIGHTGRAY, PINK, YELLOW, GREEN, SKYBLUE, PURPLE, BEIGE});

    colourNames[0] = "BLACK";
    colourNames[1] = "DARKGRAY";
    colourNames[2] = "MAROON";
    colourNames[3] = "ORANGE";
    colourNames[4] = "DARKGREEN";
    colourNames[5] = "DARKBLUE";
    colourNames[6] = "DARKPURPLE";
    colourNames[7] = "DARKBROWN";
    colourNames[8] = "OFFWHITE";
    colourNames[9] = "GRAY";
    colourNames[10] = "RED";
    colourNames[11] = "GOLD";
    colourNames[12] = "LIME";
    colourNames[13] = "BLUE";
    colourNames[14] = "VIOLET";
    colourNames[15] = "BROWN";
    colourNames[16] = "WHITE";
    colourNames[17] = "LIGHTGRAY";
    colourNames[18] = "PINK";
    colourNames[19] = "YELLOW";
    colourNames[20] = "GREEN";
    colourNames[21] = "SKYBLUE";
    colourNames[22] = "PURPLE";
    colourNames[23] = "BEIGE";

    coloursRecs.resize(MAX_COLORS_COUNT);
    for (int i = 0; i < MAX_COLORS_COUNT; i++) {
        coloursRecs[i].x = 0;
        coloursRecs[i].y = 0;
        coloursRecs[i].width = 45.0f;
        coloursRecs[i].height = 45.0f;
    }
    colourState.resize(MAX_COLORS_COUNT, false);
}

MazeSettings::~MazeSettings() {
    UnloadFont(customFont);
}

void MazeSettings::colourPalette(Color& temp, float tempX, float tempY, float textX, float textY) {
    for (int i = 0; i < MAX_COLORS_COUNT; i++) {
        coloursRecs[i].x = tempX + 45.0f *(i%8) + 7.0f *(i%8);
        coloursRecs[i].y = tempY + 45.0f *(i/8) + 7.0f *(i/8);
    }

    for (int i = 0; i < MAX_COLORS_COUNT; i++) {
        if (CheckCollisionPointRec(GetMousePosition(), coloursRecs[i])) colourState[i] = 1;
        else colourState[i] = 0;
    }

    for (int i = 0; i < MAX_COLORS_COUNT; i++) {
        DrawRectangleRec(coloursRecs[i], Fade(colours[i], colourState[i]? 0.6f : 1.0f));
        DrawRectangleLinesEx(coloursRecs[i], 1, BLACK);

        if (colourState[i]) {
            DrawRectangle((int)coloursRecs[i].x, (int)(coloursRecs[i].y + coloursRecs[i].height - 26), 
                          (int)coloursRecs[i].width, 10, BLACK);
            DrawRectangleLinesEx(coloursRecs[i], 6, WHITE);
            DrawTextEx(customFont, colourNames[i], Vector2{textX, textY}, 25, 1, BLACK);
            if(IsMouseButtonDown(MOUSE_LEFT_BUTTON) && colourState[i]) {
                temp = colours[i];
            }
        }
    }
}

void MazeSettings::choose_Wall_Colour(Color& wall_Colour) {
    DrawTextEx(customFont, "CHOOSE WALL COLOUR:", Vector2{20, 175}, 25, 1, BLACK);
    DrawText(":", 2+MeasureText("CHOOSE WALL COLOUR:", 25), 165, 40, BLACK);
    colourPalette(wall_Colour, 80, 200, MeasureText("CHOOSE WALL COLOUR:", 25)+20, 175);
}

void MazeSettings::choose_Cell_Colour(Color& un_Visited_Cell_Colour) {
    DrawTextEx(customFont, "CHOOSE CELL COLOUR:", Vector2{25, 375}, 25, 1, BLACK);
    DrawText(":", 2+MeasureText("CHOOSE CELL COLOUR:", 25), 365, 40, BLACK);
    colourPalette(un_Visited_Cell_Colour, 80, 400, MeasureText("CHOOSE CELL COLOUR:", 25)+20, 375);
}

void MazeSettings::choose_VCell_Colour(Color& visited_Cell_Colour) {
    // BUG FIX #7: Fixed incorrect text label
    DrawTextEx(customFont, "CHOOSE VISITED CELL COLOUR:", Vector2{25, 575}, 25, 1, BLACK);
    DrawText(":", 2+MeasureText("CHOOSE VISITED CELL COLOUR:", 25), 565, 40, BLACK);
    colourPalette(visited_Cell_Colour, 80, 600, MeasureText("CHOOSE VISITED CELL COLOUR:", 25)+20, 575);
}

void MazeSettings::choose_BCell_Colour(Color& backtracked_Cell_Colour) {
    // BUG FIX #7: Fixed incorrect text label
    DrawTextEx(customFont, "CHOOSE BACKTRACKED CELL COLOUR:", Vector2{25, 775}, 25, 1, BLACK);
    DrawText(":", 2+MeasureText("CHOOSE BACKTRACKED CELL COLOUR:", 25), 765, 40, BLACK);
    colourPalette(backtracked_Cell_Colour, 80, 800, MeasureText("CHOOSE BACKTRACKED CELL COLOUR:", 25)+20, 775);
}

void MazeSettings::choose_Width(float& w, float lowerLimit, float upperLimit, float perClick, 
                                 string str, float PosX, float PosY) {
    Rectangle minus{655+PosX, 225+PosY, 80, 55};
    Rectangle minusSign{675+PosX, 249+PosY, 40, 7};
    Color minusColour;
    Color minusSignColour;
    if(CheckCollisionPointRec(GetMousePosition(), minus)) {
        minusSignColour = WHITE;
        minusColour = BLACK;
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if(w > lowerLimit) {
                w -= perClick;
                WaitTime(0.2);
            }
        }
    } else {
        minusSignColour = BLACK;
        minusColour = WHITE;
    }
    
    Color plusSignColour;
    Color plusColour;
    Rectangle plus{825+PosX, 225+PosY, 80, 55};
    Rectangle plusSign1{845+PosX, 249+PosY, 40, 7};    
    Rectangle plusSign2{861.5f+PosX, 233.5f+PosY, 7, 40};
    if(CheckCollisionPointRec(GetMousePosition(), plus)) {
        plusSignColour = WHITE;
        plusColour = BLACK;
        if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
            if(w < upperLimit) {
                w += perClick;
                WaitTime(0.2);
            }
        }
    } else {
        plusSignColour = BLACK;
        plusColour = WHITE;
    }

    DrawTextEx(customFont, str.c_str(), Vector2{645+PosX, 185+PosY}, 25, 1, BLACK);
    DrawText(":", 635+PosX+MeasureText(str.c_str(), 25), 175+PosY, 40, BLACK);
    DrawRectangleRec(Rectangle{650+PosX, 220+PosY, 260, 65}, BLACK);
    DrawRectangleRec(Rectangle{655+PosX, 225+PosY, 250, 55}, WHITE);

    ostringstream oss;
    oss << fixed << setprecision(2) << w;
    string formattedW = oss.str();

    DrawRectangleRec(minus, minusColour);
    DrawRectangleRec(minusSign, minusSignColour);
    DrawText(formattedW.c_str(), 780-MeasureText(formattedW.c_str(), 30)/2+PosX, 225+55/2-30/2+PosY, 30, BLACK);
    DrawRectangleRec(plus, plusColour);
    DrawRectangleRec(plusSign1, plusSignColour);
    DrawRectangleRec(plusSign2, plusSignColour);
}

void MazeSettings::display_Current(Color& wall_ColourColor, Color& un_Visited_Cell_Colour, 
                                    Color& visited_Cell_ColourColor, Color& backtracked_Cell_ColourColor) {
    Rectangle w_colour = Rectangle{screenWidth-200, screenHeight-760, 45.0f, 45.0f};
    Rectangle c_colour = Rectangle{screenWidth-200, screenHeight-700, 45.0f, 45.0f};
    Rectangle v_colour = Rectangle{screenWidth-200, screenHeight-640, 45.0f, 45.0f};
    Rectangle b_colour = Rectangle{screenWidth-200, screenHeight-580, 45.0f, 45.0f};

    DrawTextEx(customFont, "Wall Colour", Vector2{w_colour.x-MeasureText("Wall Colour", 30)-5, w_colour.y}, 30, 1, BLACK);
    DrawText(":", w_colour.x-9, w_colour.y-5, 40, BLACK);
    DrawRectangleRec(w_colour, wall_ColourColor);
    DrawRectangleLinesEx(w_colour, 1, BLACK);
    
    DrawTextEx(customFont, "Cell Colour", Vector2{c_colour.x-MeasureText("Cell Colour", 30)-5, c_colour.y}, 30, 1, BLACK);
    DrawText(":", c_colour.x-15, c_colour.y-4, 40, BLACK);
    DrawRectangleRec(c_colour, un_Visited_Cell_Colour);
    DrawRectangleLinesEx(c_colour, 1, BLACK);

    DrawTextEx(customFont, "Visited Cell Colour", Vector2{v_colour.x-MeasureText("Visited Cell Colour", 30)-3, v_colour.y}, 30, 1, BLACK);
    DrawText(":", v_colour.x-15, v_colour.y-4, 40, BLACK);
    DrawRectangleRec(v_colour, visited_Cell_ColourColor);
    DrawRectangleLinesEx(v_colour, 1, BLACK);
    
    DrawTextEx(customFont, "Backtracked Colour", Vector2{b_colour.x-MeasureText("Backtracked Colour", 30)-3, b_colour.y}, 30, 1, BLACK);
    DrawText(":", b_colour.x-15, b_colour.y-4, 40, BLACK);
    DrawRectangleRec(b_colour, backtracked_Cell_ColourColor);
    DrawRectangleLinesEx(b_colour, 1, BLACK);
}
