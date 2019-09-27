#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void idle();
void specialKeyboard(int key, int x, int y);
void mouse(int button, int state, int x, int y);
void mouseMotion(int x, int y);
void keyboard(unsigned char key, int x, int y);

#endif
