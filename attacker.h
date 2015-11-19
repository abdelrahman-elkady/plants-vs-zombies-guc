#ifndef ATTACKER_H
#define  ATTACKER_H

#include <GL/glut.h>
#include <iostream>
#include "drawable.h"
#include "utils.h"

class Attacker : public Drawable {
private:
        void drawWheel();
        float angle;
public:
        int health;
        bool visible;
        Attacker(float zCoordinate){
                this->xCoordinate=GRID_MAX_CELL_WIDTH;
                this->yCoordinate=0.8;
                this->zCoordinate=zCoordinate;
                this->health = 3;
                this->angle=0;
                this->visible = true;
        }
        Attacker(){
                this->xCoordinate=GRID_MAX_CELL_WIDTH;
                this->yCoordinate=0.8;
                this->zCoordinate=0;
                this->health = 3;
                this->angle=0;
                this->visible = false;
        }
        virtual void draw();
        virtual void update();
};
#endif
