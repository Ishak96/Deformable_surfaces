#include <draw.h>
#include <camera.h>
#include <util.h>
#include <cloud.h>
#include <stdio.h>

extern float zoom_x, zoom_y;
extern int aff; 

//global variables
CLOUD cloud;
SUPERQUADRIC superquadric;
PARAMETERS parameters;

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

	glPushMatrix();
		
		if(aff == 1) {
			draw_cloud(cloud, 1, 0, 0);
		}
		
		glTranslatef(parameters.tx, parameters.ty, 0);
		glRotatef(parameters.angle, 1.0f, 0.0f, 0.0f);
		
		draw_SUPERQUADRIC(superquadric);
	
	glPopMatrix();
	
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char** argv){

	if(argc < 2){
		fprintf(stderr, "main: invalid argument!\n");
		printf("usage: %s [data file]\n", argv[0]);
		return -1;		
	}

	float fact = 0.3;

	cloud = get_cloud_point(argv[1], fact);

	parameters =  initial_parameters(cloud);

	int length = 15;

	float phi[2];
	float theta[2];
	default_PHIvect_THETAvect(phi, theta);

	superquadric = create_superquadrics(parameters.a1, parameters.a2,
										parameters.e, length, theta);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(50, 50);
	glutCreateWindow("superquadrics modelization");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(camera_keyboard);

	glutMainLoop();

	freeCLOUD(&cloud);
	destroy_superquadrics(&superquadric);
	return 0;
}