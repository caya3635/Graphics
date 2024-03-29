//edited ex15
//some cylinder action here https://github.com/SonarSystems/OpenGL-Tutorials

/*
 *  Textures and Lighting
 *
 *  Demonstrates using lighting and textures.
 *
 *  Key bindings:
 *  l          Toggle lighting on/off
 *  a/A        decrease/increase ambient light
 *  d/D        decrease/increase diffuse light
 *  s/S        decrease/increase specular light
 *  f/F        decrease/increase emitted light
 *  g/G        Decrease/increase shininess
 *  p	       Pause
 *  []         Lower/rise light
 *  ()	       Move light left/right
 *  arrows     Change view angle
 *  PgDn/PgUp  Zoom in and out
 *  0          Reset view angle
 *  ESC        Exit
 */

#include "CSCIx229.h"
#define PI 3.1415927
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int light=1;      //  Lighting
int rep=1;        //  Repitition
double asp=1;     //  Aspect ratio
double dim=3.0;   //  Size of world
int pause = 1;	  //  Pause

// Light values
int emission  =   0;  // Emission intensity (%)
int ambient   =  30;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;    // Shininess (value)
int zh        =  90;  // Light azimuth
float ylight  =   0;  // Elevation of light
unsigned int texture[3]; // Texture names

//some cylinder action
static void Soup(double x,double y,double z,
                 double dx,double dy,double dz,
                 double th)
{
   //  Set specular color to white
   float white[] = {1,1,1,1};
   float Emission[]  = {0.0,0.0,0.01*emission,1.0};
   glMaterialf(GL_FRONT_AND_BACK,GL_SHININESS,shiny);
   glMaterialfv(GL_FRONT_AND_BACK,GL_SPECULAR,white);
   glMaterialfv(GL_FRONT_AND_BACK,GL_EMISSION,Emission);

   glPushMatrix();

   //  Transform cylinder
   glTranslated(x,y,z);
   glRotated(th,0,0,1);
   glScaled(dx,dy,dz);

   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[0]);

   double radius = 1;
   double height = 1.5;

   int j;
   glBegin(GL_QUAD_STRIP);
   for (j = 0; j <= 360; j+=.125) {
      const float tc = (j / (float) 360);

      double x = radius * Cos(j);
      double y = height;
      double z = radius * Sin(j);

      glNormal3d(Cos(j), 0, Sin(j));

      glTexCoord2f(-tc, 0.0); glVertex3d(x, -y, z);
      glTexCoord2f(-tc, 1.0); glVertex3d(x, y, z);
   }
   glEnd();

   double i; 

   glBindTexture(GL_TEXTURE_2D,texture[1]);

   glNormal3d(0,1,0);

   /* Top of Cylinder */
   glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5,0.5); 
      glVertex3d(0.0, height, 0.0);

      for(i = 0.0; i <= 360; i+=10) {
         glTexCoord2f(-0.5*Cos(i)+0.5, 0.5*Sin(i)+0.5);
         glVertex3d(radius * Cos(i), height, radius * Sin(i));
      }
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glNormal3d(0,-1,0);

   /* Bottom of Cylinder */
   glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5,0.5); 
      glVertex3d(0.0, -height, 0.0);

      for(i = 0.0; i <= 360; i+=10) {
         glTexCoord2f(0.5*Cos(i)+0.5, 0.5*Sin(i)+0.5);
         glVertex3d(radius * Cos(i), -height, radius * Sin(i));
      }
   glEnd();

   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

/*
 *  Draw a ball
 *     at (x,y,z)
 *     radius r
 */
static void ball(double x,double y,double z,double r)
{
   //  Save transformation
   glPushMatrix();
   //  Offset, scale and rotate
   glTranslated(x,y,z);
   glScaled(r,r,r);
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
   //  Eye position
   double Ex = -5*dim*Sin(th)*Cos(ph);
   double Ey = +5*dim        *Sin(ph);
   double Ez = +5*dim*Cos(th)*Cos(ph);
   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
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
      ball(Position[0],Position[1],Position[2] , 0.1);
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
   }
   else
      glDisable(GL_LIGHTING);
   
   //  Draw scene
   Soup(0, 0, 0, 0.5, 0.5, 0.5, 80);
   
   glColor3f(0.5, 0.2, 0);
   Soup(1, 1, 1, 0.6, -0.5, 0.2 , 180);

   glColor3f(1, 0.46, 0.9);
   Soup(-2, -0.4, 5, 0.1, 0.3, 0.8, 20);

   glColor3f(0.8, 0.46, 0.87);
   Soup(-1, 2, 3.5, 0.7, 0.6, 0.5, -60);

   glColor3f(0.46, 0.87, 0.87);
   Soup(1.4, -3, -1.8 , 1, 0.9, 0.8 , -88);
   
   const double len=2.0;	
   //  Draw axes - no lighting from here on
   glDisable(GL_LIGHTING);
   glColor3f(1,1,1);
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

   //  Display parameters
   glWindowPos2i(5,5);
   Print("Angle=%d,%d  Dim=%.1f Light=%s",th,ph,dim,light?"On":"Off");
   
   if (light)
   {
      glWindowPos2i(5,25);
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
   //  Keep angles to +/-360 degrees
   th %= 360;
   ph %= 360;
   //  Update projection
   Project(45,asp,dim);
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

   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Pause light
   else if (ch == 'p')
      pause = 1-pause;
   
   //  Light elevation
   else if (ch=='[')
      ylight -= 5;
   else if (ch==']')
      ylight += 5;
   
   else if (ch=='(')
      zh -= 5;
   else if (ch==')')
      zh += 5;

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
   else if (ch=='f' && emission>0)
      emission -= 5;
   else if (ch=='F' && emission<100)
      emission += 5;
   
   //  Shininess level
   else if (ch=='g' && shininess>-1)
      shininess -= 1;
   else if (ch=='G' && shininess<7)
      shininess += 1;
   
   //  Repitition
   else if (ch=='+')
      rep++;
   else if (ch=='-' && rep>1)
      rep--;
   
   //  Translate shininess power to value (-1 => 0)
   shiny = shininess<0 ? 0 : pow(2.0,shininess);
   //  Reproject
   Project(45,asp,dim);
   //  Pause/Move as requested
   glutIdleFunc(pause?idle:NULL);
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
   Project(45,asp,dim);
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
   glutCreateWindow("Textures and Lighting - Cathy Yang");
   //  Set callbacks
   glutDisplayFunc(display);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);

   //  Load textures
   texture[0] = LoadTexBMP("label.bmp");
   texture[1] = LoadTexBMP("top.bmp");
   texture[2] = LoadTexBMP("bottom.bmp");
   
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
