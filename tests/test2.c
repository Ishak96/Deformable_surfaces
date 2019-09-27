#include<draw.h>
#include <stdio.h>


//global variables
double m_t = 30.f;
double n_t = 30.f;
double a_t,b_t,c_t,p_t,q_t;
summit** sum_t;

float zoom_x = 0.0, zoom_y = 0.0, zoom_z = 0.0;
float rot_x = 0.0, rot_y = 0.0, rot_z = 0.0, zRot = 0.0;
float xstart, ystart;

float Talal = 0.01;
int main_window;

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

	glPushMatrix();
		glTranslatef(zoom_x, zoom_y, zoom_z);			// translate projection in x,y,z space
		glRotatef(rot_x, 1.0f, 0.0f, 0.0f);				// rotate projection around x-axis
		glRotatef(rot_y, 0.0f, 1.0f, 0.0f);				// rotate projection around y-axis
		glRotatef(rot_z, 0.0f, 0.0f, 1.0f);	
		

		double** values = discretization(-PI, PI, -PI, PI, m_t, n_t);
		sum_t = summit_building(a_t, b_t, c_t, p_t, q_t, m_t, n_t, values);
		draw_superquadrics(sum_t, m_t, n_t);

	glPopMatrix();
	glutSwapBuffers();
}

// Custom transitions using the keyboard
void myKeyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'w':  zoom_x = zoom_x + 0.1; break; case 'q':  zoom_x = zoom_x - 0.1; break;
		case 's':  zoom_y = zoom_y + 0.1; break; case 'a':  zoom_y = zoom_y - 0.1; break;
		case 'x':  zoom_z = zoom_z + 0.1; break; case 'z':  zoom_z = zoom_z - 0.1; break;
		
		case 'r':  rot_x = rot_x + 1; break; case 'e':  rot_x = rot_x - 1; break;
		case 'f':  rot_y = rot_y + 1; break; case 'd':  rot_y = rot_y - 1; break;
		case 'v':  rot_z = rot_z + 1; break; case 'c':  rot_z = rot_z - 1; break;

	};
	glutPostRedisplay();
}

// Custom Translation in (x,y)
void myMouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		xstart = (float)x;
		ystart = (float)y;
	};
}

// Custom Translation in (x,y)
void myMotion(int x, int y)
{
	rot_x = zoom_x + (x - xstart) * 0.002;
	rot_y = zoom_y + (ystart - y) * 0.002;
	glutPostRedisplay();
	xstart = (float)x;
	ystart = (float)y;
}

// Rotation variable incrementation
void myIdle()
{
	zRot = zRot + Talal;
	if ( glutGetWindow() != main_window ) 
		glutSetWindow(main_window);  
	glutPostRedisplay();
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
	p_t = atof(argv[4]);
	q_t = atof(argv[5]);

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 800);
	glutInitWindowPosition(400, 35);
	main_window = glutCreateWindow("superquadrics modelization");

	init();

	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(myKeyboard);
	glutMouseFunc(myMouse);
	glutMotionFunc(myMotion);
	glutIdleFunc(myIdle);
	glutMainLoop();
	return 0;
}