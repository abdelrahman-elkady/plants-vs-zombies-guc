#include "camera.h"

void Camera::moveCamera(float x,float y, float z){
        this->x = x; this->y = y; this->z = z;
}

void Camera::rotateCamera(float xAngle,float yAngle,float zAngle){
        glPushMatrix();
        glRotatef(xAngle,1,0,0);
        glRotatef(yAngle,0,1,0);
        glRotatef(zAngle,0,0,1);
        glPopMatrix();
}

void Camera::activate(){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(this->x, this->y, this->z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}
