#include<draw.h>

void draw_superquadrics(superquadrics forme){
	glColor3f(r, g, b);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	summit* sum = forme.summits;
	int** facade = forme.facade;
	int size = forme.size;

	for(int i = 0; i < size-1; i+=2){
		glBegin(GL_TRIANGLE_STRIP);
			glVertex3f(sum[facade[i][0]].x,sum[facade[i][0]].y,sum[facade[i][0]].z);
			glVertex3f(sum[facade[i][1]].x,sum[facade[i][1]].y,sum[facade[i][1]].z);
			glVertex3f(sum[facade[i][2]].x,sum[facade[i][2]].y,sum[facade[i][2]].z);

			glVertex3f(sum[facade[i+1][0]].x,sum[facade[i+1][0]].y,sum[facade[i+1][0]].z);
			glVertex3f(sum[facade[i+1][1]].x,sum[facade[i+1][1]].y,sum[facade[i+1][1]].z);
			glVertex3f(sum[facade[i+1][2]].x,sum[facade[i+1][2]].y,sum[facade[i+1][2]].z);
		glEnd();
	}
}

void draw_debug(superquadrics forme){
	glColor3f(r, g, b);
	glPointSize(2);
	
	glBegin(GL_POINTS);
	
	summit* sum = forme.summits;
	int** facade = forme.facade;
	int size = forme.size;

	for(int i = 0; i < size; i++){
		glVertex3f(sum[facade[i][0]].x,sum[facade[i][0]].y,sum[facade[i][0]].z);
		glVertex3f(sum[facade[i][1]].x,sum[facade[i][1]].y,sum[facade[i][1]].z);
		glVertex3f(sum[facade[i][2]].x,sum[facade[i][2]].y,sum[facade[i][2]].z);
	}

	glEnd();
}

void DrawEllipsoid(unsigned int uiStacks, unsigned int uiSlices, float fA, float fB, float fC, float e1, float e2){
	float tStep = (PI) / (float)uiSlices;
	float sStep = (PI) / (float)uiStacks;
	
	glColor3f(r, g, b);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for(float t = -PI; t <= (PI)+.0001; t += tStep)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for(float s = -PI; s <= PI+.0001; s += sStep)
		{
			glVertex3f(fA * fexp(cos(t), e1) * fexp(cos(s), e2), fB * fexp(cos(t), e1) * fexp(sin(s), e2), fC * fexp(sin(t), e1));
			glVertex3f(fA * fexp(cos(t+tStep), e1) * fexp(cos(s), e2), fB * fexp(cos(t+tStep), e1) * fexp(sin(s), e2), fC * fexp(sin(t+tStep), e1));
		}
		glEnd();
	}
}

void DrawEllipsoid_cloud(unsigned int uiStacks, unsigned int uiSlices, float fA, float fB, float fC, float e1, float e2){
	float tStep = (PI) / (float)uiSlices;
	float sStep = (PI) / (float)uiStacks;
	
	glColor3f(r, g, b);
	glPointSize(2);
	glBegin(GL_POINTS);
	for(float t = -PI; t <= (PI)+.0001; t += tStep)
	{
		for(float s = -PI; s <= PI+.0001; s += sStep)
		{
			glVertex3f(fA * fexp(cos(t), e1) * fexp(cos(s), e2), fB * fexp(cos(t), e1) * fexp(sin(s), e2), fC * fexp(sin(t), e1));
			glVertex3f(fA * fexp(cos(t+tStep), e1) * fexp(cos(s), e2), fB * fexp(cos(t+tStep), e1) * fexp(sin(s), e2), fC * fexp(sin(t+tStep), e1));
		}
	}
	glEnd();
}

void draw_cloud_point(float** cloud, int size, float* color){

	if( cloud == NULL || color == NULL ){
		fprintf(stderr, "draw_cloud_point: invalid argument!\n");
	}

	glColor3f(color[0], color[1], color[2]);	
	glPointSize(POINTS_SIZE);
	glBegin(GL_POINTS);
	
	for(int i = 0; i <= size; i++){
		glVertex3f(cloud[i][0], cloud[i][1], cloud[i][2]);
	}
	
	glEnd();
}

int getRootWindowSize(int *w, int *h){
	Display* pdsp = NULL;
	Window wid = 0;
	XWindowAttributes xwAttr;

	pdsp = XOpenDisplay(NULL);
	if(!pdsp) {
		fprintf(stderr, "Failed to open default display.\n");
		return -1;
	}

	wid = DefaultRootWindow(pdsp);
	if(0 > wid){
		fprintf(stderr, "Failed to obtain the root windows Id of the default screen of given display.\n");
		return -2;
	}
 
	XGetWindowAttributes(pdsp, wid, &xwAttr);
	*w = xwAttr.width;
	*h = xwAttr.height;

	XCloseDisplay(pdsp);
	return 0;
}

int getScreenSize(int *w, int*h){
	
	Display* pdsp = NULL;
	Screen* pscr = NULL;

	pdsp = XOpenDisplay(NULL);
	if(!pdsp) {
		fprintf(stderr, "Failed to open default display.\n");
		return -1;
	}

	pscr = DefaultScreenOfDisplay(pdsp);
	if(!pscr) {
		fprintf(stderr, "Failed to obtain the default screen of given display.\n");
		return -2;
	}

	*w = pscr->width;
	*h = pscr->height;

	XCloseDisplay(pdsp);
	return 0;
}