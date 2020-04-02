//edited ex 7
//ref'd https://gist.github.com/nikAizuddin/5ea402e9073f1ef76ba6 for some cylinder action

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

#define PI 3.1415927
int mode=0;       //  Projection mode
double dim=5.0;   //  Size of world
int th = 0.0;         //  Azimuth of view angle
int ph = 0.0;         //  Elevation of view angle

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

static void Project()
{
   //  Tell OpenGL we want to manipulate the projection matrix
   glMatrixMode(GL_PROJECTION);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective transformation
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
/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
	//  Erase the window and the depth buffer
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//  Enable Z-buffering in OpenGL
	glEnable(GL_DEPTH_TEST);
	//  Undo previous transformations
	glLoadIdentity();
	//  Set view angle
	glRotatef(ph, 1, 0, 0);
	glRotatef(th, 0, 1, 0);
	
	//just put em somewhere
	H(-1.5, -0.35, 1.5, 0.4, 0.75, 0.5, -30);
	//H(-1.5, -0.68, 1.5, 0.4, 0.75, 0.5, -30);
	E(3,2,1,1,1,1,60);
	//E(3,-1,1,1,1,1,60);
	L(1.5,-1,0,0.6,0.6,0.6,-30);
	//L(1.5,-2,0,0.6,0.6,0.6,-30);	
	P(2,-0.5,0,4,3,2,-30);
	P(-0.5,-1.5,0,0.3,.4,0.6, 120);
	
	//  Render the scene
	glFlush();
	//  Make the rendered scene visible
	glutSwapBuffers();
}

/*
 *  GLUT calls this routine when an arrow key is pressed
 */
void special(int key, int x, int y)
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
	//  Keep angles to +/-360 degrees
	th %= 360;
	ph %= 360;
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when a key is pressed
 */
void key(unsigned char ch, int x, int y)
{
	//  Exit on ESC
	if (ch == 27)
		exit(0);
	//view angle to XY
	else if (ch == '1')
		th = ph = 0;

	//view angle to YZ
   	else if (ch == '2') {
      		th = 90;
      		ph = 0;
   	}
   	//view angle to XZ
   	else if (ch == '3') {
      		th = 0;
      		ph = -90;
   	}
	else if (ch == 'm' || ch == 'M')
      		mode = 1-mode;
	
	//  Tell GLUT it is necessary to redisplay the scene
	glutPostRedisplay();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void reshape(int width, int height)
{
	const double dim = 2.5;
	//  Ratio of the width to the height of the window
	double w2h = (height > 0) ? (double)width / height : 1;
	//  Set the viewport to the entire window
	glViewport(0, 0, width, height);
	//  Tell OpenGL we want to manipulate the projection matrix
	glMatrixMode(GL_PROJECTION);
	//  Undo previous transformations
	glLoadIdentity();
	//  Orthogonal projection
	glOrtho(-w2h * dim, +w2h * dim, -dim, +dim, -dim, +dim);
	//  Switch to manipulating the model matrix
	glMatrixMode(GL_MODELVIEW);
	//  Undo previous transformations
	glLoadIdentity();
}


/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc, char* argv[])
{
	//  Initialize GLUT and process user parameters
	glutInit(&argc, argv);
	//  Request double buffered, true color window with Z buffering at 600x600
	glutInitWindowSize(600, 600);
	glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);
	//  Create the window
	glutCreateWindow("3D Object - Cathy Yang");
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
	return 0;
}
