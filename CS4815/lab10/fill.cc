
#include <stdlib.h>
#include <GL/glut.h>

const double X = 1;
const double Z = 1.5;

GLfloat colours[][3] = {{0.0, 0.5, 0.5},   // teal
                       {0.5, 0.5, 0.5},   // grey
                       {1.0, 0.65, 0.0},  // orange
                       {0.0, 0.0, 0.0}};  // black


GLfloat vert[][3] = {{0.0,X},{-1*X,0.0},{0.0,-2*X}, {2*X,0.0}};

//This function takes four integer arguments that represent indices of the vertices and colours arrays. 
void polygon(int a, int b, int c , int d)
{

 	glBegin(GL_POLYGON);
		glColor3fv(colours[a]);
		glVertex2fv(vert[a]);
		glColor3fv(colours[b]);
		glVertex2fv(vert[b]);
		glColor3fv(colours[c]);
		glVertex2fv(vert[c]);
		glColor3fv(colours[d]);
		glVertex2fv(vert[d]);
	glEnd();
																										}

//This function calls the polygon() function with the appropriate indices to create a colored polygon using the global vertices and colours arrays.
void colorPoly(void)
{

	polygon(0,1,2,3);

}

void display(void)
{

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

 	colorPoly();

 	glFlush();
	glutSwapBuffers();

}



void myReshape(int w, int h)
{

    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (w <= h)
    	glOrtho(-2.0,2.0,-2.0*(GLfloat)h/(GLfloat)w,
            2.0*(GLfloat)h/(GLfloat)w,-10.0,10.0);
    else
        glOrtho(-2.0 * (GLfloat) w / (GLfloat) h,
            2.0 * (GLfloat) w / (GLfloat) h, -2.0, 2.0, -10.0, 10.0);

    glMatrixMode(GL_MODELVIEW);

}

int
main(int argc, char **argv)
{

    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(650, 650);
    glutCreateWindow("Coloured Poly");

    glutReshapeFunc(myReshape);
    glutDisplayFunc(display);
	//glutMouseFunc(mouse);
	glEnable(GL_DEPTH_TEST);

    glutMainLoop();

}