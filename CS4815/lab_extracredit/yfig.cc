//21344256

#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#if !defined(GLUT_WHEEL_UP)
#  define GLUT_WHEEL_UP   3
#  define GLUT_WHEEL_DOWN 4
#endif
#define THICKER 1
#define THINNER 2
#define RED 	3
#define GREEN 	4
#define BLUE 	5
#define BLACK 	6
#define QUIT 	7

GLfloat xwcMin = -600.0, xwcMax = 600.0;
GLfloat ywcMin = -600.0, ywcMax = 600.0;
GLsizei winWidth = 600, winHeight = 600; 
GLdouble movex,movey,downX,downY,downXnew, downYnew;

//integer 
int gHeight;
int pointSize = 0;
int pointArray[100][2];
int mX = 0;
int mY = 0;
int rubberBandOn = 0;
int downActive = 0;
int lineAmt;
int rectAmt;

//floater
float gColor[3]={0,1,0};
float fickness = 3.0;
float rotate =0.0;
float start = 0.0;
float zDepth = 0.0;
float radiusArray[50];

//bools
bool valid=false;
bool MiddleButton = false;
bool lBut = false;
bool linedraw = false;
bool circledraw = false;
bool rectangledraw = false;
enum
{
  MOUSE_LEFT_BUTTON = 0,
  MOUSE_MIDDLE_BUTTON = 1,
  MOUSE_RIGHT_BUTTON = 2,
  MOUSE_SCROLL_UP = 3,
  MOUSE_SCROLL_DOWN = 4
};

typedef enum state
{
waitOnClick,
clickedonce,
}state;

// This code defines a custom structure called 'point' that represents a 2D point with integer coordinates (x, y).
typedef struct point
{
  int x;
  int y;
}point;

point lines[256][2] ;
point rect[256][2] ;

int gCurrent=waitOnClick;

// This function, 'drawCircle', takes a float radius, x1, and y1 as input parameters and draws a circle using OpenGL. 
//It sets the color and line width of the circle, calculates the points on the circumference based on the input angle, and connects these points with lines using GL_LINES. 
void drawCircle(float radius, float x1, float y1)
{   
  glColor3fv(gColor);
  glLineWidth(fickness);
  float angle = 0;
  float x2,y2,cx,cy,fx,fy;
  int cache = 0;
  glBegin(GL_LINES);
  for (angle = 0; angle < 360; angle+=1.0)
  {
    float rad_angle = angle * 3.14 / 180;
    x2 = x1+radius * sin((double)rad_angle);
    y2 = y1+radius * cos((double)rad_angle);
    if (cache)
    {
      glVertex2f(cx,cy);
      glVertex2f(x2,y2);
    }
    else
    {
      fx = x2;
      fy = y2;
    }
      cache = 1;
      cx = x2;
      cy = y2;
  }
  glVertex2f(x2,y2);
  glVertex2f(fx,fy);

  glEnd();
}

// This function 'calculate_radius' takes two integer parameters, x1 and y1, and calculates the radius of a circle with its center at (x1, y1) and a point on the circumference at (mX, mY). 
float calculate_radius(int x1,int y1)
{
  int x_diff = mX - x1;
  int y_diff = mY - y1;
    if(x_diff<0)
    {
      x_diff *= -1;
    }
    if(y_diff<0)
    {
      y_diff *= -1;
    }
    float mag = x_diff*x_diff + y_diff*y_diff;
    float rad = sqrt(mag);
    return rad;
}

// This function, 'drawRectangle', draws a series of rectangles using OpenGL. 
//It sets the color and line width for the rectangles, then iterates through the 'rect' array up to 'rectAmt'.
void drawRectangle()
{
  glColor3fv(gColor);
  glLineWidth(fickness);
  glBegin(GL_LINES);

  for(int i=0; i<=rectAmt; i++)
  {
    glVertex2i(rect[i][0].x,rect[i][0].y);
    glVertex2i(rect[i][1].x,rect[i][0].y);
    glVertex2i(rect[i][0].x,rect[i][0].y);
    glVertex2i(rect[i][0].x,rect[i][1].y);
    glVertex2i(rect[i][0].x,rect[i][1].y);
    glVertex2i(rect[i][1].x,rect[i][1].y);
    glVertex2i(rect[i][1].x,rect[i][0].y);
    glVertex2i(rect[i][1].x,rect[i][1].y);
  }

  glEnd();
}

// This function, 'drawlines', draws a series of lines using OpenGL. It sets the color and line width for the lines, then iterates through the 'lines' array up to 'lineAmt'. 
void drawlines()
{
  glColor3fv(gColor);
  glLineWidth(fickness);
  glBegin(GL_LINES);

  for(int i=0; i<=lineAmt; i++)
  {
    glVertex2i(lines[i][0].x,lines[i][0].y);
    glVertex2i(lines[i][1].x,lines[i][1].y);
  }

  glEnd();
}

