//Edited ex9
//Ref'd first person walking from https://github.com/nhng5827/GraphicsFinal/blob/master/finalproject.c
//some cylinder action here https://gist.github.com/nikAizuddin/5ea402e9073f1ef76ba6

#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <math.h>
//  OpenGL with prototypes for glext
#define GL_GLEXT_PROTOTYPES
#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

int mode=0;       //  Projection mode
int fp = 0;
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio
double dim=5.0;   //  Size of world

double Ex = 1;
double Ey = 1;
double Ez = 25;
int rot = -10;

double Cx = 0;
double Cy = 0;
double Cz = 0;

//  Macro for sin & cos in degrees
#define Cos(th) cos(3.1415926/180*(th))
#define Sin(th) sin(3.1415926/180*(th))
#define PI 3.1415927

/*
 *  Convenience routine to output raster text
 *  Use VARARGS to make this more flexible
 */
#define LEN 8192  //  Maximum length of text string
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

/*
 *  Set projection
 */
static void Project()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
   if (fp) 
   	gluPerspective(fov,asp,.01,4*dim);

   if (mode)
      gluPerspective(fov,asp,dim/4,4*dim);
   //  Orthogonal projection
   else
      glOrtho(-asp*dim,+asp*dim, -dim,+dim, -dim,+dim);
   //  Switch to manipulating the model matrix
   glMatrixMode(GL_MODELVIEW);
   //  Undo previous transformations
   glLoadIdentity();
}

//Draw a H
static void H(double x, double y, double z, double dx, double dy, double dz, double th) {
	
	// Translations
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);

	glBegin(GL_QUADS);
	
	//color
	glColor3f(1, 1, 1);
	//front
	glVertex3f(0.0f, 0.0f, 0.17f);
	glVertex3f(0.0f, 1.0f, 0.17f);
	glVertex3f(0.33f, 1.0f, 0.17f);
	glVertex3f(0.33f, 0.0f, 0.17f);

	glVertex3f(0.33f, 0.25f, 0.17f);
	glVertex3f(0.33f, 0.5f, 0.17f);
	glVertex3f(0.66f, 0.5f, 0.17f);
	glVertex3f(0.66f, 0.25f, 0.17f);

	glVertex3f(0.66f, 0.0f, 0.17f);
	glVertex3f(0.66f, 1.0f, 0.17f);
	glVertex3f(1.0f, 1.0f, 0.17f);
	glVertex3f(1.0f, 0.0f, 0.17f);
	
	//color
	glColor3f(0, 1, 1);
	//back
	glVertex3f(0.0f, 0.0f, -0.17f);
	glVertex3f(0.0f, 1.0f, -0.17f);
	glVertex3f(0.33f, 1.0f, -0.17f);
	glVertex3f(0.33f, 0.0f, -0.17f);

	glVertex3f(0.33f, 0.25f, -0.17f);
	glVertex3f(0.33f, 0.5f, -0.17f);
	glVertex3f(0.66f, 0.5f, -0.17f);
	glVertex3f(0.66f, 0.25f, -0.17f);

	glVertex3f(0.66f, 0.0f, -0.17f);
	glVertex3f(0.66f, 1.0f, -0.17f);
	glVertex3f(1.0f, 1.0f, -0.17f);
	glVertex3f(1.0f, 0.0f, -0.17f);
	
	//color
	glColor3f(1, 0, 1);
	//right
	glVertex3f(0.33f, 1.0f, 0.17f);
	glVertex3f(0.33f, 1.0f, -0.17f);
	glVertex3f(0.33f, 0.0f, -0.17f);
	glVertex3f(0.33f, 0.0f, 0.17f);

	glVertex3f(1.0f, 1.0f, 0.17f);
	glVertex3f(1.0f, 1.0f, -0.17f);
	glVertex3f(1.0f, 0.0f, -0.17f);
	glVertex3f(1.0f, 0.0f, 0.17f);
	
	//color
	glColor3f(1, 1, 0);
	//left
	glVertex3f(0.0f, 1.0f, 0.17f);
	glVertex3f(0.0f, 1.0f, -0.17f);
	glVertex3f(0.0f, 0.0f, -0.17f);
	glVertex3f(0.0f, 0.0f, 0.17f);

	glVertex3f(0.66f, 1.0f, 0.17f);
	glVertex3f(0.66f, 1.0f, -0.17f);
	glVertex3f(0.66f, 0.0f, -0.17f);
	glVertex3f(0.66f, 0.0f, 0.17f);
	
	//color
	glColor3f(1, 0, 0);	
	//top
	glVertex3f(0.0f, 1.0f, 0.17f);
	glVertex3f(0.0f, 1.0f, -0.17f);
	glVertex3f(0.33f, 1.0f, -0.17f);
	glVertex3f(0.33f, 1.0f, 0.17f);

	glVertex3f(0.33f, 0.5f, 0.17f);
	glVertex3f(0.33f, 0.5f, -0.17f);
	glVertex3f(0.66f, 0.5f, -0.17f);
	glVertex3f(0.66f, 0.5f, 0.17f);

	glVertex3f(0.66f, 1.0f, 0.17f);
	glVertex3f(0.66f, 1.0f, -0.17f);
	glVertex3f(1.0f, 1.0f, -0.17f);
	glVertex3f(1.0f, 1.0f, 0.17f);

	//bot
	glVertex3f(0.0f, 0.0f, 0.17f);
	glVertex3f(0.0f, 0.0f, -0.17f);
	glVertex3f(0.33f, 0.0f, -0.17f);
	glVertex3f(0.33f, 0.0f, 0.17f);

	glVertex3f(0.33f, 0.25f, 0.17f);
	glVertex3f(0.33f, 0.25f, -0.17f);
	glVertex3f(0.66f, 0.25f, -0.17f);
	glVertex3f(0.66f, 0.25f, 0.17f);

	glVertex3f(0.66f, 0.0f, 0.17f);
	glVertex3f(0.66f, 0.0f, -0.17f);
	glVertex3f(1.0f, 0.0f, -0.17f);
	glVertex3f(1.0f, 0.0f, 0.17f);

	glEnd();
}

