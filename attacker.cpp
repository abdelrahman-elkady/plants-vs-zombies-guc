#include <GL/glut.h>
#include <iostream>
#include "attacker.h"
#include "utils.h"
using namespace std;

void Attacker::draw(){

        if(!this->visible) {
          return;
        }
        // Start wheels

        glPushMatrix();
        glTranslatef(0.6f,-0.2f,0.1f);
        drawWheel();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.3f,-0.2f,0.1f);
        drawWheel();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.3f,-0.2f,0.6f);
        drawWheel();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.6f,-0.2f,0.6f);
        drawWheel();
        glPopMatrix();

        // End Wheels

        glPushMatrix(); // Cones
        glTranslatef(this->xCoordinate+0.3,this->yCoordinate,this->zCoordinate+0.5);
        glRotatef(-90,0,1,0);
        glutSolidCone(0.05,0.1,15,15);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(this->xCoordinate+0.3,this->yCoordinate,this->zCoordinate+0.6);
        glRotatef(-90,0,1,0);
        glutSolidCone(0.05,0.1,15,15);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(this->xCoordinate+0.3,this->yCoordinate,this->zCoordinate+0.4);
        glRotatef(-90,0,1,0);
        glutSolidCone(0.05,0.1,15,15);
        glPopMatrix();// End Cones

        glPushMatrix(); // The upper thing !
        glTranslatef(this->xCoordinate+0.5,this->yCoordinate+0.3,this->zCoordinate+0.5);
        glScalef(0.09,0.1,0.06);
        glutSolidDodecahedron();
        glPopMatrix();

        glPushMatrix(); // The cubic body
        glTranslatef(this->xCoordinate+0.5,this->yCoordinate,this->zCoordinate+0.5);
        glutSolidCube(0.4);
        glPopMatrix();
}

void Attacker::update(){
        this->xCoordinate -= 0.01;
        this->angle += 5;
}

void Attacker::drawWheel(){
        GLUquadricObj* q = gluNewQuadric();
        glPushMatrix();
        glTranslatef(this->xCoordinate, this->yCoordinate, this->zCoordinate+0.1);
        glRotatef(180, 1,0,0);
        glRotatef(angle,0,0,1);
        gluDisk(q, 0.0f, 0.1, 15, 1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(this->xCoordinate, this->yCoordinate, this->zCoordinate+0.1);
        glRotatef(angle,0,0,1);
        gluCylinder(q,0.1,0.1,0.1,15,15);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(this->xCoordinate, this->yCoordinate, this->zCoordinate+0.2);
        glRotatef(180, 1,0,0);
        glRotatef(angle,0,0,1);
        gluDisk(q, 0.0f, 0.1, 15, 1);
        glPopMatrix();

}
