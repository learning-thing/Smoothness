#include <iostream>
#include <raylib.h>
#include "tcharacter.hpp"
#include <string.h>



int main() {

    const int screenWidth = 1080;
    const int screenHeight = 720;

    tGlideCharacter car;
    //tGlideCharacter car2;

    InitWindow(screenWidth, screenHeight, "Super Smooth Stuff");
    //SetTargetFPS(120);
    SetWindowState(FLAG_VSYNC_HINT);

    while (!WindowShouldClose()) {
        BeginDrawing();
        //ClearBackground(ColorAlpha(BLACK, 0.3));
        //DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.2));

        
        if (car.DarkMode) {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.2));
            DrawRectangle(10+car.xSpeed*2, 10+car.ySpeed*2, 110, 40, RAYWHITE);
        } else {
            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(GRAY, 0.2));
            DrawRectangle(10+car.xSpeed*2, 10+car.ySpeed*2, 110, 40, BLACK);
        }
        
        //DrawFPS(15+car.xSpeed*2.1, 15+car.ySpeed*2.1);
        
        
        car.Draw();
        car.DrawUpdate();
        car.Physics();
        car.ControlsP1();
        car.InfiniteBorder();


        EndDrawing();
    }
        
}