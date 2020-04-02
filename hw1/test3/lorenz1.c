/*
 *  Sahle A. Alturaigi
 *  Sept. 17th, 2013
 *  Finished: Sept. 20th, 2013
 *
 *  Lorentz Attractor:
 * Simple program to demonstrate generating coordinates
 * using the Lorenz Attractor
 *
 * Got some help from the following website:
 * https://github.com/mikepack/lorenz/blob/master/lorenz.c
 * http://stackoverflow.com/questions/12507054/lorenz-attractor-in-opengl
 * http://gamedev.stackexchange.com/questions/13008/how-to-get-and-use-delta-time/13011#13011
 * And from Professor Schreüder, Willam's example code
 *
 */

 /// Missing feature: Lorenz Drawing animation

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



// Globals
int th = 0;     // Azimuth of view angle
int ph = 0;     // Elevation (Altitude) of view angle
int FOV = 60;   // Field of view (for perspective)

int VERTICES = 50000;   // Number of points that will be generated
int MODE = 1;           // 1 = Orthongonal, 2 = Perspective
int SHOW_AXIS = 1;      // 1 = show grid, 0 = hide grid.
int NEED_UPDATE = 1;    // 1 = update array. 0 = update not needed.

double SCALE = 80;      // Scale of orthogonal box (scale might not be the best word...)
double ASPECT = 1;      // Aspect ratio.

GLdouble LOR_PTS[50000][3]; // Array to store coordinates
char* text[] = {"Orthogonal", "3D Persepctive"}; // Dimension display text

/*  Lorenz Parameters  */
double sigma  = 10;
double b  = 2.6666;
double r  = 28;

// Macros for sin & cos in degrees to radians
#define Cos(th) cos(3.1415927/180*(th))
#define Sin(th) sin(3.1415927/180*(th))

//------------------------------------------------------------
/*  Prototypes  */
// Generates Lorentz coordinates and stores them in global array.
void generate_array_pts();
// Display function to pass to glutDisplayFunc()
void display();
// Draws the cartesian plane
void draw_axes();
// Creates the perspective projection
static void Project(double aspect_ratio);
// Reshapes projection of window gets resized
void reshape(int width, int height);
// Button presses
void key(unsigned char ch, int x, int y);
// Arrow key presses
void special_key(int key, int x, int y);
/// MAY NOT NEED
void idle();

//------------------------------------------------------------
#define LEN 8192 // Maximum length of text string
void Print(const char* format, ...)
{
    char buf[LEN];
    char* ch = buf;
    va_list args;
    // Turn the parameters into a character string
    va_start(args, format);
    vsnprintf(buf, LEN, format, args);
    va_end(args);
    // Display the characters one at a time at the current raster position
    while(*ch)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *ch++);
}

/*
 *  Main
 */
int main(int argc, char *argv[])
{
    // Initialize GLUT and process user parameters
    glutInit(&argc, argv);
    // Request double buffered, true color window
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    // Request 500 x 500 pixel window
    glutInitWindowSize(1000, 1000);
    // Create the window
    glutCreateWindow("Lorentz Attractor");
    // Tell GLUT to call "display" when the scene should be drawn
    glutDisplayFunc(display);
    // Tell GLUT to call "reshape" when the window is resized
    glutReshapeFunc(reshape);
    // Tell GLUT to call "special_key" when an arrow key is pressed
    glutSpecialFunc(special_key);
    // Tell GLUT to call "key" when a key is pressed
    glutKeyboardFunc(key);
    /// May not need
    glutIdleFunc(idle);
    // Pass control to GLUT so it can interact with the user
    glutMainLoop();

    return 0;
}

/*  generate_array_pts  */
void generate_array_pts()
{
    if(NEED_UPDATE)
    {
        int i; // Control var
        // Coordinates
        double x = LOR_PTS[0][0] = 1;
        double y = LOR_PTS[0][1] = 1;
        double z = LOR_PTS[0][2] = 1;
        double dt = 0.001; // Time step

        //printf("%5d %8.3f %8.3f %8.3f\n",0,x,y,z);

        for (i=0; i<VERTICES-1; i++)
        {
            double dx = sigma*(y-x);
            double dy = x*(r-z)-y;
            double dz = x*y - b*z;
            x += dt*dx;
            y += dt*dy;
            z += dt*dz;

            if (SCALE == 0)
                continue;
            // Store in array so we don't need to call this func again.
            LOR_PTS[i+1][0] = x;//*(SCALE/30);
            LOR_PTS[i+1][1] = y;//*(SCALE/30);
            LOR_PTS[i+1][2] = z;//*(SCALE/30);
            //printf("%5d %8.3f %8.3f %8.3f\n",i+1,x,y,z);
        }
        NEED_UPDATE = 0;
    }
}

