#ifndef CAMERA_H
#define CAMERA_H

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

void camera_idle();
void camera_specialKeyboard(int key, int x, int y);
void camera_mouse(int button, int state, int x, int y);
void camera_mouseMotion(int x, int y);
void camera_keyboard(unsigned char key, int x, int y);

#endif