//Draw a E
static void E(double x, double y, double z, double dx, double dy, double dz, double th) {

	// Translations
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);

	glBegin(GL_QUADS);
	
	//color
	glColor3f(1, 1, 1);
	//front
	glVertex3f(0.0f, 0.0f, 0.17f);
	glVertex3f(0.0f, 1.0f, 0.17f);
	glVertex3f(0.33f, 1.0f, 0.17f);
	glVertex3f(0.33f, 0.0f, 0.17f);

	glVertex3f(1.0f, 0.8f, 0.17f);
	glVertex3f(1.0f, 1.0f, 0.17f);
	glVertex3f(0.33f, 1.0f, 0.17f);
	glVertex3f(0.33f, 0.8f, 0.17f);

	glVertex3f(1.0f, 0.4f, 0.17f);
	glVertex3f(1.0f, 0.6f, 0.17f);
	glVertex3f(0.33f, 0.6f, 0.17f);
	glVertex3f(0.33f, 0.4f, 0.17f);

	glVertex3f(1.0f, 0.2f, 0.17f);
	glVertex3f(1.0f, 0.0f, 0.17f);
	glVertex3f(0.33f, 0.0f, 0.17f);
	glVertex3f(0.33f, 0.2f, 0.17f);
	
	//color
	glColor3f(1, 0, 0);
	//back
	glVertex3f(0.0f, 0.0f, -0.17f);
	glVertex3f(0.0f, 1.0f, -0.17f);
	glVertex3f(0.33f, 1.0f, -0.17f);
	glVertex3f(0.33f, 0.0f, -0.17f);

	glVertex3f(1.0f, 0.8f, -0.17f);
	glVertex3f(1.0f, 1.0f, -0.17f);
	glVertex3f(0.33f, 1.0f, -0.17f);
	glVertex3f(0.33f, 0.8f, -0.17f);

	glVertex3f(1.0f, 0.4f, -0.17f);
	glVertex3f(1.0f, 0.6f, -0.17f);
	glVertex3f(0.33f, 0.6f, -0.17f);
	glVertex3f(0.33f, 0.4f, -0.17f);

	glVertex3f(1.0f, 0.2f, -0.17f);
	glVertex3f(1.0f, 0.0f, -0.17f);
	glVertex3f(0.33f, 0.0f, -0.17f);
	glVertex3f(0.33f, 0.2f, -0.17f);

	
	//color
	glColor3f(0, 1, 0);
	//left
	glVertex3f(0.0f, 0.0f, 0.17f);
	glVertex3f(0.0f, 1.0f, 0.17f);
	glVertex3f(0.0, 1.0f, -0.17f);
	glVertex3f(0.0f, 0.0f, -0.17f);

	
	//color
	glColor3f(0, 0, 1);
	//right
	glVertex3f(1.0f, 1.0f, 0.17f);
	glVertex3f(1.0f, 0.8f, 0.17f);
	glVertex3f(1.0f, 0.8f, -0.17f);
	glVertex3f(1.0f, 1.0f, -0.17f);

	glVertex3f(1.0f, 0.6f, 0.17f);
	glVertex3f(1.0f, 0.4f, 0.17f);
	glVertex3f(1.0f, 0.4f, -0.17f);
	glVertex3f(1.0f, 0.6f, -0.17f);

	glVertex3f(1.0f, 0.2f, 0.17f);
	glVertex3f(1.0f, 0.0f, 0.17f);
	glVertex3f(1.0f, 0.0f, -0.17f);
	glVertex3f(1.0f, 0.2f, -0.17f);

	glVertex3f(0.33f, 0.8f, 0.17f);
	glVertex3f(0.33f, 0.6f, 0.17f);
	glVertex3f(0.33f, 0.6f, -0.17f);
	glVertex3f(0.33f, 0.8f, -0.17f);

	glVertex3f(0.33f, 0.4f, 0.17f);
	glVertex3f(0.33f, 0.2f, 0.17f);
	glVertex3f(0.33f, 0.2f, -0.17f);
	glVertex3f(0.33f, 0.4f, -0.17f);

	//color
	glColor3f(0, 0, .5);
	//top
	glVertex3f(0.0f, 1.0f, 0.17f);
	glVertex3f(0.0f, 1.0f, -0.17f);
	glVertex3f(1.0f, 1.0f, -0.17f);
	glVertex3f(1.0f, 1.0f, 0.17f);

	glVertex3f(0.33f, 0.6f, 0.17f);
	glVertex3f(0.33f, 0.6f, -0.17f);
	glVertex3f(1.0f, 0.6f, -0.17f);
	glVertex3f(1.0f, 0.6f, 0.17f);

	glVertex3f(0.33f, 0.2f, 0.17f);
	glVertex3f(0.33f, 0.2f, -0.17f);
	glVertex3f(1.0f, 0.2f, -0.17f);
	glVertex3f(1.0f, 0.2f, 0.17f);
	
	//color
	glColor3f(0.3, .75, .002);
	//bot
	glVertex3f(1.0f, 0.00f, 0.17f);
	glVertex3f(0.0f, 0.00f, 0.17f);
	glVertex3f(0.0f, 0.00f, -0.17f);
	glVertex3f(1.0f, 0.00f, -0.17f);
	glEnd();
}

