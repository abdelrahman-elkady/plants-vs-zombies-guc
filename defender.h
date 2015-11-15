#include <GL/glut.h>
#include <iostream>
#include "drawable.h"
#include "bullet.h"

#ifndef DEFENDER_H
#define  DEFENDER_H

class Defender : public Drawable {
public:
        float bulletTimer;
        Bullet* bullet;
        Defender(float xCoordinate,float yCoordinate,float zCoordinate){
                this->xCoordinate=xCoordinate;
                this->yCoordinate=yCoordinate;
                this->zCoordinate=zCoordinate;
                this->bulletTimer = 0;
                bullet = new Bullet(this->xCoordinate,this->yCoordinate,this->zCoordinate);
        }
        virtual void draw();
        virtual void update();
};

#endif
