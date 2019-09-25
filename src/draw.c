#include<draw.h>

void draw_superquadrics(summit** sum, int m, int n){
	glColor3f(R, G, B);
	
	for(int i = 0; i <= (m-1); i++){
		glBegin(GL_TRIANGLES);
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

void DrawEllipsoid(unsigned int uiStacks, unsigned int uiSlices, float fA, float fB, float fC, float e1, float e2){
	float tStep = (PI) / (float)uiSlices;
	float sStep = (PI) / (float)uiStacks;
	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	for(float t = -PI/2; t <= (PI/2)+.0001; t += tStep)
	{
		glBegin(GL_TRIANGLE_STRIP);
		for(float s = -PI; s <= PI+.0001; s += sStep)
		{
			glVertex3f(fA * pow(cos(t), e1) * pow(cos(s), e2), fB * pow(cos(t), e1) * pow(sin(s), e2), fC * pow(sin(t), e1));
			glVertex3f(fA * pow(cos(t+tStep), e1) * pow(cos(s), e2), fB * pow(cos(t+tStep), e1) * pow(sin(s), e2), fC * pow(sin(t+tStep), e1));
		}
		glEnd();
	}
}