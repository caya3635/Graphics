//lighting help from HW3, bless
//SHADOW HELP from ex34, also bless.

#include "CSCIx229.h"
#define PI 3.1415927
int fp = 1;
int light=1;      //  Lighting
int mode=0;       //  Shadow mode
int proj=1;       //  Projection type
int th=0;         //  Azimuth of view angle
int ph=15;         //  Elevation of view angle
int fov=55;       //  Field of view (for perspective)
double asp=1;     //  Aspect ratio
double dim=3.0;   //  Size of world
int pause = 1;	  //  Pause
double smoke=0;
unsigned int texture[11]; // Texture names
// Light values
int emission  =   0;  // Emission intensity (%)
int ambient   =  60;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;    // Shininess (value)
int zh        =  80;  // Light azimuth
float Ylight  =   15;  // Elevation of light

#define Dfloor  25
#define Yfloor 	0
float N[] = {0, -1, 0}; // Normal vector for the plane
float E[] = {0, Yfloor, 0 }; // Point of the plane

#define MODE 6
void ShadowProjection(float L[4], float E[4], float N[4])
{
   float mat[16];
   float e = E[0]*N[0] + E[1]*N[1] + E[2]*N[2];
   float l = L[0]*N[0] + L[1]*N[1] + L[2]*N[2];
   float c = e - l;
   //  Create the matrix.
   mat[0] = N[0]*L[0]+c; mat[4] = N[1]*L[0];   mat[8]  = N[2]*L[0];   mat[12] = -e*L[0];
   mat[1] = N[0]*L[1];   mat[5] = N[1]*L[1]+c; mat[9]  = N[2]*L[1];   mat[13] = -e*L[1];
   mat[2] = N[0]*L[2];   mat[6] = N[1]*L[2];   mat[10] = N[2]*L[2]+c; mat[14] = -e*L[2];
   mat[3] = N[0];        mat[7] = N[1];        mat[11] = N[2];        mat[15] = -l;
   //  Multiply modelview matrix
   glMultMatrixf(mat);
}

/*
 *  Draw scene
 */

static void smoking(double x,double y,double z,double r)
{
   const int d=5;
   int th,ph;

   //  Save transformation
   glPushMatrix();
   //  Offset and scale
   glTranslated(x,y,z);
   glScaled(r,r,r);

   //  Latitude bands
   for (ph=-90;ph<90;ph+=d)
   {
      glBegin(GL_QUAD_STRIP);
      for (th=0;th<=360;th+=d)
      {
         glColor3f(1,1,1);
         glVertex3d(Sin(th)*Cos(ph) , Sin(ph) , Cos(th)*Cos(ph));
         glVertex3d(Sin(th)*Cos(ph+d) , Sin(ph+d) , Cos(th)*Cos(ph+d));
      }
      glEnd();
   }

   //  Undo transformations
   glPopMatrix();
}

void timer(int v) {
  if (pause == 1) {
    smoke += .05;
    if (smoke > 5.0) {
      smoke -= 5.0;
    }
    glutPostRedisplay();
  }
  glutTimerFunc(1000/100, timer, v);
}

