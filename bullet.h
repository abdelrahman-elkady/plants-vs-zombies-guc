#include <GL/glut.h>
#include <iostream>
#include "drawable.h"

#ifndef BULLET_H
#define  BULLET_H

class Bullet : public Drawable {
public:
        bool visible;
        Bullet(float xCoordinate,float yCoordinate,float zCoordinate){
                this->xCoordinate=xCoordinate;
                this->yCoordinate=yCoordinate;
                this->zCoordinate=zCoordinate;
                this->visible = true;
        }
        virtual void draw();
        virtual void update();
};

#endif
