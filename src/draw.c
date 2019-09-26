#include<draw.h>

void draw_superquadrics(summit** sum, double m, double n){
	glColor3f(R, G, B);
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	
	for(int i = 0; i <= (m-1); i++){
		glBegin(GL_TRIANGLE_STRIP);
		for(int j = 0; j <= (n-1); j++){
				glVertex3f(sum[i][j].x,sum[i][j].y,sum[i][j].z);
				glVertex3f(sum[i+1][j].x,sum[i+1][j].y,sum[i+1][j].z);
				glVertex3f(sum[i+1][j+1].x,sum[i+1][j+1].y,sum[i+1][j+1].z);

				glVertex3f(sum[i][j].x,sum[i][j].y,sum[i][j].z);
				glVertex3f(sum[i+1][j+1].x,sum[i+1][j+1].y,sum[i+1][j+1].z);
				glVertex3f(sum[i][j+1].x,sum[i][j+1].y,sum[i][j+1].z);
		}
		glEnd();
	}
}

void DrawEllipsoid(unsigned int uiStacks, unsigned int uiSlices, double fA, double fB, double fC, double e1, double e2){
	double tStep = (PI) / (double)uiSlices;
	double sStep = (PI) / (double)uiStacks;
	
	glColor3f(R, G, B);
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