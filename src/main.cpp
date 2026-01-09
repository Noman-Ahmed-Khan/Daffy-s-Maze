#include <raylib.h>
#include "ui/UI.h"
#include "utils/Constants.h"

int main() {
    InitWindow(screenWidth, screenHeight, "Menu");
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
