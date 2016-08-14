//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "road_C1.h"
#include "road_C2_C3.h"

#include <gl/glut.h>
#include <math.h>
#include <stdio.h>

#pragma package(smart_init)
//---------------------------------------------------------------------------
// Convert Radians to Degrees
#define dRadToDeg(x) (((float)x)*57.29577951308f)

// Not defined by Borland's headers, but found in SDK
const GLubyte* APIENTRY gluGetString (GLenum name);
#define GLU_VERSION             100800
#define GLU_EXTENSIONS          100801

// Tank and robot position
struct _POSITION F1_1Pos;	// F1_1 position
struct _POSITION F1_2Pos;	// F1_2 position
struct _POSITION *pObject;	// Which one is current
struct _POSITION Inicio;	// Inicio

int valor=0;
static GLfloat zPos = -120.0f;

//---------------------------------------------------------------------------
// Real simple, if this is true, your the F1_1, if false, your the F1_2
BOOL bF1_1 = TRUE;

// This is going to come in handy more than once.
double	 PI =  3.14159265359;

// Useful structure for storing coordinates of objects. We declare
// an array of these to hold the positions of the various types of objects
struct Coord
	{
	float x;
	float z;
	};

// Maximum number of each type of object
#define MAX_EACH	15

///////////////////////////////////////////////////////////////////////////////
// Initialize the world and the objects in it.
BOOL InitWorld(int ini)
{
        if (ini == 0) {
                // Initialize position of the F1_1
                F1_1Pos.xPos = -890.0f;
                F1_1Pos.zPos = -940.0f;

                // Initialize the position of the F1_2
        	F1_2Pos.xPos = -900.0f;
	        F1_2Pos.zPos = -940.0f;
        }

        if (ini == 1) {
                // Initialize position of the F1_1
                F1_1Pos.xPos = 12.0f;
                F1_1Pos.zPos = -145.0f;

                // Initialize the position of the F1_2
        	F1_2Pos.xPos = 2.0f;
	        F1_2Pos.zPos = -145.0f;
        }

        if (ini == 2) {
                // Initialize position of the F1_1
                F1_1Pos.xPos = 1215.0f;
                F1_1Pos.zPos = 1340.0f;

                // Initialize the position of the F1_2
        	F1_2Pos.xPos = 1205.0f;
	        F1_2Pos.zPos = 1340.0f;
        }

        Inicio.xPos = F1_1Pos.xPos;
	Inicio.zPos = F1_1Pos.zPos;

        F1_1Pos.radsFromEast = PI/2.0;	// Facing due north
	F1_2Pos.radsFromEast = PI/2.0;	// Facing due north

	// Set global object pointer to point at current vehicle
	// bF1_1 is set in tank.c and specifies that the tank is the initial
	// viewer.
	if(bF1_1)
		pObject = &F1_1Pos;
	else
		pObject = &F1_2Pos;

        return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
/// Objects contained in the scene
///////////////////////////////////////////////////////////////////////////////
void DrawF1_1(GLint c1)
{
        glPushMatrix();
           glTranslatef(F1_1Pos.xPos, 0.0f, F1_1Pos.zPos);
           glRotatef(-90, 1.0f, 0.0f, 0.0f);
//           glRotatef(-90, 0.0f, 0.0f, 1.0f);
           glRotatef(dRadToDeg(F1_1Pos.radsFromEast+((float)PI/2.0f)), 0.0f, 0.0f, 1.0f);
           GLfloat fLightPos[4]   = {F1_1Pos.xPos, 10.0f, F1_1Pos.zPos, 1.0f };
           glLightfv(GL_LIGHT0, GL_POSITION, fLightPos);
           glScalef (5,5,5);

           glCallList(c1);
        glPopMatrix();
}
//////////////////////////////////////////////////////////////////////////////
void DrawF1_2(GLint c2)
{
        glPushMatrix();
           glTranslatef(F1_2Pos.xPos, 0.0f, F1_2Pos.zPos+2);
           //glTranslatef(F1_2Pos.xPos, 0.0f, F1_2Pos.zPos);
           glRotatef(-90, 1.0f, 0.0f, 0.0f);
           glRotatef(-90, 0.0f, 0.0f, 1.0f);
           //glRotatef(dRadToDeg(F1_2Pos.radsFromEast+((float)PI/2.0f)), 0.0f, 0.0f, 1.0f);
           glRotatef(2+dRadToDeg(F1_2Pos.radsFromEast+((float)PI/2.0f)), 0.0f, 0.0f, 1.0f);
           GLfloat fLightPos[4]   = {F1_1Pos.xPos, 10.0f, F1_1Pos.zPos, 1.0f };
           glLightfv(GL_LIGHT0, GL_POSITION, fLightPos);
           glScalef (5,5,5);

           glCallList(c2);
        glPopMatrix();
}

/////////////////////////////////////////////////////////////////////////////////
// Draw the ground just as a grid of lines. No transformation to take place
void draw_grass(GLuint texturas[NumTextures])
{
     int i,j;

     glPushMatrix();

     float ejey = -2000;
        for (i=0; i<64; i++){
                float ejex = -2000;
                for (j=0; j<64; j++){
                        glBindTexture(GL_TEXTURE_2D,texturas[tierra]);
                        glBegin(GL_QUADS);

                             glTexCoord2f(0.0f, 0.0f); glVertex3f(ejex,-1.0,ejey+64.0);
                             glTexCoord2f(0.0f, 1.0f); glVertex3f(ejex,-1.0f,ejey);
                             glTexCoord2f(1.0f, 1.0f); glVertex3f(ejex+64.0,-1.0f,ejey);
                             glTexCoord2f(1.0f, 0.0f); glVertex3f(ejex+64.0,-1.0f,ejey+64.0);

                        glEnd();
                        ejex = ejex+64.0;
		}
                ejey = ejey+64.0;
	}

     glPopMatrix();
}

void DrawGround(GLuint texturas[NumTextures])
{
     GLfloat z;

     draw_grass(texturas);
     
     /*glPushMatrix();
        glBindTexture(GL_TEXTURE_2D,texturas[tierra]);
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(-2000.0f,-1.0f,2000.0f);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-2000.0f,-1.0f,-2000.0f);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(2000.0f,-1.0f,-2000.0f);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(2000.0f,-1.0f,2000.0f);
        glEnd();
     glPopMatrix();*/

        //Carretera Recta
        glPushMatrix();
           //Mover objeto hacia atras y abajo
           glTranslatef(Inicio.xPos-8,-0.75f,Inicio.zPos-25);
           
           //carretera
           for (z=30.0f; z>=0.0f; z-=10)
           {
           glBindTexture(GL_TEXTURE_2D,texturas[road]);
           glBegin(GL_QUADS);
              glTexCoord2f(0.0f,0.0f);
              glVertex3f(-10.0f,0.0f,z);

              glTexCoord2f(1.0f,0.0f);
              glVertex3f(10.0f,0.0f,z);

              glTexCoord2f(1.0f,1.0f);
              glVertex3f(10.0f,0.0f,z-10.0f);

              glTexCoord2f(0.0f,1.0f);
              glVertex3f(-10.0f,0.0f,z-10.0f);
           glEnd();
           glBindTexture(GL_TEXTURE_2D,texturas[arcen]);//izq
           glBegin(GL_QUADS);
              glTexCoord2f(0.0f,0.0f);
              glVertex3f(-12.0f,0.0f,z);

              glTexCoord2f(1.0f,0.0f);
              glVertex3f(-10.0f,0.0f,z);

              glTexCoord2f(1.0f,1.0f);
              glVertex3f(-10.0f,0.0f,z-10.0f);

              glTexCoord2f(0.0f,1.0f);
              glVertex3f(-12.0f,0.0f,z-10.0f);
           glEnd();

           glBindTexture(GL_TEXTURE_2D,texturas[arcen]);//dch
           glBegin(GL_QUADS);
              glTexCoord2f(1.0f,1.0f);
              glVertex3f(10.0f,0.0f,z);

              glTexCoord2f(0.0f,1.0f);
              glVertex3f(12.0f,0.0f,z);

              glTexCoord2f(0.0f,0.0f);
              glVertex3f(12.0f,0.0f,z-10.0f);

              glTexCoord2f(1.0f,0.0f);
              glVertex3f(10.0f,0.0f,z-10.0f);
           glEnd();
           }
        glPopMatrix();
        
	//Intercambiamos bufferes
}

////////////////////////////////////////////////////////////////////////////////
// Draw the Escenario
void Draw_World_SKY(GLuint texturas[NumTextures], bool Dia)
{
     glPushMatrix();
        GLUquadric *qobj = gluNewQuadric();
        gluQuadricTexture(qobj,GL_TRUE);

        glEnable(GL_TEXTURE_2D);
           if (Dia){
                glRotatef(90, 1.0f, 0.0f, 1.0f);
                glRotatef(90, 1.0f, 0.0f, 0.0f);
                glBindTexture(GL_TEXTURE_2D,texturas[SKY_Dia]);


           } else {
                glRotatef(90, 1.0f, 0.0f, 1.0f);
                glBindTexture(GL_TEXTURE_2D,texturas[SKY_Noche]);
           }
           gluSphere(qobj,2850,150,150);
           gluDeleteQuadric(qobj);
        glDisable(GL_TEXTURE_2D);
     glPopMatrix();
}
////////////////////////////////////////////////////////////////////////////////
// Render the entire scene
void RenderWorld(GLuint texturas[NumTextures],GLint c1,GLint c2,int pista,int D_N)
{

        // Draw the world
     glDisable(GL_CULL_FACE);
        DrawGround(texturas);

        if (pista == 0) {
                DrawRoad_1(texturas);
        } else {
                DrawRoad_C2_C3(texturas,pista);
        }
        if (D_N == 0) {
                Draw_World_SKY(texturas, true);
        } else {
                Draw_World_SKY(texturas, false);
        }
     glEnable(GL_CULL_FACE);
        
	// Draw the F1_2 or the F1_1. If we draw both, our view will be from
	// the inside of whichever one we are.
	DrawF1_2(c2);
	DrawF1_1(c1);
}

// Moves the object forwards or backwards
void MoveViewer(GLdouble dStep)
{
	GLdouble xDelta,zDelta;

	xDelta = dStep*cos(pObject->radsFromEast);
	zDelta = -dStep*sin(pObject->radsFromEast);

	pObject->xPos += (float)xDelta;
	pObject->zPos += (float)zDelta;

	if(pObject->xPos > 1997.0f)
		pObject->xPos = 1997.0f;

	if(pObject->xPos < -1997.0f)
		pObject->xPos = -1997.0f;


	if(pObject->zPos > 1997.0f)
		pObject->zPos = 1997.0f;

	if(pObject->zPos < -1997.0f)
		pObject->zPos = -1997.0f;

}

///////////////////////////////////////////////////////////////////////////
// Draw a blip on the radar screen
void DrawBlip()
{
        glPushMatrix();
           glColor3f(1,0,0);
           glDisable(GL_TEXTURE_2D);
           if(bF1_1){
                glTranslatef(F1_1Pos.xPos, 0.0f, F1_1Pos.zPos);
           } else {
                glTranslatef(F1_2Pos.xPos, 0.0f, F1_2Pos.zPos);
           }

           glRotatef(-90, 1.0f, 0.0f, 0.0f);
           glRotatef(-90, 0.0f, 0.0f, 1.0f);
           glScalef (30.0f, 30.0f, 30.0f);

           glutSolidIcosahedron();
           glEnable(GL_TEXTURE_2D);
        glPopMatrix();
}

///////////////////////////////////////////////////////////////////////////
// find a position on the bmp
int posicion_bmp(float paso, int ancho, int conver){
        int x,z;
        int pixel;
        if(bF1_1)
        {
                x = (int)((F1_1Pos.xPos+conver)/paso);
                z = (int)((F1_1Pos.zPos+conver)/paso);
                pixel = (int)z*ancho+x;
	} else
        {
                x = (int)((F1_2Pos.xPos+conver)/paso);
                z = (int)((F1_2Pos.zPos+conver)/paso);
                pixel = (int)z*ancho+x;
        }
        return pixel;
}