static void pokecenter(double x,double y,double z,double th)
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
   
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   
   //  Front
   glBindTexture(GL_TEXTURE_2D,texture[0]);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0,0); glVertex3f(-3.5,-1.5, 1.5);
   glTexCoord2f(1,0); glVertex3f(+3.5,-1.5, 1.5);
   glTexCoord2f(1,1); glVertex3f(+3.5,+1.5, 1.5);
   glTexCoord2f(0,1); glVertex3f(-3.5,+1.5, 1.5);
   glEnd();

   //  Back
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   
   glBegin(GL_QUADS);
   glNormal3f( 0, 0,-1);
   glTexCoord2f(0,0); glVertex3f(+3.5,-1.5,-1.5);
   glTexCoord2f(1,0); glVertex3f(-3.5,-1.5,-1.5);
   glTexCoord2f(1,1); glVertex3f(-3.5,+1.5,-1.5);
   glTexCoord2f(0,1); glVertex3f(+3.5,+1.5,-1.5);
   glEnd();
   //  Right
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_QUADS);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(+3.5,-1.5,+1.5);
   glTexCoord2f(1,0); glVertex3f(+3.5,-1.5,-1.5);
   glTexCoord2f(1,1); glVertex3f(+3.5,+1.5,-1.5);
   glTexCoord2f(0,1); glVertex3f(+3.5,+1.5,+1.5);
   glEnd();
   //  Left
   glBindTexture(GL_TEXTURE_2D,texture[1]);
   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-3.5,-1.5,-1.5);
   glTexCoord2f(1,0); glVertex3f(-3.5,-1.5,+1.5);
   glTexCoord2f(1,1); glVertex3f(-3.5,+1.5,+1.5);
   glTexCoord2f(0,1); glVertex3f(-3.5,+1.5,-1.5);
   glEnd();
   //  Top
   glBindTexture(GL_TEXTURE_2D,texture[2]);
   glBegin(GL_QUADS);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0,0); glVertex3f(-3.5,+1.5,+1.5);
   glTexCoord2f(1,0); glVertex3f(+3.5,+1.5,+1.5);
   glTexCoord2f(1,1); glVertex3f(+3.5,+1.5,-1.5);
   glTexCoord2f(0,1); glVertex3f(-3.5,+1.5,-1.5);
   glEnd();

   //chimmey
  glBegin(GL_QUADS);
  // Left
  glNormal3f(-1, 0, 0);
  glColor3f(0.823, 0.196, 0.274);
  glVertex3f(+1.5,+1.5,+1);
  glVertex3f(+1.5,+2,+1);
  glVertex3f(+1.5,+2,-1);
  glVertex3f(+1.5,+1.5,-1);
  // Right
  glNormal3f(+1, 0, 0);
  glColor3f(0.823, 0.196, 0.274);
  glVertex3f(+2.5,+1.5,+1);
  glVertex3f(+2.5,+2,+1);
  glVertex3f(+2.5,+2,-1);
  glVertex3f(+2.5,+1.5,-1);
  // Back
  glNormal3f( 0, 0,-1);
  glColor3f(0.823, 0.196, 0.274);
  glVertex3f(+1.5,+1.5,-1);
  glVertex3f(+1.5,+2,-1);
  glVertex3f(+2.5,+2,-1);
  glVertex3f(+2.5,+1.5,-1);
  // Front
  glNormal3f( 0, 0, 1);
  glColor3f(0.823, 0.196, 0.274);
  glVertex3f(+1.5,+1.5,+1);
  glVertex3f(+1.5,+2,+1);
  glVertex3f(+2.5,+2,+1);
  glVertex3f(+2.5,+1.5,+1);
  
  // bottom
  glColor3f(0, 0, 0);
  glVertex3f(+1.5,+1.51,-1);
  glVertex3f(+1.5,+1.51,+1);
  glVertex3f(+2.5,+1.51,+1);
  glVertex3f(+2.5,+1.51,-1);
  glEnd();
  
  // Chimney Smoke
  smoking(+2,+1+smoke,0, .2);
  smoking(+2,0+smoke,0, .2);
  smoking(+2,-1+smoke,0, .2);

   //  Undo transformations and textures
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);	
}

