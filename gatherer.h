#include <GL/glut.h>
#include <iostream>
#include "drawable.h"

#ifndef GATHERER_H
#define  GATHERER_H

class Gatherer : public Drawable {
private:
        float angle;
public:
        Gatherer(float xCoordinate,float yCoordinate,float zCoordinate){
                this->xCoordinate=xCoordinate;
                this->yCoordinate=yCoordinate;
                this->zCoordinate=zCoordinate;
                this->angle = 0;
        }
        virtual void draw();
        virtual void update();
};

#endif
