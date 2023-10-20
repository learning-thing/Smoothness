#include <raylib.h>
#include "tsmoothnes.hpp"




animateur anim;

void draw_thing() {
    DrawCircle(anim.x, anim.y, 10, RAYWHITE);
    DrawCircle(anim.targx, anim.targy, 10, RAYWHITE);
}

int main() {
    InitWindow(1080, 720, "Smoothnes");
    SetTargetFPS(60);


    


    while (!WindowShouldClose()) {
        BeginDrawing();

            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.3));
            
            
            draw_thing();

            anim.run();
            DrawFPS(10, 10);

        EndDrawing();


    }


    return 0;
}