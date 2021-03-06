#include <GL/glut.h>
#include <iostream>
#include "defender.h"
using namespace std;

void Defender::draw(){

        glPushMatrix(); // Horizontal Cylinder
        glColor3f(0.1092,0.91,0.5229);
        glTranslatef(this->xCoordinate+0.5,1.0f,this->zCoordinate+0.5);// TODO: link coordinates with index on grid
        GLUquadric* quadObject = gluNewQuadric();
        glRotatef(90,0,1,0);
        gluCylinder(quadObject,0.09,0.09,0.25,15,15);
        glPopMatrix(); // End Horizontal Cylinder

        glPushMatrix(); // Sphere
        glColor3f(0.1216,0.76,0.4514);
        glTranslatef(this->xCoordinate+0.5,1.0f,this->zCoordinate+0.5);// TODO: link coordinates with index on grid
        glutSolidSphere(0.13,15,15);
        glPopMatrix(); // End Sphere

        glPushMatrix(); // Cylinder
        glColor3f(0.1092,0.91,0.5229);
        glTranslatef(this->xCoordinate+0.5,0.1,this->zCoordinate+0.5);// TODO: link coordinates with index on grid
        glRotatef(-90,1,0,0);
        gluCylinder(quadObject,0.09,0.09,0.9,15,15);
        glPopMatrix(); // End Cylinder

        if(this->bulletTimer > 5500) { // bullet every 5.5 seconds
                this->bulletTimer = 0;
                this->bullet->xCoordinate = this->xCoordinate;
                this->bullet->visible = true;
        }

        this->bullet->draw();

}

void Defender::update(){
        this->bulletTimer += 33;
        this->bullet->update();
}
