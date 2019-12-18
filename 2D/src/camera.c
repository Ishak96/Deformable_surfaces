#include <camera.h>
#include <stdio.h>
#include <stdlib.h>

float zoom_x = 0.0;
float zoom_y = 0.0;

int aff = 1;

int deformation_control = 0;

float ky, k, n;

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
				printf("\nentre ky:");
				scanf("%f", &ky);
			}
			break;
		case 'b':
			deformation_control = 3;
			printf("\nentre k:");
			scanf("%f", &k);
			break;
		case 'r':
			printf("1)taper or 3)bend:\n");
			scanf("%d", &select);
			deformation_control = -select;
			break;
	};
	glutPostRedisplay();
}
