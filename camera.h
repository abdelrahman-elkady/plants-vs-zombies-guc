#include <iostream>
#include <string>
#include <GL/glut.h>
using namespace std;

#ifndef CAMERA_H
#define  CAMERA_H

class Camera
{
private:
        float xCoordinate, yCoordinate, zCoordinate,xAngle, yAngle, zAngle;
public:
        Camera(float xCoordinate,float yCoordinate, float zCoordinate,float xAngle,float yAngle,float zAngle){
                this->xCoordinate = xCoordinate; this->yCoordinate = yCoordinate; this->zCoordinate = zCoordinate;
                this->xAngle = xAngle; this->yAngle = yAngle; this->zAngle = zAngle;
                this->rotateCamera(xAngle,yAngle,zAngle);
        }

        void moveCamera(float xCoordinate,float yCoordinate, float zCoordinate);
        void rotateCamera(bool xEnable,bool yEnable,bool zEnable);
        void activate();


        float getXCoordinate(){
                return this->xCoordinate;
        }
        float getYCoordinate(){
                return this->yCoordinate;
        }
        float getZCoordinate(){
                return this->zCoordinate;
        }

        void setXCoordinate(float xCoordinate){
                this->xCoordinate = xCoordinate;
        }
        void setYCoordinate(float yCoordinate){
                this->yCoordinate = yCoordinate;
        }
        void setZCoordinate(float zCoordinate){
                this->zCoordinate = zCoordinate;
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
