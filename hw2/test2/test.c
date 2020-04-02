 /*	Colin O'Connell HW3
	*Some code taken directly from professor's example files
	*Saw how to do translations from https://github.com/dmurtari/csci4229
	*Some of chair code edited from http://programmerts.blogspot.com
 */
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

int th = 45.0;         //  Azimuth of view angle
int ph = 45.0;         //  Elevation of view angle

//Draw a chair object
static void chair(double x, double y, double z, double dx, double dy, double dz, double th) {
	
	// Translations
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);

	glBegin(GL_QUADS);

	glColor3f(0.71f, 0.65f, 0.26f);
	//Front of chair seat
	glVertex3f(-0.5f, -0.05f, 0.5f);
	glVertex3f(0.5f, -0.05f, 0.5f);
	glVertex3f(0.5f, 0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, 0.5f);

	
	//Right side of chair seat
	glVertex3f(0.5f, -0.05f, -0.5f);
	glVertex3f(0.5f, 0.05f, -0.5f);
	glVertex3f(0.5f, 0.05f, 0.5f);
	glVertex3f(0.5f, -0.05f, 0.5f);

	
	//Back side of chair seat
	glVertex3f(-0.5f, -0.05f, -0.5f);
	glVertex3f(-0.5f, 0.05f, -0.5f);
	glVertex3f(0.5f, 0.05f, -0.5f);
	glVertex3f(0.5f, -0.05f, -0.5f);

	
	//Left side of chair seat
	glVertex3f(-0.5f, -0.05f, -0.5f);
	glVertex3f(-0.5f, -0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, -0.5f);

	//Top of chair seat
	glVertex3f(0.5f, 0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, -0.5f);
	glVertex3f(0.5f, 0.05f, -0.5f);

	
	//Bottom of chair seat
	glVertex3f(0.5f, -0.05f, 0.5f);
	glVertex3f(-0.5f, -0.05f, 0.5f);
	glVertex3f(-0.5f, -0.05f, -0.5f);
	glVertex3f(0.5f, -0.05f, -0.5f);


	glColor3f(0.9f, 0.91f, 0.98f);
	//Front right leg

	//Front side
	glVertex3f(0.45f, -0.05f, 0.4f);
	glVertex3f(0.35f, -0.05f, 0.4f);
	glVertex3f(0.35f, -0.75f, 0.4f);
	glVertex3f(0.45f, -0.75f, 0.4f);
	
	//Back side
	glVertex3f(0.45f, -0.05f, 0.3f);
	glVertex3f(0.35f, -0.05f, 0.3f);
	glVertex3f(0.35f, -0.75f, 0.3f);
	glVertex3f(0.45f, -0.75f, 0.3f);
	
	//Right side
	glVertex3f(0.45f, -0.05f, 0.4f);
	glVertex3f(0.45f, -0.05f, 0.3f);
	glVertex3f(0.45f, -0.75f, 0.3f);
	glVertex3f(0.45f, -0.75f, 0.4f);

	//Left side
	glVertex3f(0.35f, -0.05f, 0.4f);
	glVertex3f(0.35f, -0.05f, 0.3f);
	glVertex3f(0.35f, -0.75f, 0.3f);
	glVertex3f(0.35f, -0.75f, 0.4f);

	//Back Right Leg

	//Front side
	glVertex3f(0.45f, -0.05f, -0.3f);
	glVertex3f(0.35f, -0.05f, -0.3f);
	glVertex3f(0.35f, -0.75f, -0.3f);
	glVertex3f(0.45f, -0.75f, -0.3f);
	
	//Back side
	glVertex3f(0.45f, -0.05f, -0.4f);
	glVertex3f(0.35f, -0.05f, -0.4f);
	glVertex3f(0.35f, -0.75f, -0.4f);
	glVertex3f(0.45f, -0.75f, -0.4f);

	//Right side
	glVertex3f(0.45f, -0.05f, -0.4f);
	glVertex3f(0.45f, -0.05f, -0.3f);
	glVertex3f(0.45f, -0.75f, -0.3f);
	glVertex3f(0.45f, -0.75f, -0.4f);

	//Left side
	glVertex3f(0.35f, -0.05f, -0.4f);
	glVertex3f(0.35f, -0.05f, -0.3f);
	glVertex3f(0.35f, -0.75f, -0.3f);
	glVertex3f(0.35f, -0.75f, -0.4f);

	//Front Left Leg
	
	//Front side
	glVertex3f(-0.45f, -0.05f, 0.4f);
	glVertex3f(-0.35f, -0.05f, 0.4f);
	glVertex3f(-0.35f, -0.75f, 0.4f);
	glVertex3f(-0.45f, -0.75f, 0.4f);
	
	//Back side

	glVertex3f(-0.45f, -0.05f, 0.3f);
	glVertex3f(-0.35f, -0.05f, 0.3f);
	glVertex3f(-0.35f, -0.75f, 0.3f);
	glVertex3f(-0.45f, -0.75f, 0.3f);

	//Right side

	glVertex3f(-0.45f, -0.05f, 0.4f);
	glVertex3f(-0.45f, -0.05f, 0.3f);
	glVertex3f(-0.45f, -0.75f, 0.3f);
	glVertex3f(-0.45f, -0.75f, 0.4f);

	//Left side

	glVertex3f(-0.35f, -0.05f, 0.4f);
	glVertex3f(-0.35f, -0.05f, 0.3f);
	glVertex3f(-0.35f, -0.75f, 0.3f);
	glVertex3f(-0.35f, -0.75f, 0.4f);

	//Back Left Leg

	//Front side
	glVertex3f(-0.45f, -0.05f, -0.3f);
	glVertex3f(-0.35f, -0.05f, -0.3f);
	glVertex3f(-0.35f, -0.75f, -0.3f);
	glVertex3f(-0.45f, -0.75f, -0.3f);
	
	//Back side
	glVertex3f(-0.45f, -0.05f, -0.4f);
	glVertex3f(-0.35f, -0.05f, -0.4f);
	glVertex3f(-0.35f, -0.75f, -0.4f);
	glVertex3f(-0.45f, -0.75f, -0.4f);

	//Right side
	glVertex3f(-0.45f, -0.05f, -0.4f);
	glVertex3f(-0.45f, -0.05f, -0.3f);
	glVertex3f(-0.45f, -0.75f, -0.3f);
	glVertex3f(-0.45f, -0.75f, -0.4f);

	//Left side
	glVertex3f(-0.35f, -0.05f, -0.4f);
	glVertex3f(-0.35f, -0.05f, -0.3f);
	glVertex3f(-0.35f, -0.75f, -0.3f);
	glVertex3f(-0.35f, -0.75f, -0.4f);

	glColor3f(0.65f, 0.50f, 0.39f);
	//Chair Back

	//Front side
	glVertex3f(-0.45f, 0.05f, -0.45f);
	glVertex3f(0.45f, 0.05f, -0.45f);
	glVertex3f(0.45f, 0.875f, -0.45f);
	glVertex3f(-0.45f, 0.875f, -0.45f);
	
	//Back side
	glVertex3f(-0.45f, 0.05f, -0.5f);
	glVertex3f(0.45f, 0.05f, -0.5f);
	glVertex3f(0.45f, 0.875f, -0.5f);
	glVertex3f(-0.45f, 0.875f, -0.5f);

	//Left side
	glVertex3f(-0.45f, 0.05f, -0.5f);
	glVertex3f(-0.45f, 0.875f, -0.5f);
	glVertex3f(-0.45f, 0.875f, -0.45f);
	glVertex3f(-0.45f, 0.05f, -0.45f);
	
	//Right side
	glVertex3f(0.45f, 0.05f, -0.5f);
	glVertex3f(0.45f, 0.875f, -0.5f);
	glVertex3f(0.45f, 0.875f, -0.45f);
	glVertex3f(0.45f, 0.05f, -0.45f);
	
	//Top
	glVertex3f(-0.45f, 0.875f, -0.5f);
	glVertex3f(-0.45f, 0.875f, -0.45f);
	glVertex3f(0.45f, 0.875f, -0.45f);
	glVertex3f(0.45f, 0.875f, -0.5f);

	glEnd();
}

