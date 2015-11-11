#include "camera.h"
#include <GL/glut.h>

void Camera::moveCamera(float xCoordinate,float yCoordinate, float zCoordinate){
        this->xCoordinate = xCoordinate; this->yCoordinate = yCoordinate; this->zCoordinate = zCoordinate;
}

void Camera::rotateCamera(bool xEnable,bool yEnable,bool zEnable){

        if(xEnable) {glRotatef(this->xAngle,1,0,0); }
        if(yEnable) {glRotatef(this->yAngle,0,1,0); }
        if(zEnable) {glRotatef(this->zAngle,0,0,1); }

}

void Camera::activate(){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(this->xCoordinate, this->yCoordinate, this->zCoordinate, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}
