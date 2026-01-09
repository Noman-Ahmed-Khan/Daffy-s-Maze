#ifndef BUTTON_H
#define BUTTON_H

#include <raylib.h>
#include <string>

class UI;
typedef void (UI::*ButtonAction)();

class myButton {
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

public:
    myButton(float _xButtonPosition, float _yButtonPosition, float _buttonWidth, 
             float _buttonHeight, float _shadowThickness, Color _buttonColor, 
             Color _shadowColor, char* _text, Color _textColor, float _textx, 
             float _texty, float _textSize);
    ~myButton();
    
    void createButton();
    void mouseHover();
    void assignMemberFunc(ButtonAction a);
    void clicked(UI* ui);
    void ShowButton();
};

#endif // BUTTON_H