//Draw a L
static void L(double x, double y, double z, double dx, double dy, double dz, double th) {

	// Translations
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);

	glBegin(GL_QUADS);
	
	//color
	glColor3f(0, .5, .5);
	//front
	glVertex3f(0.0f, 0.0f, 0.17f);
	glVertex3f(0.0f, 1.0f, 0.17f);
	glVertex3f(.33f, 1.0f, 0.17f);
	glVertex3f(.33f, 0.0f, 0.17f);

	glVertex3f(0.33f, 0.0f, 0.17f);
	glVertex3f(0.33f, 0.33f, 0.17f);
	glVertex3f(1.0f, 0.33f, 0.17f);
	glVertex3f(1.0f, 0.0f, 0.17f);
	
	//color
	glColor3f(.5, .5, .5);
	//back
	glVertex3f(0.0f, 0.0f, -0.17f);
	glVertex3f(0.0f, 1.0f, -0.17f);
	glVertex3f(.33f, 1.0f, -0.17f);
	glVertex3f(.33f, 0.0f, -0.17f);

	glVertex3f(0.33f, 0.0f, -0.17f);
	glVertex3f(0.33f, 0.33f, -0.17f);
	glVertex3f(1.0f, 0.33f, -0.17f);
	glVertex3f(1.0f, 0.0f, -0.17f);
	
	//color
	glColor3f(.5, 0, .5);
	//left
	glVertex3f(0.0f, 0.0f, 0.17f);
	glVertex3f(0.0f, 1.0f, 0.17f);
	glVertex3f(0.0, 1.0f, -0.17f);
	glVertex3f(0.0f, 0.0f, -0.17f);
	
	//color
	glColor3f(1, 1, .5);
	//right
	glVertex3f(0.33f, 1.0f, 0.17f);
	glVertex3f(0.33f, 0.33f, 0.17f);
	glVertex3f(0.33f, 0.33f, -0.17f);
	glVertex3f(0.33f, 1.0f, -0.17f);

	glVertex3f(1.0f, 0.0f, 0.17f);
	glVertex3f(1.0f, 0.33f, 0.17f);
	glVertex3f(1.0f, 0.33f, -0.17f);
	glVertex3f(1.0f, 0.0f, -0.17f);

	//color
	glColor3f(0, .8, .2);	
	//top
	glVertex3f(0.33f, 1.00f, 0.17f);
	glVertex3f(0.0f, 1.00f, 0.17f);
	glVertex3f(0.0f, 1.00f, -0.17f);
	glVertex3f(0.33f, 1.00f, -0.17f);

	glVertex3f(0.33f, 0.33f, 0.17f);
	glVertex3f(1.0f, 0.33f, 0.17f);
	glVertex3f(1.0, 0.33f, -0.17f);
	glVertex3f(0.33f, 0.33f, -0.17f);

	//color
	glColor3f(0, .0325, .777);
	//bot
	glVertex3f(1.0f, 0.00f, 0.17f);
	glVertex3f(0.0f, 0.00f, 0.17f);
	glVertex3f(0.0f, 0.00f, -0.17f);
	glVertex3f(1.0f, 0.00f, -0.17f);

	glEnd();
}

