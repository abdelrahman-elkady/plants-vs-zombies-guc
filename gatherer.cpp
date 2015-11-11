#include <GL/glut.h>
#include <iostream>
#include "gatherer.h"
using namespace std;

void Gatherer::draw(){
        glPushMatrix();
        glTranslatef(this->xCoordinate+0.5,0.5,this->zCoordinate+0.5);// TODO: link coordinates with index on grid
        float height = 0;
        for (int i = 0; i < 200; i+=1) {
                glPushMatrix();
                glTranslatef(0.0,height,0.0);
                glRotatef(7*i,0,1,0);
                glTranslatef(0.1,0.0,0.0);
                glutSolidSphere(0.02,15,15);
                height+=0.004;
                glPopMatrix();
        }
        glPopMatrix();

        glPushMatrix();
        glTranslatef(this->xCoordinate+0.5,0.5+height,this->zCoordinate+0.5);
        glScalef(0.05,0.05,0.05);
        glutSolidDodecahedron();
        glPopMatrix();
}

void Gatherer::update(){

}
