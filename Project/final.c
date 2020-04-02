#include "CSCIx229.h"
#define PI 3.1415927
int th=0;         //  Azimuth of view angle
int ph=0;         //  Elevation of view angle
int light=1;      //  Lighting
int rep=1;        //  Repitition
double asp=1;     //  Aspect ratio
double dim=3.0;   //  Size of world
int pause = 1;	  //  Pause
double smokeoffset=0;

// Light values
int emission  =   0;  // Emission intensity (%)
int ambient   =  60;  // Ambient intensity (%)
int diffuse   = 100;  // Diffuse intensity (%)
int specular  =   0;  // Specular intensity (%)
int shininess =   0;  // Shininess (power of two)
float shiny   =   1;    // Shininess (value)
int zh        =  75;  // Light azimuth
float ylight  =   45;  // Elevation of light
unsigned int texture[10]; // Texture names

static void sphere2(double x,double y,double z,double r)
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
            glColor4f(1,1,1,1);
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
    smokeoffset += .01;
    if (smokeoffset > 5.0) {
      smokeoffset -= 5.0;
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
  sphere2(+2,+1+smokeoffset,0, .2);
  sphere2(+2,-1+smokeoffset,0, .2);

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

   radius = 1;
   height = 2;
   float base = 0.5;
   float angle;

   glRotatef(-90,1,0,0);
   //cone 1/4
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

   height -= 0.4;
   radius -= 0.2;
   base += 0.75;

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

   glColor3f(.78, .85, .88);

   //pole thing
   double radius = .05;
   double height = .5;
   double j;
   double i;

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

   /* Top of Cylinder */
   glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5,0.5); 
      glVertex3d(0.0, height, 1.33);

      for(i = 0.0; i <= 360; i+=10) {
         glTexCoord2f(-0.5*Cos(i)+0.5, 0.5*Sin(i)+0.5);
         glVertex3d(radius * Cos(i), height, radius * Sin(i) + 1.33);
      }
   glEnd();

   glNormal3d(0,-1,0);

   /* Bottom of Cylinder */
   glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5,0.5); 
      glVertex3d(0.0, -height, 1.33);

      for(i = 0.0; i <= 360; i+=10) {
         glTexCoord2f(0.5*Cos(i)+0.5, 0.5*Sin(i)+0.5);
         glVertex3d(radius * Cos(i), -height, radius * Sin(i) + 1.33);
      }
   glEnd();

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

   /* Top of Cylinder */
   glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5,0.5); 
      glVertex3d(0.0, height-0.5, 0.0);

      for(i = 0.0; i <= 360; i+=10) {
         glTexCoord2f(-0.5*Cos(i)+0.5, 0.5*Sin(i)+0.5);
         glVertex3d(radius * Cos(i), height-0.5, radius * Sin(i));
      }
   glEnd();

   glNormal3d(0,-1,0);

   /* Bottom of Cylinder */
   glBegin(GL_TRIANGLE_FAN);
      glTexCoord2f(0.5,0.5); 
      glVertex3d(0.0, -height-0.5, 0.0);

      for(i = 0.0; i <= 360; i+=10) {
         glTexCoord2f(0.5*Cos(i)+0.5, 0.5*Sin(i)+0.5);
         glVertex3d(radius * Cos(i), -height-0.5, radius * Sin(i));
      }
   glEnd();
   
   glPopMatrix();
}

static void map(double x,double y,double z,double th)
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

      glBindTexture(GL_TEXTURE_2D,texture[9]);
   glBegin(GL_QUADS);
   glNormal3f( 0,+1, 0);
   glTexCoord2f(0,0); glVertex3f(-12.5,0,+10.5);
   glTexCoord2f(1,0); glVertex3f(+12.5,0,+10.5);
   glTexCoord2f(1,1); glVertex3f(+12.5,0,-10.5);
   glTexCoord2f(0,1); glVertex3f(-12.5,0,-10.5);
   glEnd();
 
   glPopMatrix();
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

void draw()
{
   //  Enable textures
   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
   
   int k;
   int DEF_D = 5;
    
   glBindTexture(GL_TEXTURE_2D,texture[8]);
    glBegin(GL_TRIANGLES);
    for (k=0;k<=360;k+=DEF_D){
      glVertex3f(0,0,1);
      glColor3f(0.0,1.0,1.0);
      glVertex3f(Cos(k),Sin(k),0);
      glColor3f(1.0,0.0,0.0);
      glVertex3f(Cos(k+DEF_D),Sin(k+DEF_D),0);
    }
    glEnd();

    glDisable(GL_TEXTURE_2D);
}

/*
 *  OpenGL (GLUT) calls this routine to display the scene
 */
void display()
{
   //  Eye position
   double Ex = -10*dim*Sin(th)*Cos(ph);
   double Ey = +10*dim        *Sin(ph);
   double Ez = +15*dim*Cos(th)*Cos(ph);
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
      float Position[]  = {15*Cos(zh),ylight,15*Sin(zh),1};
      //  Draw light position as ball (still no lighting here)
      glColor3f(1,1,1);
      ball(Position[0],Position[1],Position[2] , 15);
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
   glClearColor (0.592, 0.925, 0.949, 0);
   draw(); 

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
   glutCreateWindow("Final - Cathy Yang");
   //  Set callbacks
   glutDisplayFunc(display);
   glutTimerFunc(100, timer, 0);
   glutReshapeFunc(reshape);
   glutSpecialFunc(special);
   glutKeyboardFunc(key);
   glutIdleFunc(idle);

   //  Load textures
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
   
   //  Pass control to GLUT so it can interact with the user
   ErrCheck("init");
   glutMainLoop();
   return 0;
}