//Draw a P
static void P(double x, double y, double z, double dx, double dy, double dz, double th) {

	// Translations
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);

	//color
	glColor3f(0.999, .666, .333);	

	glBegin(GL_QUADS);

	//front
	glVertex3f(0.0f, 0.0f, 0.17f);
	glVertex3f(0.0f, 1.0f, 0.17f);
	glVertex3f(.33f, 1.0f, 0.17f);
	glVertex3f(.33f, 0.0f, 0.17f);

	//back
	glVertex3f(0.0f, 0.0f, -0.17f);
	glVertex3f(0.0f, 1.0f, -0.17f);
	glVertex3f(.33f, 1.0f, -0.17f);
	glVertex3f(.33f, 0.0f, -0.17f);	
	
	//left
	glVertex3f(0.0f, 0.0f, 0.17f);
	glVertex3f(0.0f, 1.0f, 0.17f);
	glVertex3f(0.0f, 1.0f, -0.17f);
	glVertex3f(0.0f, 0.0f, -0.17f);
	
	//right
	glVertex3f(.33f, 1.0f, 0.17f);
	glVertex3f(.33f, 0.0f, 0.17f);
	glVertex3f(.33f, 0.0f, -0.17f);
	glVertex3f(.33f, 1.0f, -0.17f);

	//top
	glVertex3f(0.0f, 1.0f, 0.17f);
	glVertex3f(0.33f, 1.0f, 0.17f);
	glVertex3f(0.33f, 1.0f, -0.17f);
	glVertex3f(0.0f, 1.0f, -0.17f);

	//bot
	glVertex3f(0.0f, 0.0f, 0.17f);
	glVertex3f(0.33f, 0.0f, 0.17f);
	glVertex3f(0.33f, 0.0f, -0.17f);
	glVertex3f(0.0f, 0.0f, -0.17f);

	glEnd();

	GLfloat radius = .33;
	GLfloat height = .17;	
	
	//color
	glColor3f(1, 1, 1);
	glBegin(GL_QUAD_STRIP);
    	GLfloat angle = 3*PI/2;
        while( angle < (5*PI)/2 ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x + .31, y + .67, height);
            glVertex3f(x + .31, y + .67, -.17);
            angle = angle + 0.1;
        }
        glVertex3f(radius, 0.0, height);
        glVertex3f(radius, 0.0, 0.0);
    	glEnd();
	
	//color
	glColor3f(0.222, 0, .666);
	glBegin(GL_POLYGON);
    	angle = 3*PI/2;
        while( angle < (5*PI)/2 ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x + .31, y  + .67, height);
            angle = angle + 0.1;
        }
        glVertex3f(radius, 0.0, height);
    	glEnd();

	glBegin(GL_POLYGON);
    	angle = 3*PI/2;
        while( angle < (5*PI)/2 ) {
            x = radius * cos(angle);
            y = radius * sin(angle);
            glVertex3f(x + .31, y  + .67, -height);
            angle = angle + 0.1;
        }
        glVertex3f(radius, 0.0, -height);
    	glEnd();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (mode)
   {
      double Ex = -2*dim*Sin(th)*Cos(ph);
      double Ey = +2*dim        *Sin(ph);
      double Ez = +2*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }

   	//just put em somewhere
	H(-1.5, -0.35, 1.5, 0.4, 0.75, 0.5, -30);
	//H(-1.5, -0.68, 1.5, 0.4, 0.75, 0.5, -30);
	E(3,2,1,1,1,1,60);
	//E(3,-1,1,1,1,1,60);
	L(1.5,-1,0,0.6,0.6,0.6,-30);
	//L(1.5,-2,0,0.6,0.6,0.6,-30);	
	P(2,-0.5,0,4,3,2,-30);
	P(-0.5,-1.5,0,0.3,.4,0.6, 120);

   //  Display parameters
   
   if (fp == 1){
  	glWindowPos2i(5,5);
   	Print("Angle=%d,%d  Dim=%.1f FOV=%d 	Projection=First Person" ,th,ph,dim,fov);
   }

   else{
	glWindowPos2i(5,5);
   	Print("Angle=%d,%d  Dim=%.1f FOV=%d 	Projection=%s",th,ph,dim,fov,mode?"Perpective":"Orthogonal");

   }
   //  Render the scene and make it visible
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key,int x,int y)
{
   //  Right arrow key - increase angle by 5 degrees
   if (key == GLUT_KEY_RIGHT)
      th += 5;
   //  Left arrow key - decrease angle by 5 degrees
   else if (key == GLUT_KEY_LEFT)
      th -= 5;
   //  Up arrow key - increase elevation by 5 degrees
   else if (key == GLUT_KEY_UP)
      ph += 5;
   //  Down arrow key - decrease elevation by 5 degrees
   else if (key == GLUT_KEY_DOWN)
      ph -= 5;
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_UP)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_DOWN && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project();
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch,int x,int y)
{
   //  Exit on ESC
   if (ch == 27)
      exit(0);
   //  Reset view angle
   else if (ch == '0')
      th = ph = 0;
   //  Switch display mode
   else if (ch == 'm' || ch == 'M')
      mode = 1-mode;
   else if (ch == 'f' || ch == 'F')
      fp = 1-fp;
   //  Change field of view angle
   else if (ch == '-' && ch>1)
      fov--;
   else if (ch == '+' && ch<179)
      fov++;

   //  Reproject
   Project();
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width,int height)
{
   //  Ratio of the width to the height of the window
   asp = (height>0) ? (double)width/height : 1;
   //  Set the viewport to the entire window
   glViewport(0,0, width,height);
   //  Set projection
   Project();
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
   glutCreateWindow("Scene in 3D - Cathy Yang");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   //  Pass control to GLUT so it can interact with the user
   glutMainLoop();
   return 0;
}
