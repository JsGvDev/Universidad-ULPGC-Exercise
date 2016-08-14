//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include "math.h"
#include "stack.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "CGRID"
#pragma resource "*.dfm"
TForm1 *Form1;
int ini_x,fin_x,ini_y,fin_y;
float r=0;
bool pintando=false;

//Poligonos
int h=1;//homogenea

double pol[100][3];
int NumVert = 0;
int UltVert = 0;

//int NumPoligonos = 0;

/*double P[3] = {1,2,3};
double M[3][3] = {{1,0,1},{0,1,1},{1,1,0}};
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
        PaintBox1->Canvas->Rectangle(0,0,PaintBox1->Width,PaintBox1->Height);
        PaintBox1->Canvas->Pen->Width = grosor_pen;
        PaintBox1->Canvas->Pen->Style = estilo_pen;
        PaintBox1->Canvas->Brush->Style = estilo_brush;
}
//-----Linea ----------------------------------------------------------------
void linea(int ini_x, int ini_y, int fin_x, int fin_y)
{
        //linea normal por Builder
        Form1->PaintBox1->Canvas->MoveTo(ini_x,ini_y);
        Form1->PaintBox1->Canvas->LineTo(fin_x,fin_y);
}
//-----Bresenham ------------------------------------------------------------
void bresenham(int ini_x, int ini_y, int fin_x, int fin_y)
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
                                                Form1->PaintBox1->Canvas->Pixels[x+1][y+sim+i]= color;
                                        }
                                } else {
                                        Form1->PaintBox1->Canvas->Pixels[x+1][y+sim]=color;
                                }
                        }
                        y+=sim;
                        p+=B;
                } else {
                        //aplicamos estilo y grosor
                        if (estilo & 1){
                                if(grosor > 1){
                                        for (int i=-grosor/2; i<((grosor/2)+1); i++) {
                                                Form1->PaintBox1->Canvas->Pixels[x+1][y+i]= color;
                                        }
                                } else {
                                        Form1->PaintBox1->Canvas->Pixels[x+1][y]=color;
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
                                                Form1->PaintBox1->Canvas->Pixels[x+sim+i][y+1]= color;
                                        }
                                } else {
                                        Form1->PaintBox1->Canvas->Pixels[x+sim][y+1]=color;
                                }
                        }
                        x+=sim;
                        p+=B;
                } else {
                        //aplicamos estilo y grosor
                        if (estilo & 1){
                                if(grosor > 1){
                                        for (int i=-grosor/2; i<((grosor/2)+1); i++) {
                                                Form1->PaintBox1->Canvas->Pixels[x+i][y+1]= color;
                                        }
                                } else {
                                        Form1->PaintBox1->Canvas->Pixels[x][y+1]=color;
                                }
                        }
                        p+=A;
                }
                estilo = _lrotr(estilo,1); //rotacion a la dcha
                y++;
        }
    }
}

//-----Círculo del Punto Medio ----------------------------------------------
void circuloPM(int ini_x, int ini_y, float r)
{
    int x,y,incx,incy,A,B,p,sim;
    TColor color = Form1->PaintBox1->Canvas->Pen->Color;
    int grosor = Form1->PaintBox1->Canvas->Pen->Width;
    unsigned long estilo = Estilos_TPenStyle(Form1->PaintBox1->Canvas->Pen->Style);

    p = (5/4)-r;

    for (x=0,y=(int)r; x<=y; x++){
        //aplicamos estilo y grosor
        if (estilo & 1){
                if(grosor > 1){
                        for (int i=-grosor/2; i<((grosor/2)+1); i++) {
                                //2º,3º,6º,7º octantes
                                Form1->PaintBox1->Canvas->Pixels[ini_x+x][ini_y+y+i]=color;
                                Form1->PaintBox1->Canvas->Pixels[ini_x+x][ini_y-y+i]=color;
                                Form1->PaintBox1->Canvas->Pixels[ini_x-x][ini_y+y+i]=color;
                                Form1->PaintBox1->Canvas->Pixels[ini_x-x][ini_y-y+i]=color;
                                //8º,1º,4º,5º octantes
                                Form1->PaintBox1->Canvas->Pixels[ini_x+y+i][ini_y+x]=color;
                                Form1->PaintBox1->Canvas->Pixels[ini_x-y+i][ini_y+x]=color;
                                Form1->PaintBox1->Canvas->Pixels[ini_x+y+i][ini_y-x]=color;
                                Form1->PaintBox1->Canvas->Pixels[ini_x-y+i][ini_y-x]=color;
                        }
                } else {
                        //2º,3º,6º,7º octantes
                        Form1->PaintBox1->Canvas->Pixels[ini_x+x][ini_y+y]=color;
                        Form1->PaintBox1->Canvas->Pixels[ini_x+x][ini_y-y]=color;
                        Form1->PaintBox1->Canvas->Pixels[ini_x-x][ini_y+y]=color;
                        Form1->PaintBox1->Canvas->Pixels[ini_x-x][ini_y-y]=color;
                        //8º,1º,4º,5º octantes
                        Form1->PaintBox1->Canvas->Pixels[ini_x+y][ini_y+x]=color;
                        Form1->PaintBox1->Canvas->Pixels[ini_x-y][ini_y+x]=color;
                        Form1->PaintBox1->Canvas->Pixels[ini_x+y][ini_y-x]=color;
                        Form1->PaintBox1->Canvas->Pixels[ini_x-y][ini_y-x]=color;
                }
        }
        estilo = _lrotr(estilo,1); //rotacion a la dcha
        if (p < 0)
        {
                p+= 2*x + 3;
        } else {
                y--;
                p+= 2*x - 2*y + 5;
        }
    }
}
//-----Relleno por Inundacion------------------------------------------------
struct pixel{
     int x;
     int y;
};
void relleno_Inund(int ini_x, int ini_y, TColor color)
{
        TColor col_pint = Form1->PaintBox1->Canvas->Pen->Color;
        int max_ancho = Form1->PaintBox1->Width;
        int x,y;
        bool arr,abj;
        struct pixel px;
        std::stack<struct pixel> pila;
        px.x=ini_x;
        px.y=ini_y;
        pila.push(px);
        while (pila.size() > 0){
                //banderas para saber el estado de los px. arriba y abajo
                arr = false;
                abj = false;

                px = pila.top();
                x=px.x; y=px.y;
                pila.pop();
                //Nos situamos al inicio
                while((x>0)&&(Form1->PaintBox1->Canvas->Pixels[x][y]==color)) x--;
                x++;
                //hacemos el scan-line
                while((Form1->PaintBox1->Canvas->Pixels[x][y]==color)&&(x<=max_ancho)){
                        Form1->PaintBox1->Canvas->Pixels[x][y]=col_pint;
                        if (Form1->PaintBox1->Canvas->Pixels[x][y+1] == color){
                                if (!arr){
                                        px.x=x;
                                        px.y=y+1;
                                        pila.push(px);
                                }
                                arr = true;
                        } else  arr = false;
                        if (Form1->PaintBox1->Canvas->Pixels[x][y-1] == color){
                                if (!abj){
                                        px.x=x;
                                        px.y=y-1;
                                        pila.push(px);
                                }
                                abj = true;
                        } else  abj = false;
                        x++;
                }
        }
}
//---------------------------------------------------------------------------
void PintaPol(double pol[][3], int NumVert)
{
        int i;
        Form1->PaintBox1->Canvas->Pen->Color = Form1->CColorGrid1->ForegroundColor;
        for (i=1; i<NumVert; i++){
                bresenham(pol[i-1][0],pol[i-1][1],pol[i][0],pol[i][1]);
        }
        bresenham(pol[i-1][0],pol[i-1][1],pol[0][0],pol[0][1]);
}
//---------------------------------------------------------------------------
void Mult (double P[3], double M[3][3])
{
        double aux=0;
        double temp[3];
        for (int i=0; i<3; i++){
                for (int j=0; j<3; j++){
                        aux+=P[j]*M[j][i];
                }
                temp[i]=aux;
                aux=0;
        }
        for (int i=0; i<3; i++) P[i]=temp[i];
}
//-----Trasladar-------------------------------------------------------------
void Trasladar (double pol[][3], int NumVert, double tx, double ty)
{
        double T[3][3]={{1,0,0},{0,1,0},{tx,ty,1}};
        for (int i=0; i<NumVert; i++) Mult(pol[i],T);
}
//-----Rotar-----------------------------------------------------------------
void Rotar (double pol[][3], int NumVert, double alfa)
{
        double R[3][3]={{cos(alfa),sin(alfa),0},{-sin(alfa),cos(alfa),0},{0,0,1}};
        for (int i=0; i<NumVert; i++) Mult(pol[i],R);
}
//-----Escalar---------------------------------------------------------------
void Escalar (double pol[][3], int NumVert, double Sx, double Sy)
{
        double S[3][3]={{Sx,0,0},{0,Sy,0},{0,0,1}};
        for (int i=0; i<NumVert; i++) Mult(pol[i],S);
}
//-----Reflexion-------------------------------------------------------------
void Reflexion (double pol[][3], int NumVert, double atan_m, int x0, int y0)
{
        double F[3][3]={{1,0,0},{0,-1,0},{0,0,1}};
        Trasladar(pol,NumVert,-x0,-y0);
        Rotar(pol,NumVert,-atan_m);
        for (int i=0; i<NumVert; i++) Mult(pol[i],F);
        Rotar(pol,NumVert,atan_m);
        Trasladar(pol,NumVert,x0,y0);
}
//-----Afilar----------------------------------------------------------------
void Afilar (double pol[][3], int NumVert, double a, double b)
{
   double A[3][3]={{1,b,0},{a,1,0},{0,0,1}};
   for (int i=0; i<NumVert; i++) Mult(pol[i],A);
}
//-----Cyrus Beck------------------------------------------------------------
void CyrusBeck(int x0, int y0, int x1, int y1, int xl, int yl, int xr, int yr)
{

   //Valor F arbitrario a cada borde:
        TPoint Fizq(xl,yl);
        TPoint Fsup(xl,yl);
        TPoint Fdch(xr,yr);
        TPoint Finf(xr,yr);
        TPoint borde[4] = {Fizq,Fsup,Fdch,Finf};
   //Valor Normales a cada borde:
        TPoint Nizq(-1,0);
        TPoint Nsup(0,-1);
        TPoint Ndch(1,0);
        TPoint Ninf(0,1);
        TPoint Ni[4] = {Nizq,Nsup,Ndch,Ninf};

        int P1P0_x; int P1P0_y; double t, te=0, ts=1;
        for (int i=0; i<4; i++){
                //aplicamos formula t = -((Ni(P0-F))/(Ni(P1-P0)))
                int P0F_x = x0-borde[i].x;
                int P0F_y = y0-borde[i].y;
                double Numerador = (Ni[i].x*P0F_x)+(Ni[i].y*P0F_y);
                P1P0_x = x1-x0;
                P1P0_y = y1-y0;
                double Denominador = (Ni[i].x*P1P0_x)+(Ni[i].y*P1P0_y);
                if (Denominador == 0) Denominador = 0.001;

                t = -Numerador/Denominador;
                if ((Denominador < 0) && (t>te)){
                        te = t;
                }
                if ((Denominador > 0) && (t<ts)){
                        ts = t;
                }
        }
        if (te < ts){

            int Pe_x = x0 + te*P1P0_x;
            int Pe_y = y0 + te*P1P0_y;
            int Ps_x = x0 + ts*P1P0_x;
            int Ps_y = y0 + ts*P1P0_y;

            bresenham(Pe_x,Pe_y,Ps_x,Ps_y);
        }
}
//-----Recortar--------------------------------------------------------------
void Recortar (double pol[][3], int NumVert, int xl, int yl, int xr, int yr)
{
        switch(Form1->RadioGroup1->ItemIndex){
                case 0: //linea Builder
                        CyrusBeck(ini_x,ini_y,fin_x,fin_y, xl,yl,xr,yr);
                        break;
        }
        switch (Form1->RadioGroup2->ItemIndex){
                case 0: //Bresenham
                        CyrusBeck(ini_x,ini_y,fin_x,fin_y, xl,yl,xr,yr);
                        break;
        }
        if ((Form1->RadioGroup3->ItemIndex >=0) || (Form1->RadioGroup4->ItemIndex >=0)){
                int i;
                for (i=1; i<NumVert; i++){
                        CyrusBeck(pol[i-1][0],pol[i-1][1],pol[i][0],pol[i][1], xl,yl,xr,yr);
                }
                CyrusBeck(pol[i-1][0],pol[i-1][1],pol[0][0],pol[0][1], xl,yl,xr,yr);

        }
}
//---------------------------------------------------------------------------
int minimo(double pol[][3], int NumVert, int XY)
{
        int min;
        min=pol[0][XY];
        for(int i=1; i<NumVert; i++){
                if (pol[i][XY] < min){
                        min=pol[i][XY];
                }
        }
        return min;
}
//---------------------------------------------------------------------------
int maximo(double pol[][3], int NumVert, int XY)
{
        int max;
        max=pol[0][XY];
        for(int i=1; i<NumVert; i++){
                if (pol[i][XY] > max){
                        max=pol[i][XY];
                }
        }
        return max;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::PaintBox1MouseDown(TObject *Sender,
      TMouseButton Button, TShiftState Shift, int X, int Y)
{
        pintando=true;
        PaintBox1->Canvas->Pen->Mode=pmNotXor;
        if (Shift.Contains(ssLeft)){
                PaintBox1->Canvas->Pen->Color = CColorGrid1->ForegroundColor;
        } else {
                PaintBox1->Canvas->Pen->Color = CColorGrid1->BackgroundColor;
        }
        ini_x=fin_x=X;
        ini_y=fin_y=Y;
        switch (RadioGroup1->ItemIndex){
                case 0: //linea Builder
                        linea(ini_x,ini_y,fin_x,fin_y);
                        break;
                case 1: //Elipse Builder
                        PaintBox1->Canvas->Ellipse(ini_x,ini_y,fin_x,fin_y);
                        break;
                case 2: //Circulo
                        r = sqrt((X-ini_x)*(X-ini_x)+(Y-ini_y)*(Y-ini_y));
                        PaintBox1->Canvas->Ellipse(ini_x-r,ini_y-r,ini_x+r,ini_y+r);
                        break;
        }
        switch (RadioGroup2->ItemIndex){
                case 0: //Bresenham
                        bresenham(ini_x,ini_y,fin_x,fin_y);
                        break;
                case 1: //Circulo del Punto Medio
                        r = sqrt((X-ini_x)*(X-ini_x)+(Y-ini_y)*(Y-ini_y));
                        circuloPM(ini_x,ini_y,r);
                        break;
                case 2: //Relleno por inundacion

                        break;
        }
        switch (RadioGroup3->ItemIndex){
                case 0: //Crear Poligono
                        if (Button != mbRight){
                                pol[NumVert][0] = X;
                                pol[NumVert][1] = Y;
                                pol[NumVert][2] = h;
                                NumVert++;
                                if (NumVert>1){
                                     bresenham(pol[NumVert-2][0],pol[NumVert-2][1],
                                               pol[NumVert-1][0],pol[NumVert-1][1]);
                                }
                        } /*Depende si capturamos el boton dch o no
                        else {
                                pol[NumVert][0] = X;
                                pol[NumVert][1] = Y;
                                pol[NumVert][2] = h;
                                NumVert++;
                        }*/
                        break;
                case 1: //Trasladar

                        break;
                case 2: //Rotar

                        break;
                case 3: //Escalar

                        break;
        }
        switch (RadioGroup4->ItemIndex){
                case 0: //Reflexion
                        linea(ini_x,ini_y,fin_x,fin_y);
                        break;
                case 1: //Afilar

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
        switch (RadioGroup1->ItemIndex){
                case 0: //linea Builder
                        linea(ini_x,ini_y,fin_x,fin_y);
                        fin_x=X; fin_y=Y;
                        linea(ini_x,ini_y,fin_x,fin_y);
                        break;
                case 1: //Elipse Builder
                        PaintBox1->Canvas->Ellipse(ini_x,ini_y,fin_x,fin_y);
                        fin_x=X; fin_y=Y;
                        PaintBox1->Canvas->Ellipse(ini_x,ini_y,fin_x,fin_y);
                        break;
                case 2: //Circulo
                        PaintBox1->Canvas->Ellipse(ini_x-r, ini_y-r, ini_x+r, ini_y+r);
                        r = sqrt((X-ini_x)*(X-ini_x)+(Y-ini_y)*(Y-ini_y));
                        PaintBox1->Canvas->Ellipse(ini_x-r,ini_y-r,ini_x+r,ini_y+r);
                        break;
        }
        switch (RadioGroup2->ItemIndex){
                case 0: //Bresenham
                        bresenham(ini_x,ini_y,fin_x,fin_y);
                        fin_x=X; fin_y=Y;
                        bresenham(ini_x,ini_y,fin_x,fin_y);
                        break;
                case 1: //Circulo del Punto Medio
                        circuloPM(ini_x,ini_y,r);
                        r = sqrt((X-ini_x)*(X-ini_x)+(Y-ini_y)*(Y-ini_y));
                        circuloPM(ini_x,ini_y,r);
                        break;
                case 2: //Relleno por inundacion
                        
                        break;
        }
        switch (RadioGroup3->ItemIndex){
                case 0: //Crear Poligono
                        
                        break;
                case 1: //Trasladar
                        PaintBox1->Canvas->Pen->Mode=pmCopy;
                        borrarClick(Sender);
                        Trasladar(pol,UltVert,X-fin_x,Y-fin_y);
                        if (CheckBox2->Checked){
                                CheckBox2Click(Sender);
                        } else {
                                PintaPol(pol,UltVert);
                        }
                        break;
                case 2: //Rotar
                        PaintBox1->Canvas->Pen->Mode=pmCopy;
                        borrarClick(Sender);
                        Trasladar(pol,UltVert,-ini_x,-ini_y);
                        Rotar(pol,UltVert,(Y-fin_y)*0.01);//factor veloc.giro
                        Trasladar(pol,UltVert,ini_x,ini_y);
                        if (CheckBox2->Checked){
                                CheckBox2Click(Sender);
                        } else {
                                PintaPol(pol,UltVert);
                        }
                        break;
                case 3: //Escalar
                        PaintBox1->Canvas->Pen->Mode=pmCopy;
                        borrarClick(Sender);
                        Trasladar(pol,UltVert,-ini_x,-ini_y);
                        Escalar(pol,UltVert,1+(X-fin_x)*0.01,1+(Y-fin_y)*0.01);//factor veloc.escala
                        Trasladar(pol,UltVert,ini_x,ini_y);
                        if (CheckBox2->Checked){
                                CheckBox2Click(Sender);
                        } else {
                                PintaPol(pol,UltVert);
                        }
                        break;
        }
        switch (RadioGroup4->ItemIndex){
                case 0: //Reflexion
                        linea(ini_x,ini_y,fin_x,fin_y);
                        fin_x=X; fin_y=Y;
                        linea(ini_x,ini_y,fin_x,fin_y);
                        break;
                case 1: //Afilar
                        PaintBox1->Canvas->Pen->Mode=pmCopy;
                        borrarClick(Sender);
                        Trasladar(pol,UltVert,-ini_x,-ini_y);
                        Afilar(pol,UltVert,(X-fin_x)*0.01,(Y-fin_y)*0.01);
                        Trasladar(pol,UltVert,ini_x,ini_y);
                        if (CheckBox2->Checked){
                                CheckBox2Click(Sender);
                        } else {
                                PintaPol(pol,UltVert);
                        }
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

 switch(RadioGroup1->ItemIndex){
        case 0: //linea Builder
                fin_x=X;fin_y=Y;
                if (CheckBox2->Checked){
                        CheckBox2Click(Sender);
                } else {
                        linea(ini_x,ini_y,fin_x,fin_y);
                }

                break;
        case 1: //Elipse Builder
                fin_x=X;fin_y=Y;
                PaintBox1->Canvas->Ellipse(ini_x,ini_y,fin_x,fin_y);
                break;
        case 2:  //Circulo
                 r = sqrt((X-ini_x)*(X-ini_x)+(Y-ini_y)*(Y-ini_y));
                 PaintBox1->Canvas->Ellipse(ini_x-r,ini_y-r,ini_x+r,ini_y+r);
                 break;
 }
 switch (RadioGroup2->ItemIndex){
        case 0: //Bresenham
                fin_x=X;fin_y=Y;
                if (CheckBox2->Checked){
                        CheckBox2Click(Sender);
                } else {
                        bresenham(ini_x,ini_y,fin_x,fin_y);
                }
                break;
        case 1: //Circulo del Punto Medio
                r = sqrt((X-ini_x)*(X-ini_x)+(Y-ini_y)*(Y-ini_y));
                circuloPM(ini_x,ini_y,r);
                break;
        case 2: //Relleno por inundacion (por pmCopy, con pmNotXor mezcla colores)
                TColor col_fondo = PaintBox1->Canvas->Pixels[X][Y];
                if (col_fondo != PaintBox1->Canvas->Pen->Color){
                        relleno_Inund(X, Y, col_fondo);
                }
                break;
 }
 switch (RadioGroup3->ItemIndex){
        case 0: //Crear Poligono
                if (Button != mbRight){
                        if (NumVert>1){
                                bresenham(pol[NumVert-2][0],pol[NumVert-2][1],
                                          pol[NumVert-1][0],pol[NumVert-1][1]);
                        } else {
                                Canvas->Rectangle(ini_x,ini_y,ini_x+5,ini_y+5);
                        }
                } else {
                        if (NumVert>2){
                                UltVert = NumVert;
                                NumVert = 0;
                                if (CheckBox2->Checked){
                                        CheckBox2Click(Sender);
                                } else {
                                        borrarClick(Sender);
                                        PintaPol(pol,UltVert);
                                }
                                //NumPoligonos++;
                        }
                }
                break;
        case 1: //Trasladar
        
                break;
        case 2: //Rotar

                break;
        case 3: //Escalar

                break;
 }
 switch (RadioGroup4->ItemIndex){
        case 0: //Reflexion
                if ((fin_x-ini_x) != 0){
                        r = atan(double(fin_y-ini_y)/(fin_x-ini_x));
                }
                Reflexion(pol,UltVert,r,ini_x,ini_y);
                if (CheckBox2->Checked){
                        CheckBox2Click(Sender);
                } else {
                        borrarClick(Sender);
                        PintaPol(pol,UltVert);
                }
                break;
        case 1: //Afilar

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
//-----Solido----------------------------------------------------------------

void __fastcall TForm1::CheckBox1Click(TObject *Sender)
{
        if (CheckBox1->Checked){
                PaintBox1->Canvas->Brush->Style = bsSolid;
        } else {
                PaintBox1->Canvas->Brush->Style = bsClear;
        }
        estilo_brush = PaintBox1->Canvas->Brush->Style;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioGroup1Click(TObject *Sender)
{
        if (RadioGroup1->ItemIndex >= 0){
                RadioGroup2->ItemIndex = -1;
                RadioGroup3->ItemIndex = -1;
                RadioGroup4->ItemIndex = -1;
                PaintBox1->Cursor = crCross;
                //NumPoligonos = 0;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioGroup2Click(TObject *Sender)
{
        if (RadioGroup2->ItemIndex >= 0){
                RadioGroup1->ItemIndex = -1;
                RadioGroup3->ItemIndex = -1;
                RadioGroup4->ItemIndex = -1;
                PaintBox1->Cursor = crCross;
                //NumPoligonos = 0;
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioGroup3Click(TObject *Sender)
{
        if (RadioGroup3->ItemIndex >= 0){
                RadioGroup1->ItemIndex = -1;
                RadioGroup2->ItemIndex = -1;
                RadioGroup4->ItemIndex = -1;
                if (RadioGroup3->ItemIndex >= 2){
                        PaintBox1->Cursor = crSizeAll;
                } else {
                        if (RadioGroup3->ItemIndex == 1){
                                PaintBox1->Cursor = crDrag;
                        } else  PaintBox1->Cursor = crCross;
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::RadioGroup4Click(TObject *Sender)
{
        if (RadioGroup4->ItemIndex >= 0){
                RadioGroup1->ItemIndex = -1;
                RadioGroup2->ItemIndex = -1;
                RadioGroup3->ItemIndex = -1;
                if (RadioGroup4->ItemIndex >= 1){
                        PaintBox1->Cursor = crSizeAll;
                } else {
                        PaintBox1->Cursor = crCross;
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::CheckBox2Click(TObject *Sender)
{
        if (CheckBox2->Checked){
                int div_pbx = PaintBox1->Width/4;
                int div_pby = PaintBox1->Height/4;
                borrarClick(Sender);
                PaintBox1->Canvas->Pen->Color = clRed;
                PaintBox1->Canvas->Brush->Color = clWhite;
                PaintBox1->Canvas->Pen->Width = 5;
                PaintBox1->Canvas->Pen->Style = psSolid;
                PaintBox1->Canvas->Rectangle(div_pbx,div_pby,div_pbx*3,div_pby*3);
                PaintBox1->Canvas->Pen->Width = grosor_pen;
                PaintBox1->Canvas->Pen->Style = estilo_pen;
                PaintBox1->Canvas->Brush->Style = estilo_brush;
                PaintBox1->Canvas->Pen->Color = CColorGrid1->ForegroundColor;
                Recortar(pol,UltVert,div_pbx,div_pby,div_pbx*3,div_pby*3);
        } else {
                borrarClick(Sender);
                switch(Form1->RadioGroup1->ItemIndex){
                        case 0: //linea Builder
                                linea(ini_x,ini_y,fin_x,fin_y);
                        break;
                }
                switch (Form1->RadioGroup2->ItemIndex){
                        case 0: //Bresenham
                                bresenham(ini_x,ini_y,fin_x,fin_y);
                                break;
                }
                if ((Form1->RadioGroup3->ItemIndex >=0) || (Form1->RadioGroup4->ItemIndex >=0)){
                        PintaPol(pol,UltVert);
                }
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::borrarClick(TObject *Sender)
{
        PaintBox1Paint(Sender);
}

//---------------------------------------------------------------------------

