#include <math.h>
#include <raylib.h>
#include <iostream>

class animateur {
    private:
    public:
        float x = 10;
        float y = 10;
        float xSpeed = 10;
        float ySpeed = 0;

        int targx = 300;
        int targy = 300;
        int distancex;
        int distancey;
        

        void reset() {
            x = 10;
            y = 10;
            xSpeed = 10;
            ySpeed = 0;
        }


        void Smart_accel() {
            if (xSpeed < distancex*0.1) {
                xSpeed+=0.5;
            } else {
                xSpeed = distancex*0.05;
            }
            
            if (ySpeed < distancey*0.1) {
                ySpeed+=0.5;
            } else {
                ySpeed = distancey*0.05;
            }

        }


        void Update() {
            x = x + xSpeed;// * GetFrameTime()*100;
            y = y + ySpeed;// * GetFrameTime()*100;
            //xSpeed *= 0.99;
            //xSpeed = (targx-x*2)*0.01;
            //xSpeed = xSpeed - GetFrameTime()*10;
            //if (xSpeed > 0) {xSpeed -= xSpeed/32;}
            distancex = targx-x;
            distancey = targy-y;


            Smart_accel();

            std::clog << "Distance X: " << distancex << std::endl;
            std::clog << "Distance Y: " << distancey << std::endl << std::endl;


            if (distancex == 0) {
                if (distancey == 0) {
                    reset();
                }
            }//Reset on low speed

        }

        void InfiniteBorder() {
                if (x < 0) {
                    x = GetScreenWidth();
                } if (x > GetScreenWidth()) {
                    x = 0;
                }

                if (y < 0) {
                    y = GetScreenHeight();
                } if (y > GetScreenHeight()) {
                    y = 0;
                }
        }

        void mouse_point() {
            targx = GetMouseX();
            targy = GetMouseY();
        }

        void run() {
            Update();
            InfiniteBorder();
            mouse_point();
        }


};