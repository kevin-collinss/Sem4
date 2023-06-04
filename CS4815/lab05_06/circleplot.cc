
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define BARCHART 1
#define PIECHART 2
#define LINECHART 3
#define ZOOM 4
#define UNZOOM 5
#define QUIT 6

class scrPt {
public:
    GLint x, y;
};

const GLdouble twoPi = 6.283185;

void circleMidpoint (scrPt , GLint ); // fn. defined in circle.cc

int scaleVar = 1;

int chart =1;

GLsizei winWidth = 600, winHeight = 500;    // Initial display window size.
GLint xRaster = 25, yRaster = 150; // Initial raster position

GLubyte label[36] = { 'J', 'a', 'n',   'F', 'e', 'b',   'M', 'a', 'r',
		      'A', 'p', 'r',   'M', 'a', 'y',   'J', 'u', 'n',
		      'J', 'u', 'l',   'A', 'u', 'g',   'S', 'e', 'p',
		      'O', 'c', 't',   'N', 'o', 'v',   'D', 'e', 'c' };

GLint dataValue[12] = { 420, 342, 324, 310, 262, 185,
			190, 196, 217, 240, 213, 438 };

void init (void)
{
  glClearColor (1.0, 1.0, 1.0, 1.0);

  glMatrixMode (GL_PROJECTION);
  gluOrtho2D (0.0, (GLdouble)winWidth, 0.0, (GLdouble)winHeight);
}

void barChart (void)
{
  GLint month, k;

  int ratio = winWidth/30;
  int ratioH = winHeight/50;
  glColor3f (1.0, 0.0, 0.0);           //  Set bar color to red.
  for (k = 0; k < 12; k++)
    glRecti (ratio + k*ratio*2.5, ratioH , ratio*2 + k*ratio*2.5, dataValue [k]);

  glColor3f (0.0, 0.0, 0.0);          //  Set text color to black.
  xRaster = ratio;                       //  Display chart labels.
  for (month = 0; month < 12; month++) {
    glRasterPos2i (xRaster, yRaster);
    for (k = 3*month; k < 3*month + 3; k++)
      glutBitmapCharacter (GLUT_BITMAP_HELVETICA_12, label [k]);
    xRaster += ratio*2.5;
  }
  
 // glViewport(0, 0, winWidth, winHeight);
}

void lineChart (void)
{
  
// put this code in chart.cc, just above the code definition of pieChart()
  int wRatio = winWidth/30; //20
  GLint x = 30;

  xRaster = wRatio*1.25;	yRaster = 150;

  glClear(GL_COLOR_BUFFER_BIT);	// clear display window

  glColor3f(0.0, 0.0, 1.0);	// set line colour to blue
  glBegin(GL_LINE_STRIP);
    for (int k = 0; k < 12; k++)
      glVertex2i(x + k*wRatio*2.5, dataValue[k]);
  glEnd();

  glColor3f(1.0, 0.0, 0.0);	// Set marker colour to red
  for (int k = 0; k < 12; k++)
  {
    glRasterPos2i(wRatio + k*wRatio*2.5, dataValue[k]-4);
    glutBitmapCharacter(GLUT_BITMAP_9_BY_15, '*');
  }

  glColor3f(0.0, 0.0, 0.0);	// black
  xRaster = wRatio;
  for (int m = 0; m < 12; m++)
  {
    glRasterPos2i(xRaster, yRaster);
    for (int k = 3*m; k < 3*m+3; k++)
      glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, label[k]);
    xRaster += wRatio * 2.5;
  }
  glFlush();
}