static void pokehouse(double x,double y,double z,double th)
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
   
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   
   //  Front
   glBindTexture(GL_TEXTURE_2D,texture[3]);
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0,0); glVertex3f(-2.5,-1.5, 2);
   glTexCoord2f(1,0); glVertex3f(+2.5,-1.5, 2);
   glTexCoord2f(1,1); glVertex3f(+2.5,+1.5, 2);
   glTexCoord2f(0,1); glVertex3f(-2.5,+1.5, 2);
   glEnd();
   
   //  Back
   glBindTexture(GL_TEXTURE_2D,texture[4]);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
   
   glBegin(GL_QUADS);
   glNormal3f( 0, 0,-1);
   glTexCoord2f(0,0); glVertex3f(+2.5,-1.5,-2);
   glTexCoord2f(1,0); glVertex3f(-2.5,-1.5,-2);
   glTexCoord2f(1,1); glVertex3f(-2.5,+1.5,-2);
   glTexCoord2f(0,1); glVertex3f(+2.5,+1.5,-2);
   glEnd();
   //  Right
   glBindTexture(GL_TEXTURE_2D,texture[4]);
   glBegin(GL_QUADS);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(+2.5,-1.5,+2);
   glTexCoord2f(1,0); glVertex3f(+2.5,-1.5,-2);
   glTexCoord2f(1,1); glVertex3f(+2.5,+1.5,-2);
   glTexCoord2f(0,1); glVertex3f(+2.5,+1.5,+2);
   glEnd();
   //  Left
   glBindTexture(GL_TEXTURE_2D,texture[4]);
   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-2.5,-1.5,-2);
   glTexCoord2f(1,0); glVertex3f(-2.5,-1.5,+2);
   glTexCoord2f(1,1); glVertex3f(-2.5,+1.5,+2);
   glTexCoord2f(0,1); glVertex3f(-2.5,+1.5,-2);
   glEnd();

   //roofthing
   glBindTexture(GL_TEXTURE_2D,texture[6]);
   glBegin(GL_TRIANGLES);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0,0); glVertex3f(-2.5,1.5, 2);
   glTexCoord2f(0.5,0); glVertex3f(+2.5,1.5, 2);
   glTexCoord2f(0,1); glVertex3f(0,+3, 2);
   glEnd();

   glBegin(GL_TRIANGLES);
   glNormal3f( 0, 0, -1);
   glTexCoord2f(0,0); glVertex3f(-2.5,1.5, -2);
   glTexCoord2f(0.5,0); glVertex3f(+2.5,1.5, -2);
   glTexCoord2f(0,1); glVertex3f(0,+3, -2);
   glEnd();

   glBindTexture(GL_TEXTURE_2D,texture[5]);
   glBegin(GL_QUADS);
   glNormal3f( -.5, 0, -.5);
   glTexCoord2f(0,0); glVertex3f(-2.5,+1.5,+2);
   glTexCoord2f(1,0); glVertex3f(-2.5,+1.5,-2);
   glTexCoord2f(1,1); glVertex3f(0,+3,-2);
   glTexCoord2f(0,1); glVertex3f(0,+3,+2);
   glEnd();

   glBegin(GL_QUADS);
   glNormal3f( .5, 0, .5);
   glTexCoord2f(0,0); glVertex3f(+2.5,+1.5,+2);
   glTexCoord2f(1,0); glVertex3f(+2.5,+1.5,-2);
   glTexCoord2f(1,1); glVertex3f(0,+3,-2);
   glTexCoord2f(0,1); glVertex3f(0,+3,+2);
   glEnd();

   //  Undo transformations and textures
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);	
}

static void tree(double x,double y,double z,double th)
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
   
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   
   double radius = 0.25;
   double height = 0.25;
   float j;
   
   //tree trunk, cylinder with no top/bot, since both of those will be covered by something else
   glBindTexture(GL_TEXTURE_2D,texture[8]);
   glBegin(GL_QUAD_STRIP);
   for (j = 0; j <= 360; j+=.125) {
      const float tc = (j / (float) 360);

      double x = radius * Cos(j);
      double y = height;
      double z = radius * Sin(j);

      glNormal3d(Cos(j), 0, Sin(j));

      glTexCoord2f(-tc, 0.0); glVertex3d(x, -y+0.25, z);
      glTexCoord2f(-tc, 1.0); glVertex3d(x, y+0.25, z);
   }
   glEnd();  

   //the rest of the tree, think first grader christmas tree
   radius = 1;
   height = 2;
   float base = 0.5;
   float angle;
   
   //rotates so it's about the Y axis instead of the Z axis
   glRotatef(-90,1,0,0);
   //cone 1/4, biggest one
   glBindTexture(GL_TEXTURE_2D,texture[7]);
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, height+base);
   for (angle = 0; angle < 360; angle+=.125) {
      glVertex3f(sin(angle) * radius, cos(angle) * radius, base);
      glNormal3f(sin(angle), cos(angle), 0);
   }
   glEnd();

   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, base);
   for (angle = 0; angle < 360; angle+=.125) {
      // normal is just pointing down
      glNormal3f(0, 0, 0);
      glVertex3f(sin(angle) * radius, cos(angle) * radius, base);
   }
   glEnd();
   
   //changes height so subsequent ones are smaller, and higher
   height -= 0.4;
   radius -= 0.2;
   base += 0.75;

   //repeat for 3 more cylinders
   //cone 2/4
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, height+base);
   for (angle = 0; angle < 360; angle+=.125) {
      glVertex3f(sin(angle) * radius, cos(angle) * radius, base);
      glNormal3f(sin(angle), cos(angle), 0);
   }
   glEnd();

   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, base);
   for (angle = 0; angle < 360; angle+=.125) {
      // normal is just pointing down
      glNormal3f(0, 0, 0);
      glVertex3f(sin(angle) * radius, cos(angle) * radius, base);
   }
   glEnd();
   
   height -= 0.4;
   radius -= 0.2;
   base += 0.75;

   //cone 3/4
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, height+base);
   for (angle = 0; angle < 360; angle+=.125) {
      glVertex3f(sin(angle) * radius, cos(angle) * radius, base);
      glNormal3f(sin(angle), cos(angle), 0);
   }
   glEnd();

   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, base);
   for (angle = 0; angle < 360; angle+=.125) {
      // normal is just pointing down
      glNormal3f(0, 0, 0);
      glVertex3f(sin(angle) * radius, cos(angle) * radius, base);
   }
   glEnd();
   
   height -= 0.4;
   radius -= 0.2;
   base += 0.75;

      //cone 4/4
   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, height+base);
   for (angle = 0; angle < 360; angle+=.125) {
      glVertex3f(sin(angle) * radius, cos(angle) * radius, base);
      glNormal3f(sin(angle), cos(angle), 0);
   }
   glEnd();

   glBegin(GL_TRIANGLE_FAN);
   glVertex3f(0, 0, base);
   for (angle = 0; angle < 360; angle+=.125) {
      // normal is just pointing down
      glNormal3f(0, 0, 0);
      glVertex3f(sin(angle) * radius, cos(angle) * radius, base);
   }
   glEnd();
   
  
   glPopMatrix();
   glDisable(GL_TEXTURE_2D);
}

