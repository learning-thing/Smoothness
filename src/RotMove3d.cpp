
#include <raylib.h>
#include <math.h>
#include <iostream>

#define MAX_COLUMNS 300

float xPos = 0;
float yPos = 1;
float zPos = 5;
float rotation = -3.2f;
float updown;
float shotangle = rotation;
float xSpeed = 0;
float ySpeed = 0;
float zSpeed = 0;
float gravity = 0.4;
float maxAccel = 1;
float Accel = 0;
float yAccel = 0;
float sideAccel = 0;
float rotation_speed = 0.05;
int frameCounter = 0;
unsigned int logRate = 1;
float deacceleration = .02;
float ground_hight = 1;
float last_frame_time;
float smooth_fov = 60;
float targ_fov;
bool debug = 1;
float windrot = 0;

Vector3 cubePosition = { 0.0f, .5f, 0.0f };

void physicsUpdate() {
    last_frame_time = GetFrameTime();
    frameCounter++;
    //acceleration
    xSpeed += Accel*sin(rotation)*0.5;
    zSpeed += Accel*cos(rotation)*0.5;

    xSpeed -= sideAccel*cos(rotation)*0.5;
    zSpeed += sideAccel*sin(rotation)*0.5;

    //deacceleration (1 = no deacceleration, 0 = instant deacceleration)
        
    xSpeed *= 1.0-deacceleration;
    zSpeed *= 1.0-deacceleration;

    

    if (yPos > ground_hight) {
        ySpeed -= gravity*GetFrameTime()*60;
    }

     if (yPos < ground_hight) {
        ySpeed = 0;
        yPos = 1;
    }
    
    xPos += xSpeed*last_frame_time;
    zPos += zSpeed*last_frame_time;
    yPos += ySpeed*last_frame_time;

    
    if (debug == 1) {//Logs
        if (frameCounter==10) {
        std::clog << "xSpeed:" << xSpeed << " \nySpeed:" << ySpeed << " \nzSpeed:" << zSpeed << "\n"
              << "Accel: " << Accel << "\nRotation: " << rotation << "\nyPos: " << yPos <<"\n\n\n";
        std::clog << GetMouseX() << "-" << GetMouseY() << "\nUpdown: "<< updown <<"\n";
        }
            if (frameCounter > logRate) {
                frameCounter = 0;
        }
    }
    


}

void controls() {
    //rotation
    last_frame_time = GetFrameTime();
    if (IsKeyDown(KEY_A)) {
        rotation += rotation_speed*last_frame_time*60;
    }
    if (IsKeyDown(KEY_D)) {
        rotation -= rotation_speed*last_frame_time*60;
    }

    //basic movement
    if (IsKeyDown(KEY_W)) {//if W go forward
        if (IsKeyDown(KEY_LEFT_SHIFT)) {//if shift is down, 
            if (Accel < maxAccel*2) {//      if theSpeed is Less than Sprint speed
                Accel += 0.1*last_frame_time*60;        //             add 0.1 to acceleration
            } 
        }else {//if shift is not down
            if (Accel < maxAccel) {
                Accel += 0.1*last_frame_time*60;
            } 
            if (Accel > maxAccel) {
                Accel = maxAccel;
            }
        }
    } 

    if (IsKeyDown(KEY_S)) {
        if (Accel > 0) {
            Accel = 0;
        }
        if (Accel > -maxAccel) {
            Accel -= 0.1*last_frame_time*60;
        }
    }

    if (IsKeyReleased(KEY_W || IsKeyReleased(KEY_S) || IsKeyReleased(KEY_SPACE))) {
        Accel = 0;
        yPos = 0;
        yAccel = 0;
    }

    

    if (!IsKeyDown(KEY_S) && !IsKeyDown(KEY_W)) {
        if (Accel > 0) {
            Accel -= 0.1;
        } if (Accel < 0) {
            Accel += 0.1;
        }
        if (Accel < 0.1f && Accel < -0.1f) {
            Accel = 0;
        }
        if (Accel > -0.1f && Accel < 0.1f) {
            Accel = 0;
        }
    }
}

