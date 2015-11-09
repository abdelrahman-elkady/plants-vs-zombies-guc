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
        Camera(float x,float y, float z,float xAngle,float yAngle,float zAngle){
                this->x = x; this->y = y; this->z = z;
                this->xAngle = xAngle; this->yAngle = yAngle; this->zAngle = zAngle;
                this->rotateCamera(xAngle,yAngle,zAngle);
        }

        void moveCamera(float x,float y, float z);
        void rotateCamera(bool xEnable,bool yEnable,bool zEnable);
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

        void setXPosition(float x){
                this->x = x;
        }
        void setYPosition(float y){
                this->y = y;
        }
        void setZPosition(float z){
                this->z = z;
        }

        float getXAngle(){
                return this->xAngle;
        }
        float getYAngle(){
                return this->yAngle;
        }
        float getZAngle(){
                return this->zAngle;
        }

        void setXAngle(float xAngle){
                this->xAngle = xAngle;
        }
        void setYAngle(float yAngle){
                this->yAngle = yAngle;
        }
        void setZAngle(float zAngle){
                this->zAngle = zAngle;
        }



};
#endif