static void mail(double x,double y,double z,double th)
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

   //pole thing
   double radius = .05;
   double height = .5;
   double j;
   double i;
   
   glColor3f(0.235, 0.278, 0.345);
   //  Front
   glBegin(GL_QUADS);
   glNormal3f( 0, 0, 1);
   glTexCoord2f(0,0); glVertex3f(-0.22,1.0, 0.33);
   glTexCoord2f(1,0); glVertex3f(+0.22,1.0, 0.33);
   glTexCoord2f(1,1); glVertex3f(+0.22,+1.33, 0.33);
   glTexCoord2f(0,1); glVertex3f(-0.22,+1.33, 0.33);
   glEnd();
   
   //  Back
   glBegin(GL_QUADS);
   glNormal3f( 0, 0,-1);
   glTexCoord2f(0,0); glVertex3f(-0.22,1.0, -0.33);
   glTexCoord2f(1,0); glVertex3f(+0.22,1.0, -0.33);
   glTexCoord2f(1,1); glVertex3f(+0.22,+1.33, -0.33);
   glTexCoord2f(0,1); glVertex3f(-0.22,+1.33, -0.33);
   glEnd();
   
   //  Right
   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-0.22,1.0,+0.33);
   glTexCoord2f(1,0); glVertex3f(-0.22,1.0,-0.33);
   glTexCoord2f(1,1); glVertex3f(-0.22,+1.33,-0.33);
   glTexCoord2f(0,1); glVertex3f(-0.22,+1.33,+0.33);
   glEnd();
   //  Left
   glBegin(GL_QUADS);
   glNormal3f(+1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(+0.22,1.0,+0.33);
   glTexCoord2f(1,0); glVertex3f(+0.22,1.0,-0.33);
   glTexCoord2f(1,1); glVertex3f(+0.22,+1.33,-0.33);
   glTexCoord2f(0,1); glVertex3f(+0.22,+1.33,+0.33);
   glEnd();
   
   //bottom
   glBegin(GL_QUADS);
   glNormal3f(0, -1, 0);
   glTexCoord2f(0,0); glVertex3f(+0.22,1.0,+0.33);
   glTexCoord2f(1,0); glVertex3f(+0.22,1.0,-0.33);
   glTexCoord2f(1,1); glVertex3f(-0.22,1.0,-0.33);
   glTexCoord2f(0,1); glVertex3f(-0.22,1.0,+0.33);
   glEnd();

   //attempt 2 at a flag lol
   glBegin(GL_QUADS);
   glColor3f(1, 0, 0);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-0.22,1.25,+0.22);
   glTexCoord2f(1,0); glVertex3f(-0.22,1.25,+0.20);
   glTexCoord2f(1,1); glVertex3f(-0.22,+1.75,+0.20);
   glTexCoord2f(0,1); glVertex3f(-0.22,+1.75,+0.22);
   glEnd();

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[10]);
   
   glColor3f(0.235, 0.278, 0.345);
   glBegin(GL_QUADS);
   glNormal3f(-1, 0, 0);
   glTexCoord2f(0,0); glVertex3f(-0.22,1.6,-0.1);
   glTexCoord2f(1,0); glVertex3f(-0.22,1.6,+0.20);
   glTexCoord2f(1,1); glVertex3f(-0.22,+1.75,+0.20);
   glTexCoord2f(0,1); glVertex3f(-0.22,+1.75,-0.1);
   glEnd();
   glDisable(GL_TEXTURE_2D);

   //top... ugh...
   radius = .165;
   height = .33;

   glRotatef(-90,1,0,0);
   glBegin(GL_QUAD_STRIP);
   for (j = 0; j <= 360; j+=.125) {
      const float tc = (j / (float) 360);

      double x = radius * Cos(j);
      double y = height;
      double z = radius * Sin(j);

      glNormal3d(Cos(j), 0, Sin(j));

      glTexCoord2f(-tc, 0.0); glVertex3d(x, -y, z+1.33);
      glTexCoord2f(-tc, 1.0); glVertex3d(x, y, z+1.33);
   }
   glEnd(); 

   glNormal3d(0,1,0);

   //"top"
   glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5,0.5); 
      glVertex3d(0.0, height, 1.33);

      for(i = 0.0; i <= 360; i+=10) {
         glTexCoord2f(-0.5*Cos(i)+0.5, 0.5*Sin(i)+0.5);
         glVertex3d(radius * Cos(i), height, radius * Sin(i) + 1.33);
      }
   glEnd();

   glNormal3d(0,-1,0);

   //"bottom"
   glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5,0.5); 
      glVertex3d(0.0, -height, 1.33);

      for(i = 0.0; i <= 360; i+=10) {
         glTexCoord2f(0.5*Cos(i)+0.5, 0.5*Sin(i)+0.5);
         glVertex3d(radius * Cos(i), -height, radius * Sin(i) + 1.33);
      }
   glEnd();


   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   glBindTexture(GL_TEXTURE_2D,texture[8]);
   //pole
   radius = 0.05;
   height = 0.5;
   
   glRotatef(-90,1,0,0);
   glBegin(GL_QUAD_STRIP);
   for (j = 0; j <= 360; j+=.125) {
      const float tc = (j / (float) 360);

      double x = radius * Cos(j);
      double y = height;
      double z = radius * Sin(j);

      glNormal3d(Cos(j), 0, Sin(j));

      glTexCoord2f(-tc, 0.0); glVertex3d(x, -y-0.5, z);
      glTexCoord2f(-tc, 1.0); glVertex3d(x, y-0.5, z);
   }
   glEnd(); 

   glNormal3d(0,1,0);

   //top
   glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5,0.5); 
      glVertex3d(0.0, height-0.5, 0.0);

      for(i = 0.0; i <= 360; i+=10) {
         glTexCoord2f(-0.5*Cos(i)+0.5, 0.5*Sin(i)+0.5);
         glVertex3d(radius * Cos(i), height-0.5, radius * Sin(i));
      }
   glEnd();

   glNormal3d(0,-1,0);

   //bot
   glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5,0.5); 
      glVertex3d(0.0, -height-0.5, 0.0);

      for(i = 0.0; i <= 360; i+=10) {
         glTexCoord2f(0.5*Cos(i)+0.5, 0.5*Sin(i)+0.5);
         glVertex3d(radius * Cos(i), -height-0.5, radius * Sin(i));
      }
   glEnd();
   glDisable(GL_TEXTURE_2D);
   
   glPopMatrix();
}

