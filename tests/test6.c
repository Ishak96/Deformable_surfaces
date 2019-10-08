#include<draw.h>
#include <camera.h>
#include <cloud.h>
#include <stdio.h>

extern float xrot, yrot;
extern float zoom_x, zoom_y;
extern int aff;

//global variables
double a_t,b_t,c_t,e1_t,e2_t;
float** cloud;
int size = 0;
int initial = 0;
float a_i, b_i, c_i, e1_i, e2_i, tx, ty, tz, angle1_i, angle2_i, angle3_i;

GLfloat angle = 90;

double m_t = 25.f;
double n_t = 25.f;
summit** sum_t;

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

	if(size == 0)
		cloud = generate_cloud_point(70, 70, a_t, b_t, c_t, e1_t, e2_t, &size);
	
	float color[3] = {1.0, 0.0, 0.0};
	draw_cloud_point(cloud, size, color);

	if(!initial){
		float* initial_values = initial_parameters(cloud, size);
		
		if(initial_values != NULL){
			e1_i = initial_values[0];
			e2_i = initial_values[1];
			tx = initial_values[2];
			ty = initial_values[3];
			tz = initial_values[4];
			angle1_i = initial_values[5];
			angle2_i = initial_values[6];
			angle3_i = initial_values[7];
			a_i = initial_values[8];
			b_i = initial_values[9];
			c_i = initial_values[10];

			double** values = discretization(-PI, PI, -PI, PI, m_t, n_t);
			sum_t = summit_building(a_i, b_i, c_i, e1_i, e2_i, m_t, n_t, values);

		
			glTranslatef(tx, ty, tz);
			glRotatef(angle1_i, 1.0f, 0.0f, 0.0f);
			glRotatef(angle2_i, 0.0f, 1.0f, 0.0f);
			glRotatef(angle3_i, 0.0f, 0.0f, 1.0f);

			draw_superquadrics(sum_t, m_t, n_t);

			initial = 1;
		}
	}
	else
		if(aff == 1)
			draw_superquadrics(sum_t, m_t, n_t);


	glPopMatrix();
	glFlush();
	glutSwapBuffers();
}

int main(int argc, char** argv){
	int H, W;
	getScreenSize(&H, &W);

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
	glutInitWindowSize(H, W);
	glutInitWindowPosition(400, 35);
	glutCreateWindow("superquadrics modelization");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutSpecialFunc(camera_specialKeyboard);
	glutMouseFunc(camera_mouse);
	glutMotionFunc(camera_mouseMotion);
	glutKeyboardFunc(camera_keyboard);

	glutMainLoop();
	return 0;
}