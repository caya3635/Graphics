/*
 *  Transparency
 *
 *  Demonstrates transpareny using a single transparent object.
 *
 *  Key bindings:
 *  l/L        Toggles lighting on/off
 *  m/M        Toggle texture mode modulate/replace
 *  c/C        Toggle white/colored faces
 *  F1         Toggle depth test
 *  +/-        Increase/decrease alpha
 *  a/A        Decrease/increase ambient light
 *  d/D        Decrease/increase diffuse light
 *  s/S        Decrease/increase specular light
 *  e/E        Decrease/increase emitted light
 *  n/N        Decrease/increase shininess
 *  []         Lower/rise light
 *  x          Toggle axes
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */
#include "CSCIx229.h"
int mode=0;       //  Texture mode
int depth=0;      //  Depth test
int ntex=0;       //  Cube faces
int axes=1;       //  Display axes
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int light=1;      //  Lighting
int color=0;      //  Colored faces
int alpha=100;    //  Transparency
double asp=1;     //  Aspect ratio
double dim=1.0;   //  Size of world
// Light values
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;  // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light
unsigned int texture[7]; // Texture names

/*
 *  Draw a cube
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void cube(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,mode?GL_REPLACE:GL_MODULATE);
   glColor4f(1,1,1,0.01*alpha);
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   //  Enable blending
   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA,GL_ONE);
   //  Front
   if (color) glColor4f(1,0,0,0.01*alpha);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_QUADS);
   glNormal3f( 0.0, 0.0, 1.0);
   glTexCoord2f(0,0); glVertex3f(-1.0,-1.0, 1.0);
   glTexCoord2f(1,0); glVertex3f(+1.0,-1.0, 1.0);
   glTexCoord2f(1,1); glVertex3f(+1.0,+1.0, 1.0);
   glTexCoord2f(0,1); glVertex3f(-1.0,+1.0, 1.0);
   glEnd();
   //  Back
   if (color) glColor4f(0,0,1,0.01*alpha);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f( 0.0, 0.0,-1.0);
   glTexCoord2f(0,0); glVertex3f(+1.0,-1.0,-1.0);
   glTexCoord2f(1,0); glVertex3f(-1.0,-1.0,-1.0);
   glTexCoord2f(1,1); glVertex3f(-1.0,+1.0,-1.0);
   glTexCoord2f(0,1); glVertex3f(+1.0,+1.0,-1.0);
   glEnd();
   //  Right
   if (color) glColor4f(1,1,0,0.01*alpha);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f(+1.0, 0.0, 0.0);
   glTexCoord2f(0,0); glVertex3f(+1.0,-1.0,+1.0);
   glTexCoord2f(1,0); glVertex3f(+1.0,-1.0,-1.0);
   glTexCoord2f(1,1); glVertex3f(+1.0,+1.0,-1.0);
   glTexCoord2f(0,1); glVertex3f(+1.0,+1.0,+1.0);
   glEnd();
   //  Left
   if (color) glColor4f(0,1,0,0.01*alpha);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[4]);
   glBegin(GL_QUADS);
   glNormal3f(-1.0, 0.0, 0.0);
   glTexCoord2f(0,0); glVertex3f(-1.0,-1.0,-1.0);
   glTexCoord2f(1,0); glVertex3f(-1.0,-1.0,+1.0);
   glTexCoord2f(1,1); glVertex3f(-1.0,+1.0,+1.0);
   glTexCoord2f(0,1); glVertex3f(-1.0,+1.0,-1.0);
   glEnd();
   //  Top
   if (color) glColor4f(0,1,1,0.01*alpha);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f( 0.0,+1.0, 0.0);
   glTexCoord2f(0,0); glVertex3f(-1.0,+1.0,+1.0);
   glTexCoord2f(1,0); glVertex3f(+1.0,+1.0,+1.0);
   glTexCoord2f(1,1); glVertex3f(+1.0,+1.0,-1.0);
   glTexCoord2f(0,1); glVertex3f(-1.0,+1.0,-1.0);
   glEnd();
   //  Bottom
   if (color) glColor4f(1,0,1,0.01*alpha);
   if (ntex) glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_QUADS);
   glNormal3f( 0.0,-1.0, 0.0);
   glTexCoord2f(0,0); glVertex3f(-1.0,-1.0,-1.0);
   glTexCoord2f(1,0); glVertex3f(+1.0,-1.0,-1.0);
   glTexCoord2f(1,1); glVertex3f(+1.0,-1.0,+1.0);
   glTexCoord2f(0,1); glVertex3f(-1.0,-1.0,+1.0);
   glEnd();
   //  Undo transformations and textures
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
   glDisable(GL_BLEND);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     dimensions (dx,dy,dz)
 *     rotated th about the y axis
 */
