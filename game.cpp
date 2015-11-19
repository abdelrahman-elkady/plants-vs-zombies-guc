#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
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
bool checkUnitCollision(Drawable*, Attacker*);
void drawBitmapText(string, float, float, float);

const int FPS = 33;

Camera* camera = new Camera(0.0,10.0,10.0,0.0,0.0,0.0);

Tile grid[5][9];
Attacker* attackers[50];

bool paused = false;
bool cinematic = false;
bool gameOver = false;

int selectionMode = ROW_SELECTION;

int selectedRow = -1;
int selectedColumn = -1;

float spawnTimer = 0;
int kills = 0;
float resources = 500;
int lanesDestroyed = 0;
int resourceGatherers=0;


namespace patch
{
template < typename T > std::string to_string( const T& n )
{
        std::ostringstream stm;
        stm << n;
        return stm.str();
}
}


void render(void) {

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        if(!gameOver) {
                drawBitmapText("Cost of Defender --> 150 ", 0.5, 11.5, 0);
                drawBitmapText("Cost of Resource Gatherer --> 100 ", 0.5, 11.0, 0);
                drawBitmapText("Resources " + patch::to_string(int(resources)), 0.5, 10.5, 0);
                drawBitmapText("Killed Zombies " + patch::to_string(int(kills)), 3, 10.5, 0);
        }else {
                if(lanesDestroyed >= 3) {
                        drawBitmapText("The zombies ate your brains! ", 0.5, 11.5, 0);
                }else {
                        drawBitmapText("You survived the Zombie attack !", 0.5, 11.5, 0);
                }
        }

        camera->activate();

        glPushMatrix();         // camera
        if(cinematic) {
                camera->rotateCamera(false,true,false);
        }

        glTranslatef(-4.5,0.0,-2.5);         // Translating the whole scene

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

        for(unsigned int i = 0; i < 50; i++) {
                if(attackers[i] != NULL) {
                        attackers[i]->draw();
                }
        }

        glPopMatrix();         // end camera


        glutSwapBuffers();
}

void timer(int t) {
        if(lanesDestroyed >= 3 || kills >= 50) {
                gameOver = true;
                glutPostRedisplay();
                return;
        }
        if(!paused) {

                if(cinematic) {
                        camera->setXAngle(camera->getXAngle() + 0.5);
                        camera->setYAngle(camera->getYAngle() + 0.5);
                        camera->setZAngle(camera->getZAngle() + 0.5);
                } else {
                        camera->setXAngle(0.0);
                        camera->setYAngle(0.0);
                        camera->setZAngle(0.0);
                }


                for (int i = 0; i < 5; i++) {
                        for (int j = 0; j < 9; j++) {
                                if(grid[i][j].drawableObject != NULL) {
                                        grid[i][j].drawableObject->update();
                                }
                        }
                }

                for(unsigned int i = 0; i < 50; i++) {
                        if(attackers[i] != NULL) {

                                if( attackers[i]->visible && attackers[i]->xCoordinate <= -0.5) {
                                        int lane = int((attackers[i])->zCoordinate);
                                        attackers[i]->visible = false;

                                        // removing units on lane
                                        for (int k = 0; k < 9; k++) {
                                                grid[lane][k].destroyed = true;
                                                grid[lane][k].drawableObject = NULL;
                                        }

                                        // removing attackers on lane
                                        for (int k = 0; k < 50; k++) {
                                                if(attackers[k] != NULL && int(attackers[k]->zCoordinate) == lane) {
                                                        attackers[k]->visible = false;
                                                }
                                        }


                                        lanesDestroyed++;
                                }

                                for (int j = 0; j < 9; j++) {
                                        int lane = int((attackers[i])->zCoordinate);
                                        if(dynamic_cast<Defender*>(grid[lane][j].drawableObject) != NULL ) {
                                                if(checkBulletCollision((dynamic_cast<Defender*>(grid[lane][j].drawableObject))->bullet,attackers[i])) {
                                                        if(attackers[i]->health <= 0) {
                                                                kills++;
                                                                resources += 50;
                                                                attackers[i]->visible = false;
                                                        }
                                                }
                                        }

                                        if(grid[lane][j].drawableObject != NULL) {
                                                if(checkUnitCollision((grid[lane][j].drawableObject),attackers[i])) {
                                                        if(dynamic_cast<Gatherer*>(grid[lane][j].drawableObject) != NULL) {
                                                                resourceGatherers--;
                                                        }
                                                        grid[lane][j].drawableObject = NULL;
                                                }
                                        }
                                }
                        }
                }

                for(unsigned int i = 0; i < 50; i++) {
                        if(attackers[i] != NULL) {
                                attackers[i]->update();
                        }
                }

                if(spawnTimer > 8000 + generateRandom(0,2000)) { // Random generation period ( +- 2 seconds )
                        for (int i = 0; i < 50; i++) {
                                int lane = generateRandom(0,4);
                                if((attackers[i] == NULL || !attackers[i]->visible) && !grid[lane][0].destroyed) {
                                        attackers[i] = new Attacker(lane);
                                        spawnTimer = 0;
                                        break;
                                }
                        }

                }

                resources += 0.13 * resourceGatherers;

                spawnTimer += 33;

        }

        glutPostRedisplay();
        glutTimerFunc(FPS, timer, 0);
}

