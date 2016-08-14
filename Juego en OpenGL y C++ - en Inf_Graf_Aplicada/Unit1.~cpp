//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "Unit2.h"
#include "car.h"
#include "ferrari.h"

#include "ami_bmp.h"
#include "loadtga.h"
#include "GL/glext.h"
#include <math.h>
#include <stdlib.h>

#pragma package(smart_init)
#pragma resource "*.dfm"

//---------------------------------------------------------------------------
//Variables Auxiliares:
TForm1 *Form1;

int modo_color=0;
int track=0;
int Dia_noche=0;
int pto_ini=0;
bool fog = true;
bool light = true;

float velocidad = 0.0;
bool tecla[6] = {false,false,false,false, false, false};

//Datos para textura:
GLuint texturas[NumTextures]; // vector donde se leerá las texturas
char *NombresTexturas[NumTextures] = {"textura/road.tga","textura/borde.tga","textura/SKY_Dia.tga",
                                      "textura/SKY_Noche.tga","textura/grass2.tga"};

//Datos para modelos
GLint F1=0;
GLint carF1=0;

//Datos para lectura bmp
struct canales canal;
char *imagenes[3]={"bmp/circuito_1.bmp","bmp/circuito_2.bmp","bmp/circuito_3.bmp"};
int area = 4000;

//---------------------------------------------------------------------------
//FUNCIONES Auxiliares:
//---------------------------------------------------------------------------

void LoadTexture_car(char*filename)
{
        unsigned char *pbytes;
        GLint iwidth, iheight, icomponents;
        GLenum eFormat;

        pbytes = gltLoadTGA(filename,&iwidth,&iheight,&icomponents,&eFormat);
        gluBuild2DMipmaps(GL_TEXTURE_2D,icomponents,iwidth,iheight,eFormat,
                          GL_UNSIGNED_BYTE,pbytes);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        free(pbytes);
}

