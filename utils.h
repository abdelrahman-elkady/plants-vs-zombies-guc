#ifndef APP_CONSTANTS_H
#define  APP_CONSTANTS_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <GL/glut.h>

using namespace std;

#include "bullet.h"

#define SPACEBAR 32
#define Z_KEY 122
#define A_KEY 97
#define P_KEY 112
#define D_KEY 100
#define R_KEY 114
#define C_KEY 99
#define V_KEY 118

#define NUM_1 49
#define NUM_2 50
#define NUM_3 51
#define NUM_4 52
#define NUM_5 53
#define NUM_6 54
#define NUM_7 55
#define NUM_8 56
#define NUM_9 57


const int GRID_MAX_CELL_LENGTH = 4;
const int GRID_MAX_CELL_WIDTH = 8;

const int ROW_SELECTION = 0;
const int COLUMN_SELECTION = 1;
const int TYPE_SELECTION = 2;

inline int keyToNumeric(unsigned char key) {
        switch (key) {
        case NUM_1:
                return 1;
        case NUM_2:
                return 2;
        case NUM_3:
                return 3;
        case NUM_4:
                return 4;
        case NUM_5:
                return 5;
        case NUM_6:
                return 6;
        case NUM_7:
                return 7;
        case NUM_8:
                return 8;
        case NUM_9:
                return 9;
        default:
                return -1;
        }
}

inline int generateRandom(int min,int max){
        return int(min + (rand() % (int)(max - min + 1)));
}

#endif
