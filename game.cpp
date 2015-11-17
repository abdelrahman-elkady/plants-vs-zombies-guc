#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <stddef.h>
#include "math.h"

#include "camera.h"
#include "tile.h"
#include "gatherer.h"
#include "defender.h"
#include "bullet.h"
#include "attacker.h"
#include "utils.h"

using namespace std;

void timer(int);
void keyboardHandler(unsigned char, int, int);
void drawAxes();
bool checkBulletCollision(Bullet*,Attacker*);

const int FPS = 33;
int s = 0;

Camera* camera = new Camera(7.0,4.0,7.0,0.0,0.0,0.0);

Tile grid[5][9];
vector<Attacker*> attackers;
bool paused = false;

int selectionMode = ROW_SELECTION;

int selectedRow = -1;
int selectedColumn = -1;

float spawnTimer = 0;
void render(void) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        camera->activate();

        glPushMatrix(); // camera
        camera->rotateCamera(false,true,false);
        drawAxes();

        glTranslatef(-4.5,0.0,-2.5); // Translating the whole scene

        glColor3f(0.0,0.5,0.0);

        // Grid drawing
        // Note that grid is 0.5+ in y direction
        for (int i = 0; i < 5; i++) {
                for (int j = 0; j < 9; j++) {
                        glPushMatrix();
                        glTranslatef(j,0,i);

                        if(grid[i][j].highlighted) {
                                glColor3f(0.2387,0.77,0.7346);
                        }
                        else if((i%2==0 && j%2 ==0) || (i%2==1 && j%2 ==1)) {
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
                for (int j = 0; j < 9; j++) {
                        if(grid[i][j].drawableObject != NULL) {
                                grid[i][j].drawableObject->draw();
                        }
                }
        }

        for(unsigned int i = 0; i != attackers.size(); i++) {
                if(attackers.at(i) != NULL) {
                        glColor3f(attackers.at(i)->health/3.0,0.0,0.0);
                        attackers.at(i)->draw();
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
                        for (int j = 0; j < 9; j++) {
                                if(grid[i][j].drawableObject != NULL) {
                                        grid[i][j].drawableObject->update();
                                }
                        }
                }

                for(unsigned int i = 0; i != attackers.size(); i++) {
                        if(attackers.at(i) != NULL) {
                                for (int j = 0; j < 8; j++) {
                                        int lane = int((attackers.at(i))->zCoordinate);
                                        if(dynamic_cast<Defender*>(grid[lane][j].drawableObject) != NULL ) {
                                                checkBulletCollision((dynamic_cast<Defender*>(grid[lane][j].drawableObject))->bullet,attackers.at(i));
                                                if(attackers.at(i)->health <= 0) {
                                                        attackers.erase(attackers.begin() + i);
                                                }
                                        }
                                }
                        }
                }

                for(unsigned int i = 0; i != attackers.size(); i++) {
                        if(attackers.at(i) != NULL) {
                                attackers.at(i)->update();
                        }
                }

                if(spawnTimer > 8000 + generateRandom(0,2000)) { // Random generation period ( +- 2 seconds )
                        attackers.push_back(new Attacker(generateRandom(0,4)));
                        spawnTimer = 0;
                }
                spawnTimer += 33;
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

        if(selectionMode == ROW_SELECTION) {
                if(key >= NUM_1 && key <= NUM_5) {
                        selectedRow = keyToNumeric(key) - 1;
                        selectionMode = COLUMN_SELECTION;
                }
        } else if (selectionMode == COLUMN_SELECTION) {
                if(key >= NUM_1 && key <= NUM_9) {
                        selectedColumn = keyToNumeric(key) - 1;
                        selectionMode = TYPE_SELECTION;
                        grid[selectedRow][selectedColumn].highlighted = true;
                }
        }else if (selectionMode == TYPE_SELECTION) {
                if(key == D_KEY) {
                        grid[selectedRow][selectedColumn].drawableObject = new Defender(selectedColumn,0,selectedRow);
                        selectionMode = ROW_SELECTION;
                        grid[selectedRow][selectedColumn].highlighted = false;
                        selectedRow = -1;
                        selectedColumn = -1;
                } else if (key == R_KEY) {
                        grid[selectedRow][selectedColumn].drawableObject = new Gatherer(selectedColumn,0,selectedRow);
                        selectionMode = ROW_SELECTION;
                        grid[selectedRow][selectedColumn].highlighted = false;
                        selectedRow = -1;
                        selectedColumn = -1;
                } else if (key == C_KEY) {
                        grid[selectedRow][selectedColumn].drawableObject = NULL;
                        selectionMode = ROW_SELECTION;
                        grid[selectedRow][selectedColumn].highlighted = false;
                        selectedRow = -1;
                        selectedColumn = -1;
                }
        }

}

bool checkBulletCollision(Bullet* bullet,Attacker* attacker) {
        if ( bullet->visible && (bullet->zCoordinate) == (attacker->zCoordinate) && fabs(bullet->xCoordinate - attacker->xCoordinate) <= 0.2 ) {
                bullet->visible = false;
                attacker->health--;
        }
        return false;
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

        glutMainLoop();

        return 0;
}
