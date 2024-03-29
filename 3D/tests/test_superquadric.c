#include <draw.h>
#include <camera.h>
#include <util.h>
#include <stdio.h>

extern float xrot, yrot;
extern float zoom_x, zoom_y;

//global variables
SUPERQUADRIC superquadric;

void init(void){
	glClearColor(0, 0, 0, 0);
	glClearDepth(1.0);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
}

void reshape(int w, int h){
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-50.0, 50.0, -25.0, 75.0, -100.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void display(void){

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glColor3d(1,0,0);

	glLoadIdentity();	
	glScalef(2.0, 2.0, 2.0);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor4f(0.0, 0.0, 0.75, 0.5);
	glLineWidth(2.0);
	
	glTranslatef(zoom_x, zoom_y, 0.0);
	glRotatef(xrot, 1.0f, 0.0f, 0.0f);
	glRotatef(yrot, 0.0f, 1.0f, 0.0f);

	glPushMatrix();
		draw_SUPERQUADRIC(superquadric);
	glPopMatrix();
	
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char** argv){

	if(argc < 6){
		fprintf(stderr, "main: invalid argument!\n");
		printf("usage: %s [a] [b] [c] [e1] [e2]\n", argv[0]);
		return -1;
	}

	int parallels = 30;
	int meridians = 30;

	float a = atof(argv[1]);
	float b = atof(argv[2]);
	float c = atof(argv[3]);
	float e1 = atof(argv[4]);
	float e2 = atof(argv[5]);

	float phi[2];
	float theta[2];
	default_PHIvect_THETAvect(phi, theta);	

	superquadric = create_superquadrics(a, b, c, e1, e2,
								  		parallels, meridians,
								  		phi, theta);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("superquadrics modelization");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(camera_specialKeyboard);
	glutMouseFunc(camera_mouse);
	glutMotionFunc(camera_mouseMotion);
	glutKeyboardFunc(camera_keyboard);

	glutMainLoop();

	destroy_superquadrics(&superquadric);
	return 0;
}