void LeerTextura (){

        unsigned char *pbytes;
        GLint iwidth, iheight, icomponents;
        GLenum eFormat;

        for (int iloop=0; iloop < NumTextures; iloop++)
        {
                glBindTexture(GL_TEXTURE_2D,texturas[iloop]);
                pbytes = gltLoadTGA(NombresTexturas[iloop],&iwidth,&iheight,&icomponents,&eFormat);
                gluBuild2DMipmaps(GL_TEXTURE_2D,icomponents,iwidth,iheight,eFormat,
                                  GL_UNSIGNED_BYTE,pbytes);

                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

                //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
                //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);


                free(pbytes);
        }
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
        ami_read_bmp(imagenes[track],&canal.red,&canal.green,&canal.blue,&canal.width,&canal.height);
        //liberar memoria
        
	// Initializes the world geography data
	InitWorld(pto_ini);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PanelRadarGLInit(TObject *Sender)
{
        // Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

        carF1=car();
        F1=ferrari();

	glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

        glGenTextures(NumTextures,texturas);
        LeerTextura();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PanelBrujulaGLInit(TObject *Sender)
{
 	// Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Green drawing color
	glRGB(0,255,0);

	// Just draw the outlines of the polygons
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PanelVistaGLInit(TObject *Sender)
{
        GLfloat glfLightAmbient[] = { 0.1f, 0.1f, 0.1f, 1.0f };
        GLfloat glfLightDiffuse[] = { 1.2f, 1.2f, 1.2f, 1.0f };
        GLfloat glfLightSpecular[] = { 0.9f, 0.9f, 0.9f, 1.0f };
        
        //
        // Añadir luces al mundo
        //

        glLightfv (GL_LIGHT0, GL_AMBIENT, glfLightAmbient);
        glLightfv (GL_LIGHT0, GL_DIFFUSE, glfLightDiffuse);
        glLightfv (GL_LIGHT0, GL_SPECULAR, glfLightSpecular);
        glEnable (GL_LIGHTING);
        glEnable (GL_LIGHT0);

        glEnable (GL_DEPTH_TEST);
        glDisable (GL_CULL_FACE);
        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE ,1);

        carF1=car();
        F1=ferrari();

        // Black background
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f );

        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);

        glGenTextures(NumTextures,texturas);
        LeerTextura();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::PanelVistaResize(TObject *Sender)
{
        GLsizei nWidth = PanelVista->Width;
        GLsizei nHeight = PanelVista->Height;
        double dAspect;

        //evitar div/0
        if (nHeight == 0) nHeight = 1;

	dAspect = (double)nWidth/(double)nHeight;

        // Set the viewport to be the entire window
	glViewport(0, 0, nWidth, nHeight);

	// Setup Perspective
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish viewing volume
//	gluPerspective(45.0, dAspect,1,2000);
      	gluPerspective(75.0, dAspect,1,3000);

        glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PanelBrujulaResize(TObject *Sender)
{
        GLsizei nWidth = PanelBrujula->Width;
        GLsizei nHeight = PanelBrujula->Height;

	// Set the viewport to be the entire window
	glViewport(0, 0, nWidth, nHeight);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establishes a 2 by 2 square with zero in the center
	gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::PanelRadarResize(TObject *Sender)
{
        GLsizei nWidth = PanelRadar->Width;
        GLsizei nHeight = PanelRadar->Height;
        double dAspect;

        //evitar div/0
        if (nHeight == 0) nHeight = 1;

	dAspect = (double)nWidth/(double)nHeight;

        // Set the viewport to be the entire window
	glViewport(0, 0, nWidth, nHeight);

	// Setup Perspective
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Establish viewing volume
//	gluPerspective(45.0, dAspect,1,2000);
      	gluPerspective(90.0, dAspect,1,1000);

        glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyDown(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
	switch (Key) {
        case VK_UP:
            tecla[0] = true; //hacia adelante
            break;
        case VK_DOWN:
            tecla[1] = true; //hacia atras
            break;
        case VK_LEFT:
            tecla[2] = true; //hacia la izquierda
            break;
        case VK_RIGHT:
            tecla[3] = true; //hacia la derecha
            break;
       case 112:
            tecla[4] = true;
            Label1->Caption = "VISTA DESDE EL F1_1";
	    break;
        case 113:
            tecla[5] = true;
            Label1->Caption = "VISTA DESDE EL F1_2 ";
	    break;
        default: return;
     }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::FormKeyUp(TObject *Sender, WORD &Key,
      TShiftState Shift)
{
        switch (Key) {

           case VK_UP:
              tecla[0] = false; //hacia adelante
              break;
           case VK_DOWN:
              tecla[1] = false; //hacia atras
              break;
           case VK_LEFT:
              tecla[2] = false; //hacia la izquierda
              break;
           case VK_RIGHT:
              tecla[3] = false; //hacia la derecha
              break;
       case 112:   // Tecla F1
              tecla[4] = false;
              break;
        case 113:  // Tecla F2
              tecla[5] = false;
              break;
        default: return;
     }
}
//---------------------------------------------------------------------------
int estoy_dentro()
{
        float paso = (float)area/canal.width;
        int conver = (int)(area/2);

        //return 1;
        int pixel = posicion_bmp(paso,canal.width,conver);
        int valor = canal.red[pixel];
        if(valor < 200 )
        {
                return 1; //estoy dentro
        } else {
                if(valor < 230 )
                {
                        return 2;
                } else return 0;
        }
}

//---------------------------------------------------------------------------
void mover_F1()
{
        if (estoy_dentro() > 0){
                if ((tecla[0] == true) && (tecla[1] == false)) { //acelerando
                        if (velocidad < 15) velocidad = velocidad + 0.1;

                        MoveViewer(velocidad);

                        if (tecla[2] == true)
                        {
                                //pObject->radsFromEast += PI/30.0f;
                                pObject->radsFromEast += PI/90.0f;
                                if(pObject->radsFromEast> (2.0*PI))
                                        pObject->radsFromEast = 0.0;
                        }
                        if (tecla[3] == true)
                        {
                                pObject->radsFromEast -= PI/90.0;
                                if(pObject->radsFromEast < 0.0)
                                pObject->radsFromEast = (2.0*PI);
                        }
                }
                if ((tecla[0] == false) && (tecla[1] == true)) {

                        if (velocidad > 0) { //frenando
                                velocidad = velocidad - 0.3;
                        }

                        if ((velocidad <= 0) && (velocidad > -2)) { //marcha atras
                                velocidad = velocidad - 0.1;
                        }

                        MoveViewer(velocidad);

                        if (tecla[2] == true)
                        {
                                pObject->radsFromEast += PI/90.0f;
                                if(pObject->radsFromEast> (2.0*PI))
                                        pObject->radsFromEast = 0.0;
                        }
                        if (tecla[3] == true)
                        {
                                pObject->radsFromEast -= PI/90.0;
                                if(pObject->radsFromEast < 0.0)
                                        pObject->radsFromEast = (2.0*PI);
                                }
                        }
                if ((tecla[0] == false) && (tecla[1] == false)) //inercia
                {
                        if (velocidad >= 0.5) {
                                velocidad = velocidad - 0.1;
                        }
                        if ((velocidad >= 0)&&(velocidad < 0.5)) {
                                velocidad = 0.0;
                        }
                        if (velocidad < 0) {
                                velocidad = velocidad + 0.1;
                        }

                        MoveViewer(velocidad);

                        if (tecla[2] == true)
                        {
                                pObject->radsFromEast += PI/90.0f;
                                if(pObject->radsFromEast> (2.0*PI))
                                        pObject->radsFromEast = 0.0;
                        }
                        if (tecla[3] == true)
                        {
                                pObject->radsFromEast -= PI/90.0;
                                if(pObject->radsFromEast < 0.0)
                                        pObject->radsFromEast = (2.0*PI);
                        }
                }
        } else {//fuera del circuito
                if ((tecla[0] == true) && (tecla[1] == false)) { //acelerando
                        if (velocidad > 1)
                        {
                                velocidad = velocidad - 0.5;
                        } else {
                               velocidad = velocidad + 0.1;
                        }

                        MoveViewer(velocidad);

                        if (tecla[2] == true)
                        {
                                //pObject->radsFromEast += PI/30.0f;
                                pObject->radsFromEast += PI/90.0f;
                                if(pObject->radsFromEast> (2.0*PI))
                                        pObject->radsFromEast = 0.0;
                        }
                        if (tecla[3] == true)
                        {
                                pObject->radsFromEast -= PI/90.0;
                                if(pObject->radsFromEast < 0.0)
                                pObject->radsFromEast = (2.0*PI);
                        }
                }
                if ((tecla[0] == false) && (tecla[1] == true)) {

                        if (velocidad > 0) { //frenando
                                velocidad = velocidad - 0.2;
                        }

                        if ((velocidad <= 0) && (velocidad > -0.5)) { //marcha atras
                                velocidad = velocidad - 0.1;
                        }

                        MoveViewer(velocidad);

                        if (tecla[2] == true)
                        {
                                pObject->radsFromEast += PI/90.0f;
                                if(pObject->radsFromEast> (2.0*PI))
                                        pObject->radsFromEast = 0.0;
                        }
                        if (tecla[3] == true)
                        {
                                pObject->radsFromEast -= PI/90.0;
                                if(pObject->radsFromEast < 0.0)
                                        pObject->radsFromEast = (2.0*PI);
                                }
                        }
                if ((tecla[0] == false) && (tecla[1] == false)) //inercia
                {
                        if (velocidad >= 0.5) {
                                velocidad = velocidad - 0.5;
                        }
                        if ((velocidad >= 0)&&(velocidad < 0.5)) {
                                velocidad = 0.0;
                        }
                        if (velocidad < 0) {
                                velocidad = velocidad + 0.5;
                        }

                        MoveViewer(velocidad);

                        if (tecla[2] == true)
                        {
                                pObject->radsFromEast += PI/90.0f;
                                if(pObject->radsFromEast> (2.0*PI))
                                        pObject->radsFromEast = 0.0;
                        }
                        if (tecla[3] == true)
                        {
                                pObject->radsFromEast -= PI/90.0;
                                if(pObject->radsFromEast < 0.0)
                                        pObject->radsFromEast = (2.0*PI);
                        }
                }
        }

        //Vistas
        if (tecla[4] == true) {
                bF1_1 = true;
                pObject = &F1_1Pos;
                //Label1->Caption = "VISTA DESDE EL F1_1";
        }
        if (tecla[5] == true) {
                bF1_1 = false;
                pObject = &F1_2Pos;
                //Label1->Caption = "VISTA DESDE EL F1_2 ";
        }
}
//---------------------------------------------------------------------------
void Niebla ()
{
    // color de la niebla
    GLfloat fLowLight[] = { 0.95f, 0.95f, 0.95f, 1.0f };
    glClearColor(fLowLight[0], fLowLight[1], fLowLight[2], fLowLight[3]);

    glEnable(GL_FOG);
    glFogfv(GL_FOG_COLOR, fLowLight);
    glFogf(GL_FOG_START, 2000.0f);
    glFogf(GL_FOG_END, 3000.0f);
    glFogi(GL_FOG_MODE, GL_LINEAR);
}

void __fastcall TForm1::PanelVistaPaint(TObject *Sender)
{
	float fRadius = 1.0f;

        // Clear the color and depth buffers.
        //
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        switch (modo_color) {
                case 0: // modo sólido
                        glEnable (GL_DEPTH_TEST);
                        glDisable (GL_CULL_FACE);
                        glEnable (GL_LIGHTING);
                        glEnable (GL_LIGHT0);
                        glLightModeli(GL_LIGHT_MODEL_TWO_SIDE ,1);
                        glEnable(GL_TEXTURE_2D);
                        glTexEnvi(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_DECAL);
                        glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
                        break;
                case 1: // modo alámbrico
                        glDisable(GL_TEXTURE_2D);
                        glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
                        glEnable(GL_CULL_FACE);
                        glDisable(GL_DEPTH_TEST);
                        glDisable (GL_LIGHTING);
                        glDisable (GL_LIGHT0);
                        break;
        }

        glPushMatrix();

	   // Handy dandy little function
	   gluLookAt(pObject->xPos- 4*(fRadius*(float)cos(pObject->radsFromEast)),
                     1.5f,
                     pObject->zPos + 4*(fRadius*(float)sin(pObject->radsFromEast)),   // Eye Position (x,y,z)
                     pObject->xPos + (fRadius*(float)cos(pObject->radsFromEast)),     // Center X
		     0.5f,                                                            // Center Y
		     pObject->zPos - (fRadius*(float)sin(pObject->radsFromEast)),     // Center Z
                     0.0f, 1.0f, 0.0f);                                               // Up is straight up Y axis

           if (fog) {
                Niebla();
           } else {
                glDisable(GL_FOG);
           }
           if (light) {
                glEnable (GL_LIGHTING);
                glEnable (GL_LIGHT0);
           } else {
                glDisable (GL_LIGHTING);
                glDisable (GL_LIGHT0);
           }

           RenderWorld(texturas,carF1,F1,track,Dia_noche);
	glPopMatrix();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PanelBrujulaPaint(TObject *Sender)
{
	GLfloat fDegrees;
	GLint	nDegrees;

	// Clear the window with current clearing color
	glClear(GL_COLOR_BUFFER_BIT);

	glPushMatrix();

           // Draw the fixed position needle (CCW winding)
           glBegin(GL_QUADS);
                glVertex2f(0.0f,0.8f);
        	glVertex2f(0.1f, 0.0f);
        	glVertex2f(0.0f, -0.4f);
        	glVertex2f(-0.1f, 0.0f);
           glEnd();

           // Convert radians to degrees
           fDegrees =  57.2957795f * (GLfloat)(pObject->radsFromEast);

           // Offset because stored value is angle from due east
           fDegrees = 90.0f - fDegrees;
           glRotatef(fDegrees,0.0f, 0.0f, 1.0f);

           // Draw the outline of an N
           glBegin(GL_LINE_STRIP);
           	glVertex2f(-0.05f, 0.85f);
           	glVertex2f(-0.05f, 0.99f);
           	glVertex2f(0.05f, 0.85f);
           	glVertex2f(0.05f, 0.99f);
           glEnd();

           // Draw the outline of an E
           glBegin(GL_LINE_STRIP);
           	glVertex2f(0.97f, 0.08f);
           	glVertex2f(0.86f, 0.08f);
           	glVertex2f(0.86f, -0.08f);
           	glVertex2f(0.98f, -0.08f);
           glEnd();

           glBegin(GL_LINES);
           	glVertex2f(0.93f, 0.0f);
           	glVertex2f(0.86f, 0.0f);
           glEnd();

           // Draw the outline of a W
           glBegin(GL_LINE_STRIP);
           	glVertex2f(-0.99f, 0.05f);
           	glVertex2f(-0.95f, -0.05f);
           	glVertex2f(-0.90f, 0.05f);
           	glVertex2f(-0.86f, -0.05f);
           	glVertex2f(-0.81f, 0.05f);
           glEnd();

           // Draw the outline of an S
           glBegin(GL_LINE_STRIP);
           	glVertex2f(0.05f, -0.84f);
           	glVertex2f(-0.05f, -0.84f);
           	glVertex2f(-0.05f, -0.90f);
           	glVertex2f(0.05f, -0.90f);
           	glVertex2f(0.05f, -0.96f);
           	glVertex2f(-0.06f,-0.96f);
           glEnd();

           // Draw circular tick marks
           for(nDegrees = 0; nDegrees < 360; nDegrees += 10)
           {
           	glPushMatrix();
                	glRotatef((GLfloat)nDegrees,0.0f, 0.0f, 1.0f);
               		glBegin(GL_LINES);
        			glVertex2f(0.0f, 0.70f);
                		// Longer tick marks at NSEW
        			if(nDegrees == 0 || nDegrees == 90 || nDegrees == 180 || nDegrees == 270)
        				glVertex2f(0.0f, 0.82f);
           			else
        				glVertex2f(0.0f, 0.77f);
                	glEnd();

	        glPopMatrix();
           }

	glPopMatrix();
	glFlush();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PanelRadarPaint(TObject *Sender)
{

        float fRadius = 1.0f;

        // Clear the color and depth buffers.
        //
        glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

       glPushMatrix();
           glEnable(GL_CULL_FACE);
	   // Handy dandy little function
	   /*gluLookAt(-4*(fRadius*(float)cos(pObject->radsFromEast)),
                     2700.0f,
                     4*(fRadius*(float)sin(pObject->radsFromEast)),   // Eye Position (x,y,z)
                     4*(fRadius*(float)cos(pObject->radsFromEast)),     // Center X
		     0.0f,                                                            // Center Y
		     -4*(fRadius*(float)sin(pObject->radsFromEast)),     // Center Z
                     0.0f, 1.0f, 0.0f);*/
           gluLookAt(-4*(fRadius*(float)cos(pObject->radsFromEast)),
                     350.0f,
                     4*(fRadius*(float)sin(pObject->radsFromEast)),   // Eye Position (x,y,z)
                     4*(fRadius*(float)cos(pObject->radsFromEast)),     // Center X
		     0.0f,                                                            // Center Y
		     -4*(fRadius*(float)sin(pObject->radsFromEast)),     // Center Z
                     0.0f, 1.0f, 0.0f);
           gluLookAt(pObject->xPos- 4*(fRadius*(float)cos(pObject->radsFromEast)),
                     1.5f,
                     pObject->zPos + 4*(fRadius*(float)sin(pObject->radsFromEast)),   // Eye Position (x,y,z)
                     pObject->xPos + (fRadius*(float)cos(pObject->radsFromEast)),     // Center X
		     0.5f,                                                            // Center Y
		     pObject->zPos - (fRadius*(float)sin(pObject->radsFromEast)),     // Center Z
                     0.0f, 1.0f, 0.0f);
           // Handy dandy little function */
	   /*gluLookAt(-4*(fRadius*(float)cos(pObject->radsFromEast)),
                     775.0f,
                     4*(fRadius*(float)sin(pObject->radsFromEast)),   // Eye Position (x,y,z)
                     4*(fRadius*(float)cos(pObject->radsFromEast)),     // Center X
		     0.0f,                                                            // Center Y
		     -4*(fRadius*(float)sin(pObject->radsFromEast)),     // Center Z
                     1.0f, 0.0f, 0.0f);*/

           
           RenderWorld(texturas,carF1,F1,track,Dia_noche);
           DrawBlip();
	glPopMatrix();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        Form1->Label2->Caption = int (velocidad);
        mover_F1();
        PanelRadar->Refresh();
        PanelVista->Refresh();
        PanelBrujula->Refresh();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SinColorClick(TObject *Sender)
{
        TMenuItem *m = (TMenuItem *) Sender;
        modo_color = m->Tag;
        if (!m->Checked) m->Checked = true;
        PanelVista->Repaint();
}
//---------------------------------------------------------------------------



void __fastcall TForm1::Principiante1Click(TObject *Sender)
{
        TMenuItem *pista = (TMenuItem *) Sender;
        track = pista->Tag;

        if (track == 0) pto_ini = 0;
        if (track == 2) pto_ini = 1;
        if (track == 1) pto_ini = 2;

        ami_read_bmp(imagenes[track],&canal.red,&canal.green,&canal.blue,&canal.width,&canal.height);
        InitWorld(pto_ini);

        if (!pista->Checked) pista->Checked = true;
        PanelVista->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Dia1Click(TObject *Sender)
{
        TMenuItem *dia = (TMenuItem *) Sender;
        Dia_noche = dia->Tag;
        if (!dia->Checked) dia->Checked = true;
        PanelVista->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ON1Click(TObject *Sender)
{
        TMenuItem *fogg = (TMenuItem *) Sender;
        if (fogg->Tag == 0) {
                fog = true;
        } else {
                fog = false;
        }
        if (!fogg->Checked) fogg->Checked = true;
        PanelVista->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::ON2Click(TObject *Sender)
{
        TMenuItem *luz = (TMenuItem *) Sender;
        if (luz->Tag == 0) {
                light = true;
        } else {
                light = false;
        }
        if (!luz->Checked) luz->Checked = true;
        PanelVista->Repaint();
}
//---------------------------------------------------------------------------

