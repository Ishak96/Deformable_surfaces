#include<draw.h>

void draw_SUPERQUADRIC(SUPERQUADRIC superquadric){
	glColor3f(R_C, G_C, B_C);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	SUMMIT* sum = superquadric.summits;
	int** fac = superquadric.facades;

	for(int i = 0; i < superquadric.size_facades; i++){
		int summit_size = superquadric.facades[i][0];
		if(summit_size == 3){
			glBegin(GL_TRIANGLE_STRIP);
				glVertex3f(sum[fac[i][1]].x,sum[fac[i][1]].y,sum[fac[i][1]].z);
				glVertex3f(sum[fac[i][2]].x,sum[fac[i][2]].y,sum[fac[i][2]].z);
				glVertex3f(sum[fac[i][3]].x,sum[fac[i][3]].y,sum[fac[i][3]].z);				
			glEnd();
		}
		else{
			glBegin(GL_QUADS);
				glVertex3f(sum[fac[i][1]].x,sum[fac[i][1]].y,sum[fac[i][1]].z);
				glVertex3f(sum[fac[i][2]].x,sum[fac[i][2]].y,sum[fac[i][2]].z);
				glVertex3f(sum[fac[i][3]].x,sum[fac[i][3]].y,sum[fac[i][3]].z);
				glVertex3f(sum[fac[i][4]].x,sum[fac[i][4]].y,sum[fac[i][4]].z);
			glEnd();
		}
	}
}

void draw_debug(SUPERQUADRIC superquadric){
	glColor3f(R_C, G_C, B_C);
	glPointSize(2);

	SUMMIT* sum = superquadric.summits;

	glBegin(GL_POINTS);
		for(int i = 0; i < superquadric.size_summits; i++)
			glVertex3f(sum[i].x,sum[i].y,sum[i].z);
	glEnd();
}

void DrawEllipsoid(unsigned int uiStacks, unsigned int uiSlices, float fA, float fB, float fC, float e1, float e2){
	float tStep = (PI) / (float)uiSlices;
	float sStep = (PI) / (float)uiStacks;
	
	glColor3f(R_C, G_C, B_C);
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
	
	glColor3f(R_C, G_C, B_C);
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