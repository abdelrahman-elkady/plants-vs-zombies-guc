#include <GL/glut.h>
#include <iostream>
#include "drawable.h"
#include "appconstants.h"

#ifndef ATTAKER_H
#define  ATTAKER_H

class Attacker : public Drawable {
private:
        void drawWheel();
        float angle;
public:
        int health;
        Attacker(float zCoordinate){
                this->xCoordinate=GRID_MAX_CELL_WIDTH;
                this->yCoordinate=0.8;
                this->zCoordinate=zCoordinate;
                this->health = 3;
                this->angle=0;
        }
        virtual void draw();
        virtual void update();
};
#endif
