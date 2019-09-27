#include<draw.h>
#include <stdio.h>


//global variables
double a_t,b_t,c_t,e1_t,e2_t;

GLfloat angle = 90;

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

	glPushMatrix();
	glLoadIdentity();
	glScalef(2.0, 2.0, 2.0);
	glRotatef(angle, 1.0, 0.0, 0.0);

	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glColor4f(0.0, 0.0, 0.75, 0.5);
	glLineWidth(2.0);

	DrawEllipsoid(20, 20, a_t, b_t, c_t, e1_t, e2_t);

	glPopMatrix();
	glutSwapBuffers();
}

int main(int argc, char** argv){

	if(argc < 5){
		fprintf(stderr, "main: invalid argument!\n");
		printf("usage: %s [a] [b] [c] [e1] [e2]..\n", argv[0]);
		return -1;
	}

	a_t = atof(argv[1]);
	b_t = atof(argv[2]);
	c_t = atof(argv[3]);
	e1_t = atof(argv[4]);
	e2_t = atof(argv[5]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(400, 35);
	glutCreateWindow("superquadrics modelization");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutMainLoop();
	return 0;
}