//test scene
void scene1()
{
   //tree(0, 0, 0, 0);
   //pokecenter(0, 0, 0, 0);
   //mail(0, 0, 0, 0);
   //pokehouse(0, 0, 0, 0);
   //mail(0, 0, 0, 0);
}

void scene()
{
   //so many trees
   //top row
   glColor3f(1, 1, 1);
   tree(11, 0, -8, 0);
   tree(9, 0, -8, 0);
   tree(7, 0, -8, 0);
   tree(5, 0, -8, 0);
   tree(3, 0, -8, 0);
   tree(-1, 0, -8, 0);
   tree(-3, 0, -8, 0);
   tree(-5, 0, -8, 0);
   tree(-7, 0, -8, 0);
   tree(-9, 0, -8, 0);
   tree(-11, 0, -8, 0);
   //left
   tree(-11, 0, -8, 0);
   tree(-11, 0, -6, 0);
   tree(-11, 0, -4, 0);
   tree(-11, 0, -2, 0);
   tree(-11, 0, 0, 0);
   tree(-11, 0, 2, 0);
   tree(-11, 0, 4, 0);
   tree(-11, 0, 6, 0);
   tree(-11, 0, 8, 0);
   tree(-11, 0, 10, 0);
   tree(-11, 0, 12, 0);
   //bottom row
   tree(-9, 0, 12, 0);
   tree(-7, 0, 12, 0);
   tree(1, 0, 12, 0);
   tree(3, 0, 12, 0);
   tree(5, 0, 12, 0);
   tree(7, 0, 12, 0);
   tree(9, 0, 12, 0);
   tree(11, 0, 12, 0);
   //right row
   tree(11, 0, 12, 0);
   tree(11, 0, 10, 0);
   tree(11, 0, 8, 0);
   tree(11, 0, 6, 0);
   tree(11, 0, 4, 0);
   tree(11, 0, 2, 0);
   tree(11, 0, 0, 0);
   tree(11, 0, -2, 0);
   tree(11, 0, -4, 0);
   tree(11, 0, -6, 0);
   tree(11, 0, -8, 0);
   //buildings
   glColor3f(1, 1, 1);
   pokehouse(-4.5, 1.5, -2, 0);
   glColor3f(1, 1, 1);
   pokehouse(4.5, 1.5, -2, 0);
   glColor3f(1, 1, 1);
   mail(-7.5, 0, -1, 0);
   mail(1.5, 0, -1, 0);
   glColor3f(1, 1, 1);
   pokecenter(4.5, 1.5, 4.5, 0);
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Light position and colors
   float Ambient[]  = {0.3,0.3,0.3,1.0};
   float Diffuse[]  = {1.0,1.0,1.0,1.0};
   float Position[] = {3*Cos(zh)-8,Ylight, 8*Sin(zh),1};

   //  Erase the window and the depth buffer
   glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT|GL_STENCIL_BUFFER_BIT);

   //  Enable Z-buffering in OpenGL
   glEnable(GL_DEPTH_TEST);
   //  Undo previous transformations
   glLoadIdentity();
   //  Perspective - set eye position
   if (proj)
   {
      double Ex = -10*dim*Sin(th)*Cos(ph);
      double Ey = +10*dim        *Sin(ph);
      double Ez = +10*dim*Cos(th)*Cos(ph);
      gluLookAt(Ex,Ey,Ez , 0,0,0 , 0,Cos(ph),0);
   }
   //  Orthogonal - set world orientation
   else
   {
      glRotatef(ph,1,0,0);
      glRotatef(th,0,1,0);
   }

   if (light){
   //  Draw light position as sphere (still no lighting here)
   glColor3f(1,1,1);
   glPushMatrix();
   glTranslated(Position[0],Position[1],Position[2]);
   glutSolidSphere(0.03,10,10);
   glPopMatrix();
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
   glLightfv(GL_LIGHT0,GL_POSITION,Position);
   }
  
   else 
      glDisable(GL_LIGHTING);

   glClearColor (0.592, 0.925, 0.949, 0);

   //  Draw floor
   glEnable(GL_TEXTURE_2D);
   glEnable(GL_POLYGON_OFFSET_FILL);
   glBindTexture(GL_TEXTURE_2D,texture[9]);
   glPolygonOffset(1,1);
   glColor3f(1,1,1);
   glNormal3f(0,1,0);
   glBegin(GL_QUADS);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0,0); glVertex3f(-12.5,0,+12.5);
   glTexCoord2f(1,0); glVertex3f(+12.5,0,+12.5);
   glTexCoord2f(1,1); glVertex3f(+12.5,0,-8.5);
   glTexCoord2f(0,1); glVertex3f(-12.5,0,-8.5);
   glEnd();
   glDisable(GL_POLYGON_OFFSET_FILL);
   glDisable(GL_TEXTURE_2D);

   //  Draw scene
   glColor3f(1, 1, 1);
   scene();
   
   if (light){
   //  Save what is glEnabled
   glPushAttrib(GL_ENABLE_BIT);
   //  Draw shadow
         glDisable(GL_LIGHTING);
         //  Enable stencil operations
         glEnable(GL_STENCIL_TEST);

         /*
          *  Step 1:  Set stencil buffer to 1 where there are shadows
          */
         //  Existing value of stencil buffer doesn't matter
         glStencilFunc(GL_ALWAYS,1,0xFFFFFFFF);
         //  Set the value to 1 (REF=1 in StencilFunc)
         //  only if Z-buffer would allow write
         glStencilOp(GL_KEEP,GL_KEEP,GL_REPLACE);
         //  Make Z-buffer and color buffer read-only
         glDepthMask(0);
         glColorMask(0,0,0,0);
         //  Draw flattened scene
         glPushMatrix();
         ShadowProjection(Position,E,N);
         scene();
         glPopMatrix();
         //  Make Z-buffer and color buffer read-write
         glDepthMask(1);
         glColorMask(1,1,1,1);

         /*
          *  Step 2:  Draw shadow masked by stencil buffer
          */
         //  Set the stencil test draw where stencil buffer is > 0
         glStencilFunc(GL_LESS,0,0xFFFFFFFF);
         //  Make the stencil buffer read-only
         glStencilOp(GL_KEEP,GL_KEEP,GL_KEEP);
         //  Enable blending
         glEnable(GL_BLEND);
         glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
         glColor4f(0,0,0,0.5);
         //  Draw the shadow over the entire floor
         glBegin(GL_QUADS);
         glVertex3f(-Dfloor,Yfloor,-Dfloor);
         glVertex3f(+Dfloor,Yfloor,-Dfloor);
         glVertex3f(+Dfloor,Yfloor,+Dfloor);
         glVertex3f(-Dfloor,Yfloor,+Dfloor);
         glEnd();
   //  Undo glEnables
   glPopAttrib();
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
   double t = glutGet(GLUT_ELAPSED_TIME)/4001.0;
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
   {
      if (ph > 0 )
         ph -= 5;
      else
	 NULL;
   }
   //  PageUp key - increase dim
   else if (key == GLUT_KEY_PAGE_DOWN)
      dim += 0.1;
   //  PageDown key - decrease dim
   else if (key == GLUT_KEY_PAGE_UP && dim>1)
      dim -= 0.1;
   //  Keep angles to +/-360 degrees, 180 to keep from gong underground
   th %= 360;
   ph %= 180;
   //  Update projection
   Project(proj?fov:0,asp,dim);
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
   {
      th = 0;
      ph = 15;
   }

   //  Toggle lighting
   else if (ch == 'l' || ch == 'L')
      light = 1-light;
   //  Pause light
   else if (ch == 'p')
      pause = 1-pause;
   
   //  Light elevation
   else if (ch=='[')
      Ylight -= 5;
   else if (ch==']')
      Ylight += 5;
   
   else if (ch=='(')
      zh -= 5;
   else if (ch==')')
      zh += 5;
   
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
   Project(proj?fov:0,asp,dim);
}

/*
 *  Start up GLUT and tell it what to do
 */
int main(int argc,char* argv[])
{
   //  Initialize GLUT
   glutInit(&argc,argv);
   //  Request double buffered, true color window with Z buffering at 600x600
   glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL | GLUT_DOUBLE);
   glutInitWindowSize(600,600);
   glutCreateWindow("Final, PALLET TOWN - Cathy Yang");
   //  Set callbacks
   glutDisplayFunc(display);
   glutTimerFunc(100, timer, 0);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);
   //  Floor texture
   texture[0] = LoadTexBMP("poke.bmp");
   texture[1] = LoadTexBMP("pokeside.bmp");
   texture[2] = LoadTexBMP("pokeroof.bmp");
   texture[3] = LoadTexBMP("HECK.bmp");
   texture[4] = LoadTexBMP("HECK3.bmp");
   texture[5] = LoadTexBMP("HECK2.bmp");
   texture[6] = LoadTexBMP("HECK31.bmp");
   texture[7] = LoadTexBMP("tree.bmp");
   texture[8] = LoadTexBMP("trunk.bmp");
   texture[9] = LoadTexBMP("map.bmp");
   texture[10] = LoadTexBMP("ca-flag.bmp");
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
