#include <GL/glut.h>
#include <iostream>
#include "gatherer.h"
using namespace std;

void Gatherer::draw(){

        glPushMatrix(); // Spring drawing
        glTranslatef(this->xCoordinate+0.5,0.3,this->zCoordinate+0.5);// TODO: link coordinates with index on grid
        float height = 0;
        for (int i = 0; i < 150; i+=1) {
                glPushMatrix();
                glColor3f(0.56,0.2147,0.0);
                glRotatef(this->angle,0,1,0);
                glTranslatef(0.0,height,0.0);
                glRotatef(8*i,0,1,0);
                glTranslatef(0.1,0.0,0.0);
                glutSolidSphere(0.03,15,15);
                height+=0.007;
                glPopMatrix();
        }
        glPopMatrix(); // End Spring drawing

        glPushMatrix(); // Icosahedron drawing
        glColor3f(1.0,0.843137255,0.0);
        glTranslatef(this->xCoordinate+0.5,0.3+height,this->zCoordinate+0.5);
        glRotatef(this->angle,0,1,0);
        glScalef(0.17,0.17,0.17);
        glutSolidIcosahedron();
        glPopMatrix(); // End Icosahedron drawing

}

void Gatherer::update(){
        this->angle -= 2.5;
}
