//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
#include <ctype.h>
#include "Funciones.h"
#include <stdio>
#include <io.h>
#include <stdlib>
#include <string>
#include <iostream>

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
using namespace std;

TMetodo *Metodo;
//---------------------------------------------------------------------------
__fastcall TMetodo::TMetodo(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TMetodo::btnCifrarClick(TObject *Sender)
{
  char* Men_preparado;
  bool sal;

  Men_preparado = Men_prep(Mensaje_entrada->Text.UpperCase().c_str());

  switch(Opciones->ItemIndex)
    {
        case 0: // Grupos de cinco
        {
            alfabeto_c(alfabetoc,1,0,27);
            cifrar(alfabetom,alfabetoc,Men_preparado,criptograma);
            Mensaje_Salida->Text=criptograma;
            break;
        }
        case 1: // Sustitución afín
        {
            alfabeto_c(alfabetoc,textDeci->Text.ToInt(),textDespla->Text.ToInt(),27);
            if(eleccion_entrada_datos->ItemIndex==1)
            {
                sal = encriptaarchivo(alfabetom,alfabetoc,Abre->FileName.c_str(),Guardar->FileName.c_str(),"",0);

            }
            else
            {
                cifrar(alfabetom,alfabetoc,Men_preparado,criptograma);
                Mensaje_Salida->Text=criptograma;
            }
            break;
        }
        case 2: // Vigenere
        {
            char* clavevig;
            clavevig = Veri_clave(textclavevige->Text.UpperCase().c_str());
            if(eleccion_entrada_datos->ItemIndex==1)
            {
                sal = encriptaarchivo(alfabetom,alfabetoc,Abre->FileName.c_str(),Guardar->FileName.c_str(),clavevig,1);
            }
            else
            {
                cifra_Vig(clavevig,Men_preparado,criptograma,27,1);
                Mensaje_Salida->Text=criptograma;
            }
            break;
        }
        case 3: // Beaufort
        {
            char* clavebeauf;
            clavebeauf = Veri_clave(textclavebeauf->Text.UpperCase().c_str());
            if(eleccion_entrada_datos->ItemIndex==1)
            {
                sal = encriptaarchivo(alfabetom,alfabetoc,Abre->FileName.c_str(),Guardar->FileName.c_str(),clavebeauf,3);
            }
            else
            {
                cifra_Beauf(clavebeauf,Men_preparado,criptograma,27,1);
                Mensaje_Salida->Text=criptograma;
            }
            break;
        }
        case 4: // Playfair
        {
            char* claveplay;
            claveplay = Veri_clave(textclaveplay->Text.UpperCase().c_str());
            if(eleccion_entrada_datos->ItemIndex==1)
            {
                sal = encriptaarchivo(alfabetom,alfabetoc,Abre->FileName.c_str(),Guardar->FileName.c_str(),claveplay,5);
            }
            else
            {

                cifra_play(claveplay,Men_preparado,1);
                Mensaje_Salida->Text=criptograma;

            }
            break;
        }
        case 5: //Transposición por grupos
        {
            char* clavegrupos;
            clavegrupos = Veri_clave(textclavegrupos->Text.UpperCase().c_str());
            if(eleccion_entrada_datos->ItemIndex==1)
            {
                sal = encriptaarchivo(alfabetom,alfabetoc,Abre->FileName.c_str(),Guardar->FileName.c_str(),clavegrupos,7);
            }
            else
            {

                transposicion_grupo(clavegrupos,Men_preparado,criptograma,false);
                Mensaje_Salida->Text=criptograma;
            }
            break;
        }
        case 6: // Transposición por series
        {
            if(eleccion_entrada_datos->ItemIndex==1)
            {
                sal = encriptaarchivo(alfabetom,alfabetoc,Abre->FileName.c_str(),Guardar->FileName.c_str()," ",9);
            }
            else
            {

                transposicion_series (Men_preparado,criptograma,0);
                Mensaje_Salida->Text=criptograma;
            }
            break;
        }
        case 7: // Transposición por filas
        {
            if(eleccion_entrada_datos->ItemIndex==1)
            {
                sal = encriptaarchivo(alfabetom,alfabetoc,Abre->FileName.c_str(),Guardar->FileName.c_str(),Num_filas->Text.c_str(),11);
            }
            else
            {

                transposicion_filas(Men_preparado,criptograma,Num_filas->Text.ToInt(),0);
                Mensaje_Salida->Text=criptograma;
            }
            break;
        }
        case 8: // Transposición por columnas
        {
            if(eleccion_entrada_datos->ItemIndex==1)
            {
                sal = encriptaarchivo(alfabetom,alfabetoc,Abre->FileName.c_str(),Guardar->FileName.c_str(),Num_col->Text.c_str(),13);
            }
            else
            {

            transposicion_columnas (Men_preparado,criptograma,Num_col->Text.ToInt(),0);
            Mensaje_Salida->Text=criptograma;
            }
            break;
        }

    }
        if(sal == true)
        Application->MessageBox("Finalizado","",0);
}
//---------------------------------------------------------------------------
void __fastcall TMetodo::btnSalirClick(TObject *Sender)
{
    Close();
}
//---------------------------------------------------------------------------
// Errores:
void __fastcall TMetodo::textDeciExit(TObject *Sender)
{
    if(textDeci->Text.ToInt()<=0){
        textDeci->Text="1";
        Application->MessageBox("LA DECIMACIÓN DEBE SER COMO MINIMO 1","Aviso de ERROR",0);
    }
    if(textDeci->Text.ToInt()>27){
        textDeci->Text="1";
        Application->MessageBox("LA DECIMACIÓN DEBE SER COMO MÁXIMO EL MODULO","Aviso de ERROR",0);
    }
    if(mcd(textDeci->Text.ToInt(),27)!=1){
        Application->MessageBox("DESPLAZAMIENTO Y MODULO DEBEN SER PRIMOS ENTRE SI","Aviso de ERROR",0);
        textDeci->Text="1";
    }
}
void __fastcall TMetodo::textDesplaExit(TObject *Sender)
{
    if(textDespla->Text.ToInt()<=0){
        textDespla->Text="0";
        Application->MessageBox("EL DESPLAZAMIENTO DEBE SER COMO MÍNIMO 0","Aviso de ERROR",0);
    }
    if(textDespla->Text.ToInt()>27){
        textDespla->Text="0";
        Application->MessageBox("EL DESPLAZAMIENTO DEBE SER COMO MÁXIMO EL MODULO","Aviso de ERROR",0);
    }
}
//---------------------------------------------------------------------------

void __fastcall TMetodo::OpcionesChange(TObject *Sender)
{
    SAfin -> Visible = false;
    Vigenere -> Visible = false;
    Beaufort -> Visible = false;
    Playfair -> Visible = false;
    Grupos -> Visible = false;
    Series -> Visible = false;
    Filas -> Visible = false;
    Columnas -> Visible = false;

    switch(Opciones -> ItemIndex)
    {
     // Case 0: Corresponde al caso de grupos de cinco.

        case 1: // Sustitución afín
        {
            SAfin -> Visible = true;
            break;
        }

        case 2: // Vigenère
        {
            Vigenere -> Visible = true;
            break;
        }
        case 3: // Beaufort
        {
            Beaufort -> Visible = true;
            break;
        }
        case 4: // Payfair
        {
            Playfair -> Visible = true;
            break;
        }
        case 5: // Transposición por grupos
        {
            Grupos -> Visible = true;
            break;
        }
        case 6: // Transposición por series
        {
            Series -> Visible = true;
            break;
        }
        case 7: // Transposición por filas
        {
            Filas -> Visible = true;
            break;
        }
        case 8: // Transposición por columnas
        {
            Columnas -> Visible = true;
            break;
        }
        default:
        {
            break;
        }
    }
}
//---------------------------------------------------------------------------



void __fastcall TMetodo::btnDescifrarClick(TObject *Sender){
  char* Men_preparado;
  char* clave;
  char* clavebeauf;
  char* claveplay;
  bool sal;
  Men_preparado = Men_prep(Mensaje_Salida->Text.UpperCase().c_str());
  clave = Veri_clave(textclavevige->Text.UpperCase().c_str());
  clavebeauf = Veri_clave(textclavebeauf->Text.UpperCase().c_str());
  claveplay = Veri_clave(textclaveplay->Text.UpperCase().c_str());



switch(Opciones->ItemIndex)
    {
        case 1: // Sustitución afín
        {
            alfabeto_c(alfabetoc,textDeci->Text.ToInt(),textDespla->Text.ToInt(),27);
            if(eleccion_entrada_datos->ItemIndex==1)
            {

            }
            else
            {
                cifrar(alfabetoc,alfabetom,Mensaje_Salida->Text.c_str(),criptograma);
                Mensaje_entrada->Text=criptograma;
            }
            break;
        }
        case 2: // Vigenere
        {
            if(eleccion_entrada_datos->ItemIndex==1)
            {
                sal = encriptaarchivo(alfabetom,alfabetoc,Abre->FileName.c_str(),Guardar->FileName.c_str(),clave,2);
            }
            else
            {
                cifra_Vig(clave,Men_preparado,criptograma,27,-1);
                Mensaje_entrada->Text=criptograma;   
            }
            break;
        }
        case 3: // Beaufort
        {
            if(eleccion_entrada_datos->ItemIndex==1)
            {
                sal = encriptaarchivo(alfabetom,alfabetoc,Abre->FileName.c_str(),Guardar->FileName.c_str(),clavebeauf,4);
            }
            else
            {
                cifra_Beauf(clavebeauf,Men_preparado,criptograma,27,1);
                Mensaje_entrada->Text=criptograma;
            }
            break;
        }
        case 4: // Playfair
        {
            if(eleccion_entrada_datos->ItemIndex==1)
            {
                sal = encriptaarchivo(alfabetom,alfabetoc,Abre->FileName.c_str(),Guardar->FileName.c_str(),claveplay,6);
            }
            else
            {
                cifra_play(claveplay,Men_preparado,2);
                Mensaje_entrada->Text=criptograma;
                break;
            }
            break;
        }


        case 5: //Transposición por grupos
        {
            if(eleccion_entrada_datos->ItemIndex==1)
            {
                sal = encriptaarchivo(alfabetom,alfabetoc,Abre->FileName.c_str(),Guardar->FileName.c_str(),textclavegrupos->Text.c_str(),8);
            }
            else
            {

                okk = transposicion_grupo(textclavegrupos->Text.c_str(),Men_preparado,criptograma,true);
                if(okk == true)
                    Mensaje_entrada->Text=criptograma;
            }
            break;
        }
        case 6: // Transposición por series
        {
            if(eleccion_entrada_datos->ItemIndex==1)
            {
                sal = encriptaarchivo(alfabetom,alfabetoc,Abre->FileName.c_str(),Guardar->FileName.c_str()," ",10);
            }
            else
            {

                transposicion_series (Men_preparado,criptograma,1);
                Mensaje_entrada->Text=criptograma;
            }
            break;
        }
        case 7: // Transposición por filas
        {
            if(eleccion_entrada_datos->ItemIndex==1)
            {
                sal = encriptaarchivo(alfabetom,alfabetoc,Abre->FileName.c_str(),Guardar->FileName.c_str(),Num_filas->Text.c_str(),12);
            }
            else
            {

                transposicion_filas(Men_preparado,criptograma,Num_filas->Text.ToInt(),1);
                Mensaje_entrada->Text=criptograma;
            }
            break;
        }
        case 8: // Transposición por columnas
        {
            if(eleccion_entrada_datos->ItemIndex==1)
            {
                sal = encriptaarchivo(alfabetom,alfabetoc,Abre->FileName.c_str(),Guardar->FileName.c_str(),Num_col->Text.c_str(),14);
            }
            else
            {
 
                transposicion_columnas (Men_preparado,criptograma,Num_col->Text.ToInt(),1);
                Mensaje_entrada->Text=criptograma;
            }
            break;
        }
    }
        if(sal == true)
        Application->MessageBox("Finalizado","",0);
}
//---------------------------------------------------------------------------



void __fastcall TMetodo::AbreficheroClick(TObject *Sender)
{
    Abre->Execute();
    Label11->Caption="ORIGEN:  " + Abre->FileName;
    Label11 -> Visible = true;
    Guardar->Execute();
    Label12->Caption="DESTINO: " + Guardar->FileName;
    Label12 -> Visible = true;
}
//---------------------------------------------------------------------------




void __fastcall TMetodo::eleccion_entrada_datosClick(TObject *Sender)
{
    if(eleccion_entrada_datos->ItemIndex==1)
    {
        GroupBox3->Visible=false;
        Fichero->Visible=true;
    }
    else
    {
        GroupBox3->Visible=true;
        Fichero->Visible=false;
    }
}
//---------------------------------------------------------------------------

