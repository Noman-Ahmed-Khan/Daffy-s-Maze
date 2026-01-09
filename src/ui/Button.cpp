#include "Button.h"
#include <string>
#include "../utils/Constants.h"

using namespace std;

myButton::myButton(float _xButtonPosition, float _yButtonPosition, float _buttonWidth, 
                   float _buttonHeight, float _shadowThickness, Color _buttonColor, 
                   Color _shadowColor, char* _text, Color _textColor, float _textx, 
                   float _texty, float _textSize) 
    : xButtonPosition(_xButtonPosition), yButtonPosition(_yButtonPosition), 
      buttonWidth(_buttonWidth), buttonHeight(_buttonHeight), shadowThickness(_shadowThickness), 
      buttonColor(_buttonColor), shadowColor(_shadowColor), text(_text), textColor(_textColor), 
      textx(_textx), texty(_texty), textSize(_textSize) {
    this -> _buttonColor = _buttonColor;
    this -> _shadowColor = _shadowColor;
    this -> textColorTemp = _textColor;
    
    // BUG FIX #9: Use relative path instead of hardcoded absolute path
    string fontPath = "src/Fonts/Godshomedemo-K794e.ttf";
    customFont = LoadFont(fontPath.c_str());
    
    buttonRect = (Rectangle){xButtonPosition, yButtonPosition, buttonWidth, buttonHeight}; 
}

myButton::~myButton() {
    UnloadFont(customFont);
}

void myButton::createButton() {
    float xShadowPosition = ((((GetMouseX()-(xButtonPosition+buttonWidth/2))/buttonWidth)*shadowThickness)+xButtonPosition);
    xShadowPosition = (CheckCollisionPointRec(GetMousePosition(), buttonRect))? 
        xButtonPosition+shadowThickness*2 : xShadowPosition;
    float yShadowPosition = ((((GetMouseY()-(yButtonPosition+buttonHeight/2))/buttonHeight)*shadowThickness)+yButtonPosition);
    yShadowPosition = (CheckCollisionPointRec(GetMousePosition(), buttonRect))? 
        yButtonPosition+shadowThickness*2 : yShadowPosition;

    Rectangle shadowRect = (Rectangle){xShadowPosition, yShadowPosition, buttonWidth, buttonHeight};
    
    DrawRectangleRounded(shadowRect, 1000, 1000, shadowColor);
    DrawRectangleRounded(buttonRect, 1000, 1000, buttonColor);
    DrawTextEx(customFont, text, Vector2{textx, texty}, textSize, 0.5, textColor);
}

void myButton::mouseHover() {
    if(CheckCollisionPointRec(GetMousePosition(), buttonRect)) {
        buttonColor = Color{200, 191, 255, 255};
        shadowColor = Color{255, 200, 200, 200};
        textColor = Color{255, 200, 200, 200};
    } else {
        buttonColor = _buttonColor;
        shadowColor = _shadowColor;
        textColor = textColorTemp;
    }
}

void myButton::assignMemberFunc(ButtonAction a) {
    action = a;
}

void myButton::clicked(UI* ui) {
    if(CheckCollisionPointRec(GetMousePosition(), buttonRect) && IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
        if(ui && action) {
            (ui->*action)();
        }
    }
}

void myButton::ShowButton() {
    createButton();
    mouseHover();
}
