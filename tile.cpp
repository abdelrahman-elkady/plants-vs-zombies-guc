#include <GL/glut.h>
#include "tile.h"

void Tile::draw(){
        glScalef(1,0.5,1);
        glTranslatef(0.5,0.5,0.5);
        glutSolidCube(1);
}