static void ball(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glRotated(th,0,1,0);
   glScaled(dx,dy,dz);
   //  White ball
   glColor3f(1,1,1);
   glutSolidSphere(1.0,16,16);
   //  Undo transofrmations
   glPopMatrix();
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Length of axes
   const double len=2.0;
   //  Eye position
   double Ex = -2*dim*Sin(th)*Cos(ph);
   double Ey = +2*dim        *Sin(ph);
   double Ez = +2*dim*Cos(th)*Cos(ph);
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   if (depth)
      glEnable(GL_DEPTH_TEST);
   else
      glDisable(GL_DEPTH_TEST);
   //  Set perspective
   glLoadIdentity();
   gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   //  Light switch
   if (light)
   {
      //  Translate intensity to color vectors
      float Ambient[]   = {0.01*ambient ,0.01*ambient ,0.01*ambient ,1.0};
      float Diffuse[]   = {0.01*diffuse ,0.01*diffuse ,0.01*diffuse ,1.0};
      float Specular[]  = {0.01*specular,0.01*specular,0.01*specular,1.0};
      //  Light direction
      float Position[]  = {5*Cos(zh),ylight,5*Sin(zh),1};
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 0.1,0.1,0.1 , 0);
      //  OpenGL should normalize normal vectors
      glEnable(GL_NORMALIZE);
      //  Enable lighting
      glEnable(GL_LIGHTING);
      //  glColor sets ambient and diffuse color materials
      glColorMaterial(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE);
      glEnable(GL_COLOR_MATERIAL);
      //  Enable light 0
      glEnable(GL_LIGHT0);
      //  Set ambient, diffuse, specular components and position of light 0
      glLightfv(GL_LIGHT0,GL_AMBIENT ,Ambient);
      glLightfv(GL_LIGHT0,GL_DIFFUSE ,Diffuse);
      glLightfv(GL_LIGHT0,GL_SPECULAR,Specular);
      glLightfv(GL_LIGHT0,GL_POSITION,Position);
      glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1);
   }
   else
      glDisable(GL_LIGHTING);
   //  Draw scene
   cube(0,0,0 , 0.5,0.5,0.5 , 0);
   
   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
   if (axes)
   {
      glBegin(GL_LINES);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(len,0.0,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,len,0.0);
      glVertex3d(0.0,0.0,0.0);
      glVertex3d(0.0,0.0,len);
      glEnd();
      //  Label axes
      glRasterPos3d(len,0.0,0.0);
      Print("X");
      glRasterPos3d(0.0,len,0.0);
      Print("Y");
      glRasterPos3d(0.0,0.0,len);
      Print("Z");
   }
   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f Light=%s Texture=%s",th,ph,dim,light?"On":"Off",mode?"Replace":"Modulate");
    glWindowPos2i(5,25);
    Print("Alpha=%d  DepthTest=%s",alpha,depth?"On":"Off");
   if (light)
   {
      glWindowPos2i(5,45);
      Print("Ambient=%d  Diffuse=%d Specular=%d Emission=%d Shininess=%.0f",ambient,diffuse,specular,emission,shiny);
   }
   //  Render the scene and make it visible
   ErrCheck("display");
   glFlush();
   glutSwapBuffers();
}

/*
 *  GLUT calls this routine when the window is resized
 */
void idle()
{
   //  Elapsed time in seconds
   double t = glutGet(GLUT_ELAPSED_TIME)/1000.0;
   zh = fmod(90*t,360.0);
   //  Tell GLUT it is necessary to redisplay the scene
   glutPostRedisplay();
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
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Depth test
   else if (key == GLUT_KEY_F1)
      depth = 1-depth;
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(60,asp,dim);
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
   //  Toggle texture mode
   else if (ch == 'm' || ch == 'M')
      mode = 1-mode;
   //  Toggle axes
   else if (ch == 'x' || ch == 'X')
      axes = 1-axes;
   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Toggle colored faces
   else if (ch == 'c' || ch == 'C')
      color = 1-color;
   //  Toggle textures mode
   else if (ch == 't')
      ntex = 1-ntex;
   //  Light elevation
   else if (ch=='[')
      ylight -= 0.1;
   else if (ch==']')
      ylight += 0.1;
   //  Ambient level
   else if (ch=='a' && ambient>0)
      ambient -= 5;
   else if (ch=='A' && ambient<100)
      ambient += 5;
   //  Diffuse level
   else if (ch=='d' && diffuse>0)
      diffuse -= 5;
   else if (ch=='D' && diffuse<100)
      diffuse += 5;
   //  Specular level
   else if (ch=='s' && specular>0)
      specular -= 5;
   else if (ch=='S' && specular<100)
      specular += 5;
   //  Emission level
   else if (ch=='e' && emission>0)
      emission -= 5;
   else if (ch=='E' && emission<100)
      emission += 5;
   //  Shininess level
   else if (ch=='n' && shininess>-1)
      shininess -= 1;
   else if (ch=='N' && shininess<7)
      shininess += 1;
   //  Repitition
   else if (ch=='+' && alpha<100)
      alpha += 5;
   else if (ch=='-' && alpha>0)
      alpha -= 5;
   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(60,asp,dim);
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
   Project(60,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE | GLUT_ALPHA);
   glutInitWindowSize(600,600);
   glutCreateWindow("Transparency");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Load textures
   texture[0] = LoadTexBMP("glass.bmp");
   texture[1] = LoadTexBMP("img1.bmp");
   texture[2] = LoadTexBMP("img2.bmp");
   texture[3] = LoadTexBMP("img3.bmp");
   texture[4] = LoadTexBMP("img4.bmp");
   texture[5] = LoadTexBMP("img5.bmp");
   texture[6] = LoadTexBMP("img6.bmp");
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
