#include<draw.h>

void draw_superquadrics(superquadrics forme){
	glColor3f(r, g, b);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	int m = forme.m;
	int n = forme.n;
	summit* sum = forme.summits;

	for(int i = 0; i <= m-1; i++){
		glBegin(GL_TRIANGLE_STRIP);
		for(int j = 0; j <= n-1; j++){
				glVertex3f(sum[i*n+j].x,sum[i*n+j].y,sum[i*n+j].z);
				glVertex3f(sum[(i+1)*n+j].x,sum[(i+1)*n+j].y,sum[(i+1)*n+j].z);
				glVertex3f(sum[(i+1)*n+(j+1)].x,sum[(i+1)*n+(j+1)].y,sum[(i+1)*n+(j+1)].z);

				glVertex3f(sum[i*n+j].x,sum[i*n+j].y,sum[i*n+j].z);
				glVertex3f(sum[(i+1)*n+(j+1)].x,sum[(i+1)*n+(j+1)].y,sum[(i+1)*n+(j+1)].z);
				glVertex3f(sum[i*n+(j+1)].x,sum[i*n+(j+1)].y,sum[i*n+(j+1)].z);
		}
		glEnd();
	}
}

void draw_debug(superquadrics forme){
	glColor3f(r, g, b);
	glPointSize(2);
	glBegin(GL_POINTS);
	
	int m = forme.m;
	int n = forme.n;
	summit* sum = forme.summits;
	for(int i = 0; i <= (m-1); i++){
		glBegin(GL_TRIANGLE_STRIP);
		for(int j = 0; j <= (n-1); j++){
				glVertex3f(sum[i*n+j].x,sum[i*n+j].y,sum[i*n+j].z);
		}
	}
	glEnd();
}

void DrawEllipsoid(unsigned int uiStacks, unsigned int uiSlices, double fA, double fB, double fC, double e1, double e2){
	double tStep = (PI) / (double)uiSlices;
	double sStep = (PI) / (double)uiStacks;
	
	glColor3f(r, g, b);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for(double t = -PI; t <= (PI)+.0001; t += tStep)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for(double s = -PI; s <= PI+.0001; s += sStep)
		{
			glVertex3f(fA * fexp(cos(t), e1) * fexp(cos(s), e2), fB * fexp(cos(t), e1) * fexp(sin(s), e2), fC * fexp(sin(t), e1));
			glVertex3f(fA * fexp(cos(t+tStep), e1) * fexp(cos(s), e2), fB * fexp(cos(t+tStep), e1) * fexp(sin(s), e2), fC * fexp(sin(t+tStep), e1));
		}
		glEnd();
	}
}

void DrawEllipsoid_cloud(unsigned int uiStacks, unsigned int uiSlices, double fA, double fB, double fC, double e1, double e2){
	double tStep = (PI) / (double)uiSlices;
	double sStep = (PI) / (double)uiStacks;
	
	glColor3f(r, g, b);
	glPointSize(2);
	glBegin(GL_POINTS);
	for(double t = -PI; t <= (PI)+.0001; t += tStep)
	{
		for(double s = -PI; s <= PI+.0001; s += sStep)
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