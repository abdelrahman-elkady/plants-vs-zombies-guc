#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <stddef.h>

#include "camera.h"
#include "tile.h"
#include "gatherer.h"
#include "defender.h"
#include "bullet.h"
#include "appconstants.h"

using namespace std;

void timer(int);
void keyboardHandler(unsigned char, int, int );
void drawAxes();

const int FPS = 33;


Camera* camera = new Camera(7.0,7.0,7.0,0.0,0.0,0.0);
Gatherer* gatherer1 = new Gatherer(0.0,0.0,0.0);
Gatherer* gatherer2 = new Gatherer(1.0,0.0,0.0);
Gatherer* gatherer3 = new Gatherer(0.0,0.0,1.0);
Defender* defender1 = new Defender(2.0,0.0,0.0);
Defender* defender2 = new Defender(2.0,0.0,4.0);

Tile grid[5][7];

bool paused = false;

float xZoomUnit = 0.2;

void render(void) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera->activate();

        glPushMatrix(); // camera

        camera->rotateCamera(false,true,false);
        drawAxes();

        glColor3f(0.0,0.5,0.0);

        // Grid drawing
        // Note that grid is 0.5+ in y direction
        for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 7; j++) {
                        glPushMatrix();
                        glTranslatef(j,0,i);
                        if((i%2==0 && j%2 ==0) || (i%2==1 && j%2 ==1)) {
                                glColor3f(0.0,0.4,0.0);
                        }else{
                                glColor3f(0.0,0.5,0.0);
                        }
                        grid[i][j].draw();
                        glPopMatrix();
                }
        }
        // End Grid drawing

        glColor3f(1.0,0.1,0.1);
        for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 7; j++) {
                        if(grid[i][j].drawableObject != NULL) {
                                grid[i][j].drawableObject->draw();
                        }
                }
        }

        glPopMatrix(); // end camera

        glutSwapBuffers();
}

void timer(int t) {

        if(!paused) {

                camera->setXAngle(camera->getXAngle() + 0.5);
                camera->setYAngle(camera->getYAngle() + 0.5);
                camera->setZAngle(camera->getZAngle() + 0.5);


                for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 7; j++) {
                                if(grid[i][j].drawableObject != NULL) {
                                        grid[i][j].drawableObject->update();
                                }
                        }
                }
        }

        glutPostRedisplay();
        glutTimerFunc(FPS, timer, 0);
}

void keyboardHandler(unsigned char key, int x, int y){

        if(key == Z_KEY) {
                camera->setXCoordinate(camera->getXCoordinate()+0.5);
                camera->setYCoordinate(camera->getYCoordinate()+0.5);
                camera->setZCoordinate(camera->getZCoordinate()+0.5);
        }
        if(key == A_KEY) {
                camera->setXCoordinate(camera->getXCoordinate()-0.5);
                camera->setYCoordinate(camera->getYCoordinate()-0.5);
                camera->setZCoordinate(camera->getZCoordinate()-0.5);
        }

        if(key == P_KEY) {
                paused = !paused;
        }

}

void drawAxes(void){
        glPushMatrix();

        glLineWidth(2.0);

        glBegin(GL_LINES);
        glColor3f(1,0,0); // x axis is red.
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(500.0f,0.0f,0.0f);
        glColor3f(0,1,0); // y axis is green.
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,500.0f,0.0f);
        glColor3f(0,0,1); // z axis is blue.
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,500.0f);
        glEnd();

        glPopMatrix ();
}

void initLighting(){
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glEnable(GL_NORMALIZE);
        glEnable(GL_COLOR_MATERIAL);
        glEnable(GL_SMOOTH);
        glShadeModel(GL_SMOOTH);
}

int main(int argc, char** argv) {
        glutInit(&argc, argv);

        glutInitWindowSize(800, 600);
        glutInitWindowPosition(150, 150);

        glutCreateWindow("Plants vs Zombies");
        glutDisplayFunc(render);
        glutTimerFunc(0, timer, 0);
        glutKeyboardFunc(keyboardHandler);

        glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

        glEnable(GL_DEPTH_TEST);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, 800 / 600, 0.1f, 300.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0f, 2.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

        initLighting();

        grid[0][0].drawableObject = gatherer1;
        grid[0][1].drawableObject = gatherer2;
        grid[1][0].drawableObject = gatherer3;
        grid[0][2].drawableObject = defender1;
        grid[4][2].drawableObject = defender2;

        glutMainLoop();

        return 0;
}
