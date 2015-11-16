#include <GL/glut.h>
#include <iostream>
#include "bullet.h"
#include "utils.h"
using namespace std;

void Bullet::draw(){

        if(this->visible) {
                glPushMatrix();
                glColor3f(0.84,0.239,0.1596);
                glTranslatef(this->xCoordinate+0.5,1.4,this->zCoordinate+0.5);
                glutSolidSphere(0.05,15,15);
                glPopMatrix();
        }

}

void Bullet::update(){
        if(this->xCoordinate - 0.5 > GRID_MAX_CELL_WIDTH) {
                this->visible = false;
        }else {
                this->xCoordinate += 0.07;
        }
}
