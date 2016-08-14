//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "math.h"
#define pi 3.1416
#include "stack.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGRID"
#pragma resource "*.dfm"
TForm1 *Form1;
int ini_x,fin_x,ini_y,fin_y;
float r=0;
bool pintando=false;
bool pintar_pol=false;

//Poligonos
int h=1;//homogenea

double pol[100][4];
int arista[200][2];
int NumVert = 0;
int UltVert = 0;
int NumArista = 0;
int NumLado = 3;

//int NumPoligonos = 0;

/*double P[4] = {4,0,2,1};
double M[4][4] = {{1,0,0,0},{0,1,0,0},{0,0,1,0},{-4,0,-2,1}};
/*/

//Estilos
const TPenStyle pStyle[] = { psSolid, psDash, psDot, psDashDot, psDashDotDot };

//Valores para mantener cuando se minimiza la ventana de paintbox
TPenStyle estilo_pen;
TBrushStyle estilo_brush;
int grosor_pen;

unsigned long Estilos_TPenStyle(int estilo)
{
 switch (estilo) {
        case psDash: return 0x0000FFFF;
        case psDot: return 0x00FF00FF;
        case psDashDot: return 0xFFF00F00;
        case psDashDotDot: return 0xFF0F0F0F;
        default: return 0xFFFFFFFF;
 }
}

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PaintBox1Paint(TObject *Sender)
{

        PaintBox1->Canvas->Pen->Color = clBlack;
        PaintBox1->Canvas->Brush->Color = clWhite;
        PaintBox1->Canvas->Pen->Width = 1;
        PaintBox1->Canvas->Pen->Style = psSolid;
        PaintBox2->Canvas->Pen->Color = clBlack;
        PaintBox2->Canvas->Brush->Color = clWhite;
        PaintBox2->Canvas->Pen->Width = 1;
        PaintBox2->Canvas->Pen->Style = psSolid;
        PaintBox3->Canvas->Pen->Color = clBlack;
        PaintBox3->Canvas->Brush->Color = clWhite;
        PaintBox3->Canvas->Pen->Width = 1;
        PaintBox3->Canvas->Pen->Style = psSolid;
        PaintBox1->Canvas->Rectangle(0,0,PaintBox1->Width,PaintBox1->Height);
        PaintBox2->Canvas->Rectangle(0,0,PaintBox2->Width,PaintBox1->Height);
        PaintBox3->Canvas->Rectangle(0,0,PaintBox3->Width,PaintBox1->Height);
        PaintBox1->Canvas->Pen->Width = grosor_pen;
        PaintBox1->Canvas->Pen->Style = estilo_pen;
        PaintBox1->Canvas->Brush->Style = estilo_brush;
        PaintBox2->Canvas->Pen->Width = grosor_pen;
        PaintBox2->Canvas->Pen->Style = estilo_pen;
        PaintBox2->Canvas->Brush->Style = estilo_brush;
        PaintBox3->Canvas->Pen->Width = grosor_pen;
        PaintBox3->Canvas->Pen->Style = estilo_pen;
        PaintBox3->Canvas->Brush->Style = estilo_brush;
}
//-----Linea ----------------------------------------------------------------
void linea(int ini_x, int ini_y, int fin_x, int fin_y)
{
        //linea normal por Builder
        Form1->PaintBox1->Canvas->MoveTo(ini_x,ini_y);
        Form1->PaintBox1->Canvas->LineTo(fin_x,fin_y);
}
//-----Bresenham ------------------------------------------------------------
void bresenham(int ini_x, int ini_y, int fin_x, int fin_y, int PB)
{
    int x,y,incx,incy,A,B,p,sim;
    TColor color = Form1->PaintBox1->Canvas->Pen->Color;
    int grosor = Form1->PaintBox1->Canvas->Pen->Width;
    unsigned long estilo = Estilos_TPenStyle(Form1->PaintBox1->Canvas->Pen->Style);

    incx=abs(fin_x-ini_x);
    incy=abs(fin_y-ini_y);

    //horizontal > Vertical
    if (incx > incy) {
        //cambio de variable para dibujar el octante contrario
        if (ini_x>fin_x){
                float aux;
                aux=ini_x;
                ini_x=fin_x;
                fin_x=aux;
                aux=ini_y;
                ini_y=fin_y;
                fin_y=aux;
        }

        A=2*incy;
        B=2*incy-2*incx;
        p=2*incy-incx;

        //simetrías
        if (ini_y<fin_y) sim=1; else sim=-1;
        //8º,1º,4º,5º octantes
        x=ini_x;y=ini_y;
        while(x<fin_x){

                if(p>0){
                        //aplicamos estilo y grosor
                        if (estilo & 1){
                                if(grosor > 1){
                                        for (int i=-grosor/2; i<((grosor/2)+1); i++) {
                                                switch (PB){
                                                   case 1: Form1->PaintBox1->Canvas->Pixels[x+1][y+sim+i]= color;
                                                           break;
                                                   case 2: Form1->PaintBox2->Canvas->Pixels[x+1][y+sim+i]= color;
                                                           break;
                                                   case 3: Form1->PaintBox3->Canvas->Pixels[x+1][y+sim+i]= color;
                                                           break;
                                                }
                                        }
                                } else {
                                        switch (PB){
                                           case 1: Form1->PaintBox1->Canvas->Pixels[x+1][y+sim]=color;
                                                   break;
                                           case 2: Form1->PaintBox2->Canvas->Pixels[x+1][y+sim]=color;
                                                   break;
                                           case 3: Form1->PaintBox3->Canvas->Pixels[x+1][y+sim]=color;
                                                   break;
                                        }
                                }
                        }
                        y+=sim;
                        p+=B;
                } else {
                        //aplicamos estilo y grosor
                        if (estilo & 1){
                                if(grosor > 1){
                                        for (int i=-grosor/2; i<((grosor/2)+1); i++) {
                                                switch (PB){
                                                   case 1: Form1->PaintBox1->Canvas->Pixels[x+1][y+i]= color;
                                                           break;
                                                   case 2: Form1->PaintBox2->Canvas->Pixels[x+1][y+i]= color;
                                                           break;
                                                   case 3: Form1->PaintBox3->Canvas->Pixels[x+1][y+i]= color;
                                                           break;
                                                }
                                        }
                                } else {
                                        switch (PB){
                                           case 1: Form1->PaintBox1->Canvas->Pixels[x+1][y]=color;
                                                   break;
                                           case 2: Form1->PaintBox2->Canvas->Pixels[x+1][y]=color;
                                                   break;
                                           case 3: Form1->PaintBox3->Canvas->Pixels[x+1][y]=color;
                                                   break;
                                        }
                                }
                        }
                        p+=A;
                }
                estilo = _lrotr(estilo,1); //rotacion a la dcha
                x++;
        }
    } else {

        if (ini_y>fin_y){
                float aux;
                aux=ini_x;
                ini_x=fin_x;
                fin_x=aux;
                aux=ini_y;
                ini_y=fin_y;
                fin_y=aux;
        }

        A=2*incx;
        B=2*incx-2*incy;
        p=2*incx-incy;

        //simetrías
        if (ini_x<fin_x) sim=1; else sim=-1;
        //2º,3º,6º,7º octantes
        x=ini_x;y=ini_y;
        while(y<fin_y){

                if(p>0){
                        //aplicamos estilo y grosor
                        if (estilo & 1){
                                if(grosor > 1){
                                        for (int i=-grosor/2; i<((grosor/2)+1); i++) {
                                                switch (PB){
                                                   case 1: Form1->PaintBox1->Canvas->Pixels[x+sim+i][y+1]= color;
                                                           break;
                                                   case 2: Form1->PaintBox2->Canvas->Pixels[x+sim+i][y+1]= color;
                                                           break;
                                                   case 3: Form1->PaintBox3->Canvas->Pixels[x+sim+i][y+1]= color;
                                                           break;
                                                }
                                        }
                                } else {
                                        switch (PB){
                                           case 1: Form1->PaintBox1->Canvas->Pixels[x+sim][y+1]=color;
                                                   break;
                                           case 2: Form1->PaintBox2->Canvas->Pixels[x+sim][y+1]=color;
                                                   break;
                                           case 3: Form1->PaintBox3->Canvas->Pixels[x+sim][y+1]=color;
                                                   break;
                                        }
                                }
                        }
                        x+=sim;
                        p+=B;
                } else {
                        //aplicamos estilo y grosor
                        if (estilo & 1){
                                if(grosor > 1){
                                        for (int i=-grosor/2; i<((grosor/2)+1); i++) {
                                                switch (PB){
                                                   case 1: Form1->PaintBox1->Canvas->Pixels[x+i][y+1]= color;
                                                           break;
                                                   case 2: Form1->PaintBox2->Canvas->Pixels[x+i][y+1]= color;
                                                           break;
                                                   case 3: Form1->PaintBox3->Canvas->Pixels[x+i][y+1]= color;
                                                           break;
                                                }
                                        }
                                } else {
                                        switch (PB){
                                           case 1: Form1->PaintBox1->Canvas->Pixels[x][y+1]=color;
                                                   break;
                                           case 2: Form1->PaintBox2->Canvas->Pixels[x][y+1]=color;
                                                   break;
                                           case 3: Form1->PaintBox3->Canvas->Pixels[x][y+1]=color;
                                                   break;
                                        }
                                }
                        }
                        p+=A;
                }
                estilo = _lrotr(estilo,1); //rotacion a la dcha
                y++;
        }
    }
}
//-----Piramide--------------------------------------------------------------
void CreaPiramide(double pol[][4], int arista[][2], int Cx, int Cy, int Cz)
{
        // Pico de la piramide y eje central
        pol[NumVert][0] = Cx;
        pol[NumVert][1] = Cy;
        pol[NumVert][2] = Cz+100;
        pol[NumVert][3] = h;
        NumVert++;

        pol[NumVert][0] = Cx;
        pol[NumVert][1] = Cy;
        pol[NumVert][2] = Cz-50;
        pol[NumVert][3] = h;
        NumVert++;

        pol[NumVert][0] = Cx;
        pol[NumVert][1] = Cy;
        pol[NumVert][2] = Cz+150;
        pol[NumVert][3] = h;
        NumVert++;

        //Creamos las aristas
        for (int i=0; i<NumVert-4; i++){
                arista[NumArista][0] = i;
                arista[NumArista][1] = i+1;
                NumArista++;
        }
        arista[NumArista][0] = NumVert-4;
        arista[NumArista][1] = 0;
        NumArista++;
        for (int i=0; i<NumVert-3; i++){
                arista[NumArista][0] = i;
                arista[NumArista][1] = NumVert-3;
                NumArista++;
        }
        arista[NumArista][0] = NumVert-2;
        arista[NumArista][1] = NumVert-1;
        NumArista++;
}
//-----Prisma----------------------------------------------------------------
void CreaPrisma(double pol[][4], int arista[][2], int Cx, int Cy, int Cz)
{
        //Duplicamos verticas, cara trasera
        for (int i=0; i<NumVert; i++){
                pol[NumVert+i][0] = pol[i][0];
                pol[NumVert+i][1] = pol[i][1];
                pol[NumVert+i][2] = pol[i][2]+100;
                pol[NumVert+i][3] = pol[i][3];
        }
        NumVert*=2;
        //Creamos las aristas
        for (int i=0; i<NumVert/2-1; i++){
                arista[NumArista][0] = i;
                arista[NumArista][1] = i+1;
                NumArista++;
        }
        arista[NumArista][0] = NumVert/2-1;
        arista[NumArista][1] = 0;
        NumArista++;
        for (int i=NumVert/2; i<NumVert-1; i++){
                arista[NumArista][0] = i;
                arista[NumArista][1] = i+1;
                NumArista++;
        }
        arista[NumArista][0] = NumVert-1;
        arista[NumArista][1] = NumVert/2;
        NumArista++;
        for (int i=0; i<NumVert/2-1; i++){
                arista[NumArista][0] = i;
                arista[NumArista][1] = i+NumVert/2;
                NumArista++;
        }
        arista[NumArista][0] = NumVert/2-1;
        arista[NumArista][1] = NumVert-1;
        NumArista++;

        //eje central
        pol[NumVert][0] = Cx;
        pol[NumVert][1] = Cy;
        pol[NumVert][2] = Cz-50;
        pol[NumVert][3] = h;
        NumVert++;

        pol[NumVert][0] = Cx;
        pol[NumVert][1] = Cy;
        pol[NumVert][2] = Cz+150;
        pol[NumVert][3] = h;
        NumVert++;
        arista[NumArista][0] = NumVert-2;
        arista[NumArista][1] = NumVert-1;
        NumArista++;
}
//---------------------------------------------------------------------------
void Pinta_FIG(double pol[][4], int arista[][2], int NumVert, int NumAr)
{
        for (int i=0; i<NumAr-1; i++){
                //Plano XY
                bresenham(pol[arista[i][0]][0],pol[arista[i][0]][1],
                          pol[arista[i][1]][0],pol[arista[i][1]][1],1);
                //Plano ZY
                bresenham(pol[arista[i][0]][2],pol[arista[i][0]][1],
                          pol[arista[i][1]][2],pol[arista[i][1]][1],2);
                //Plano XZ
                bresenham(pol[arista[i][0]][0],pol[arista[i][0]][2],
                          pol[arista[i][1]][0],pol[arista[i][1]][2],3);
        }

        //eje central de rojo

        TColor color = Form1->PaintBox1->Canvas->Pen->Color;
        Form1->PaintBox1->Canvas->Pen->Color = clRed;
        Form1->PaintBox2->Canvas->Pen->Color = clRed;
        Form1->PaintBox3->Canvas->Pen->Color = clRed;

        //Plano XY
        bresenham(pol[arista[NumAr-1][0]][0],pol[arista[NumAr-1][0]][1],
                  pol[arista[NumAr-1][1]][0],pol[arista[NumAr-1][1]][1],1);
        //Plano ZY
        bresenham(pol[arista[NumAr-1][0]][2],pol[arista[NumAr-1][0]][1],
                  pol[arista[NumAr-1][1]][2],pol[arista[NumAr-1][1]][1],2);
        //Plano XZ
        bresenham(pol[arista[NumAr-1][0]][0],pol[arista[NumAr-1][0]][2],
                  pol[arista[NumAr-1][1]][0],pol[arista[NumAr-1][1]][2],3);

        Form1->PaintBox1->Canvas->Pen->Color = color;
        Form1->PaintBox2->Canvas->Pen->Color = color;
        Form1->PaintBox3->Canvas->Pen->Color = color;


}
//---------------------------------------------------------------------------
void PintaPol(double pol[][4], int NumVert)
{
        int i;
        Form1->PaintBox1->Canvas->Pen->Color = Form1->CColorGrid1->ForegroundColor;
        //Plano XY
        for (i=1; i<NumVert; i++){
                bresenham(pol[i-1][0],pol[i-1][1],pol[i][0],pol[i][1],1);
        }
        bresenham(pol[i-1][0],pol[i-1][1],pol[0][0],pol[0][1],1);
        //Plano ZY
        for (i=1; i<NumVert; i++){
                bresenham(pol[i-1][2],pol[i-1][1],pol[i][2],pol[i][1],2);
        }
        bresenham(pol[i-1][2],pol[i-1][1],pol[0][2],pol[0][1],2);
        //Plano XZ
        for (i=1; i<NumVert; i++){
                bresenham(pol[i-1][0],pol[i-1][2],pol[i][0],pol[i][2],3);
        }
        bresenham(pol[i-1][0],pol[i-1][2],pol[0][0],pol[0][2],3);
}
//---------------------------------------------------------------------------
void Mult (double P[4], double M[4][4])
{
        double aux=0;
        double temp[4];
        for (int i=0; i<4; i++){
                for (int j=0; j<4; j++){
                        aux+=P[j]*M[j][i];
                }
                temp[i]=aux;
                aux=0;
        }
        for (int i=0; i<4; i++) P[i]=temp[i];
}
//-----Trasladar-------------------------------------------------------------
void Trasladar (double pol[][4], int NumVert, double tx, double ty, double tz)
{
        double T[4][4]={{1,0,0,0},{0,1,0,0},{0,0,1,0},{tx,ty,tz,1}};
        for (int i=0; i<NumVert; i++) Mult(pol[i],T);
}
//-----Rotar X---------------------------------------------------------------
void RotarX (double pol[][4], int NumVert, double alfa)
{
        double R[4][4]={{1,0,0,0},
                        {0,cos(alfa),sin(alfa),0},
                        {0,-sin(alfa),cos(alfa),0},
                        {0,0,0,1}};
        for (int i=0; i<NumVert; i++) Mult(pol[i],R);
}
//-----Rotar Y---------------------------------------------------------------
void RotarY (double pol[][4], int NumVert, double alfa)
{
        double R[4][4]={{cos(alfa),0,-sin(alfa),0},
                        {0,1,0,0},
                        {sin(alfa),0,cos(alfa),0},
                        {0,0,0,1}};
        for (int i=0; i<NumVert; i++) Mult(pol[i],R);
}
//-----Rotar Z---------------------------------------------------------------
void RotarZ (double pol[][4], int NumVert, double alfa)
{
        double R[4][4]={{cos(alfa),sin(alfa),0,0},
                        {-sin(alfa),cos(alfa),0,0},
                        {0,0,1,0},
                        {0,0,0,1}};
        for (int i=0; i<NumVert; i++) Mult(pol[i],R);
}
//-----Escalar---------------------------------------------------------------
void Escalar (double pol[][4], int NumVert, double Sx, double Sy, double Sz)
{
        double S[4][4]={{Sx,0,0,0},{0,Sy,0,0},{0,0,Sz,0},{0,0,0,1}};
        for (int i=0; i<NumVert; i++) Mult(pol[i],S);
}
//-----Afilar----------------------------------------------------------------
void Afilar (double pol[][4], int NumVert, double a, double b)
{
   double A[4][4]={{1,0,0,0},{0,1,0,0},{-a,-b,1,0},{0,0,0,1}};
   for (int i=0; i<NumVert; i++) Mult(pol[i],A);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PaintBox1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        pintando=true;
        PaintBox1->Canvas->Pen->Mode=pmNotXor;
        PaintBox2->Canvas->Pen->Mode=pmNotXor;
        PaintBox3->Canvas->Pen->Mode=pmNotXor;
        if (Shift.Contains(ssLeft)){
                PaintBox1->Canvas->Pen->Color = CColorGrid1->ForegroundColor;
        } else {
                PaintBox1->Canvas->Pen->Color = CColorGrid1->BackgroundColor;
        }
        ini_x=fin_x=X;
        ini_y=fin_y=Y;
        switch (RadioGroup3->ItemIndex){
                case 0: //Crear Poligono
                        if (Button != mbRight){
                                if ((Sender == PaintBox1)||(Sender == PaintBox2)){
                                        pol[NumVert][0] = X;
                                        pol[NumVert][1] = Y;
                                        pol[NumVert][2] = X;
                                        pol[NumVert][3] = h;
                                        NumVert++;
                                }
                                if (Sender == PaintBox3){
                                        pol[NumVert][0] = X;
                                        pol[NumVert][1] = Y;
                                        pol[NumVert][2] = Y;
                                        pol[NumVert][3] = h;
                                        NumVert++;
                                }
                                if (NumVert>1){
                                     //XY
                                     bresenham(pol[NumVert-2][0],pol[NumVert-2][1],
                                               pol[NumVert-1][0],pol[NumVert-1][1],1);
                                     //ZY
                                     bresenham(pol[NumVert-2][2],pol[NumVert-2][1],
                                               pol[NumVert-1][2],pol[NumVert-1][1],2);
                                     //XZ
                                     bresenham(pol[NumVert-2][0],pol[NumVert-2][2],
                                               pol[NumVert-1][0],pol[NumVert-1][2],3);
                                }
                        } /*Depende si capturamos el boton dch o no
                        else {
                                pol[NumVert][0] = X;
                                pol[NumVert][1] = Y;
                                pol[NumVert][2] = h;
                                NumVert++;
                        }*/
                        break;
        }
        switch (RadioGroup1->ItemIndex){
                case 0: //Piramide
                case 1: //Prisma
                        double angulo = (2*pi)/NumLado;
                        r = sqrt((X-ini_x)*(X-ini_x)+(Y-ini_y)*(Y-ini_y));
                        int X0,Y0,X1,Y1;
                        for (int i=0; i<NumLado; i++){
                                X0 = ini_x + r*cos(i*angulo);
                                Y0 = ini_y + r*sin(i*angulo);
                                X1 = ini_x + r*cos((i+1)*angulo);
                                Y1 = ini_y + r*sin((i+1)*angulo);
                                if (Sender == PaintBox1){
                                        bresenham(X0,Y0,X1,Y1,1);
                                }
                                if (Sender == PaintBox2){
                                        bresenham(X0,Y0,X1,Y1,2);
                                }
                                if (Sender == PaintBox3){
                                        bresenham(X0,Y0,X1,Y1,3);
                                }


                        }
                        break;
        }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PaintBox1MouseMove(TObject *Sender,
      TShiftState Shift, int X, int Y)
{
 if (pintando){
        //modo de visualizacion del pincel
        PaintBox1->Canvas->Pen->Mode=pmNotXor;
        if (Shift.Contains(ssLeft)){
                PaintBox1->Canvas->Pen->Color = CColorGrid1->ForegroundColor;
        } else {
                PaintBox1->Canvas->Pen->Color = CColorGrid1->BackgroundColor;
        }
        TColor color = PaintBox1->Canvas->Pen->Color;
        switch (RadioGroup3->ItemIndex){
                case 0: //Crear Poligono

                        break;
                case 1: //Trasladar
                        PaintBox1->Canvas->Pen->Mode=pmCopy;
                        PaintBox2->Canvas->Pen->Mode=pmCopy;
                        PaintBox3->Canvas->Pen->Mode=pmCopy;
                        borrarClick(Sender);
                        PaintBox1->Canvas->Pen->Color = color;
                        if( Sender == PaintBox1)
                                Trasladar(pol,UltVert,X-fin_x,Y-fin_y,0);
                        if( Sender == PaintBox2)
                                Trasladar(pol,UltVert,0,Y-fin_y,X-fin_x);
                        if( Sender == PaintBox3)
                                Trasladar(pol,UltVert,X-fin_x,0,Y-fin_y);
                        if (!pintar_pol){
                                Pinta_FIG(pol,arista,UltVert,NumArista);
                        } else {
                                PintaPol(pol,UltVert);
                        }
                        break;
                case 2: //Rotar
                        PaintBox1->Canvas->Pen->Mode=pmCopy;
                        PaintBox2->Canvas->Pen->Mode=pmCopy;
                        PaintBox3->Canvas->Pen->Mode=pmCopy;
                        borrarClick(Sender);
                        PaintBox1->Canvas->Pen->Color = color;
                        if( Sender == PaintBox1){
                                Trasladar(pol,UltVert,-ini_x,-ini_y,0);
                                RotarZ(pol,UltVert,(Y-fin_y)*0.01);//factor veloc.giro
                                Trasladar(pol,UltVert,ini_x,ini_y,0);
                        }
                        if( Sender == PaintBox2){
                                Trasladar(pol,UltVert,0,-ini_y,-ini_x);
                                RotarX(pol,UltVert,(Y-fin_y)*0.01);//factor veloc.giro
                                Trasladar(pol,UltVert,0,ini_y,ini_x);
                        }
                        if( Sender == PaintBox3){
                                Trasladar(pol,UltVert,-ini_x,0,-ini_y);
                                RotarY(pol,UltVert,(Y-fin_y)*0.01);//factor veloc.giro
                                Trasladar(pol,UltVert,ini_x,0,ini_y);
                        }
                        if (!pintar_pol){
                                Pinta_FIG(pol,arista,UltVert,NumArista);
                        } else {
                                PintaPol(pol,UltVert);
                        }
                        break;
                case 3: //Escalar
                        PaintBox1->Canvas->Pen->Mode=pmCopy;
                        PaintBox2->Canvas->Pen->Mode=pmCopy;
                        PaintBox3->Canvas->Pen->Mode=pmCopy;
                        borrarClick(Sender);
                        PaintBox1->Canvas->Pen->Color = color;
                        if( Sender == PaintBox1){
                                Trasladar(pol,UltVert,-ini_x,-ini_y,0);
                                Escalar(pol,UltVert,1+(X-fin_x)*0.01,1+(Y-fin_y)*0.01,1);//factor veloc.escala
                                Trasladar(pol,UltVert,ini_x,ini_y,0);
                        }
                        if( Sender == PaintBox2){
                                Trasladar(pol,UltVert,0,-ini_y,-ini_x);
                                Escalar(pol,UltVert,1,1+(Y-fin_y)*0.01,1+(X-fin_x)*0.01);//factor veloc.escala
                                Trasladar(pol,UltVert,0,ini_y,ini_x);
                        }
                        if( Sender == PaintBox3){
                                Trasladar(pol,UltVert,-ini_x,0,-ini_y);
                                Escalar(pol,UltVert,1+(X-fin_x)*0.01,1,1+(Y-fin_y)*0.01);//factor veloc.escala
                                Trasladar(pol,UltVert,ini_x,0,ini_y);
                        }
                        if (!pintar_pol){
                                Pinta_FIG(pol,arista,UltVert,NumArista);
                        } else {
                                PintaPol(pol,UltVert);
                        }
                        break;
                case 4: //Afilar
                        PaintBox1->Canvas->Pen->Mode=pmCopy;
                        PaintBox2->Canvas->Pen->Mode=pmCopy;
                        PaintBox3->Canvas->Pen->Mode=pmCopy;
                        borrarClick(Sender);
                        PaintBox1->Canvas->Pen->Color = color;
                        if( Sender == PaintBox1){
                                Trasladar(pol,UltVert,-ini_x,-ini_y,0);
                                Afilar(pol,UltVert,(X-fin_x)*0.01,(Y-fin_y)*0.01);
                                Trasladar(pol,UltVert,ini_x,ini_y,0);
                        }
                        if( Sender == PaintBox2){
                                Trasladar(pol,UltVert,0,-ini_y,-ini_x);
                                Afilar(pol,UltVert,(Y-fin_y)*0.01,(X-fin_x)*0.01);
                                Trasladar(pol,UltVert,0,ini_y,ini_x);
                        }
                        if( Sender == PaintBox3){
                                Trasladar(pol,UltVert,-ini_x,0,-ini_y);
                                Afilar(pol,UltVert,(X-fin_x)*0.01,(Y-fin_y)*0.01);
                                Trasladar(pol,UltVert,ini_x,0,ini_y);
                        }
                        if (!pintar_pol){
                                Pinta_FIG(pol,arista,UltVert,NumArista);
                        } else {
                                PintaPol(pol,UltVert);
                        }
                        break;
        }
        double angulo = (2*pi)/NumLado;
        int X0,Y0,X1,Y1,Z1;
        switch (RadioGroup1->ItemIndex){
                case 0: //Piramide
                case 1: //Prisma
                        for (int i=0; i<NumLado; i++){
                                X0 = ini_x + r*cos(i*angulo);
                                Y0 = ini_y + r*sin(i*angulo);
                                X1 = ini_x + r*cos((i+1)*angulo);
                                Y1 = ini_y + r*sin((i+1)*angulo);
                                if (Sender == PaintBox1)
                                        bresenham(X0,Y0,X1,Y1,1);
                                if (Sender == PaintBox2)
                                        bresenham(X0,Y0,X1,Y1,2);
                                if (Sender == PaintBox3)
                                        bresenham(X0,Y0,X1,Y1,3);
                        }
                        r = sqrt((X-ini_x)*(X-ini_x)+(Y-ini_y)*(Y-ini_y));
                        for (int i=0; i<NumLado; i++){
                                X0 = ini_x + r*cos(i*angulo);
                                Y0 = ini_y + r*sin(i*angulo);
                                X1 = ini_x + r*cos((i+1)*angulo);
                                Y1 = ini_y + r*sin((i+1)*angulo);
                                if (Sender == PaintBox1)
                                        bresenham(X0,Y0,X1,Y1,1);
                                if (Sender == PaintBox2)
                                        bresenham(X0,Y0,X1,Y1,2);
                                if (Sender == PaintBox3)
                                        bresenham(X0,Y0,X1,Y1,3);
                        }
                        break;
                case 2: //Rotacion General
                        PaintBox1->Canvas->Pen->Mode=pmCopy;
                        PaintBox2->Canvas->Pen->Mode=pmCopy;
                        PaintBox3->Canvas->Pen->Mode=pmCopy;
                        borrarClick(Sender);
                        PaintBox1->Canvas->Pen->Color = color;

                        X1 = pol[UltVert-2][0];
                        Y1 = pol[UltVert-2][1];
                        Z1 = pol[UltVert-2][2];
                        Trasladar(pol,UltVert,-X1,-Y1,-Z1);

                        int b = pol[UltVert-1][1];
                        int c = pol[UltVert-1][2];
                        RotarX(pol,UltVert,(atan(double(b)/c)));
                        int a = pol[UltVert-1][0];
                        double d1 = sqrt((b*b)+(c*c));
                        RotarY(pol,UltVert,-(atan(double(a)/d1)));

                        RotarZ(pol,UltVert,(Y-fin_y)*0.01);

                        RotarY(pol,UltVert,(atan(double(a)/d1)));
                        RotarX(pol,UltVert,-(atan(double(b)/c)));
                        Trasladar(pol,UltVert,X1,Y1,Z1);

                        Pinta_FIG(pol,arista,UltVert,NumArista);
                        break;
        }
        //actualización del punto
        fin_x = X;
        fin_y = Y;
 }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PaintBox1MouseUp(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
 pintando=false;
 PaintBox1->Canvas->Pen->Mode=pmCopy;
 PaintBox2->Canvas->Pen->Mode=pmCopy;
 PaintBox3->Canvas->Pen->Mode=pmCopy;
 TColor color = PaintBox1->Canvas->Pen->Color;
 switch (RadioGroup3->ItemIndex){
        case 0: //Crear Poligono
                if (Button != mbRight){
                        if (NumVert>1){
                                //XY
                                bresenham(pol[NumVert-2][0],pol[NumVert-2][1],
                                          pol[NumVert-1][0],pol[NumVert-1][1],1);
                                //ZY
                                bresenham(pol[NumVert-2][2],pol[NumVert-2][1],
                                          pol[NumVert-1][2],pol[NumVert-1][1],2);
                                //XZ
                                bresenham(pol[NumVert-2][0],pol[NumVert-2][2],
                                          pol[NumVert-1][0],pol[NumVert-1][2],3);
                        } else {
                                Canvas->Rectangle(ini_x,ini_y,ini_x+5,ini_y+5);
                        }
                } else {
                        if (NumVert>2){
                                UltVert = NumVert;
                                NumVert = 0;
                                borrarClick(Sender);
                                PintaPol(pol,UltVert);
                        }
                }
                break;
 }
 switch (RadioGroup1->ItemIndex){
        case 0: //Piramide
        case 1: //Prisma
                double angulo = (2*pi)/NumLado;
                int X0,Y0;
                r = sqrt((X-ini_x)*(X-ini_x)+(Y-ini_y)*(Y-ini_y));
                NumVert = 0;
                for (int i=0; i<NumLado; i++){
                        X0 = ini_x + r*cos(i*angulo);
                        Y0 = ini_y + r*sin(i*angulo);
                        //if (Sender == PaintBox1){
                                pol[NumVert][0] = X0;
                                pol[NumVert][1] = Y0;
                                pol[NumVert][2] = 100;
                                pol[NumVert][3] = h;
                                NumVert++;
                        /*}
                        if (Sender == PaintBox2){
                                pol[NumVert][0] = X0;
                                pol[NumVert][1] = Y0;
                                pol[NumVert][2] = X0;
                                pol[NumVert][3] = h;
                                NumVert++;
                        }
                        if (Sender == PaintBox3){
                                pol[NumVert][0] = X0;
                                pol[NumVert][1] = Y0;
                                pol[NumVert][2] = Y0;
                                pol[NumVert][3] = h;
                                NumVert++;
                        }*/

                }
                if (RadioGroup1->ItemIndex == 0){
                        CreaPiramide(pol,arista,ini_x,ini_y,100);
                } else {
                        CreaPrisma(pol,arista,ini_x,ini_y,100);
                }
                borrarClick(Sender);
                PaintBox1->Canvas->Pen->Color = color;
                Pinta_FIG(pol,arista,UltVert,NumArista);
                UltVert = NumVert;
                NumVert = 0;
                break;
 }
}
//-----Cambio de Color-------------------------------------------------------

void __fastcall TForm1::CColorGrid1Change(TObject *Sender)
{
       InfoClfg->Color = CColorGrid1->ForegroundColor;
       InfoClbg->Color = CColorGrid1->BackgroundColor;
}
//-----Estilos---------------------------------------------------------------

void __fastcall TForm1::ComboBox1Change(TObject *Sender)
{
        PaintBox1->Canvas->Pen->Style = pStyle[ComboBox1->ItemIndex];
        estilo_pen = PaintBox1->Canvas->Pen->Style;
}
//-----Grosor----------------------------------------------------------------

void __fastcall TForm1::grosorChange(TObject *Sender)
{
        int n = grosor->Text.ToIntDef(1);
        if (n > 0) {
                PaintBox1->Canvas->Pen->Width = n;
                UpDown1->Position = n;
        } else {
                grosor->Text = "1";
                UpDown1->Position = 1;
        }
        grosor_pen = PaintBox1->Canvas->Pen->Width;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::UpDown1Click(TObject *Sender, TUDBtnType Button)
{
        grosor->Text = UpDown1->Position;
}
//-----Lados-----------------------------------------------------------------

void __fastcall TForm1::ladosChange(TObject *Sender)
{
        NumLado = lados->Text.ToIntDef(1);
        if (NumLado > 3) {
                UpDown2->Position = NumLado;
        } else {
                lados->Text = "3";
                UpDown2->Position = 3;
        }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::UpDown2Click(TObject *Sender, TUDBtnType Button)
{
        lados->Text = UpDown2->Position;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioGroup3Click(TObject *Sender)
{
        if (RadioGroup3->ItemIndex >= 0){
                RadioGroup1->ItemIndex = -1;
                if (RadioGroup3->ItemIndex >= 2){
                        PaintBox1->Cursor = crSizeAll;
                        PaintBox2->Cursor = crSizeAll;
                        PaintBox3->Cursor = crSizeAll;
                } else {
                        if (RadioGroup3->ItemIndex == 1){
                                PaintBox1->Cursor = crDrag;
                                PaintBox2->Cursor = crDrag;
                                PaintBox3->Cursor = crDrag;
                        } else {
                                pintar_pol = true;
                                PaintBox1->Cursor = crCross;
                                PaintBox2->Cursor = crCross;
                                PaintBox3->Cursor = crCross;
                        }
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioGroup1Click(TObject *Sender)
{
        if (RadioGroup1->ItemIndex >= 0){
                RadioGroup3->ItemIndex = -1;
                pintar_pol = false;
                if (RadioGroup1->ItemIndex == 2){
                        PaintBox1->Cursor = crSizeAll;
                        PaintBox2->Cursor = crSizeAll;
                        PaintBox3->Cursor = crSizeAll;
                } else {
                        NumArista = 0;
                        PaintBox1->Cursor = crCross;
                        PaintBox2->Cursor = crCross;
                        PaintBox3->Cursor = crCross;
                }
        }
}

//---------------------------------------------------------------------------

void __fastcall TForm1::borrarClick(TObject *Sender)
{
        PaintBox1Paint(Sender);
}

//---------------------------------------------------------------------------



