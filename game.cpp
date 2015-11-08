#include <GL/glut.h>
#include "camera.h"
#include <iostream>

using namespace std;

#define SPACEBAR 32

void timer(int);
void keyboardHandler(unsigned char, int, int );

const int FPS = 33;

float rotAng;

Camera *camera = new Camera(8.0,8.0,8.0);

void Display(void) {
        cout << camera->getXPosition() << endl;
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();
        glRotatef(rotAng, 0, 1, 0);
        glColor3f(0.0f, 0.0f, 0.0f);
        glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
        glRotatef(-rotAng, 0, 1, 0);
        glTranslatef(2, 0, 0);
        glRotatef(rotAng, 1, 0, 0);
        glColor3f(0.5f, 0.5f, 0.5f);
        glutSolidSphere(0.5, 25, 25);
        glPopMatrix();

        glFlush();
}

void timer(int t) {
        rotAng += 1;

        glutPostRedisplay();
        glutTimerFunc(FPS, timer, 0);
}

void keyboardHandler(unsigned char key, int x, int y){
        if(key == SPACEBAR) {
                camera->activate();
        }
}

int main(int argc, char** argv) {
        glutInit(&argc, argv);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);
        glutInitWindowSize(800, 600);
        glutInitWindowPosition(150, 150);

        glutCreateWindow("Plants vs Zombies");
        glutDisplayFunc(Display);
        glutTimerFunc(0, timer, 0);
        glutKeyboardFunc(keyboardHandler);

        glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
        glClearColor(1.0f, 1.0f, 1.0f, 0.0f);

        glEnable(GL_DEPTH_TEST);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(45.0f, 800 / 600, 0.1f, 300.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0f, 2.0f, 5.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

        glutMainLoop();

        return 0;
}
