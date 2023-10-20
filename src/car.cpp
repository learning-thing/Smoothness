#include "raylib.h"
#include <math.h>

float last_frame_time = 0;
float clean_frame_time = 0;
float targ_fov = 64.0;

float xPos = 0;
float  xSpeed = 0;

float yPos = 10;
float  ySpeed = 0;

float zPos = 0;
float zSpeed = 0;

float velocity = 0;
float updown = 0;
float leftright = 0;

float friction = 0.01;

int cam_distance = 30;

float rotation_speed = 0.05;


Camera3D camera = { 0 };
void updateCamera() {
    last_frame_time = GetFrameTime();
    if (targ_fov < 64.0f+velocity*2) {
        targ_fov += 0.3;
    } 

    if (targ_fov > 64.0f+velocity*2) {
        targ_fov -= 0.3;
    }
    
    camera.position = (Vector3){ xPos-sin(leftright)*cam_distance, yPos+cam_distance/3*2, zPos-cos(leftright)*cam_distance };  // Simple Follow Cam
    //camera.position = (Vector3){ 0, yPos+cam_distance, 0 };  // Camera position (Obvious)
    camera.target = (Vector3){ xPos, yPos, zPos };      // Camera looking at point (ok interesting)
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = targ_fov;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;
}


void updatePhysics() {
    last_frame_time = GetFrameTime();//Update position
    xPos += xSpeed*last_frame_time;
    zPos += zSpeed*last_frame_time;

    xSpeed += velocity*sin(leftright);
    zSpeed += velocity*cos(leftright);

    xSpeed *= 1-friction;
    zSpeed *= 1-friction;
    
}

void controls() {
    clean_frame_time = last_frame_time*60;
    if (IsKeyDown(KEY_W)) {//Accelerate
        velocity += 0.3*clean_frame_time;
    }

    if (IsKeyReleased(KEY_W) || IsKeyReleased(KEY_S)) {//Stop acceleration
        velocity = 0;
    }

    if (IsKeyDown(KEY_S)) {
        velocity -= 1*last_frame_time*60;
    }

    if (IsKeyDown(KEY_A)) {
        leftright += rotation_speed*clean_frame_time;
    }

    if (IsKeyDown(KEY_D)) {
        leftright -= rotation_speed*clean_frame_time;
    }

    if (IsKeyDown(KEY_SPACE)) {
        xSpeed *= 0.92;
        zSpeed *= 0.92;
    }
}


void DrawCar() {
    DrawSphere((Vector3){xPos-sin(leftright)*5, yPos, zPos-cos(leftright)*5}, 7, WHITE);
    DrawSphere((Vector3){xPos, yPos, zPos}, 7, WHITE);
}


int main() {
    InitWindow(1080, 720, "Drifting");
    //SetTargetFPS();
    SetWindowState(FLAG_MSAA_4X_HINT);
    SetWindowState(FLAG_VSYNC_HINT);
    while (!WindowShouldClose()) {
        updateCamera();
        controls();
        BeginDrawing();
            ClearBackground(ColorAlpha(BLACK, 0.1));
            DrawFPS(20, 20);
            BeginMode3D(camera);

                updatePhysics();
                DrawGrid(1000, 100);
                DrawCar();
            EndMode3D();
        EndDrawing();
    }
    CloseWindow();
        
    return 0;
}