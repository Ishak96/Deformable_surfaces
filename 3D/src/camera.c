#include <camera.h>
#include <stdio.h>
#include <stdlib.h>

int fullscreen = 0;
int mouseDown = 0;

float xrot = 0.0f;
float yrot = 0.0f;

float xdiff = 0.0f;
float ydiff = 0.0f;

float zoom_x = 0.0;
float zoom_y = 0.0;

int aff = 1;

int deformation_control = 0;

float kx, ky, k, alpha, n;

void camera_idle(){
	if (!mouseDown){
		xrot += 0.3f;
		yrot += 0.4f;
	}
	glutPostRedisplay();
}

void camera_specialKeyboard(int key, int x, int y){
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

void camera_mouse(int button, int state, int x, int y){
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN){
		mouseDown = 1;
		xdiff = x - yrot;
		ydiff = -y + xrot;
	}
	else{
		mouseDown = 0;
	}
}

void camera_mouseMotion(int x, int y){
	if (mouseDown){
		yrot = x - xdiff;
		xrot = y + ydiff;

		glutPostRedisplay();
	}
}

void camera_keyboard(unsigned char key, int x, int y){
	int select;
	switch (key){
		case 'd':
			zoom_x = zoom_x + .5; 
			break; 
		case 'q':
			zoom_x = zoom_x - .5; 
			break;
		case 'z':
			zoom_y = zoom_y + .5; 
			break;
		case 's':
			zoom_y = zoom_y - .5; 
			break;
		case 'a':
			aff = -aff;
			break;
		case 't':
			printf("1)twist or 2)taper:\n");
			scanf("%d", &select);
			if(select == 1){
				deformation_control = 2;
				printf("\nentre n:");
				scanf("%f", &n);
			}
			else{
				deformation_control = 1;
				printf("\nentre kx:");
				scanf("%f", &kx);
				printf("\nentre ky:");
				scanf("%f", &ky);
			}
			break;
		case 'b':
			deformation_control = 3;
			printf("\nentre k:");
			scanf("%f", &k);
			printf("\nentre alpha:");
			scanf("%f", &alpha);
			break;
		case 'r':
			printf("1)taper or 3)bend:\n");
			scanf("%d", &select);
			deformation_control = -select;
			break;
	};
	glutPostRedisplay();
}
