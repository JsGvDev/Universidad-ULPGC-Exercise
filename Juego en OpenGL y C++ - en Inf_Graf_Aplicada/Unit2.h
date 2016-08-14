//---------------------------------------------------------------------------

#ifndef Unit2H
#define Unit2H

#define glRGB(x, y, z)	glColor3ub((GLubyte)x, (GLubyte)y, (GLubyte)z)

// Internal data structures
struct _POSITION
	{
	GLfloat xPos;				// X position on world grid
	GLfloat zPos;				// Z position on world grid
	GLdouble radsFromEast;      // Orientation from direct line east
	};

extern struct _POSITION *pObject;	// Which one is current
extern struct _POSITION F1_1Pos, F1_2Pos;
extern BOOL bF1_1;

// Prevent anoying compiler warnings - only used locally
#define fsin(x)	(float)sin(x)
#define fcos(x) (float)cos(x)
extern double PI;

extern GLfloat palito;

// Initialize the world and the objects in it.
BOOL InitWorld(int ini);

// Render the entire scene
void RenderWorld(GLuint texturas[],GLint c1,GLint c2,int pista,int D_N);

// Moves the tank or robot forwards or backwards
void MoveViewer(GLdouble dStep);

// Draw a blip on the radar screen if we are within 700 units of the other object
// The 700 comes from the radar outer radius and can be changed by changing it.
void DrawBlip();

int posicion_bmp(float paso, int ancho, int conver);

//---------------------------------------------------------------------------
#endif
 