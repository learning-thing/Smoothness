#include <raylib.h>
#include <math.h>
#include <iostream>

float xPos = 20;
float yPos = 20;
float xSpeed = 0;
float ySpeed = 0;
float maxAccel = 10;
float Accel = 0;
float rotation = 0;
float rotation_speed = 0.09;

void draw_thing() {
    DrawCircle(xPos, yPos, 10, RAYWHITE);
    DrawCircle(xPos+sin(rotation)*10, yPos+cos(rotation)*10, 10, RAYWHITE);
    DrawCircle(xPos-sin(rotation)*10, yPos-cos(rotation)*10, 20, RAYWHITE);
    if (Accel > 0) {
        DrawCircle(xPos-sin(rotation)*25, yPos-cos(rotation)*30, 17, RED);
    } else {
        DrawCircle(xPos-sin(rotation)*25, yPos-cos(rotation)*30, 17, RAYWHITE);
    }
}

void controls() {
    //rotation
    if (IsKeyDown(KEY_A)) {
        rotation += rotation_speed*GetFrameTime()*60;
    }
    if (IsKeyDown(KEY_D)) {
        rotation -= rotation_speed*GetFrameTime()*60;
    }

    //basic movement
    if (IsKeyDown(KEY_W)) {
        Accel = 1;
    } else {
        Accel = 0;
    }

}

void controlsP2() {
    //rotation
    if (IsKeyDown(KEY_A)) {
        rotation += rotation_speed*GetFrameTime()*60;
    }
    if (IsKeyDown(KEY_D)) {
        rotation -= rotation_speed*GetFrameTime()*60;
    }

    //basic movement
    if (IsKeyDown(KEY_W)) {
        Accel = 1;
    } else {
        Accel = 0;
    }

}


void physicsUpdate() {
    //acceleration
    xSpeed += Accel*sin(rotation)*0.5;
    ySpeed += Accel*cos(rotation)*0.5;

    //deacceleration (1 = no deacceleration, 0 = instant deacceleration)
    xSpeed *= 0.98;
    ySpeed *= 0.98;

    xPos += xSpeed*GetFrameTime()*100;
    yPos += ySpeed*GetFrameTime()*100;
}


void physicsUpdateP2() {
    //acceleration
    xSpeed += Accel*sin(rotation)*0.5;
    ySpeed += Accel*cos(rotation)*0.5;

    //deacceleration (1 = no deacceleration, 0 = instant deacceleration)
    xSpeed *= 0.98;
    ySpeed *= 0.98;

    xPos += xSpeed*GetFrameTime()*100;
    yPos += ySpeed*GetFrameTime()*100;
}

void InfiniteBorderP2() {
    if (xPos < 0) {
        xPos= GetScreenWidth();
    } if (xPos> GetScreenWidth()) {
        xPos= 0;
    }

    if (yPos< 0) {
        yPos= GetScreenHeight();
    } if (yPos> GetScreenHeight()) {
        yPos= 0;
    }
}

void InfiniteBorder() {
    if (xPos < 0) {
        xPos= GetScreenWidth();
    } if (xPos> GetScreenWidth()) {
        xPos= 0;
    }

    if (yPos< 0) {
        yPos= GetScreenHeight();
    } if (yPos> GetScreenHeight()) {
        yPos= 0;
    }
}


int main() {
    InitWindow(1920, 1080, "ASteroids controls");
    //SetWindowState(FLAG_VSYNC_HINT);
    SetTargetFPS(120);
    ToggleFullscreen();

    while (!WindowShouldClose()) {
        //ClearBackground(BLACK);
        DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), ColorAlpha(BLACK, 0.2f));
        controls();
        physicsUpdate();
        InfiniteBorder();
        BeginDrawing();
            DrawFPS(GetScreenWidth()/2+xSpeed*2, 20+ySpeed*2);
            draw_thing();

            
        EndDrawing();
    }



    return 0;

}