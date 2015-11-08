#include <iostream>
#include <string>
#include <GL/glut.h>
using namespace std;

#ifndef CAMERA_H
#define  CAMERA_H

class Camera
{
private:
        float x, y, z,xAngle, yAngle, zAngle;
public:
        Camera(float x,float y, float z){
                this->x = x; this->y = y; this->z = z;
        }

        void moveCamera(float x,float y, float z);
        void rotateCamera(float xAngle,float yAngle,float zAngle);
        void activate();

        float getXPosition(){
                return this->x;
        }
        float getYPosition(){
                return this->y;
        }
        float getZPosition(){
                return this->z;
        }

        void getXPosition(float x){
                this->x = x;
        }
        void getYPosition(float y){
                this->y = y;
        }
        void getZPosition(float z){
                this->z = z;
        }


};
#endif