//Draw a bench object
static void bench(double x, double y, double z, double dx, double dy, double dz, double th) {

	// Translations
	glTranslated(x, y, z);
	glRotated(th, 0, 1, 0);
	glScaled(dx, dy, dz);

	glBegin(GL_QUADS);

	glColor3f(0.91f, 0.76f, 0.65f);
	//Front of bench
	glVertex3f(-0.5f, -0.05f, 0.5f);
	glVertex3f(0.5f, -0.05f, 0.5f);
	glVertex3f(0.5f, 0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, 0.5f);


	//Right side of bench
	glVertex3f(0.5f, -0.05f, -0.5f);
	glVertex3f(0.5f, 0.05f, -0.5f);
	glVertex3f(0.5f, 0.05f, 0.5f);
	glVertex3f(0.5f, -0.05f, 0.5f);


	//Back side of bench
	glVertex3f(-0.5f, -0.05f, -0.5f);
	glVertex3f(-0.5f, 0.05f, -0.5f);
	glVertex3f(0.5f, 0.05f, -0.5f);
	glVertex3f(0.5f, -0.05f, -0.5f);


	//Left side of bench
	glVertex3f(-0.5f, -0.05f, -0.5f);
	glVertex3f(-0.5f, -0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, -0.5f);

	//Top of bench
	glVertex3f(0.5f, 0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, 0.5f);
	glVertex3f(-0.5f, 0.05f, -0.5f);
	glVertex3f(0.5f, 0.05f, -0.5f);


	//Bottom of bench
	glVertex3f(0.5f, -0.05f, 0.5f);
	glVertex3f(-0.5f, -0.05f, 0.5f);
	glVertex3f(-0.5f, -0.05f, -0.5f);
	glVertex3f(0.5f, -0.05f, -0.5f);


	glColor3f(0.52f, 0.37f, 0.26f);
	//Front right leg

	//Front side
	glVertex3f(0.45f, -0.05f, 0.4f);
	glVertex3f(0.35f, -0.05f, 0.4f);
	glVertex3f(0.35f, -0.75f, 0.4f);
	glVertex3f(0.45f, -0.75f, 0.4f);

	//Back side
	glVertex3f(0.45f, -0.05f, 0.3f);
	glVertex3f(0.35f, -0.05f, 0.3f);
	glVertex3f(0.35f, -0.75f, 0.3f);
	glVertex3f(0.45f, -0.75f, 0.3f);

	//Right side
	glVertex3f(0.45f, -0.05f, 0.4f);
	glVertex3f(0.45f, -0.05f, 0.3f);
	glVertex3f(0.45f, -0.75f, 0.3f);
	glVertex3f(0.45f, -0.75f, 0.4f);

	//Left side
	glVertex3f(0.35f, -0.05f, 0.4f);
	glVertex3f(0.35f, -0.05f, 0.3f);
	glVertex3f(0.35f, -0.75f, 0.3f);
	glVertex3f(0.35f, -0.75f, 0.4f);

	//Back Right Leg

	//Front side
	glVertex3f(0.45f, -0.05f, -0.3f);
	glVertex3f(0.35f, -0.05f, -0.3f);
	glVertex3f(0.35f, -0.75f, -0.3f);
	glVertex3f(0.45f, -0.75f, -0.3f);

	//Back side
	glVertex3f(0.45f, -0.05f, -0.4f);
	glVertex3f(0.35f, -0.05f, -0.4f);
	glVertex3f(0.35f, -0.75f, -0.4f);
	glVertex3f(0.45f, -0.75f, -0.4f);

	//Right side
	glVertex3f(0.45f, -0.05f, -0.4f);
	glVertex3f(0.45f, -0.05f, -0.3f);
	glVertex3f(0.45f, -0.75f, -0.3f);
	glVertex3f(0.45f, -0.75f, -0.4f);

	//Left side
	glVertex3f(0.35f, -0.05f, -0.4f);
	glVertex3f(0.35f, -0.05f, -0.3f);
	glVertex3f(0.35f, -0.75f, -0.3f);
	glVertex3f(0.35f, -0.75f, -0.4f);

	//Front Left Leg

	//Front side
	glVertex3f(-0.45f, -0.05f, 0.4f);
	glVertex3f(-0.35f, -0.05f, 0.4f);
	glVertex3f(-0.35f, -0.75f, 0.4f);
	glVertex3f(-0.45f, -0.75f, 0.4f);

	//Back side

	glVertex3f(-0.45f, -0.05f, 0.3f);
	glVertex3f(-0.35f, -0.05f, 0.3f);
	glVertex3f(-0.35f, -0.75f, 0.3f);
	glVertex3f(-0.45f, -0.75f, 0.3f);

	//Right side

	glVertex3f(-0.45f, -0.05f, 0.4f);
	glVertex3f(-0.45f, -0.05f, 0.3f);
	glVertex3f(-0.45f, -0.75f, 0.3f);
	glVertex3f(-0.45f, -0.75f, 0.4f);

	//Left side

	glVertex3f(-0.35f, -0.05f, 0.4f);
	glVertex3f(-0.35f, -0.05f, 0.3f);
	glVertex3f(-0.35f, -0.75f, 0.3f);
	glVertex3f(-0.35f, -0.75f, 0.4f);

	//Back Left Leg

	//Front side
	glVertex3f(-0.45f, -0.05f, -0.3f);
	glVertex3f(-0.35f, -0.05f, -0.3f);
	glVertex3f(-0.35f, -0.75f, -0.3f);
	glVertex3f(-0.45f, -0.75f, -0.3f);

	//Back side
	glVertex3f(-0.45f, -0.05f, -0.4f);
	glVertex3f(-0.35f, -0.05f, -0.4f);
	glVertex3f(-0.35f, -0.75f, -0.4f);
	glVertex3f(-0.45f, -0.75f, -0.4f);

	//Right side
	glVertex3f(-0.45f, -0.05f, -0.4f);
	glVertex3f(-0.45f, -0.05f, -0.3f);
	glVertex3f(-0.45f, -0.75f, -0.3f);
	glVertex3f(-0.45f, -0.75f, -0.4f);

	//Left side
	glVertex3f(-0.35f, -0.05f, -0.4f);
	glVertex3f(-0.35f, -0.05f, -0.3f);
	glVertex3f(-0.35f, -0.75f, -0.3f);
	glVertex3f(-0.35f, -0.75f, -0.4f);

	glEnd();
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

	//Draw the first normal chair
	chair(0,0,0,1,1,1,0);
	//Draw the second smaller, offset chair
	chair(1.5, -0.35, 1.5, 0.4, 0.75, 0.5, -30);
	//Draw bench item
	bench(-2, 0, 1.5, 4, 1, 1, 0);

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
	//  Reset view angle
	else if (ch == '0')
		th = ph = 0;
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
	glutCreateWindow("Assignment 3: Colin O'Connell");
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