void pieChart (void)
{
    scrPt circCtr, piePt;
    GLint radius = winWidth / 4;               // Circle radius.

    GLdouble sliceAngle, previousSliceAngle = 0.0;

    GLint k, nSlices = 12;                     // Number of Slices. 
    GLfloat dataValues[12] = {10.0, 7.0, 13.0, 5.0, 13.0, 14.0,
                               3.0, 16, 5.0, 3.0, 17.0, 8.0};
    GLfloat dataSum = 0.0;
 
    circCtr.x = winWidth / 2;                  // Circle center position.
    circCtr.y = winHeight / 2;
    circleMidpoint (circCtr, radius);  // Call midpoint circle-plot routine.

    for (k = 0; k < nSlices; k++)
        dataSum += dataValues[k];

    for (k = 0; k < nSlices; k++) {
        sliceAngle = twoPi * dataValues[k] / dataSum + previousSliceAngle;
        piePt.x = (GLint) (circCtr.x + radius * cos (sliceAngle));
        piePt.y = (GLint) (circCtr.y + radius * sin (sliceAngle));
        glBegin (GL_LINES);
            glVertex2i (circCtr.x, circCtr.y);
            glVertex2i (piePt.x, piePt.y);
        glEnd ( );
        previousSliceAngle = sliceAngle;
    }
    
    	// Set the viewport to be the entire window
    glViewport(0, 0, winWidth, winHeight);
}

void displayFcn (void)
{
    glClear (GL_COLOR_BUFFER_BIT);   //  Clear display window.

    glColor3f (0.0, 0.0, 1.0);       //  Set circle color to blue.

    glPushMatrix();
    glScalef(scaleVar, scaleVar, 1);
    
    //    pieChart ( );
    if(chart==1){
    barChart();
    }else if(chart==2){
    pieChart();
    }else if(chart==3){
    lineChart();
    }
    
    glPopMatrix();
    glutSwapBuffers ( );
    
}


void winReshapeFcn (int newWidth, int newHeight)
{
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ( );
    gluOrtho2D (0.0, GLdouble (newWidth), 0.0, GLdouble (newHeight));
    glViewport(0, 0, newWidth, newHeight);

    /*  Reset display-window size parameters.  */
    winWidth = newWidth;
    winHeight = newHeight;    
    
    

    glutPostRedisplay();
}



void chartOption(unsigned char key, int x, int y){
if(key == 'q' || key == 'Q'){
	exit(0);
}
	
if( key == 'b' || key == 'B'){
	chart = 1;
	displayFcn();
	}

if (key == 'p' || key == 'P' ){
	chart = 2;
	displayFcn();
	}

	
if (key == 'l' || key == 'L' ){
	chart = 3;
	displayFcn();
	}
	
if (key == 'z'){
	scaleVar = scaleVar*2;
}

if (key == 'Z'){
	scaleVar = scaleVar/2;
}

displayFcn();
}



void processMenuEvents(int option){

switch(option){
	case BARCHART: chart=1; break;
	case PIECHART: chart =2; break;
	case LINECHART: chart =3; break;
	case ZOOM: scaleVar = scaleVar*2; break;
	case UNZOOM: scaleVar = scaleVar/2 ; break;
	case QUIT: exit(0); break;
	}
	
	displayFcn();
}

void createGLUTMenus(){

int barChartMenu;
	barChartMenu = glutCreateMenu(processMenuEvents);
	glutAddMenuEntry("Bar Chart",BARCHART);
	glutAddMenuEntry("Pie Chart",PIECHART);
	glutAddMenuEntry("Line Chart",LINECHART);
	glutAddMenuEntry("Zoom",ZOOM);
	glutAddMenuEntry("UnZoom",UNZOOM);
	glutAddMenuEntry("Quit",QUIT);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
} 


int main (int argc, char** argv)
{
    glutInit (&argc, argv);
    //    glutInitDisplayMode (GLUT_SINGLE | GLUT_RGB);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition (100, 100);
    glutInitWindowSize (winWidth, winHeight);
    glutCreateWindow ("Charts");
    
    createGLUTMenus();
    glutKeyboardFunc(chartOption);

    init ( );
    glutDisplayFunc (displayFcn);
    glutReshapeFunc (winReshapeFcn);

    glutMainLoop ( );
}