void mouseControls() {
    //rotation
    rotation = GetMouseX()*-0.009f;
    updown = GetMouseY()*0.009f;
    
    
    //basic movement
    if (IsKeyDown(KEY_W)) {//if W go forward
        if (IsKeyDown(KEY_LEFT_SHIFT)) {//if shift is down, 
            if (Accel < maxAccel*2) {//      if theSpeed is Less than Sprint speed
                Accel += 0.1*GetFrameTime()*60;        //             add 0.1 to acceleration
            } 
        }else {//if shift is not down
            if (Accel < maxAccel) {
                Accel += 0.1*GetFrameTime()*60;
            }

        }
    } 

    if (IsKeyDown(KEY_S)) {
        if (Accel > 0) {
            Accel = 0;
        }
        if (Accel > -maxAccel) {
            Accel -= 0.1*GetFrameTime()*60;
        }
    }

    if (IsKeyDown(KEY_A)) {
        if (sideAccel > 0) {
            sideAccel = 0;
        }
        if (sideAccel > -maxAccel) {
            sideAccel -= 0.1*GetFrameTime()*60;
        }
    }

    if (IsKeyDown(KEY_D)) {
        if (sideAccel < 0) {
            sideAccel = 0;
        }
        if (sideAccel < maxAccel) {
            sideAccel += 0.1*GetFrameTime()*60;
        }
    }



    if (IsKeyReleased(KEY_W || IsKeyReleased(KEY_S) || IsKeyReleased(KEY_A) || IsKeyReleased(KEY_D))) {
        Accel = round(Accel);
        sideAccel = 0;
    }



    if (IsKeyDown(KEY_SPACE)) {
        if (yPos == ground_hight) {
            ySpeed = 10;
        }
    }


    if (!IsKeyDown(KEY_S) && !IsKeyDown(KEY_W)) {
        if (Accel > 0) {
            Accel -= 0.1;
        } if (Accel < 0) {
            Accel += 0.1;
        }
        if (Accel < 0.1f && Accel < -0.1f) {
            Accel = 0;
        }
        if (Accel > -0.1f && Accel < 0.1f) {
            Accel = 0;
        }
    }

    if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D)) {
        sideAccel = 0;
    }

    
}

Camera3D camera = { 0 };
void updateFPS() {
    last_frame_time = GetFrameTime();
    targ_fov = 64.0f+6*Accel;
    
    if (smooth_fov < targ_fov) {
        smooth_fov += (targ_fov-smooth_fov)*GetFrameTime()*60;
    } else {
        if (smooth_fov > targ_fov) {
            smooth_fov -= (smooth_fov-targ_fov)*GetFrameTime()*60;
        } 
    }

    camera.position = (Vector3){ xPos, yPos, zPos };  // Camera position (Obvious)
    camera.target = (Vector3){ xPos+sin(rotation)*2, yPos+sin(updown)*2, zPos+(cos(rotation)*2) };      // Camera looking at point (ok interesting)
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = smooth_fov;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;
}

void updateCube() {
    cubePosition = camera.target;
}



int main() {
    SetWindowState(FLAG_MSAA_4X_HINT);
    SetWindowState(FLAG_VSYNC_HINT);
    InitWindow(1920, 1080, "Smoothness in 3d");
    //SetTargetFPS(60);
    DisableCursor();
    SetMousePosition(0, 0);
    ToggleFullscreen();

    camera.position = (Vector3){ 0.0f, 5.0f, 5.0f };  // Camera position (Obvious)
    camera.target = (Vector3){ xPos+sin(rotation)*18, yPos+sin(updown), zPos+cos(rotation)*18};      // Camera looking at point (ok interesting)
      // Camera looking at point (ok interesting)
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
    camera.fovy = 64.0f;                                // Camera field-of-view Y
    camera.projection = CAMERA_PERSPECTIVE;  

    float heights[MAX_COLUMNS] = { 0 };
    Vector3 positions[MAX_COLUMNS] = { 0 };
    Color colors[MAX_COLUMNS] = { 0 };
    
    for (int i = 0; i < MAX_COLUMNS; i++)
    {
        heights[i] = (float)GetRandomValue(1, 12)*5;
        positions[i] = (Vector3){ (float)GetRandomValue(-200, 200), heights[i]*1.2f, (float)GetRandomValue(-200, 200) };
        colors[i] = (Color){ GetRandomValue(20, 255), GetRandomValue(10, 55), 30, 255 };
    }


    

    while (!WindowShouldClose()) {
        physicsUpdate();
        mouseControls();
        updateFPS();
        //updateCube();

        BeginDrawing();
        
        //DisableCursor();
        ClearBackground(BLACK);
        

            DrawFPS(GetScreenWidth()/2, 20);
                BeginMode3D(camera);
                //windrot+= 0.01;
                
                for (int i = 0; i < MAX_COLUMNS; i++)
                {
                    DrawCube(positions[i], 2.0f+sin(windrot)*100, heights[i], 2.0f, ColorAlpha(WHITE, 1*Accel/3));
                    DrawCubeWires(positions[i], 2.0f+sin(windrot)*100, heights[i], 2.0f, RAYWHITE);
                }
                
                    //DrawCube(cubePosition, 2.0f, 2.0f, 2.0f, RED);
                    DrawCubeWires(cubePosition, 2.0f, 2.0f, 2.0f, RAYWHITE);
                    DrawGrid(1000, 1.0f);
                EndMode3D();
        EndDrawing();

    }
    EnableCursor();
    CloseWindow();
    return 0;
}