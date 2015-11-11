#include <GL/glut.h>
#include "tile.h"

void Tile::draw(){
        // glBegin(GL_QUADS);
        // glVertex3f(0,0,0);
        // glVertex3f(this->width,0,0);
        // glVertex3f(this->width,0,this->height);
        // glVertex3f(0,0,this->height);
        // glEnd();
        glPushMatrix();
        glScalef(1,0.5,1);
        glTranslatef(0.5,0.5,0.5);
        glutSolidCube(1);
        glPopMatrix();
}