// This function, 'displayFcn', serves as the display callback for an OpenGL program using the GLUT library. It first sets the clear color to white and clears the display window. Then, it calls 'drawlines', 'drawRectangle', and 'drawCircle' functions to draw the respective shapes (lines, rectangles, and circles) using the global arrays 'lines', 'rect', 'pointArray', and 'radiusArray'.

// 'glutSwapBuffers()' is called to perform double-buffering, ensuring smooth rendering of the shapes. After this, the line width is set back to 1.0, and four blue lines are drawn, extending from the origin in the positive and negative x and y directions.

// The function then sets the projection and modelview matrices, defining the 2D orthographic view and translating the view by 'movex' and 'movey' values divided by 5. Finally, 'glutSwapBuffers()' is called again to swap the front and back buffers, completing the rendering process.
void displayFcn (void)
{
    glClearColor(1.0, 1.0, 1.0, 1.0);
   	glClear (GL_COLOR_BUFFER_BIT);   //  Clear display window.

   /*  Set example number of control points and number of
    *  curve positions to be plotted along the Bezier curve.
    */
    drawlines();
    drawRectangle();
    for(int i=0; i<pointSize; i+=2)
    {
      int rad_index = (int)(i/2);
      float rad = radiusArray[rad_index];
      if (rad>1)
      {
        drawCircle(rad,pointArray[i][0],pointArray[i][1]);
      }
    }

    glutSwapBuffers();
  	glLineWidth(1.0);

   	glBegin(GL_LINES);
      glColor3f (0.0, 0.0, 1.0);
	    glVertex2i(0, 0);
	    glVertex2i((-winWidth* 3), 0);
	    glVertex2i(0, 0);
	    glVertex2i((winWidth * 3), 0);
	    glVertex2i(0, 0);
	    glVertex2i(0, (-winHeight * 3));
	    glVertex2i(0, 0);
	    glVertex2i(0, (winHeight * 3));
  	glEnd();
  	glFlush();

   glMatrixMode (GL_PROJECTION);
   glLoadIdentity ( );
   gluOrtho2D (xwcMin, xwcMax, ywcMin, ywcMax); 
   glMatrixMode (GL_MODELVIEW);
   glLoadIdentity ( );
   movex = movex / 5;
   movey = movey / 5;
   glTranslatef(movex,movey,0.0);
   glutSwapBuffers();
   //glutPostRedisplay();
}

// this handles window resizing events by adjusting the viewport and updating the orthographic projection. 
void winReshapeFcn (GLint newWidth, GLint newHeight)
{
  glViewport (0, 0, newHeight, newHeight);

  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ( );

  gluOrtho2D (xwcMin, xwcMax, ywcMin, ywcMax);

  glutPostRedisplay();
}

void processMenuEvents(int option)
{
    switch(option)
    {
      case QUIT : exit(0); break;
      case THICKER : fickness +=5 ; break;
      case THINNER : fickness -=5 ; break;
      case RED 	   : gColor[0]=1,gColor[1]=0,gColor[2]=0; break;
      case GREEN 	 : gColor[0]=0,gColor[1]=1,gColor[2]=0; break;
      case BLUE 	 : gColor[0]=0,gColor[1]=0,gColor[2]=1; break;
      case BLACK 	 : gColor[0]=0,gColor[1]=0,gColor[2]=0; break;
    }
}

