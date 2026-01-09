#ifndef MAZESETTINGS_H
#define MAZESETTINGS_H

#include <raylib.h>
#include <vector>
#include <string>

using std::vector;
using std::string;

class MazeSettings {
protected:
    int MAX_COLORS_COUNT;
    vector<Color> colours; 
    const char* colourNames[24];
    vector<Rectangle> coloursRecs;
    vector<bool> colourState;
    Font customFont;
    
public: 
    MazeSettings();
    ~MazeSettings();
    
    void colourPalette(Color& temp, float tempX, float tempY, float textX, float textY);
    void choose_Wall_Colour(Color& wall_Colour);
    void choose_Cell_Colour(Color& un_Visited_Cell_Colour);
    void choose_VCell_Colour(Color& visited_Cell_Colour);
    void choose_BCell_Colour(Color& backtracked_Cell_Colour);
    void choose_Width(float& w, float lowerLimit, float upperLimit, float perClick, 
                      string str, float PosX = 0, float PosY = 0);
    void display_Current(Color& wall_ColourColor, Color& un_Visited_Cell_Colour, 
                         Color& visited_Cell_ColourColor, Color& backtracked_Cell_ColourColor);
};

#endif // MAZESETTINGS_H
