#include <raylib.h>
#include <math.h>
#include <iostream>


int main(int argc, char *arv[]) {
    float rotation = 0.0f;
    float gear_radius = 120;
    float gearX = 1080;
    float Xspeed = 1;
    float gearY = 480;
    float Yspeed = 1;
    float rotation_speed = 60;
    float rotation2 = 0.0f;


    InitWindow(1080, 720, "Smoothnes");
    SetWindowState(FLAG_VSYNC_HINT);
    DisableCursor();
    SetMousePosition(0,0);

    //ToggleFullscreen();
    DisableCursor();


    int framerates[4] = {10, 60, 120, 240};
    //SetTargetFPS(framerates[2]);


    while (!WindowShouldClose()) {
        BeginDrawing();

            DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.1f));
            //ClearBackground(BLACK);
            DrawFPS(10, 10);

            //DrawCircle(gearX/2+sin(rotation)*gear_radius, gearY,   30+cos(rotation)*10, RAYWHITE);//Just a thick circle
            DrawCircle(gearX/2+sin(rotation)*gear_radius, gearY+cos(rotation)*gear_radius+sin(rotation2)*gear_radius, 30+sin(rotation2)*10+cos(rotation2), RAYWHITE);//Just a thick circle (3d)
            
            //DrawCircle(GetMouseX()+sin(rotation)*gear_radius*5, GetMouseY()+sin(rotation*2)*gear_radius, 18, RAYWHITE);//Infinity following mouse
            //DrawCircle(GetMouseX()+sin(rotation)*gear_radius*6, GetMouseY()-20, 13, RAYWHITE);
            
             //std::clog << rotation << std::endl << " - sin > " << sin(rotation) << std::endl << std::endl;;
           


        EndDrawing();
        //rotation += rotation_speed*GetFrameTime()*0.1f;//need to optimize
        //rotation += rotation_speed*GetFrameTime()*0.1f;//need to optimize
        rotation = GetMouseX()*0.01;
        rotation2 = GetMouseY()*0.01;

        

        

    }
    return 0;


}