void keyboardHandler(unsigned char key, int x, int y){

        if(key == Z_KEY && !cinematic) {
                camera->setYCoordinate(camera->getYCoordinate()+0.5);
                camera->setZCoordinate(camera->getZCoordinate()+0.5);
        }
        if(key == A_KEY && !cinematic) {
                camera->setYCoordinate(camera->getYCoordinate()-0.5);
                camera->setZCoordinate(camera->getZCoordinate()-0.5);
        }

        if(key == V_KEY) {
                cinematic = !cinematic;
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
                if(key == D_KEY && !grid[selectedRow][selectedColumn].destroyed && resources >= 150 && grid[selectedRow][selectedColumn].drawableObject == NULL) {
                        grid[selectedRow][selectedColumn].drawableObject = new Defender(selectedColumn,0,selectedRow);
                        resources -= 150;
                        selectionMode = ROW_SELECTION;
                        grid[selectedRow][selectedColumn].highlighted = false;
                        selectedRow = -1;
                        selectedColumn = -1;
                } else if (key == R_KEY && !grid[selectedRow][selectedColumn].destroyed && resources >= 100 && grid[selectedRow][selectedColumn].drawableObject == NULL) {
                        grid[selectedRow][selectedColumn].drawableObject = new Gatherer(selectedColumn,0,selectedRow);
                        resourceGatherers++;
                        resources -= 100;
                        selectionMode = ROW_SELECTION;
                        grid[selectedRow][selectedColumn].highlighted = false;
                        selectedRow = -1;
                        selectedColumn = -1;
                } else if (key == C_KEY && !grid[selectedRow][selectedColumn].destroyed) {
                        grid[selectedRow][selectedColumn].drawableObject = NULL;
                        selectionMode = ROW_SELECTION;
                        grid[selectedRow][selectedColumn].highlighted = false;
                        selectedRow = -1;
                        selectedColumn = -1;
                }else {
                        selectionMode = ROW_SELECTION;
                        grid[selectedRow][selectedColumn].highlighted = false;
                        selectedRow = -1;
                        selectedColumn = -1;
                }
        }

}

bool checkBulletCollision(Bullet* bullet,Attacker* attacker) {
        if (bullet->visible && attacker->visible && (bullet->zCoordinate) == (attacker->zCoordinate) && fabs(bullet->xCoordinate - attacker->xCoordinate) <= 0.2 ) {
                bullet->visible = false;
                attacker->health--;
                return true;
        }
        return false;
}

bool checkUnitCollision(Drawable* object, Attacker* attacker) {
        if(attacker->visible && attacker->zCoordinate == object->zCoordinate && fabs(attacker->xCoordinate - object->xCoordinate) <= 0.3 ) {
                return true;
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



void drawBitmapText(string text, float x, float y, float z)
{
        glDisable(GL_TEXTURE_2D);
        glMatrixMode( GL_PROJECTION );
        glPushMatrix();
        glLoadIdentity();
        gluOrtho2D(0.0, 800, 0.0, 600);
        glMatrixMode( GL_MODELVIEW );
        glPushMatrix();
        glLoadIdentity();

        glDisable( GL_DEPTH_TEST );
        glDisable(GL_LIGHTING);

        glColor3f(1.0, 0.0, 0.0);
        glRasterPos2i(x*50, y*50);

        for (unsigned int i = 0; i < text.size(); i++)
        {
                glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, text[i]);
        }

        glEnable( GL_DEPTH_TEST );
        glEnable(GL_LIGHTING);
        glMatrixMode( GL_PROJECTION );
        glPopMatrix();
        glMatrixMode( GL_MODELVIEW );
        glPopMatrix();

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
