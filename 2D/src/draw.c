#include<draw.h>

void draw_SUPERQUADRIC(SUPERQUADRIC superquadric){
	glColor3f(R_C, G_C, B_C);

	SUMMIT* sum = superquadric.summits;
	
	glBegin(GL_LINES);
	for(int i = 0; i < superquadric.size_summits - 1; i++){
			glVertex2f(sum[i].x, sum[i].y);
			glVertex2f(sum[i+1].x, sum[i+1].y);
	}
	glEnd();	
	
	int i = superquadric.size_summits - 1;

	glBegin(GL_LINES);
		glVertex2f(sum[i].x, sum[i].y);
		glVertex2f(sum[0].x, sum[0].y);
	glEnd();
}

void draw_debug(SUPERQUADRIC superquadric){
	glColor3f(R_C, G_C, B_C);
	glPointSize(3);

	SUMMIT* sum = superquadric.summits;

	glBegin(GL_POINTS);
		for(int i = 0; i < superquadric.size_summits; i++)
			glVertex2f(sum[i].x,sum[i].y);
	glEnd();
}

void draw_cloud(CLOUD cloud, float R, float G, float B){

	glColor3f(R, G, B);	
	glPointSize(3);
	glBegin(GL_POINTS);
	
	for(int i = 0; i < cloud.size; i++){
		glVertex2f(cloud.points[i][0], cloud.points[i][1]);
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