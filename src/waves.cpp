#include <raylib.h>
#include <math.h>
#include <iostream>
#include <string>


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
float strafe_vel = 0;

float friction = 0.03;

int cam_distance = 300;

float rotation_speed = 0.05;
float rota = 0;
unsigned int spacing = 6;
float cubesize = 3;
float cuby;
int wavespeed = 1;
float mousey;

int framecount = 1;
char framename[7] = {0,0,framecount, '.', 'p', 'n', 'g'};

void controls() {
    mousey = GetMouseY();
    
    updown = mousey*0.01;
    leftright = -GetMouseX()*0.01;

    if (mousey > 400)  {
        SetMousePosition(GetMouseX(), 400);
    }

    if (mousey < 200)  {
        SetMousePosition(GetMouseX(), 200);
    }

    //control waves
    if (IsKeyReleased(KEY_UP)) {
        spacing++;
    }

    if (IsKeyReleased(KEY_DOWN)) {
        spacing--;
    }

    if (IsKeyReleased(KEY_M)) {
        cubesize++;
    }

    if (IsKeyReleased(KEY_N)) {
        cubesize--;
    }
    if (IsKeyReleased(KEY_Q)) {
        wavespeed++;
    }
    if (IsKeyReleased(KEY_E)) {
        wavespeed--;
    }



    if (IsKeyDown(KEY_W)) {//Accelerate
        velocity += 0.1*clean_frame_time;
    }

    if (IsKeyReleased(KEY_W) || IsKeyReleased(KEY_S)) {//Stop acceleration
        velocity = 0;
    }

    if (IsKeyDown(KEY_S)) {
        velocity -= 0.1*clean_frame_time;
    }

    if (IsKeyDown(KEY_A)) {
        strafe_vel -= 0.1*clean_frame_time;
    }

    if (IsKeyDown(KEY_D)) {
        strafe_vel += 0.1*clean_frame_time;
    }

    if (IsKeyReleased(KEY_A) || IsKeyReleased(KEY_D)) {
        strafe_vel = 0;
    }

    if (IsKeyDown(KEY_SPACE)) {
        xSpeed *= 0.92;
        zSpeed *= 0.92;
    }
}



void updatePhysics() {

    last_frame_time = GetFrameTime();//Update position
    clean_frame_time = last_frame_time*64;

    xPos += xSpeed*last_frame_time;
    zPos += zSpeed*last_frame_time;
    yPos += ySpeed*last_frame_time;

    xSpeed += velocity*sin(leftright);
    zSpeed += velocity*cos(leftright);
    ySpeed += velocity*sin(updown)*2;

    xSpeed -= strafe_vel*cos(leftright);
    zSpeed += strafe_vel*sin(leftright);

    xSpeed *= 1-friction*clean_frame_time;
    zSpeed *= 1-friction*clean_frame_time;
    ySpeed *= 1-friction*clean_frame_time;

    rota += wavespeed*clean_frame_time/6;
}

Camera3D camera = { 0 };
void updateCamera() {
    last_frame_time = GetFrameTime();
    if (targ_fov < 64.0f+velocity/2) {
        targ_fov += 0.3;
    } 

    if (targ_fov > 64.0f+velocity*2) {
        targ_fov -= 0.3;
    }
    
    camera.position = (Vector3){ xPos, yPos, zPos };  // Simple Follow Cam
    //camera.position = (Vector3){ 0, yPos+cam_distance, 0 };  // Camera position (Obvious)
    camera.target = (Vector3){ xPos+sin(leftright)*cam_distance, yPos+sin(updown)*50, zPos+cos(leftright)*cam_distance };      // Camera looking at point (ok interesting)
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = targ_fov;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;
}

void autoview() {
    camera.position = (Vector3){ xPos-sin(leftright)*cam_distance, yPos, zPos-cos(leftright)*cam_distance };  // Simple Follow Cam
    //camera.position = (Vector3){ 0, yPos+cam_distance, 0 };  // Camera position (Obvious)
    camera.target = (Vector3){ xPos, yPos, zPos };      // Camera looking at point (ok interesting)
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = targ_fov;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;
    leftright += last_frame_time*0.1*wavespeed;



    if (IsKeyReleased(KEY_UP)) {
        spacing++;
    }

    if (IsKeyReleased(KEY_DOWN)) {
        spacing--;
    }

    if (IsKeyReleased(KEY_M)) {
        cubesize++;
    }

    if (IsKeyReleased(KEY_N)) {
        cubesize--;
    }
    if (IsKeyReleased(KEY_Q)) {
        wavespeed++;
    }
    if (IsKeyReleased(KEY_E)) {
        wavespeed--;
    }
}


int main() {
    SetWindowState(FLAG_MSAA_4X_HINT);
    InitWindow(1920, 1080, "Wave simulation");
    ToggleFullscreen();
    //SetTargetFPS(60);
    SetWindowState(FLAG_VSYNC_HINT);//We need mack smoothness BOYS
    DisableCursor();

    
    while (!WindowShouldClose()) {
        //controls();
        //updateCamera();


        autoview();
        updatePhysics();

        BeginDrawing();
            DrawFPS(10, 10);

            ClearBackground(BLACK);
            BeginMode3D(camera);
            //DrawGrid(100, 10);
            
            
            //Draw Waves
            for (float xw = 0; xw < 100; xw++) {
                for (float yw = 0; yw < 100; yw++) {
                    cuby = sin((rota-yw-xw)*0.1)*spacing;
                    //DrawCubeWires((Vector3){xw*spacing, 10+cuby, yw*spacing}, cubesize, cubesize, cubesize, WHITE);
                    DrawCube((Vector3){xw*spacing, 10+(cuby)*spacing, yw*spacing}, cubesize, cubesize, cubesize, ColorAlpha(RED, 0.6+cuby/spacing/2));//With color by height simple
                    //DrawCube((Vector3){xw*spacing, 10+(cuby-sin(xw-yw))*spacing, yw*spacing}, cubesize, cubesize, cubesize, ColorAlphaBlend(BLUE, GREEN, WHITE));//With color mixer

                }
            }
            


            EndMode3D();
        EndDrawing();
    }
    CloseWindow();
    return 0;
}