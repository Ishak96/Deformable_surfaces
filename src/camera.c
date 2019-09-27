#include <camera.h>
#include <stdio.h>

int fullscreen = 0;
int mouseDown = 0;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;

float zoom_x = 0.0;
float zoom_y = 0.0;

void idle(){
	if (!mouseDown){
		xrot += 0.3f;
		yrot += 0.4f;
	}
	glutPostRedisplay();
}

void specialKeyboard(int key, int x, int y){
	if (key == GLUT_KEY_F1){
		fullscreen = !fullscreen;

		if (fullscreen)
			glutFullScreen();
		else{
			glutReshapeWindow(800, 800);
			glutPositionWindow(50, 50);
		}
	}
}

void mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		mouseDown = 1;
		xdiff = x - yrot;
		ydiff = -y + xrot;
	}
	else{
		mouseDown = 0;
	}
}

void mouseMotion(int x, int y){
	if (mouseDown){
		yrot = x - xdiff;
		xrot = y + ydiff;

		glutPostRedisplay();
	}
}

void keyboard(unsigned char key, int x, int y){
	switch (key){
		case 'd':
			zoom_x = zoom_x + 1.0; 
			break; 
		case 'q':
			zoom_x = zoom_x - 1.0; 
			break;
		case 'z':
			zoom_y = zoom_y + 1.0; 
			break;
		case 's':
			zoom_y = zoom_y - 1.0; 
			break;
	};
	glutPostRedisplay();
}
