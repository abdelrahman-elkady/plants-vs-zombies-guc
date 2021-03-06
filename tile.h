#ifndef TILE_H
#define  TILE_H

#include <GL/glut.h>
#include <iostream>
#include "drawable.h"

class Tile {
private:
        float width,height;
public:
        Drawable* drawableObject;
        bool highlighted;
        bool destroyed;

        Tile(float width=1,float height=1) {
                this->width = width;
                this->height = height;
                this->highlighted = false;
                this->destroyed = false;
        }

        void draw();

        float getWidth(){
                return this->width;
        }
        float getHeight(){
                return this->height;
        }

        void setWidth(float width){
                this->width = width;
        }
        void setHeight(float height){
                this->height = height;
        }

};
#endif
