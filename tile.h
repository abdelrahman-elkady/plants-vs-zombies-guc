#include <GL/glut.h>
#include <iostream>

#ifndef TILE_H
#define  TILE_H

class Tile {
private:
        float width,height;
public:

        Tile(float width=1,float height=1) {
                this->width = width;
                this->height = height;
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