/*  display  */
void display()
{
    int i = 0; // Control var for for loops

    /*
    *   Max and Mins for each dimension of Lorenz attractor. Got from a separate program.
    *   I use it for generating different colors
    */
    double xmin = -17.950;
    double xmax = 19.721;
    double ymin = -23.986;
    double ymax = 27.352;
    double zmin = 0.961;
    double zmax = 48.337;

    // Clear the image
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //glPushMatrix();

    // Enable Z-buffering depth test
    glEnable(GL_DEPTH_TEST);

    // Enable Blending (To make it look nicer)
    glEnable(GL_BLEND);
    glEnable(GL_LINE_SMOOTH);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    // Reset previous transforms
    glLoadIdentity();

    /// Choose how to rotate (For ortho and perspective)
    if(MODE == 1) // Ortho
    {
        // Sets ortho rotation view
        glRotated(ph, 1, 0, 0);
        glRotated(th, 0, 1, 0);
    }
    else if(MODE == 2) // Perspective
    {
        double Ex = -2*SCALE*Sin(th)*Cos(ph);
        double Ey = +2*SCALE*Sin(ph);
        double Ez = +2*SCALE*Cos(th)*Cos(ph);
        gluLookAt(Ex, Ey, Ez, 0, 0, 0, 0, Cos(ph), 0);
    }

    // Set point color and size
    //glColor3f(1, 0.5, 0.5);

    // Create the array of lorenz points/update current array.
    generate_array_pts();

    /// Draw the Lorenz attractor
    glBegin(GL_LINE_STRIP);
    switch(MODE)
    {
    case 1: // Ortho view
        for(i = 0; i < VERTICES; ++i)
        {
            // Makes some cool colors!
            glColor3f(LOR_PTS[i][0]/xmax, LOR_PTS[i][1]/ymax, LOR_PTS[i][2]/zmax);
            glVertex3d(LOR_PTS[i][0], LOR_PTS[i][1], LOR_PTS[i][2]);
        }
        break;
    case 2: // Perspective view
        for(i = 0; i < VERTICES; ++i)
        {
            // Makes some other cool colors
            glColor3f(LOR_PTS[i][0]/xmin, LOR_PTS[i][1]/ymin, LOR_PTS[i][2]/zmin);
            glVertex3d(LOR_PTS[i][0], LOR_PTS[i][1], LOR_PTS[i][2]);
        }
        break;
    }

    glEnd();
    draw_axes(); // Draw the cartesian coordinate plane

    // Display parameters
    glColor3f(1, 1, 1);
    glWindowPos2i(5, 5);
    Print("View Angle=%d, %d Scale=%.1f FOV=%d Projection=%s", th, ph, SCALE, FOV, text[MODE-1]);

    glFlush();
    glutSwapBuffers();

    //glPopMatrix();
}

/*  draw_axes  */
void draw_axes()
{
    if(SHOW_AXIS)
    {
        float scaler = SCALE/1.5;

        // Draw axes in white
        glColor3f(1, 1, 1);
        glBegin(GL_LINES);
        glVertex3d(0, 0, 0);
        glVertex3d(scaler, 0, 0);
        glVertex3d(0, 0, 0);
        glVertex3d(0, scaler, 0);
        glVertex3d(0, 0, 0);
        glVertex3d(0, 0, scaler);
        glEnd();

        // Label Axes
        glRasterPos3d(scaler, 0, 0);
        Print("X");
        glRasterPos3d(0, scaler, 0);
        Print("Y");
        glRasterPos3d(0, 0, scaler);
        Print("Z");
    }
}

/*  Project  */
static void Project(double aspect_ratio)
{
    // Maniuplating projection matrix now in lieu of model matrix
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    if(MODE  == 1) // Ortho
        glOrtho(-aspect_ratio*SCALE, +aspect_ratio*SCALE, -SCALE, +SCALE, -SCALE, +SCALE);
    else if (MODE == 2) // Perspec
        gluPerspective(FOV, aspect_ratio, SCALE/4, 4*SCALE);

    // Going back to model view matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

/*  reshape  */
void reshape(int width, int height)
{
    // Ratio of the width to the height of the window
    ASPECT = (height>0) ? (double)width/height : 1;
    // Set the viewport to the entire window
    glViewport(0, 0, width, height);

    Project(ASPECT);
}

/*  key  */ /// INCOMPLETE (redraw key)
void key(unsigned char ch, int x, int y)
{
    // If ESC, quit program.
    if (ch == 27)
        exit(0);

    // Reset view angle
    else if (ch == '0')
    {
        th = 0;
        ph = 0;
        FOV = 55;
    }

    // Toggles the cartesian coordinate plane
    else if (ch == 'a')
    {
        switch(SHOW_AXIS)
        {
        case 1:
            SHOW_AXIS = 0;
            break;
        default:
            SHOW_AXIS = 1;
            break;
        }
    }

    // Switching between perspective and ortho
    else if ((ch == '1') || (ch == '2'))
    {
        switch(ch)
        {
        case '1':
            MODE = 1;
            break;
        case '2':
            MODE = 2;
            break;
        }
    }

    // Zoom in
    else if ((ch == 'w') || (ch == 'W'))
    {
        if(MODE == 1) // Ortho
            SCALE += 0.5;
        else if(MODE == 2)
            ++FOV;
        NEED_UPDATE = 1;
    }

    // Zoom out. Makes sure FOV and SCALE don't go below 1
    else if (((ch == 'q') || (ch == 'Q')) && ((FOV > 1) && (SCALE > 1)))
    {
        if(MODE == 1) // Ortho
            SCALE -= 0.5;
        else if(MODE == 2)
            --FOV;
        NEED_UPDATE = 1;
    }

    // Reproject
    Project(ASPECT);

    // Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

/*  special_key  */
void special_key(int key, int x, int y)
{
    // Right arrow key - increase azimuth by 5 degrees
    if (key == GLUT_KEY_RIGHT)
        th += 3;
    else if (key == GLUT_KEY_LEFT)
        th -= 3;
    else if (key == GLUT_KEY_UP)
        ph += 3;
    else if (key == GLUT_KEY_DOWN)
        ph -= 3;

    // Keep angles to +/-360 degrees
    th %= 360;
    ph %= 360;

    // Tell GLUT it is necessary to redisplay the scene
    glutPostRedisplay();
}

/*  idle  */
/// MAY NOT NEED
void idle()
{
    glutPostRedisplay();
}
