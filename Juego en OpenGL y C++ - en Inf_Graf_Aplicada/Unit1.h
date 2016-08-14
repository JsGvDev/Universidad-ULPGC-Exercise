//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include "OpenGLSrc.h"
#include <Menus.hpp>
//---------------------------------------------------------------------------

#define NumTextures 5
#define road 0
#define arcen 1
#define SKY_Dia 2
#define SKY_Noche 3
#define tierra 4


class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TTimer *Timer1;
        TLabel *Label1;
        TOpenGL *PanelBrujula;
        TOpenGL *PanelRadar;
        TOpenGL *PanelVista;
        TMainMenu *MainMenu1;
        TMenuItem *OP;
        TMenuItem *Color;
        TMenuItem *SinColor;
        TLabel *Label2;
        TMenuItem *Circuito1;
        TMenuItem *Principiante1;
        TMenuItem *Intermedio1;
        TMenuItem *Avanzado1;
        TMenuItem *Tiempo1;
        TMenuItem *Dia1;
        TMenuItem *Noche1;
        TMenuItem *Camaras1;
        TMenuItem *Niebla1;
        TMenuItem *ON1;
        TMenuItem *OFF1;
        TMenuItem *ON2;
        TMenuItem *OFF2;

        void __fastcall PanelRadarGLInit(TObject *Sender);
        void __fastcall PanelBrujulaGLInit(TObject *Sender);
        void __fastcall PanelVistaGLInit(TObject *Sender);
        void __fastcall PanelVistaResize(TObject *Sender);
        void __fastcall PanelBrujulaResize(TObject *Sender);
        void __fastcall PanelRadarResize(TObject *Sender);
        void __fastcall FormKeyDown(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall FormKeyUp(TObject *Sender, WORD &Key,
          TShiftState Shift);
        void __fastcall PanelVistaPaint(TObject *Sender);
        void __fastcall PanelBrujulaPaint(TObject *Sender);
        void __fastcall PanelRadarPaint(TObject *Sender);
        void __fastcall Timer1Timer(TObject *Sender);
        void __fastcall SinColorClick(TObject *Sender);
        void __fastcall Principiante1Click(TObject *Sender);
        void __fastcall Dia1Click(TObject *Sender);
        void __fastcall ON1Click(TObject *Sender);
        void __fastcall ON2Click(TObject *Sender);
        
private:	// User declarations

public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;

struct sample_MATERIAL{
 GLfloat ambient[3];
 GLfloat diffuse[3];
 GLfloat specular[3];
 GLfloat emission[3];
 GLfloat alpha;
 GLfloat phExp;
 int   texture;
};
struct sample_TEXTURE{
 char * name;
 GLint  id;
};
struct canales {
	unsigned char *red;
	unsigned char *green;
	unsigned char *blue;
	int width,height;
};
void LoadTexture_car(char*filename);
//---------------------------------------------------------------------------
#endif
