/*
 * Simple program to demonstrate generating coordinates
 * using the Lorenz Attractor
 * edited lorenz.c
 * ref'd ex6
 * help from https://github.com/untra/lorenz/blob/master/lorenz.c
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int th = 120; //azimuth
int ph = -30; //elevation

int N = 50000;
double value[50000][3];
double color[50000][3];

/*  Lorenz Parameters  */
double s  = 10;
double b  = 2.6666;
double r  = 28;

/*
 *  Main
 */

//ex6
#define LEN 8192  // Maximum length of text string
void Print(const char* format , ...)
{
  char    buf[LEN];
  char*   ch=buf;
  va_list args;
  //  Turn the parameters into a character string
  va_start(args,format);
  vsnprintf(buf,LEN,format,args);
  va_end(args);
  //  Display the characters one at a time at the current raster position
  while (*ch)
  glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18,*ch++);
}

//original lorenz.c, store values instead
void lorenz(void)
{
   int i;
   /*  Coordinates  */
   double x = 1;
   double y = 1;
   double z = 1;
   /*  Time step  */
   double dt = 0.001;

   //printf("%5d %8.3f %8.3f %8.3f\n",0,x,y,z);
   /*
    *  Integrate 50,000 steps (50 time units with dt = 0.001)
    *  Explicit Euler integration
    */
   for (i=0;i<50000;i++)
   {
      double dx = s*(y-x);
      double dy = x*(r-z)-y;
      double dz = x*y - b*z;
      x += dt*dx;
      y += dt*dy;
      z += dt*dz;
      
      //scaled so it's on the graph, but still large enough to appreciate some COLORS
      value[i][0] = x*.03;
      value[i][1] = y*.03;
      value[i][2] = z*.03;
   }
}

//ex6
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);

   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;

   //  Reset sbr
   else if (ch == '-')
   {
	s  = 10;
	b  = 2.6666;
	r  = 28;
   }	
   //alpha
   else if (ch=='w')
      s += .25;
   else if (ch=='s')
      s -= .25;

   //beta
   else if (ch=='g')
      b += 0.25;
   else if (ch=='b')
      b -= 0.25;

   //rho
   else if (ch=='4')
      r += .25;
   else if (ch=='r')
      r -= .25;
   
   glutPostRedisplay();
}

void special(int key,int x,int y)
{
   //  Right arrow key - increase azimuth by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease azimuth by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   
   double dim = 3;

   //  Ratio of the width to the height of the window
   double w2h = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Orthogonal projection box adjusted for the
   //  aspect ratio of the window
   glOrtho(-dim*w2h,+dim*w2h, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}
void display()
{
   lorenz();   

   //  Clear the image
   glClear(GL_COLOR_BUFFER_BIT);
   //  Reset previous transforms
   glLoadIdentity();
   //  Set view angle
   glRotated(ph,1,0,0);
   glRotated(th,0,1,0);
   
   //we want it in a LINE
   glColor3f(1,1,0);
   glBegin(GL_LINE_STRIP);
   for(int i = 0; i<50000; i++)
   {
	
	if (i == 0)
	   glColor3f(0.576, 0.960, 0.964);
	else if(i == 10000)
	   glColor3f(0.964, 0.576, 0.882);
	else if(i == 25000)
	   glColor3f(1, 1, 1);
	else if(i == 40000)
	   glColor3f(0.964, 0.576, 0.882);
	else if(i == 50000)
	   glColor3f(0.576, 0.960, 0.964);

	glVertex3dv(value[i]);
   }
   glEnd();
   

   //  Draw axes in white
   glColor3f(1,1,1);
   glBegin(GL_LINES);
   glVertex3d(0,0,0);
   glVertex3d(1,0,0);
   glVertex3d(0,0,0);
   glVertex3d(0,1,0);
   glVertex3d(0,0,0);
   glVertex3d(0,0,1);
   glEnd();
   //  Label axes
   glRasterPos3d(1,0,0);
   Print("X");
   glRasterPos3d(0,1,0);
   Print("Y");
   glRasterPos3d(0,0,1);
   Print("Z");
   //  Display parameters
   glWindowPos2i(5,5);
   Print("View Angle=%d,%d",th,ph);
   glWindowPos2i(10, 22);
   Print("s=%.02f b=%.04f r=%.02f",s,b,r);
   //  Flush and swap
   glFlush();
   glutSwapBuffers();
}

int main(int argc,char* argv[])
{
   lorenz();

   //  Initialize GLUT and process user parameters
   glutInit(&argc,argv);
   //  Request double buffered, true color window 
   glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
   //  Request 500 x 500 pixel window
   glutInitWindowSize(500,500);
   //  Create the window
   glutCreateWindow("Lorenz Attractor - Cathy Yang");
   //  Tell GLUT to call "display" when the scene should be drawn
   glutDisplayFunc(display);
  //  Tell GLUT to call "reshape" when the window is resized
   glutReshapeFunc(reshape);
   //  Tell GLUT to call "special" when an arrow key is pressed
   glutSpecialFunc(special);
   //  Tell GLUT to call "key" when a key is pressed
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   //  Return code
   return 0;
}
