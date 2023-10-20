#include <iostream>
#include <math.h>
#include <raylib.h>

class tCharacter {     
    public:
        //Position and Location stuff
        float rotation = 90.0f;
        float xPos = 200.0f;
        float yPos = 200.0f;
        float xSpeed = 7.0f;
        float ySpeed = 7.0f;
        int maxSpeed = 10.0f;
        float rotationSpeed = 0.5f;
        int ballSize = 15;

        void glide() {
            if (xSpeed > 0.01f)     {
                xSpeed -= 0.1f;
            }
            
            if (ySpeed < -0.01f) {
                ySpeed -= 0.1f;
            }
        }

        void Draw() {
            DrawCircle(xPos-ballSize/2, yPos-ballSize/2, ballSize, RAYWHITE);
        }

        void DrawUpdate() {
            xPos = xPos + xSpeed * sin(rotation);
            yPos = yPos + ySpeed * cos(rotation);

            /*
            if (xSpeed > maxSpeed) {
                std::cout << "Speed_limit\n";
                xSpeed = maxSpeed;
            }

            if (ySpeed > maxSpeed) {
                std::cout << "Speed_limit\n";
                ySpeed = maxSpeed;
            }
            */
        }


        void ControlUpdate() {
            if (IsKeyDown(KEY_A)) {
                xSpeed -= 1.1f;
            }

            if (IsKeyDown(KEY_D)) {
                if (xSpeed < maxSpeed) {
                    xSpeed += 1.1f;
                } 
            
            if (IsKeyDown(KEY_W)) {
                if (ySpeed < maxSpeed) {
                    ySpeed -= 1.1f;
                }
            }
            if (IsKeyDown(KEY_W)) {
                if (ySpeed > -maxSpeed) {
                    ySpeed += 1.1f;
                }
            }

            if (xPos > GetScreenWidth()-10.0f) {
                xPos = GetScreenWidth()-10.0f;
                xSpeed *= -1.0f;
            }
            if (yPos > GetScreenHeight()-10.0f) {
                yPos = GetScreenHeight()-10.0f;
                ySpeed *= -1.0f;
            }
            if (xPos < 10.0f) {
                xPos = 10.0f;
                xSpeed *= -1.0f;
            }
            if (yPos < 10.0f) {
                yPos = 10.0f;
                ySpeed *= -1.0f;
            }
        }
};












class tGlideCharacter {
    private:
    

    public:
        float rotation = 90.0f;
        float xPos = 200.0f;
        float yPos = 200.0f;
        float xSpeed = 7.0f;
        float ySpeed = 0.0f;
    
        int maxSpeed = 30.0f;
        float rotationSpeed = 0.5f;
        int ballSize = 15;
        float deaccel = 0.96;
        bool DarkMode = true;

        float accel = 0.8;
        int colorManager = 0;


        void Draw() {
            switch (colorManager)
            {
            case 0: DrawCircle(xPos-ballSize/2, yPos-ballSize/2, ballSize, WHITE); break;
            case 1: DrawCircle(xPos-ballSize/2, yPos-ballSize/2, ballSize, GREEN); break;
            case 2: DrawCircle(xPos-ballSize/2, yPos-ballSize/2, ballSize, BLUE); break;
            case 3: DrawCircle(xPos-ballSize/2, yPos-ballSize/2, ballSize, YELLOW); break;
            case 4: DrawCircle(xPos-ballSize/2, yPos-ballSize/2, ballSize, ORANGE); break;
            case 5: DrawCircle(xPos-ballSize/2, yPos-ballSize/2, ballSize, RED); break;
            case 6: DrawCircle(xPos-ballSize/2, yPos-ballSize/2, ballSize, BLACK); break;
            case 7: DrawCircle(xPos-ballSize/2, yPos-ballSize/2, ballSize, PURPLE); break;
            case 8: DrawCircle(xPos-ballSize/2, yPos-ballSize/2, ballSize, PINK); break;
            
            default: DrawCircle(xPos-ballSize/2, yPos-ballSize/2, ballSize, WHITE); break;
            }

            if (IsKeyReleased(KEY_E)) {
                if (colorManager < 9) {
                    colorManager++;
                } else {
                    colorManager = 0;
                }
            }


        }

        void Physics() {
            //std::clog << xSpeed << "\n";
            if ((0 - xSpeed) < 0.1) {
                xSpeed *= deaccel;
            } 

            if ((0 - xSpeed) > -0.1) {
                xSpeed *= deaccel;
            } 

            //   Same for Y
            if ((0 - ySpeed) < 0.1) {
                ySpeed *= deaccel;
            } 

            if ((0 - ySpeed) > -0.1) {
                ySpeed *= deaccel;
            }
        }

        void DrawUpdate() {
            xPos = xPos + xSpeed * GetFrameTime()*100;
            yPos = yPos + ySpeed * GetFrameTime()*100;
        }



        void ControlsP1() {
            if (IsKeyDown(KEY_D)) {
                if (xSpeed < maxSpeed) {
                    rotation += rotationSpeed;
                }
            }
            if (IsKeyDown(KEY_A)) {
                if (xSpeed > maxSpeed*-1) {
                    rotation -= rotationSpeed;
                }
            }

            if (IsKeyDown(KEY_W)) {
                if (ySpeed > maxSpeed*-1) {
                    ySpeed -= accel*cos(rotation);
                }
            }
            std::clog << rotation << std::endl;

            if (IsKeyDown(KEY_S)) {
                if (ySpeed < maxSpeed) {
                    ySpeed += accel;
                }
            }

            if (IsKeyReleased(KEY_Q)) {
                if (DarkMode)    {
                    DarkMode = false;
                } else {
                    DarkMode = true;
                }
            }
        }


        void ControlsP2() {
            if (IsKeyDown(KEY_RIGHT)) {
                xSpeed += accel;
            }
            if (IsKeyDown(KEY_LEFT)) {
                xSpeed -= accel;
            }

            if (IsKeyDown(KEY_UP)) {
                ySpeed -= accel;
            }

            if (IsKeyDown(KEY_DOWN)) {
                ySpeed += accel;
            }

            if (IsKeyReleased(KEY_Q)) {
                if (DarkMode)    {
                    DarkMode = false;
                } else {
                    DarkMode = true;
                }
            }
        }


        void InfiniteBorder() {
            if (xPos < 0) {
                xPos = GetScreenWidth();
            } if (xPos > GetScreenWidth()) {
                xPos = 0;
            }

            if (yPos < 0) {
                yPos = GetScreenHeight();
            } if (yPos > GetScreenHeight()) {
                yPos = 0;
            }
        }


        void BounceBorder() {
            if (xPos < 0) {
                xPos = 0.01;
                xSpeed *= -5;
            } if (xPos > GetScreenWidth()) {
                xPos = GetScreenWidth()-0.01;
                xSpeed *= -5;
            }

            if (yPos < 0) {
                yPos = 0.01;
                ySpeed *= -5;
            } if (yPos > GetScreenHeight()) {
                yPos = GetScreenHeight()-0.01;
                ySpeed *= -5;
            }
        }


};