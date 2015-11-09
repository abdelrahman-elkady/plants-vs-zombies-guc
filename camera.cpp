#include "camera.h"
#include <GL/glut.h>

void Camera::moveCamera(float x,float y, float z){
        this->x = x; this->y = y; this->z = z;
}

void Camera::rotateCamera(bool xEnable,bool yEnable,bool zEnable){

        if(xEnable) {glRotatef(this->xAngle,1,0,0); }
        if(yEnable) {glRotatef(this->yAngle,0,1,0); }
        if(zEnable) {glRotatef(this->zAngle,0,0,1); }

}

void Camera::activate(){
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(this->x, this->y, this->z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);
}