void createGLUTMenus()
{
	int menu,submenuSize,submenuColor;

	submenuColor=glutCreateMenu(processMenuEvents);
	  glutAddMenuEntry("Red",RED);
	  glutAddMenuEntry("Green",GREEN);
	  glutAddMenuEntry("Blue",BLUE);
	  glutAddMenuEntry("Black",BLACK);

	submenuSize=glutCreateMenu(processMenuEvents);
	  glutAddMenuEntry("Thicken",THICKER);
	  glutAddMenuEntry("Thin",THINNER);

	menu=glutCreateMenu(processMenuEvents);
	  glutAddSubMenu("Colour",submenuColor);
	  glutAddSubMenu("Size",submenuSize);
	  glutAddMenuEntry("Quit",QUIT);
	  glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init()
{
  glClearColor(0,0,0,1);
  lineAmt=-1;
  rectAmt=-1;
  createGLUTMenus();
}

void mouseclick(int button, int state,int x, int y)
{
  GLint viewport[4];
  GLdouble modelview[16];
  GLdouble projection[16];
  GLfloat winX, winY, winZ;
  GLdouble worldX, worldY, worldZ;
  glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
  glGetDoublev( GL_PROJECTION_MATRIX, projection );
  glGetIntegerv( GL_VIEWPORT, viewport );
  winX = (float)x;
  winY = (float)viewport[3] - (float)y;
  winZ = 0;
  gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);

  if (state == GLUT_DOWN && circledraw == true && button==GLUT_LEFT_BUTTON)
  {
    downActive = 1;
  }

  if (state == GLUT_UP && circledraw == true)
  {
    if(downActive)
    {
      pointArray[pointSize][0]=worldX;
      pointArray[pointSize][1]=worldY;
      pointSize++;
      downActive = 0;
      rubberBandOn = !rubberBandOn;
    }
    glutIdleFunc(NULL);
  }

  if(button==GLUT_LEFT_BUTTON && state==GLUT_UP)
  {
    if(linedraw == true)
    {
      switch(gCurrent)
      {
        case waitOnClick:
          ++lineAmt;
          lines[lineAmt][0].x=worldX;
          lines[lineAmt][0].y=worldY; 
          lines[lineAmt][1].x=worldX;
          lines[lineAmt][1].y=worldY;
          gCurrent++;
        break;

        case clickedonce:
          lines[lineAmt][1].x=worldX;
          lines[lineAmt][1].y=worldY;
          gCurrent=waitOnClick;
        break;
      }
    }

    else if(rectangledraw == true)
    {
      switch(gCurrent)
      {
      case waitOnClick:
        ++rectAmt;
        rect[rectAmt][0].x=worldX;
        rect[rectAmt][0].y=worldY; 
        rect[rectAmt][1].x=worldX;
        rect[rectAmt][1].y=worldY;
        gCurrent++;
      break;

      case clickedonce:
        rect[rectAmt][1].x=worldX;
        rect[rectAmt][1].y=worldY;
        gCurrent=waitOnClick;
      break;
      }
    }
  }

  else
  {
    MiddleButton = ((button == GLUT_MIDDLE_BUTTON) && (state == GLUT_DOWN));
    downX = worldX; 
    downY = worldY;
    int mod = glutGetModifiers(); 
    if (mod == GLUT_ACTIVE_CTRL)
    {
      if (button == MOUSE_SCROLL_UP)
      {
        xwcMin += 5;
        ywcMin += 5;  
      }
      else if(button == MOUSE_SCROLL_DOWN)
      {
        xwcMin -= 5;
        ywcMin -= 5;
      }
    }
  }
  glutPostRedisplay();
}

void MotionCallback(int x, int y)
{
  if (MiddleButton)
  {
    GLint viewport[4];
    GLdouble modelview[16];
    GLdouble projection[16];
    GLfloat winX, winY, winZ;
    GLdouble worldX, worldY, worldZ;
    glGetDoublev( GL_MODELVIEW_MATRIX, modelview );
    glGetDoublev( GL_PROJECTION_MATRIX, projection );
    glGetIntegerv( GL_VIEWPORT, viewport );
    winX = (float)x;
    winY = (float)viewport[3] - (float)y;
    winZ = 0;
    gluUnProject( winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);
    movex =worldX - x;
    movey= worldY - y;

  }
}

void mouseDrag(int x, int y)
{
  GLint viewport[4];
  GLdouble modelview[16];
  GLdouble projection[16]; 
  GLfloat winX, winY, winZ; 
  GLdouble worldX, worldY, worldZ;
  glGetDoublev( GL_MODELVIEW_MATRIX, modelview ); 
  glGetDoublev( GL_PROJECTION_MATRIX, projection );
  glGetIntegerv( GL_VIEWPORT, viewport );
  winX = (float)x;
  winY = (float)viewport[3] - (float)y;
  winZ = 0;
  gluUnProject(winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);
  if(circledraw == true)
  {
    mX = worldX;
    mY = worldY;
    if (rubberBandOn)
    {
      float rd = calculate_radius(pointArray[pointSize-1][0],pointArray[pointSize-1][1]);
      radiusArray[pointSize/2] = rd;
    }
    displayFcn();
  }

  if(linedraw == true)
  {
    if(gCurrent==clickedonce)
    {
      lines[lineAmt][1].x=worldX;
      lines[lineAmt][1].y=worldY;
      glutPostRedisplay();
    }
  }

  else if(rectangledraw == true)
  {
    if(gCurrent==clickedonce)
    {
      rect[rectAmt][1].x=worldX;
      rect[rectAmt][1].y=worldY;
      glutPostRedisplay();
    }
  }
}

void keyboard(unsigned char key, int x, int y) {
  if (key == 'l' || key == 'L') 
  {
    linedraw = true;
    circledraw = false;
    rectangledraw = false;
  }
  if (key == 'c' || key == 'C') 
  {
    linedraw = false;
    circledraw = true;
    rectangledraw = false;
  }
  if (key == 'r' || key == 'R') 
  {
    linedraw = false;
    circledraw = false;
    rectangledraw = true;
  }
}

int main(int argc, char ** argv)
{
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE);
glutInitWindowPosition(100,100);
glutInitWindowSize(500,500);
glutCreateWindow("Draw Boi");
glutReshapeFunc(winReshapeFcn);
glutDisplayFunc(displayFcn);
glutKeyboardFunc(keyboard);
glutMouseFunc(mouseclick);
glutPassiveMotionFunc(mouseDrag);
glutMotionFunc(MotionCallback);
init();

glutMainLoop();
return 0;
} 