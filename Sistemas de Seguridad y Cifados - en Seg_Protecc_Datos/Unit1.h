//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>


//---------------------------------------------------------------------------
class TMetodo : public TForm
{
__published:	// IDE-managed Components
        TGroupBox *GroupBox1;
        TRadioGroup *eleccion_entrada_datos;
        TGroupBox *GroupBox2;
        TGroupBox *GroupBox3;
        TMemo *Mensaje_Salida;
        TLabel *Label1;
        TLabel *Label2;
        TButton *btnCifrar;
        TButton *btnDescifrar;
        TButton *btnSalir;
        TComboBox *Opciones;
        TGroupBox *SAfin;
        TLabel *Decimacion;
        TLabel *Desplazamiento;
        TLabel *Modulo;
        TEdit *textDeci;
        TEdit *textDespla;
        TEdit *textMod;
        TGroupBox *Vigenere;
        TLabel *Label3;
        TEdit *textclavevige;
        TGroupBox *Beaufort;
        TLabel *Label4;
        TEdit *textclavebeauf;
        TGroupBox *Playfair;
        TLabel *Label5;
        TEdit *textclaveplay;
        TGroupBox *Grupos;
        TLabel *Label6;
        TEdit *textclavegrupos;
        TGroupBox *Series;
        TLabel *Label7;
        TLabel *Label8;
        TGroupBox *Filas;
        TLabel *Label9;
        TEdit *Num_filas;
        TGroupBox *Columnas;
        TLabel *Label10;
        TEdit *Num_col;
        TGroupBox *Fichero;
        TButton *Abrefichero;
        TLabel *Label11;
        TOpenDialog *Abre;
        TSaveDialog *Guardar;
        TLabel *Label12;
        TMemo *Mensaje_entrada;
        void __fastcall btnCifrarClick(TObject *Sender);
        void __fastcall btnSalirClick(TObject *Sender);
        void __fastcall OpcionesChange(TObject *Sender);
        void __fastcall textDeciExit(TObject *Sender);
        void __fastcall textDesplaExit(TObject *Sender);
        void __fastcall btnDescifrarClick(TObject *Sender);
        void __fastcall AbreficheroClick(TObject *Sender);
        void __fastcall eleccion_entrada_datosClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TMetodo(TComponent* Owner);
};
//---------------------------------------------------------------------------
extern PACKAGE TMetodo *Metodo;
//---------------------------------------------------------------------------
#endif
